#include <vxworks.h>
#include <taskLib.h>
#include "hba.h"
#include "fc_utility.h"
#include "fc_api.h"

/*-------------------- �豸����ӿ� --------------------*/
/* ��FC�ڵ㿨,������Դ */
FCUINT FC_DevOpen(FCHANDLE *hDev, FCUINT DevId)
{
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    if (DevId >= MAX_DEVICE_NUM)
    {
        return FC_PARAMS_INVALID;
    }
    
    pHbaDevCB = hbaDevCreate(DevId);
    if (pHbaDevCB == NULL)
    {
        return FC_FAILURE;
    }
    
    /* ��ȡ�õ��豸������ظ�Ӧ�ò� */
    *hDev = (FCHANDLE)pHbaDevCB;
    return FC_SUCCESS;
}

/* �ر�FC�ڵ㿨���ͷ���Դ */
FCUINT FC_DevClose(FCHANDLE hDev)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevDestroy(pHbaDevCB);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    return FC_SUCCESS;
}


FCUINT FC_DevReset(FCHANDLE hDev)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_PARAMS_INVALID;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevReset(pHbaDevCB);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    return FC_SUCCESS;
}

/* ��ȡFC�ڵ����N�˿�״̬ */
FCUINT FC_DevGetState(FCHANDLE hDev, FCUINT *state)
{
    INT32 ret;
    FCUINT portStatus[2];
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (state == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevGetPortState(pHbaDevCB, portStatus, 2);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    if (portStatus[0] == PORT_LINK_UP || portStatus[1] == PORT_LINK_UP)
    {
        *state = PORT_LINK_UP;
    }
    else
    {
        *state = PORT_LINK_DOWN;
    }
    
    return FC_SUCCESS;
}

/* ��ȡFC�ڵ����N�˿ڰ汾�� */
FCUINT FC_DevGetVersion(FCHANDLE hDev, FCUINT *version)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (version == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevGetVersion(pHbaDevCB, version);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    
    return FC_SUCCESS;
}

/* ����FC�ڵ㿨 */
FCUINT FC_DevConfig(FCHANDLE hDev, PDEV_CONFIG dev_config)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (dev_config == NULL)
    {
        return FC_FAILURE;
    }
    /* ���� 1-16 */
    if (!(dev_config->credit_num > 0 && dev_config->credit_num <= 16))
    {
        return FC_FAILURE;
    }
    /* ���� 0 ����Ӧ 1-1Gbps 2-2Gbps */
    if (!(dev_config->speed == 1 || dev_config->speed == 2))
    {
        return FC_FAILURE;
    }
    /* ���շ���DID����ʹ�� */
    if (!(dev_config->did_filter_enab == 0 || dev_config->did_filter_enab == 1))
    {
        return FC_FAILURE;
    }
    /* e_d_tovʱ�䣬��λ�Ǻ��� */
    if (!(dev_config->e_d_tov > 0 && dev_config->e_d_tov < 3600))
    {
        return FC_FAILURE;
    }
    /* ����ʹ�� 0-��ֹ 1-ʹ�� */
    if (!(dev_config->redundant_enab == 0 || dev_config->redundant_enab == 1))
    {
        return FC_FAILURE;
    }
    /* ��ʱ���ǵ�ʱ�䣬��λ�Ǻ��� */
#if 0
    if (!(dev_config->time_out > 0 && dev_config->time_out < 3600))
    {
        return FC_FAILURE;
    }
#endif

    if (!(dev_config->qdrBufUnitSize >= QDR_BUF_UNIT_SIZE_MIN && dev_config->qdrBufUnitSize <= QDR_BUF_UNIT_SIZE_MAX))
    {
        return FC_FAILURE;
    }	
	
    /* ���ö˿� */
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevConfig(pHbaDevCB, dev_config);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    /* ��ʼ���豸 */
    ret = hbaDevInitialize(pHbaDevCB);
    if (ret != DEV_SUCCESS) 
    {
            return FC_INITIALISE_FAIL;
    }
    /* ʹ�豸���Խ������� */
    hbaDevRun(pHbaDevCB);
    
    return FC_SUCCESS;
}

/* ע���жϽ��ջص����� */
FCUINT FC_DevRegMsgHandler(FCHANDLE hDev, FC_NP_RECV_FUNCPTR func)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (func == NULL)
    {
        return FC_FAILURE;
    }
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevRegMsgHandler(pHbaDevCB, func);
    if (ret == DEV_SUCCESS)
    {
        return FC_SUCCESS;
    }
    return FC_FAILURE;
}

/* ע���жϽ��ջص����� */
FCUINT FC_DevUnRegMsgHandler(FCHANDLE hDev)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevUnRegMsgHandler(pHbaDevCB);
    if (ret == DEV_SUCCESS)
    {
        return FC_SUCCESS;
    }
    return FC_FAILURE;
}

/*-------------------- ͨ�Ź���ӿ� --------------------*/
/* ���������ݵĻ����� */
FCUINT FC_RecvData(FCHANDLE hDev, void **ppBuffer, FCUINT *nLen)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (ppBuffer == NULL)
    {
        return FC_FAILURE;
    }
    if (nLen == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevRecvData(pHbaDevCB, ppBuffer, nLen);
    if (ret == DEV_SUCCESS)
    {
        return FC_SUCCESS;
    }
    if (ret == ASM_RECV_NO_DATA)
    {
        return FC_RECV_NO_DATA;
    }
    return FC_FAILURE;
}

/* �ͷŽ��ջ����� */
FCUINT FC_ReleaseBuf(FCHANDLE hDev, void * pBuffer)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (pBuffer == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    ret = hbaDevReleaseBuf(pHbaDevCB, pBuffer);
    if (ret != DEV_SUCCESS)
    {
        return FC_FAILURE;
    }
    return FC_SUCCESS;
}

/* --------------------ʱͳ����ӿ� --------------------*/

/* ��ȡFC�ڵ����ʱ�� */
FCUINT FC_TM_GetRtc(FCHANDLE hDev, FCTime *time)
{
    HBA_DEV_CB *pHbaDevCB;
    
    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    if (time == NULL)
    {
        return FC_FAILURE;
    }

    pHbaDevCB = (HBA_DEV_CB *)hDev;
    hbaDevGetRtc(pHbaDevCB, time);
    
    return FC_SUCCESS;
}

/* ����FC�ڵ����ʱ�� */
FCUINT FC_TM_SetRtc(FCHANDLE hDev, FCTime *time)
{
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL || time == NULL)
    {
        return FC_FAILURE;
    }

    pHbaDevCB = (HBA_DEV_CB *)hDev;
    hbaDevSetRtc(pHbaDevCB, time);
    return FC_SUCCESS;
}

/*��ʼ���*/
FCUINT FC_DevStartMonitor(FCHANDLE hDev)
{
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    hbaDevStartMonitor(pHbaDevCB);
    
    return FC_SUCCESS;

}

/*ֹͣ���*/
FCUINT FC_DevStopMonitor(FCHANDLE hDev)
{
    HBA_DEV_CB *pHbaDevCB;

    if (hDev == NULL)
    {
        return FC_FAILURE;
    }
    
    pHbaDevCB = (HBA_DEV_CB *)hDev;
    hbaDevStopMonitor(pHbaDevCB);
    
    return FC_SUCCESS;

}

