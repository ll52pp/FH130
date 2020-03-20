#include <vxworks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pciConfigLib.h>
#include <cacheLib.h>
#include <taskLib.h>
#include <tickLib.h>
#include <logLib.h>
#include <intLib.h>
#include "hba.h"
#include "list.h"
#include "hw.h"

HBA_DEV_CB HbaDevCB[MAX_DEVICE_NUM] = {0};
int g_prtDrv = 0;
int g_bRebootHookAdded = 0;

/*-------------------- �豸����ӿ� --------------------*/
void hbaDrvShutDown(void)
{
	int i;
	for (i=0; i<MAX_DEVICE_NUM; i++)
	{
		if (HbaDevCB[i].status != HBA_DEV_STATUS_NONE)
		{
			hbaDevDestroy(&HbaDevCB[i]);
		}
	}
}


/* ��ʼ���� */
HBA_DEV_CB *hbaDevCreate(UINT32 DeviceId)
{
    int BusNo = 0;    /* bus number */
    int DeviceNo = 0; /* device number */
    int FuncNo = 0;   /* function number */
    INT32 membaseCsr = 0;
    UINT8 irq;
    HBA_DEV_CB *hbaDevNode;
    
    ASSERT(DeviceId < MAX_DEVICE_NUM);
	if(DeviceId >= MAX_DEVICE_NUM)
	{
		return NULL;
	}

    if (HbaDevCB[DeviceId].status != HBA_DEV_STATUS_NONE)
    {
        return NULL;
    }
    if (pciFindDevice(HBA_VENDOR_ID, HBA_DEVICE_ID, DeviceId, &BusNo, &DeviceNo, &FuncNo) != OK)
    {
        /* not found */
        return NULL;
    }
    pciConfigInLong (BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_0, &membaseCsr);
    pciConfigInByte (BusNo, DeviceNo, FuncNo, PCI_CFG_DEV_INT_LINE, &irq);
    hbaDevNode = &HbaDevCB[DeviceId];
	memset(hbaDevNode, 0, sizeof(HBA_DEV_CB));
    hbaDevNode->BusNo = BusNo;
    hbaDevNode->DeviceNo = DeviceNo;
    hbaDevNode->FuncNo = FuncNo;
    hbaDevNode->pMembaseCsr = (UINT8 *)membaseCsr;
    hbaDevNode->irq = irq;
    hbaDevNode->DeviceId = DeviceId;
	hbaDevNode->bUseInterrupt = 1;
	hbaDevNode->bManuCloseInterrupt = 0;
	hbaDevNode->bToStop = 0;
	hbaDevNode->recvTaskId = ERROR;
	hbaDevNode->periodFmTaskId = ERROR;	

    /* ��ʼ��������� */
    hbaDevInitLists(hbaDevNode);

    /* ����ԭ�Ӳ����ѿ��л�����������к͸�FPGA�����õ��ź��� */
    hbaDevNode->semListHwLock = semBCreate(SEM_Q_FIFO, SEM_FULL);

    /* ��ʼ�����������еȴ������ݵ��ź��� */
    hbaDevNode->semRecv = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

	/*��ʼ����ؿ�ʼ���ź���*/
	hbaDevNode->semMonitorStart = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	
	/*��ʼ��ֹͣ����Ÿ�����ź���*/
	hbaDevNode->semDrainFpga = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

	hbaDevNode->semPeriodSelfCheck = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	
	
    /* �����жϻص����� */
    hbaDevNode->pRecvCallbackFunc = NULL;
    hbaDevNode->semRegRecvCallbackLock = semBCreate(SEM_Q_FIFO, SEM_FULL);

	hwResetFpga(hbaDevNode->pMembaseCsr,1);
	
    hbaDevNode->status = HBA_DEV_STATUS_CREATED;

	if (g_bRebootHookAdded == 0)
	{
		rebootHookAdd(( FUNCPTR )hbaDrvShutDown);
		g_bRebootHookAdded = 1;
	}
    
    return hbaDevNode;
}

/* �ر������豸�����ͷ��豸��Դ */
INT32 hbaDevDestroy(HBA_DEV_CB *pHbaDevCB)
{
    ASSERT(pHbaDevCB != NULL);
	if(pHbaDevCB == NULL)
	{
		return DEV_HANDLE_ERR;
	}
	
    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_SUCCESS;
    }

    hbaDevSetPortRxEnab(pHbaDevCB, 0);	
	pHbaDevCB->bToStop = 1;

	semGive(pHbaDevCB->semMonitorStart);
	semGive(pHbaDevCB->semRecv);
	while(1)
	{
		if(pHbaDevCB->recvTaskId == ERROR)
			break;

		taskDelay(1);
	}
	
	printf("%s task exit OK.\n", HBA_RECV_TASK_NAME);
	
	semGive(pHbaDevCB->semDrainFpga);

	if(pHbaDevCB->bUseInterrupt)
	{/*�ر��ж�*/
		pHbaDevCB->bManuCloseInterrupt = 1;
		hbaDevIntDiable(pHbaDevCB);
		hbaDevHwIntControl(pHbaDevCB, 0);
	}

	semGive(pHbaDevCB->semPeriodSelfCheck);
	while(1)
	{
		if(pHbaDevCB->periodFmTaskId == ERROR)
			break;

		taskDelay(1);
	}
	
	printf("%s task exit OK.\n", HBA_PERIOD_TASK_NAME);

	
    /* �ͷŶ��� */
    hbaDevFreeLists(pHbaDevCB);

    /* �ͷ��ź��� */
    if (pHbaDevCB->semListHwLock != NULL)
    {
        semDelete(pHbaDevCB->semListHwLock);
        pHbaDevCB->semListHwLock = NULL;
    }
    if (pHbaDevCB->semRecv != NULL)
    {
        semDelete(pHbaDevCB->semRecv);
        pHbaDevCB->semRecv = NULL;
    }
	if (pHbaDevCB->semRegRecvCallbackLock != NULL)
    {
        semDelete(pHbaDevCB->semRegRecvCallbackLock);
        pHbaDevCB->semRegRecvCallbackLock = NULL;
    }

	if (pHbaDevCB->semMonitorStart != NULL)
    {
        semDelete(pHbaDevCB->semMonitorStart);
        pHbaDevCB->semMonitorStart = NULL;
    }

	if (pHbaDevCB->semDrainFpga != NULL)
    {
        semDelete(pHbaDevCB->semDrainFpga);
        pHbaDevCB->semDrainFpga = NULL;
    }

	if (pHbaDevCB->semPeriodSelfCheck != NULL)
    {
        semDelete(pHbaDevCB->semPeriodSelfCheck);
        pHbaDevCB->semPeriodSelfCheck = NULL;
    }

	
	/*�ͷ��ڴ�*/
	if(pHbaDevCB->DmaBufBaseAddr != NULL)
	{
		DMA_BUF_FREE(pHbaDevCB->DmaBufBaseAddr);
		pHbaDevCB->DmaBufBaseAddr = NULL;
	}

	if(pHbaDevCB->DmaBufHeaderAddr != NULL)
	{
		HBA_MEM_FREE(pHbaDevCB->DmaBufHeaderAddr);
		pHbaDevCB->DmaBufHeaderAddr = NULL;
	}

	if(pHbaDevCB->dmaBufAddrStatAry != NULL)
	{
		HBA_MEM_FREE(pHbaDevCB->dmaBufAddrStatAry);
		pHbaDevCB->dmaBufAddrStatAry = NULL;
	}
	
    /* ��ʼ���жϻص����� */
    pHbaDevCB->pRecvCallbackFunc = NULL;
    pHbaDevCB->status = HBA_DEV_STATUS_NONE;

    return DEV_SUCCESS;
}

INT32 hbaDevReset(HBA_DEV_CB * pHbaDevCB)
{
	ASSERT(pHbaDevCB != NULL);
	if(pHbaDevCB == NULL)
	{
		return DEV_HANDLE_ERR;
	}
	
	if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
	{
		return DEV_SUCCESS;
	}

	if (pHbaDevCB->status == HBA_DEV_STATUS_CREATED)
	{
		return DEV_SUCCESS;
	}
	

	hbaDevSetPortRxEnab(pHbaDevCB, 0);	
	pHbaDevCB->bToStop = 1;

	semGive(pHbaDevCB->semMonitorStart);
	semGive(pHbaDevCB->semRecv);
	while(1)
	{
		if(pHbaDevCB->recvTaskId == ERROR)
			break;

		taskDelay(1);
	}
	
	printf("%s task exit OK.\n", HBA_RECV_TASK_NAME);
	
	semGive(pHbaDevCB->semDrainFpga);

	if(pHbaDevCB->bUseInterrupt)
	{
		pHbaDevCB->bManuCloseInterrupt = 1;
		hbaDevIntDiable(pHbaDevCB);
		hbaDevHwIntControl(pHbaDevCB, 0);
	}

	semGive(pHbaDevCB->semPeriodSelfCheck);
	while(1)
	{
		if(pHbaDevCB->periodFmTaskId == ERROR)
			break;

		taskDelay(1);
	}
	
	printf("%s task exit OK.\n", HBA_PERIOD_TASK_NAME);

	if(pHbaDevCB->DmaBufBaseAddr != NULL)
	{
		DMA_BUF_FREE(pHbaDevCB->DmaBufBaseAddr);
		pHbaDevCB->DmaBufBaseAddr = NULL;
	}

	if(pHbaDevCB->DmaBufHeaderAddr != NULL)
	{
		HBA_MEM_FREE(pHbaDevCB->DmaBufHeaderAddr);
		pHbaDevCB->DmaBufHeaderAddr = NULL;
	}

	if(pHbaDevCB->dmaBufAddrStatAry != NULL)
	{
		HBA_MEM_FREE(pHbaDevCB->dmaBufAddrStatAry);
		pHbaDevCB->dmaBufAddrStatAry = NULL;
	}

	pHbaDevCB->pRecvCallbackFunc = NULL;

    listEmptyList(&pHbaDevCB->list_hw);
    listEmptyList(&pHbaDevCB->recv_channel.list_recv);

	hwResetFpga(pHbaDevCB->pMembaseCsr,0);
	
	pHbaDevCB->status = HBA_DEV_STATUS_CREATED;

	return DEV_SUCCESS;
}


/* ��ȡ����N�˿ڵ�ǰ�Ĺ���״̬ */
INT32 hbaDevGetPortState(HBA_DEV_CB *pHbaDevCB, UINT32 *portStatus, UINT32 count)
{
    PREG_HW reg_hw;
    
    ASSERT(pHbaDevCB != NULL);
    ASSERT(portStatus != NULL);
    ASSERT(count == 2);
    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    hwGetPortStatus(reg_hw, (int *)portStatus, count);
    
    return DEV_SUCCESS;
}

/* ��ȡ��Ӳ���汾��Ϣ */
INT32 hbaDevGetVersion(HBA_DEV_CB *pHbaDevCB, UINT32 *version)
{
    int value;
    PREG_HW reg_hw;
    
    ASSERT(pHbaDevCB != NULL);
    ASSERT(version != NULL);    
    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    value = hwGetFpgaVersion(reg_hw);
    *version = (MAJOR_VER << 24) | (MINOR_VER << 16) | ((value & 0xFF) << 8) | FIRMWARE_VER;
    
    return DEV_SUCCESS;
}

/* ����FC�ڵ㿨 */
INT32 hbaDevConfig(HBA_DEV_CB *pHbaDevCB, PDEV_CONFIG dev_config)
{
    PREG_HW reg_hw;
    
    ASSERT(pHbaDevCB != NULL);
    ASSERT(dev_config != NULL);
    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;

	memcpy(&pHbaDevCB->devConfig, dev_config, sizeof(DEV_CONFIG));
      
    /* ���� fcid */
    hwSetPortFcid(reg_hw, dev_config->fcid);
    /* ���� */
    hwSetPortCreditNum(reg_hw, dev_config->credit_num);
    /* ���� 0 ����Ӧ 1-1Gbps 2-2Gbps */
    hwSetPortSpeed(reg_hw, dev_config->speed);
    /* ���շ���DID����ʹ�� */
    hwSetPortDidFilterEnab(reg_hw, dev_config->did_filter_enab);
    /* e_d_tovʱ�䣬��λ�Ǻ��� */
    hwSetPortEdtovTime(reg_hw, dev_config->e_d_tov);
    /* ����ʹ�� 0-��ֹ 1-ʹ�� */
    hwSetPortRedundantEnab(reg_hw, dev_config->redundant_enab);
    /* ��ʱ���ǵ�ʱ�䣬��λ�Ǻ��� */
    hwSetPortTimeOut(reg_hw, dev_config->time_out);
    
    return DEV_SUCCESS;
}

/* ����FC�ڵ㿨������ */
INT32 hbaDevConfigSpeed(HBA_DEV_CB *pHbaDevCB, INT32 speed)
{
    PREG_HW reg_hw;
    
    ASSERT(pHbaDevCB != NULL);
    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }

	if(speed > 2)
	{
		return DEV_PARAMS_INVALID;
	}

	reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
	pHbaDevCB->devConfig.speed = speed;

    /* ���� 0 ����Ӧ 1-1Gbps 2-2Gbps */
    hwSetPortSpeed(reg_hw, speed);
    
    return DEV_SUCCESS;
}

/*�����û�����QDR��QDR����ز���*/
STATUS hbaDevSetQDRDrvParams(HBA_DEV_CB *pHbaDevCB)
{
	UINT32 tmpQdrBufUnitSize;
	UINT32 qdrBufSizeAlign = 4*1024;	
	if(pHbaDevCB == NULL)
		return FALSE;

	tmpQdrBufUnitSize = pHbaDevCB->devConfig.qdrBufUnitSize;
	tmpQdrBufUnitSize = (tmpQdrBufUnitSize + qdrBufSizeAlign - 1 ) & (~(qdrBufSizeAlign - 1));
	if(tmpQdrBufUnitSize < QDR_BUF_UNIT_SIZE_MIN)
	{
		tmpQdrBufUnitSize = QDR_BUF_UNIT_SIZE_MIN;
	}
	else if(tmpQdrBufUnitSize > QDR_BUF_UNIT_SIZE_MAX)
	{
		tmpQdrBufUnitSize = QDR_BUF_UNIT_SIZE_MAX;
	}

	pHbaDevCB->drvBufUnitSize = pHbaDevCB->qdrBufUnitSize = tmpQdrBufUnitSize;
	pHbaDevCB->drvBufUnitNum = DMA_BUF_TOTAL_MAX /(pHbaDevCB->drvBufUnitSize);
	if(pHbaDevCB->drvBufUnitNum > 1024)
	{
		pHbaDevCB->drvBufUnitNum = 1024;
	}
	
	pHbaDevCB->qdrBufUnitNum = QDR_BUFFER_MAX/(pHbaDevCB->qdrBufUnitSize);

}
/* ��ʼ���� */
INT32 hbaDevInitialize(HBA_DEV_CB *pHbaDevCB)
{
    INT32 ret;
    
    ASSERT(pHbaDevCB != NULL);
    if (pHbaDevCB->status != HBA_DEV_STATUS_CREATED)
    {
        return DEV_INVALID_OP;
    }

	hwResetFpga(pHbaDevCB->pMembaseCsr,0);

	hwRtcControl(pHbaDevCB->pMembaseCsr,1,200,0,0);

	if(FALSE == hbaDevSetQDRDrvParams(pHbaDevCB))
	{
		return DEV_OTHER_FAILURE;
	}

    /* ����Qdr buffer */
    hbaDevConfigQdrBuffer(pHbaDevCB);
    /* ����������ݵ�DMA��������ͷ */
    ret = hbaDevAllocBuffer(pHbaDevCB);
    if (ret != OK)
    {
        return DEV_OTHER_FAILURE;
    }
    pHbaDevCB->status = HBA_DEV_STATUS_INITED;
    return DEV_SUCCESS;
}

/* ʹ�豸���Խ������� */
INT32 hbaDevRun(HBA_DEV_CB *pHbaDevCB)
{
    ASSERT(pHbaDevCB != NULL);
    ASSERT(pHbaDevCB->status == HBA_DEV_STATUS_INITED);
	
	pHbaDevCB->bToStop = 0;

    /* ���������߳� */
    pHbaDevCB->recvTaskId = taskSpawn(HBA_RECV_TASK_NAME,
                                      HBA_RECV_TASK_PRIORITY,
                                      0,
                                      HBA_RECV_TASK_STACKSIZE,
                                      hbaDevRecvTask,
                                      (int)pHbaDevCB,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (pHbaDevCB->recvTaskId == ERROR)
    {
        return DEV_OTHER_FAILURE;
    }

    pHbaDevCB->periodFmTaskId = taskSpawn(HBA_PERIOD_TASK_NAME,
                                      HBA_PERIOD_TASK_PRIORITY,
                                      0,
                                      HBA_PERIOD_TASK_STACKSIZE,
                                      hbaDevPeriodTask,
                                      (int)pHbaDevCB,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (pHbaDevCB->periodFmTaskId == ERROR)
    {
        return DEV_OTHER_FAILURE;
    }
	
	
    /* �ҽ��жϴ����� */
    hbaDevIntConnect(pHbaDevCB);

	hbaDevOpenHardInterrupt(pHbaDevCB);

    pHbaDevCB->status = HBA_DEV_STATUS_STARTED;

    return DEV_SUCCESS;
}

/* ע���жϽ��ջص����� */
INT32 hbaDevRegMsgHandler(HBA_DEV_CB *pHbaDevCB, FC_NP_RECV_FUNCPTR func)
{
    ASSERT(pHbaDevCB != NULL);
    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }
    /* ԭ�Ӳ��� */
    semTake(pHbaDevCB->semRegRecvCallbackLock, WAIT_FOREVER);
    pHbaDevCB->pRecvCallbackFunc = func;
    semGive(pHbaDevCB->semRegRecvCallbackLock);

    return DEV_SUCCESS;
}

/* ע���жϽ��ջص����� */
INT32 hbaDevUnRegMsgHandler(HBA_DEV_CB *pHbaDevCB)
{
    ASSERT(pHbaDevCB != NULL);
    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_SUCCESS;
    }
    /* ԭ�Ӳ��� */
    semTake(pHbaDevCB->semRegRecvCallbackLock, WAIT_FOREVER);
    pHbaDevCB->pRecvCallbackFunc = NULL;
    semGive(pHbaDevCB->semRegRecvCallbackLock);

    return DEV_SUCCESS;
}

/*-------------------- ͨ�Ź���ӿ� --------------------*/
/* ȡ�����ݵĵ�ַ�ͳ��� */
INT32 hbaDevRecvData(HBA_DEV_CB *pHbaDevCB, void **ppBuffer, UINT *nLen)
{
    int i, data_length;
    R_CTRL *r_ctrl;
    DMA_BUFFER_NODE_HEADER *node_header;
	DMA_BUFFER_NODE *dma_node_buffer;
    RECV_CHANNEL *recv_channel;
    
    ASSERT(pHbaDevCB != NULL);
    if (pHbaDevCB->status != HBA_DEV_STATUS_STARTED)
    {
        return DEV_STS_ERR;
    }

    recv_channel = &pHbaDevCB->recv_channel;
    node_header = (DMA_BUFFER_NODE_HEADER *)listRemoveNodeFromListHead(&recv_channel->list_recv);
    if (node_header == NULL)
    {
        /* the list is empty */
        return ASM_RECV_NO_DATA;
    }

	dma_node_buffer = node_header->dma_buf_node;
    r_ctrl = (R_CTRL *)dma_node_buffer;
    *nLen = r_ctrl->r0.u.length;
    *ppBuffer = dma_node_buffer + 1; /* ֻ��Ӧ�÷������ݣ�������R_CTRL�� */

    return DEV_SUCCESS;
}

/* �ͷ����ݻ����� */
INT32 hbaDevReleaseBuf(HBA_DEV_CB *pHbaDevCB, void *pBuffer)
{
    DMA_BUFFER_NODE_HEADER *node_header;
    DMA_BUFFER_NODE *pDma_buf_node;

    ASSERT(pHbaDevCB != NULL);
    ASSERT(pBuffer != NULL);
    if (pHbaDevCB->status != HBA_DEV_STATUS_STARTED)
    {
        return DEV_STS_ERR;
    }
	
    /* �˻�sizeof(R_CTRL)���ֽڲ���DMA��������ͷ�� */
    pDma_buf_node = (DMA_BUFFER_NODE *)((UINT8 *)pBuffer - sizeof(R_CTRL));
	node_header = hbaDevGetNodeHeaderAddr(pHbaDevCB,pDma_buf_node);
	hbaDevFreeRecvBuffer(pHbaDevCB, node_header);

    return DEV_SUCCESS;
}

/* --------------------ʱͳ����ӿ� --------------------*/
/* ��ȡRTCʱ�� */
VOID hbaDevGetRtc(HBA_DEV_CB *pHbaDevCB, FCTime *pFCTime)
{
    UINT64 time;
    PREG_HW reg_hw;
    
    ASSERT(pHbaDevCB != NULL);
    ASSERT(pFCTime != NULL);
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    
    hwReadRtcPrepare(reg_hw);
    time = hwGetRtc(reg_hw);
    hwReadRtcFinish(reg_hw);
    hbaDrvTimeToFCTime(time, pFCTime);
}

/* ����RTCʱ�� */
VOID hbaDevSetRtc(HBA_DEV_CB *pHbaDevCB, FCTime *pFCTime)
{
	int ret;
	UINT32 high, low;

	if(pHbaDevCB == NULL || pFCTime == NULL)
		return;

    ret = hbaDrvFCTimeToTime(pFCTime, &high, &low);
	if(ret == -1)
		return;

    hwSetRtc((PREG_HW)pHbaDevCB->pMembaseCsr, high, low);
}

/* ��ȡ���ں�ʱ�� */
VOID hbaDevGetDateTime(HBA_DEV_CB *pHbaDevCB, FCDate *pFCDate, FCTime *pFCTime)
{
    UINT64 time;
    UINT32 date;
    PREG_HW reg_hw;
    
    ASSERT(pHbaDevCB != NULL);
    ASSERT(pFCTime != NULL);
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;

    hwReadRtcPrepare(reg_hw);
    date = hwGetDate(reg_hw);
    time = hwGetRtc(reg_hw);
    hwReadRtcFinish(reg_hw);
    hbaDrvDateToFCDate(date, pFCDate);
    hbaDrvTimeToFCTime(time, pFCTime);
}

/* �������� */
VOID hbaDevSetDate(HBA_DEV_CB *pHbaDevCB, FCDate * pFCDate)
{
    UINT32 date;
    PREG_HW reg_hw;

    ASSERT(pHbaDevCB != NULL);
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    date = hbaDrvFCDateToDate(pFCDate);
    hwSetDate(reg_hw, date);
}

/*------------------------------------------------------*/
/*-------------------- �ڲ��������� --------------------*/
/*------------------------------------------------------*/
/* ��ʼ��������� */
VOID hbaDevInitLists(HBA_DEV_CB *pHbaDevCB)
{
    ASSERT(pHbaDevCB != NULL);
    ASSERT(pHbaDevCB->status == HBA_DEV_STATUS_NONE);
    listInit(&pHbaDevCB->list_hw, 1);
    listInit(&pHbaDevCB->recv_channel.list_recv, 1);
    pHbaDevCB->recv_channel.semListRecvLock  = semBCreate(SEM_Q_FIFO, SEM_FULL);
}

/* �ͷ�������� */
VOID hbaDevFreeLists(HBA_DEV_CB * pHbaDevCB)
{
    ASSERT(pHbaDevCB != NULL);
    if (pHbaDevCB->status != HBA_DEV_STATUS_CREATED)
    {
        return;
    }
    /* ��FPGA���ͺͽ����йصĶ��� */
    listExit(&pHbaDevCB->list_hw);
    listExit(&pHbaDevCB->recv_channel.list_recv);
    if (pHbaDevCB->recv_channel.semListRecvLock)
    {
        semDelete(pHbaDevCB->recv_channel.semListRecvLock);
        pHbaDevCB->recv_channel.semListRecvLock = NULL;
    }
}

/* ����Qdr buffer */
INT32 hbaDevConfigQdrBuffer(HBA_DEV_CB *pHbaDevCB)
{
    INT32 i, node_count, node_size, start_address;
    PREG_HW reg_hw;
	UINT32 QDR_BUFFER_NODE_SIZE;

	if(pHbaDevCB == NULL)
		return 0;

	QDR_BUFFER_NODE_SIZE = pHbaDevCB->qdrBufUnitSize;
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    node_count = pHbaDevCB->qdrBufUnitNum;
    node_size = QDR_BUFFER_NODE_SIZE - QDR_FPGA_RESERVED;
    ASSERT(node_count > 0);
    ASSERT(node_count <= 256);
    ASSERT(node_size > 0);
    printf("QDR_BUFFER_MAX=0x%x QDR_BUFFER_NODE_SIZE=0x%x QDR_FPGA_RESERVED=0x%x node_count=0x%x node_size=0x%x\n",
        QDR_BUFFER_MAX, QDR_BUFFER_NODE_SIZE, QDR_FPGA_RESERVED, node_count, node_size);
    /* ����Qdr buffer size */
    hwQdrConfigBufferSize(reg_hw, node_size);
    /* ����ÿ��Qdr buffer�Ŀ�ʼ��ַ  */
   for (i = 0; i < node_count; ++i)
   {
       start_address = i * QDR_BUFFER_NODE_SIZE / 16;
       hwQdrConfigBufferStartAddress(reg_hw, start_address);
   }

   return 0;
}

/* ����������ݵ�DMA��������ͷ */
INT32 hbaDevAllocBuffer(HBA_DEV_CB *pHbaDevCB)
{
    INT32 ret, i, count, buf_size, valid_buf_num, dmaBufSize, headerBufSize;
    INT32 credits[3];
    UINT8 *buf, *dma_buf, *dma_header_buf;
    DMA_BUFFER_NODE *dma_buf_node;
    DMA_BUFFER_NODE_HEADER *dma_buf_node_header;
	UINT32 NODE_NUM;
	UINT32 NODE_SIZE;

    ASSERT(pHbaDevCB != NULL);
	if(pHbaDevCB == NULL)
	{
		return ERROR;
	}

	NODE_NUM = pHbaDevCB->drvBufUnitNum;
	NODE_SIZE = pHbaDevCB->drvBufUnitSize;

    /* ����DMA������ */
    buf_size = DMA_BUF_ALIGN_SIZE + NODE_NUM * (NODE_OVERFLOW_SIZE + NODE_SIZE + NODE_OVERFLOW_SIZE);
    buf = (UINT8 *)DMA_BUF_MALLOC(buf_size);
    if (buf == NULL)
    {
        printf("malloc dma buf failed size=%d\n", buf_size);
        return ERROR;
    }
    pHbaDevCB->DmaBufBaseAddr = buf;
    /* �Է�����ڴ���ʼ�� */
    memset(buf, 0, buf_size);    
    printf("dma buf node addr=%p size=%d\n", buf, buf_size);
	dmaBufSize = buf_size;

    /* DMA�ڴ��ַ��Ҫ���� */
    buf = (UINT8 * )(((UINT32)buf + DMA_BUF_ALIGN_SIZE - 1) & ~(DMA_BUF_ALIGN_SIZE - 1));
    dma_buf = buf;
    for (i = 0; i < NODE_NUM; ++i)
    {
        INT32 k;
        UINT8 *p0, *p1;

        p0 = buf + i * (NODE_OVERFLOW_SIZE + NODE_SIZE + NODE_OVERFLOW_SIZE);
        p1 = p0 + NODE_OVERFLOW_SIZE + NODE_SIZE;
        for (k = 0; k < NODE_OVERFLOW_SIZE / sizeof(int); ++k)
        {
            ((INT32 *)p0)[k] = 0xDEADBEEF;
            ((INT32 *)p1)[k] = 0xDEADBEEF;
        }
    }    

    /* ����DMAͷ�Ļ����� */
    buf_size = NODE_NUM * sizeof(DMA_BUFFER_NODE_HEADER);
    buf = HBA_MEM_MALLOC(buf_size);
    if (buf ==  NULL)
    {
        DMA_BUF_FREE(pHbaDevCB->DmaBufBaseAddr);
		pHbaDevCB->DmaBufBaseAddr = NULL;
        printf("malloc dma buf node header failed size=%d\n", buf_size);
        return ERROR;
    }
    pHbaDevCB->DmaBufHeaderAddr = dma_header_buf = buf;

    /* �Է�����ڴ���ʼ�� */
    memset(buf, 0, buf_size);    
    printf("dma buf node header addr=%p size=%d\n", buf, buf_size);
	headerBufSize = buf_size;

    /* ����DMA ��ַ��������Ļ����� */
    buf_size = NODE_NUM * sizeof(DMA_BUFFER_ADDR_ELEMENT);
    buf = HBA_MEM_MALLOC(buf_size);
    if (buf ==  NULL)
    {
        DMA_BUF_FREE(pHbaDevCB->DmaBufBaseAddr);
		pHbaDevCB->DmaBufBaseAddr = NULL;
        DMA_BUF_FREE(pHbaDevCB->DmaBufHeaderAddr);
		pHbaDevCB->DmaBufHeaderAddr = NULL;

        printf("malloc dma buf node header failed size=%d\n", buf_size);
        return ERROR;
    }
    pHbaDevCB->dmaBufAddrStatAry = (DMA_BUFFER_ADDR_ELEMENT*)buf;	
    memset(buf, 0, buf_size);    
    printf("dma buf element array addr=%p size=%d\n", buf, buf_size);
	
    /* �������� */
    for (i = 0; i < NODE_NUM; ++i)
    {
        dma_buf_node = (DMA_BUFFER_NODE *)(dma_buf + NODE_OVERFLOW_SIZE);
        dma_buf_node_header = (DMA_BUFFER_NODE_HEADER *)dma_header_buf;

        dma_buf_node->r0 = dma_buf_node->r1 = 0;
        dma_buf_node_header->dma_buf_node = dma_buf_node;
        dma_buf_node_header->buffer_index = i;
        /* ��FPGAע�Ỻ�����ĵ�ַ������ */
        hbaDevRegisterRxDmaBuf(pHbaDevCB, i, (int)dma_buf_node);
        /* ��FPGAѹ������ */
        credits[0] = i;
		credits[1] = 0;
		credits[2] = 0;
        hbaDevPushCredits(pHbaDevCB, credits, 1);

        /* �ѻ������������� */
        listAddNodeToListTail(dma_buf_node_header, &pHbaDevCB->list_hw);
        /* ƫ�� */
        dma_buf += (NODE_OVERFLOW_SIZE + NODE_SIZE + NODE_OVERFLOW_SIZE);
        dma_header_buf += sizeof(DMA_BUFFER_NODE_HEADER);

		pHbaDevCB->dmaBufAddrStatAry[i].pDmaBufNodeAddr = dma_buf_node;
		pHbaDevCB->dmaBufAddrStatAry[i].pDmaBufNodeHeaderAddr = dma_buf_node_header;

		printf("index=%d, dmaBufAddr=0x%08x, bufNodeAddr=%08x.\n",i, dma_buf_node,dma_buf_node_header);
    }

	ASSERT(dma_buf <= (pHbaDevCB->DmaBufBaseAddr + dmaBufSize));
	ASSERT(dma_header_buf <= (pHbaDevCB->DmaBufHeaderAddr + headerBufSize));
	if(g_prtDrv)
	{
		printf("dmabuflastAddr=0x%08x, endAddr=0x%08x.\n", dma_buf, (pHbaDevCB->DmaBufBaseAddr + dmaBufSize));
		printf("headerbuflastAddr=0x%08x, endAddr=0x%08x.\n", dma_header_buf, (pHbaDevCB->DmaBufHeaderAddr + headerBufSize));		
	}

	pHbaDevCB->DmaBufAddrIntervalSize = (NODE_OVERFLOW_SIZE + NODE_SIZE + NODE_OVERFLOW_SIZE);
    return OK;
}

/* ��FPGAע�Ỻ�����ĵ�ַ������ */
VOID hbaDevRegisterRxDmaBuf(HBA_DEV_CB *pHbaDevCB, int index, int dma_buf)
{
    PREG_HW reg_hw;
    
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    hwRegisterRxDmaBuf(reg_hw, index, dma_buf);
}

/* ��FPGAѹ������ */
VOID hbaDevPushCredits(HBA_DEV_CB *pHbaDevCB, int *credits, int valid_buf_num)
{
    PREG_HW reg_hw;
    
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    hwPushCreditsToFpga(reg_hw, credits, valid_buf_num);
}

/* ����ʹ�ܣ�ʹ�˿��ܹ��� */
VOID hbaDevSetPortRxEnab(HBA_DEV_CB *pHbaDevCB, int rx_enab)
{
    PREG_HW reg_hw;

    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    hwSetPortRxEnab(reg_hw, rx_enab);
}

/* �ҽ��жϴ����� */
STATUS hbaDevIntConnect(HBA_DEV_CB *pHbaDevCB /*, UINT8 irq*/)
{
    STATUS ret; 
    ret = pciIntConnect ( (VOIDFUNCPTR *)(int)(pHbaDevCB->irq), (VOIDFUNCPTR)hbaDevIntHandler, (int) pHbaDevCB);
    if (ret != OK)
    {
        printf("pciIntConnect() Fail, irq=%d\n", pHbaDevCB->irq);    
    }

    return ret;
}

/* �ж�ʹ�ܿ��� */
VOID hbaDevHwIntControl(HBA_DEV_CB *pHbaDevCB, int enab)
{
    PREG_HW reg_hw;

    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    hwSetIntrptEnable(reg_hw, enab);
}

int gDevIntCounter = 0;
int gLinkStatusChangCount = 0;

VOID hbaDevIntHandler(HBA_DEV_CB *pHbaDevCB)
{
    /* logMsg("%s: enter \n", (int)__FUNCTION__, 0,0,0,0,0); */
    int link_change = 0;    
    UINT32 linkStatus;
    ULONG value;
    INTERRUPT  intrp;
    PREG_HW reg_hw;
    
    gDevIntCounter++;
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    link_change = hwGetLinkChangePending(reg_hw);
    /* ����Ƿ�����·�仯���ж� */
    if (link_change)
    {
        /* ���Ĵ�����·�Ƿ�仯������仯�����޸���·��־����������·�仯���� */
        linkStatus = hbaDevCheckLinkStatus(pHbaDevCB);
        if (pHbaDevCB->linkStatus != linkStatus)
        {
            pHbaDevCB->linkStatus = linkStatus;            
            pHbaDevCB->linkStatusChgCount++;
            gLinkStatusChangCount = pHbaDevCB->linkStatusChgCount;
        }
            
        /* �����·�仯��������0���������ڼ��ĺ������ص����жϺ��� */
        if (pHbaDevCB->linkStatusChgCount > 0)
        {
            semGive(pHbaDevCB->semPeriodSelfCheck); 
        }
    }

    /* �ر��жϺ� */
    hbaDevIntDiable(pHbaDevCB);
    /* �ر��жϣ������pendingλ */
    hbaDevHwIntControl(pHbaDevCB, 0);

	pHbaDevCB->bManuCloseInterrupt = 1;

    /* ���Ѵ������� */
    semGive(pHbaDevCB->semRecv); 

    /* logMsg("%s: exit \n", (int)__FUNCTION__, 0,0,0,0,0); */
}

/*
��ȡFPGA�Ĵ�����ȡ��2���˿ڵ���·״ֵ̬��
�ú��������жϴ������б����ã����ܵ���printf����
*/
UINT32 hbaDevCheckLinkStatus(HBA_DEV_CB *pHbaDevCB)
{
    UINT32 ret;
    int port_status[2];	
    PREG_HW reg_hw;
	
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;
    hwGetPortStatus(reg_hw, port_status, 2);

    /* �����˿�ֻҪ��һ��link״̬�������ģ���������*/
    if (port_status[0] == PORT_LINK_UP || port_status[1] == PORT_LINK_UP)
    {
	ret = IC_LINK_STATUS_SUCCESS;
    }
    else
    {
        ret = IC_LINK_STATUS_FAILED;
    }
    return ret;
}

STATUS hbaDevIntEnable (HBA_DEV_CB *pHbaDevCB)
{                                                                      
    STATUS ret;
    ret = intEnable ((int)pHbaDevCB->irq);
    return ret;
}                                           

STATUS hbaDevIntDiable(HBA_DEV_CB *pHbaDevCB)
{
    STATUS ret;
    ret = intDisable((int)pHbaDevCB->irq);
    return ret;
}

INT32 hbaDevRecvTask(HBA_DEV_CB *pHbaDevCB)
{
    int dataRecvFlag = 0;
    int iDataRecvCount, nLen;
    void *pBuffer = NULL;
    RECV_CHANNEL *recv_channel;
    R_CTRL *r_ctrl;
    DMA_BUFFER_NODE_HEADER *node_header;
	DMA_BUFFER_NODE *dma_buf_node;

    ASSERT(pHbaDevCB != NULL);
    recv_channel = &pHbaDevCB->recv_channel;

    while(1)
    {
    	if(pHbaDevCB->monitorStatus != HBA_MONITOR_STATUS_START)
    	{
    		if(pHbaDevCB->monitorStatus == HBA_MONITOR_STATUS_STOP)
    		{
    			hbaDevDrainFpga(pHbaDevCB);
    		}

			if(pHbaDevCB->bToStop != 1)
			{/*���bToStop �Ƿ������ϣ���������Ҫ�������������豸���ͷ�*/
    			semTake(pHbaDevCB->semMonitorStart, WAIT_FOREVER);
			}
    	}

        if (pHbaDevCB->bToStop)
        {
        	hbaDevDrainFpga(pHbaDevCB);
            break;
        }
        iDataRecvCount = 0;
        do {
            dataRecvFlag = hbaDevRecvOneBuffer(pHbaDevCB);

			/* ���ע�����жϣ������ݰ��ϱ���Ӧ�ò� */
			semTake(pHbaDevCB->semRegRecvCallbackLock, WAIT_FOREVER);
			if (pHbaDevCB->pRecvCallbackFunc != NULL)
			{
				node_header = (DMA_BUFFER_NODE_HEADER *)listRemoveNodeFromListHead(&recv_channel->list_recv);
				if (node_header != NULL)
				{
					dataRecvFlag = 1;
					dma_buf_node = node_header->dma_buf_node;
					r_ctrl = (R_CTRL *)dma_buf_node;
					nLen = r_ctrl->r0.u.length;
					pBuffer = dma_buf_node + 1; /* ֻ��Ӧ�÷������ݣ�������R_CTRL�� */
					if(g_prtDrv)
					{
						printf("list r_ctrl=0x%08x, index=%d, buf=0x%08x. len=%d.\n", r_ctrl, node_header->buffer_index, pBuffer, nLen);
					}
					pHbaDevCB->pRecvCallbackFunc((INT32 *)pHbaDevCB, pBuffer, nLen);
				}
			}
			semGive(pHbaDevCB->semRegRecvCallbackLock);

            if (dataRecvFlag == 1)
            {
                iDataRecvCount++;
			}			
	
        } while (dataRecvFlag == 1 && iDataRecvCount < 16);

		hbaDevOpenHardInterrupt(pHbaDevCB);
	
		semTake(pHbaDevCB->semRecv, 1);
    }

    pHbaDevCB->recvTaskId = ERROR;

    return 0;
}

/*�Ÿ��û���������*/
VOID hbaDevDrainUserList(HBA_DEV_CB *pHbaDevCB)
{
    int data_length, qdr_empty;
    RECV_CHANNEL *recv_channel;
    R_CTRL *r_ctrl;
    DMA_BUFFER_NODE_HEADER *node_header;
	DMA_BUFFER_NODE *dma_buf_node;	
    PREG_HW reg_hw;
	int dataRecvFlag = 0;
    void *pBuffer = NULL;	
	int nLen;



    ASSERT(pHbaDevCB != NULL);
    recv_channel = &pHbaDevCB->recv_channel;
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;

	semTake(pHbaDevCB->semRegRecvCallbackLock, WAIT_FOREVER);	
	while(1)
	{
		node_header = (DMA_BUFFER_NODE_HEADER *)listRemoveNodeFromListHead(&recv_channel->list_recv);
		if(node_header == NULL)
		{
			break;
		}
		if (pHbaDevCB->pRecvCallbackFunc != NULL)
		{/*�û�ע��ص��������û������ͷ�BUFFER*/
			dma_buf_node = node_header->dma_buf_node;
			r_ctrl = (R_CTRL *)dma_buf_node;
			nLen = r_ctrl->r0.u.length;
			pBuffer = dma_buf_node + 1; /* ֻ��Ӧ�÷������ݣ�������R_CTRL�� */
			if(g_prtDrv)
			{
				printf("list r_ctrl=0x%08x, buf=0x%08x. len=%d.\n", r_ctrl, pBuffer, nLen);
			}
			pHbaDevCB->pRecvCallbackFunc((INT32 *)pHbaDevCB, pBuffer, nLen);
		}
		else
		{/*���������ͷ�BUFFER*/
			hbaDevFreeRecvBuffer(pHbaDevCB, node_header);
		}		
	}
	semGive(pHbaDevCB->semRegRecvCallbackLock);
	
	hbaDevOpenHardInterrupt(pHbaDevCB);		
	
	return ;
}

/* �Ÿ�QDR������������ */
/*����������1 QDRΪ�գ�2 �û�����û�нڵ�, 3Ӳ���ڵ�û�����ݻ��������û�û�ͷ��û�������Ӳ������û�нڵ� */
VOID hbaDevDrainFpga(HBA_DEV_CB *pHbaDevCB)
{
    int qdr_empty;
    RECV_CHANNEL *recv_channel;
    R_CTRL *r_ctrl;
    DMA_BUFFER_NODE_HEADER *node_header;
	DMA_BUFFER_NODE *dma_buf_node;	
    PREG_HW reg_hw;
	int dataRecvFlag = 0;
	int usrListEmpty = 0;
    void *pBuffer = NULL;	
	int nLen;

	
	if(pHbaDevCB == NULL)
	{
		return;
	}
	
    ASSERT(pHbaDevCB != NULL);

	/*�Ȱ��û������е����ݶ��Ÿ�*/
	hbaDevDrainUserList(pHbaDevCB);

    recv_channel = &pHbaDevCB->recv_channel;
    reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;

	usrListEmpty = 0;	
    while (1)
    {
		dataRecvFlag = hbaDevRecvOneBuffer(pHbaDevCB);
		if(dataRecvFlag != 1)
		{/*Ӳ���ڵ�û�����ݻ���û�нڵ�*/

			/*�鿴QDR�Ƿ�Ϊ��*/
			qdr_empty = hwGetQdrBufferEmpty(reg_hw);
			if(qdr_empty == 1 && usrListEmpty == 1)
			{
				break;
			}
		}
		
		/*��������*/
		semTake(pHbaDevCB->semRegRecvCallbackLock, WAIT_FOREVER);
		node_header = (DMA_BUFFER_NODE_HEADER *)listRemoveNodeFromListHead(&recv_channel->list_recv);
		if (node_header == NULL)
		{
			usrListEmpty = 1;
		}
		else
		{
			usrListEmpty = 0;
			if (pHbaDevCB->pRecvCallbackFunc != NULL)
			{/* ���ע�����жϣ������ݰ��ϱ���Ӧ�ò� */
				dma_buf_node = node_header->dma_buf_node;
				r_ctrl = (R_CTRL *)dma_buf_node;
				nLen = r_ctrl->r0.u.length;
				pBuffer = dma_buf_node + 1; /* ֻ��Ӧ�÷������ݣ�������R_CTRL�� */
				if(g_prtDrv)
				{
					printf("list r_ctrl=0x%08x, buf=0x%08x. len=%d.\n", r_ctrl, pBuffer, nLen);
				}
				pHbaDevCB->pRecvCallbackFunc((INT32 *)pHbaDevCB, pBuffer, nLen);
			}
			else
			{/*���������ͷ�BUFFER*/
				hbaDevFreeRecvBuffer(pHbaDevCB, node_header);
			}
		}
		semGive(pHbaDevCB->semRegRecvCallbackLock);
    }

	hbaDevOpenHardInterrupt(pHbaDevCB);
	

	/*�����Ÿ�*/
	semGive(pHbaDevCB->semDrainFpga);

}

int lastEmptyBufIndex=0;
int lastNoDataBufIndex=0;


/* ���������һ�������������� */
/*����ֵ��-1��ʾӲ���б�û�нڵ㣨����û��Ӳ������BUFFER���� 0��ʾ����Ϊ0���߳��������⣻1��ʾ������*/
int hbaDevRecvOneBuffer(HBA_DEV_CB *pHbaDevCB)
{
    int i, data_length;
    R_CTRL *r_ctrl;
    DMA_BUFFER_NODE_HEADER *node_header;
	UINT32 NODE_SIZE = pHbaDevCB->qdrBufUnitSize;

    node_header = (DMA_BUFFER_NODE_HEADER *)listGetFirstNodeFromList(&pHbaDevCB->list_hw);
    if (node_header == NULL)
    {
        /* the list is empty */
		lastEmptyBufIndex = 1;
        return -1;
    }
    
    /* Check whether the data in the buffer has been sent */
    ASSERT(node_header->dma_buf_node != NULL);
    HBA_CACHE_INVAL(node_header->dma_buf_node, NODE_SIZE);
    r_ctrl = (R_CTRL *)node_header->dma_buf_node;
    data_length = r_ctrl->r0.u.length;
    if (data_length == 0)
    {
    	lastNoDataBufIndex = node_header->buffer_index;
		lastEmptyBufIndex = 0;
        return 0;
    }
    ASSERT(data_length > 0);
    ASSERT(data_length <= NODE_SIZE - sizeof(R_CTRL));
    if (data_length > NODE_SIZE - sizeof(R_CTRL))
    {
        printf("***invalid length in recv buffer, r0=0x%08x r1=0x%08x\n", r_ctrl->r0.value, r_ctrl->r1.value);
        hbaDevFreeRecvBuffer(pHbaDevCB, node_header);
        return 0;
    }

	semTake(pHbaDevCB->semListHwLock, WAIT_FOREVER);
    node_header = listRemoveNodeFromListHead(&pHbaDevCB->list_hw);
	/*��FPGA����ȡ�������ݣ�Ϊ�˷�ֹʱ�����С��һ�£�Ӧ��ֱ�ӷ���ͨ����������*/
    hbaDevFillRecvList(pHbaDevCB, node_header);

	if(g_prtDrv)
	{
		printf("get buf_index=%d.\n", node_header->buffer_index);
	}

	semGive(pHbaDevCB->semListHwLock);

	pHbaDevCB->stat_recvDmaBufCnt++;
	pHbaDevCB->stat_recvDmaBufValidLen += data_length;

    return 1;
}

ULONG r1TestVal = 0;
ULONG testBufIndex = 0;


/* �ͷŻ�������ʹFPGA�ܹ��������øû������������� */
VOID hbaDevFreeRecvBuffer(HBA_DEV_CB *pHbaDevCB, DMA_BUFFER_NODE_HEADER *node_header)
{
    int credits[3];
    R_CTRL *rctrl; 
    
    ASSERT(pHbaDevCB != NULL) ;
    if (node_header == NULL || pHbaDevCB == NULL)
    {
        return;
    }

    /* ���r0, r1 */
    rctrl = (R_CTRL *)node_header->dma_buf_node;
    rctrl->r0.value = rctrl->r0.value = 0;
    HBA_CACHE_FLUSH(node_header->dma_buf_node, sizeof(R_CTRL));

    /* �����ú��������������ԭ�ӵ� */
    semTake(pHbaDevCB->semListHwLock, WAIT_FOREVER);
    /* ��FPGAѹ������ */
    credits[0] = node_header->buffer_index;
	credits[1] = 0;
	credits[2] = 0;
	if(g_prtDrv)
	{	
		rctrl->r1.value = r1TestVal++;
		testBufIndex = node_header->buffer_index;
		printf("free budIndex=%d.\n", testBufIndex);
	}
    hbaDevPushCredits(pHbaDevCB, credits, 1);
    listAddNodeToListTail(node_header, &pHbaDevCB->list_hw);
    semGive(pHbaDevCB->semListHwLock);
    
    return;
}

/* �������ݵĻ������������������ */
BOOL hbaDevFillRecvList(HBA_DEV_CB *pHbaDevCB, DMA_BUFFER_NODE_HEADER  *node_header)
{
    RECV_CHANNEL *recv_channel;
    R_CTRL *r_ctrl;

	if(pHbaDevCB == NULL || node_header == NULL)
	{
		return FALSE;
	}

    r_ctrl = (R_CTRL *)node_header->dma_buf_node;

    recv_channel = &pHbaDevCB->recv_channel;
    listAddNodeToListTail(node_header, &recv_channel->list_recv);    
    return TRUE;
}

void* hbaDevGetNodeHeaderAddr(HBA_DEV_CB * pHbaDevCB, void* pDmaBuf)
{
	int i = 0,j=0;
	UINT32 NODE_NUM;
	UINT32 NODE_SIZE;
	unsigned int intervalSize;
	if(pHbaDevCB == NULL || pDmaBuf == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}

	NODE_NUM = pHbaDevCB->drvBufUnitNum;
	NODE_SIZE = pHbaDevCB->drvBufUnitSize;
	intervalSize = pHbaDevCB->DmaBufAddrIntervalSize;

	if(pDmaBuf < pHbaDevCB->dmaBufAddrStatAry[0].pDmaBufNodeAddr
		|| pDmaBuf > pHbaDevCB->dmaBufAddrStatAry[NODE_NUM-1].pDmaBufNodeAddr)
	{
		ASSERT(FALSE);
		return NULL;
	}

	j = ((UINT32)pDmaBuf - (UINT32)(pHbaDevCB->dmaBufAddrStatAry[0].pDmaBufNodeAddr)) % intervalSize;
	if(j != 0)
	{
		ASSERT(FALSE);
		return NULL;
	}
	i = ((UINT32)pDmaBuf - (UINT32)(pHbaDevCB->dmaBufAddrStatAry[0].pDmaBufNodeAddr)) / intervalSize;

	return pHbaDevCB->dmaBufAddrStatAry[i].pDmaBufNodeHeaderAddr;

}

/*�豸��ʼ���*/
INT32 hbaDevStartMonitor(HBA_DEV_CB *pHbaDevCB)
{
	if(pHbaDevCB == NULL)
	{
		return DEV_HANDLE_ERR;
	}

    /* ����ʹ�ܣ�ʹ�˿��ܹ��� */
	if(pHbaDevCB->status != HBA_DEV_STATUS_STARTED)
	{
		return DEV_STS_ERR;
	}

	pHbaDevCB->monitorStatus = HBA_MONITOR_STATUS_START;
	semGive(pHbaDevCB->semMonitorStart);
    hbaDevSetPortRxEnab(pHbaDevCB, 1);
	return DEV_SUCCESS;
}

/*�豸ֹͣ���*/
INT32 hbaDevStopMonitor(HBA_DEV_CB *pHbaDevCB)
{
	if(pHbaDevCB == NULL)
	{
		return DEV_HANDLE_ERR;
	}

	if(pHbaDevCB->monitorStatus != HBA_MONITOR_STATUS_START)
	{
		return DEV_SUCCESS;
	}
	pHbaDevCB->monitorStatus = HBA_MONITOR_STATUS_STOP;
    hbaDevSetPortRxEnab(pHbaDevCB, 0);

	/*�ͷŽ����ź�������������߳�*/
	semGive(pHbaDevCB->semRecv);

	semTake(pHbaDevCB->semDrainFpga, WAIT_FOREVER);
	
	return DEV_SUCCESS;	
}

/*��Ӳ���ж�*/
VOID hbaDevOpenHardInterrupt(HBA_DEV_CB *pHbaDevCB)
{
	if(pHbaDevCB->bUseInterrupt)
	{
		pHbaDevCB->bManuCloseInterrupt = 0;
		/* �����ж� */
		hbaDevHwIntControl(pHbaDevCB, 1);
		hbaDevIntEnable(pHbaDevCB);
	}	
}


UINT32 hbaDevGetStatByType(PREG_HW reg_hw, UINT32 type)
{
	STATISTICS_CONTROL status;
	UINT32 tempValue = 0;	
	int wait = 100;

	status.value = 0;
	status.u.start = 0;
	status.u.type = type;
	WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, status.value);

    while(wait --);
	
	tempValue = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);

	return tempValue;
}



/*��ȡͳ��ֵ*/
FCUINT hbaDevCheckStatistics(HBA_DEV_CB *pHbaDevCB)
{
	FCUINT ret = 0;
	PREG_HW reg_hw;
	STATISTICS_CONTROL status;	
	int i;
	int portBaseAddr = 0;
	
	reg_hw = (PREG_HW)pHbaDevCB->pMembaseCsr;

	/*set snapshot*/
	status.value = 0;
	status.u.start = 1;
	WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, status.value);
	
	taskDelay(1);

	/*get stat*/
#if 0
	pHbaDevCB->fpgaStatInfo.recvFrameNumTotal += hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_FRAME_NUM);
	pHbaDevCB->fpgaStatInfo.recvIUNumTotal += hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_IU_NUM);
	pHbaDevCB->fpgaStatInfo.recvErrorIUNumTotal += hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_ERROR_IU_NUM);
#endif

	pHbaDevCB->fpgaStatInfo.recvDiscardFrameNumTotal += hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_DISCARD_IU_NUM);

#if 0
	pHbaDevCB->fpgaStatInfo.recvInvalidFrameNumTotal += hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_INVALID_FRAME_NUM);

	pHbaDevCB->fpgaStatInfo.sendFrameNumTotal += hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_SEND_FRAME_NUM);
	pHbaDevCB->fpgaStatInfo.sendIUNumTotal += hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_SEND_IU_NUM);
#endif

	for (i=0; i<MAX_PORT_NUM; i++)
	{
		if (i == 0)
			portBaseAddr = FPGA_STAT_PORT_0_BASE;
		else
			portBaseAddr = FPGA_STAT_PORT_1_BASE;

	
		pHbaDevCB->portStatInfo[i].RxUndersizeFrameCnt   += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_UNDERSIZE_FRAME);
		pHbaDevCB->portStatInfo[i].RxOversizeFrameErrCnt += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_OVERSIZE_FRAME);
		pHbaDevCB->portStatInfo[i].RxAllFrameCnt         += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_ALL_FRAME);
		pHbaDevCB->portStatInfo[i].RxValidFrameCnt       += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_VALID_FRAME);
		pHbaDevCB->portStatInfo[i].RxWordCnt             += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_FRAME_LEN);
		pHbaDevCB->portStatInfo[i].RxRRDYCnt             += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_RRDY);
		pHbaDevCB->portStatInfo[i].RxKErrCnt             += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_K_ERR);

		pHbaDevCB->portStatInfo[i].LinkChgUp2DownCnt     += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_LNK_CHG_UP2DWN);

		pHbaDevCB->portStatInfo[i].TxAllFrameCnt         += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_TX_ALL_FRAME);
		pHbaDevCB->portStatInfo[i].TxValidFrameCnt       += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_TX_VALID_FRAME);
		pHbaDevCB->portStatInfo[i].TxWordCnt             += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_TX_FRAME_LEN);
		pHbaDevCB->portStatInfo[i].TxRRDYCnt             += hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_TX_RRDY);

	}
	
	return ret;
}

INT32 hbaDevPeriodTask(HBA_DEV_CB *pHbaDevCB)
{
    int ret, tickPeriod;

    ASSERT(pHbaDevCB != NULL);
	
	tickPeriod = sysClkRateGet() * 1;

    while(1)
    {
		hbaDevCheckStatistics(pHbaDevCB);

        if (pHbaDevCB->bToStop)
        {
            break;
        }
		
		semTake(pHbaDevCB->semPeriodSelfCheck, tickPeriod);
    }

    pHbaDevCB->periodFmTaskId = ERROR;

    return 0;
}




/*--------------------SHOW FUNCTION----------------*/

#define HBA_SHOW_DEVCB 		0x00000001
#define HBA_SHOW_LIST 		0x00000002
#define HBA_SHOW_STAT       0x00000003

#define HBA_SHOW_END       0x00000004


int hbaDrvPrintRecvBuffer(LIST_NODE *ptr,  UINT32 opaque)
{
	DMA_BUFFER_NODE_HEADER * pRecvBuf = (DMA_BUFFER_NODE_HEADER*)ptr;

	if (opaque == 3)
	{
		printf("	Buffer %p, bufferIndex %d, DMABuffer %p\n", ptr, pRecvBuf->buffer_index, pRecvBuf->dma_buf_node);
	}
	else
	{
		printf("	Buffer %p, bufferIndex %d \n", ptr, pRecvBuf->buffer_index);
	}
	
	return 0;
}

void hbaDrvShowDeviceList(HBA_DEV_CB * pHbaDevCB, int detail)
{
	int i;
	int count;
	
	/* ����Ӳ������ */
	if (detail == 1 || detail == 0)
	{
		printf("\n  list_recv_hw : \n");
		count = listFuncForeach(&pHbaDevCB->list_hw, hbaDrvPrintRecvBuffer, 3, 0);	
		printf("   --- total: %d  \n\n", count);
	}

	/* ����ͨ�������ն��� */
	if (detail == 2 || detail == 0)
	{
		printf("  list_recv_user : \n");
		count = listFuncForeach(&pHbaDevCB->recv_channel.list_recv, hbaDrvPrintRecvBuffer, 3, 0);
		printf("   --- total: %d  \n\n", count);
	}
}

void hbaDrvShowDeviceCB(HBA_DEV_CB * pHbaDevCB, int detail)
{
	printf("  status   = %d\n", pHbaDevCB->status);
	
	printf("  deviceId = %u\n", pHbaDevCB->DeviceId);
	
	printf("  BusNo    = %u\n", pHbaDevCB->BusNo);
	printf("  DeviceNo = %u\n", pHbaDevCB->DeviceNo);
	printf("  FuncNo   = %u\n", pHbaDevCB->FuncNo);


	printf("  pMembaseCsr   = %p\n", pHbaDevCB->pMembaseCsr);
	printf("  irq           = %d\n", (int)pHbaDevCB->irq);
	 

	printf("  DmaBufBaseAddr   = %p\n", pHbaDevCB->DmaBufBaseAddr);
	printf("  DmaBufHeaderAddr   = %p\n", pHbaDevCB->DmaBufHeaderAddr);

	printf("  pRecvCallBackFunc  = 0x%08x\n", (UINT)pHbaDevCB->pRecvCallbackFunc);

	pHbaDevCB->linkStatus = hbaDevCheckLinkStatus(pHbaDevCB);
	printf("  linkStatus   = 0x%x(%s)\n", pHbaDevCB->linkStatus, (pHbaDevCB->linkStatus==IC_LINK_STATUS_SUCCESS)? "STATUS_SUCCESS":"STATUS_FAILED");
	
	printf("  bToStop   = %d\n", (int)pHbaDevCB->bToStop);
	printf("  recvTaskId   = %d\n", pHbaDevCB->recvTaskId);
	printf("  monitor Status   = %d\n", pHbaDevCB->monitorStatus);

	printf("  bUseInterrupt   = %d\n", (int)pHbaDevCB->bUseInterrupt);
	printf("  bManuCloseInterrupt   = %d\n", (int)pHbaDevCB->bManuCloseInterrupt);

	printf("  recvDmaBufCnt   = %lld\n", pHbaDevCB->stat_recvDmaBufCnt);
	printf("  recvDmaBufValidLen	= %lld\n", pHbaDevCB->stat_recvDmaBufValidLen);

	printf("  qdrBufUnitSize   = %d\n", pHbaDevCB->qdrBufUnitSize);
	printf("  qdrBufUnitNum	= %d\n", pHbaDevCB->qdrBufUnitNum);
	printf("  drvBufUnitSize   = %d\n", pHbaDevCB->drvBufUnitSize);
	printf("  drvBufUnitNum	= %d\n", pHbaDevCB->drvBufUnitNum);
	printf("  DmaBufAddrIntervalSize	= %d\n", pHbaDevCB->DmaBufAddrIntervalSize);

	printf("config fcid = 0x%08x, credit_num = %d ,speed =%d, did_filter_enab =%d,e_d_tov = %d,redundant_enab =%d ,time_out =%d, qdrBufUnitSize=0x%x.\n", pHbaDevCB->devConfig.fcid
		,pHbaDevCB->devConfig.credit_num
		,pHbaDevCB->devConfig.speed 		 
		,pHbaDevCB->devConfig.did_filter_enab 
		,pHbaDevCB->devConfig.e_d_tov		  
		,pHbaDevCB->devConfig.redundant_enab  
		,pHbaDevCB->devConfig.time_out
		,pHbaDevCB->devConfig.qdrBufUnitSize);
	
}


void hbaDrvShowDeviceStat(HBA_DEV_CB * pHbaDevCB, int detail)
{
	int i=0;

	printf("    fpga recv discard Frame Num = %lld \n",   (pHbaDevCB->fpgaStatInfo.recvDiscardFrameNumTotal));

	for (i=0; i<MAX_PORT_NUM; i++)
	{
		printf("    RxUndersizeFrameCnt  [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].RxUndersizeFrameCnt));
		printf("    RxOversizeFrameErrCnt[%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].RxOversizeFrameErrCnt));
		printf("    RxAllFrameCnt        [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].RxAllFrameCnt));
		printf("    RxValidFrameCnt      [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].RxValidFrameCnt));
		printf("    RxWordCnt            [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].RxWordCnt));
		printf("    RxRRDYCnt            [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].RxRRDYCnt));
		printf("    RxKErrCnt            [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].RxKErrCnt));
		
		printf("    LinkChgUp2DownCnt    [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].LinkChgUp2DownCnt));
		
		printf("    TxAllFrameCnt        [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].TxAllFrameCnt));
		printf("    TxValidFrameCnt      [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].TxValidFrameCnt));
		printf("    TxWordCnt            [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].TxWordCnt));
		printf("    TxRRDYCnt            [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].TxRRDYCnt));
		printf("    TxKErrCnt            [%d] = %lld \n", i, (pHbaDevCB->portStatInfo[i].TxKErrCnt));
	}

}



void hbaDrvShowAllHelp()
{
	printf("---------------------------------------.\n");
	printf("hbaDrvShowAll 1 ------------Show device info.\n");
	printf("hbaDrvShowAll 2 ------------Show device recv hwlist & usrlist info.\n");
	printf("hbaDrvShowAll 2,1 ------------Show device recv hwlist info.\n");
	printf("hbaDrvShowAll 2,2 ------------Show device recv usrlist info.\n");	
	printf("hbaDrvShowAll 3 ------------Show device fpga statistics info.\n");
	printf("---------------------------------------.\n");
}

void hbaDrvShowAll(int content, int detail)
{
	int i;
	
	if(content == 0 || content >= HBA_SHOW_END)
	{
		hbaDrvShowAllHelp();
		return;
	}
	
	for (i=0; i<MAX_DEVICE_NUM; i++)
	{
		if (HbaDevCB[i].status != HBA_DEV_STATUS_NONE)
		{
			printf("===========================================\n");	
			printf("[HbaDevCB = 0x%08x]\n", &HbaDevCB[i]);
			
			
			if (content == HBA_SHOW_DEVCB)
			{	
				hbaDrvShowDeviceCB(&HbaDevCB[i], detail);
			}
			else if (content == HBA_SHOW_LIST)
			{
				/* detail ָ���ĸ����С�
					1:����Ӳ������ ��5:����ͨ�������ն��� ��0:���ж���  */

				hbaDrvShowDeviceList(&HbaDevCB[i], detail);
			}
			else if(content == HBA_SHOW_STAT)
			{
				hbaDrvShowDeviceStat(&HbaDevCB[i], detail);
			}

			
		}
	}
}




