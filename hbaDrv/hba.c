#include <vxworks.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "endian.h"

#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
    
    #include <pciConfigLib.h>

#endif

#include <cacheLib.h>
#include <taskLib.h>
#include <tickLib.h>
#include <logLib.h>
#include <intLib.h>
#include "hba.h"
#include "list.h"
#include "hw.h"
#include "utils.h"

FC_MEMCPY_FUNCPTR pHbaMemCopyFunc = NULL;

int g_nc_bnc_switch_debug = 0;

int g_intArr[8] = {0x11111111, 0x22222222, 0x44444444, 0x88888888,
                   0x5A5A5A5A, 0xA5A5A5A5, 0xF0F0F0F0, 0x00000000};


#if _HBA_ENDIAN == _HBA_BIG_ENDIAN

    /*����Զ���ȡPCI���ÿռ����ַ*/

#else

    /*С���ֶ�ָ��PCI���ÿռ����ַ*/

    /*�û���ַ��ָ������171��Ҫ��*/
    #define PCI_CFG_BASE_ADDRESS_0    0x10
    #define PCI_CFG_DEV_INT_LINE      0x3C

#endif



#ifdef HBA_INCLUDE_FLASH

#include "hba_flash.h"

#endif

/*�ÿ��ش򿪺� ������ģ����Թ�����ȥ�����ݿ�����������ݷ��͵�������ʣ� ��Ϊ�������ݿ�����ռ�ô���CPU�� 
   ����ʵ������Ӧ�ùص� */
/*#define NO_DATA_MEMCPY*/

extern int abc;

extern BLUE_PRINT gBluePrint[];

#if _HBA_ENDIAN == _HBA_BIG_ENDIAN

#else

    extern STATUS pcieIntConnect(VOIDFUNCPTR * vector, VOIDFUNCPTR routine, int parameter);
    extern STATUS pcieIntDisconnect(VOIDFUNCPTR * vector, VOIDFUNCPTR routine);
    extern STATUS pcieFindDevice(int vendorId, int deviceId, int index, int *pBusNo, int *pDeviceNo, int *pFuncNo);
    extern STATUS pcieConfigInLong(int busNo, int deviceNo, int funcNo, int address, UINT32 * pData);
    extern STATUS pcieConfigInByte(int busNo, int deviceNo, int funcNo, int address, UINT8 * pData);

#endif

HBA_DEV_CB gHbaDevCB[MAX_DEVICE_NUM] = {0};
BOOL bHbaDrvInited = FALSE;
BOOL bUseInterrupt = FALSE;

/* �Ƿ��ж�֪ͨ��������Ϣ���ǣ�true --�ж�֪ͨ�� false --��֪ͨ*/
BOOL bDiscard = FALSE;

 /* FPGA�Ƿ�����Ϣ */
BOOL bUseMsgDiscard  = TRUE;
 
/* ���Ա���*/
#define HBA_DBG_CONFIG  0x00000001
#define HBA_DBG_SEND    0x00000100
#define HBA_DBG_RECV    0x00000200

/* ���Ա���*/
UINT32 g_hbaDebug = 0 ;

INT32 hbaDevStartTasks(HBA_DEV_CB *dc);
STATUS hbaDevIntDiable(HBA_DEV_CB *dc);
STATUS hbaDevIntEnable (HBA_DEV_CB *dc);
STATUS hbaDevHwIntEnable (HBA_DEV_CB *dc);
STATUS hbaDevHwIntDiable(HBA_DEV_CB *dc);
STATUS hbaDevIntConnect (HBA_DEV_CB *dc /*, UINT8 irq*/);
STATUS hbaDevIntDisconnect (HBA_DEV_CB *dc);

/* ======================================================================
 * Function:
 *   This function is used to convert unsigned 64-bit int value to string.
 * Inputs:
 *   qwValue: unsigned 64-bit int value
 *   dwReturn: buffer size
 * Outputs:
 *   lpszReturn: return buffer
 * Returns:
 *   FALSE on failure
 *   TRUE on success
 * ======================================================================
 */
int UInt64toStr(UINT64 qwValue, char *lpszReturn, UINT32 dwReturn)
{
    UINT64 qwQuotient = qwValue;
    UINT32 dwRemainder = 0;
    UINT32 dwIndex = 0, i;
    char szData[256];
    
    if (lpszReturn == NULL) 
        {
            return ERROR;
        }
    *lpszReturn = '\0';


    memset(szData, 0, sizeof(szData));
    if (qwQuotient == 0)
    {
        *lpszReturn = '0';
        return OK;
    }
    

    while (qwQuotient != 0)
    {
        dwRemainder = (UINT32)(qwQuotient % 10);
        qwQuotient = qwQuotient / 10;            
        
        szData[dwIndex] =(char)dwRemainder + '0';
        dwIndex++;        

    }
    szData[dwIndex] = '\0';

    if (dwReturn < dwIndex) 
        {
            return ERROR;
        }
    for (i = 0; i<dwIndex; i++)
    {
        lpszReturn[i] = szData[dwIndex-i-1];
    }
    lpszReturn[dwIndex] = '\0';

    return OK;
}

char g_UInt64String[256];

char *UInt64toStr2(UINT64 qwValue)
{
    memset(g_UInt64String, 0, sizeof(g_UInt64String));
    UInt64toStr(qwValue, g_UInt64String, sizeof(g_UInt64String));
    return g_UInt64String;
}

void printRecvDmaR0R1(RECV_DMA_BUFFER * pRecvDmaBuffer)
{
    R_CTRL *ctrl;
    
    ctrl = (R_CTRL *)pRecvDmaBuffer;
    printf("DmaBufferAddr=0x%p, R0=0x%08x,R1=0x%08x!\n", pRecvDmaBuffer, (int)ctrl->r0.value, (int)ctrl->r1.value);
}

int hbaDrvRegMemCopyFunc(FC_MEMCPY_FUNCPTR func)
{
    #define TEST_COPY_SIZE     1024
    unsigned char src[TEST_COPY_SIZE];
    unsigned char dest[TEST_COPY_SIZE];

    if (func == NULL)
    {
        pHbaMemCopyFunc = NULL;
        return OK;
    }

    /* ����һ���ڴ濽�������ڴ濽����������Ч�� */
    memset(src,  0x12,     TEST_COPY_SIZE);
    memset(dest, 0,     TEST_COPY_SIZE);

    (*func)(dest, src, TEST_COPY_SIZE);

    if (memcmp(dest, src, TEST_COPY_SIZE) != 0)
    {
        printf("Check memory copy function fail. %p\n", func);
        return ERROR;
    }

    pHbaMemCopyFunc = func;
    return OK;
}

void hbaDrvMemCopy(void * dest, void * src, UINT32 size)
{
    if (pHbaMemCopyFunc)
    {
        (*pHbaMemCopyFunc)(dest, src, size);
    }
    else
    {
        memcpy(dest, src, size);
    }
}

/* ���ڴ��ж�̬����һ��IU buffer */
IU_BUFFER * hbaDrvAllocIUBuffer(UINT bufSize)
{
    IU_BUFFER * pIUBuffer = NULL;

    if (bufSize == 0)
    {
        return NULL;
    }
    
    pIUBuffer = (IU_BUFFER * )HBA_MALLOC(sizeof(IU_BUFFER));
    if (pIUBuffer == NULL)
    {
        return NULL;
    }
    
    pIUBuffer->pBuffer = (UINT8 *)HBA_MALLOC(bufSize);
    if (pIUBuffer->pBuffer == NULL)
    {
        HBA_MEM_FREE(pIUBuffer);
        return NULL;
    }

    pIUBuffer->nBufSize = bufSize;
    pIUBuffer->nDataLen = 0;    

    return pIUBuffer;
}    

void hbaDrvFreeIUBuffer(IU_BUFFER * pIUBuffer)
{
    if (pIUBuffer == NULL)
    {
        return;
    }
    if (pIUBuffer->pBuffer != NULL)
    {
        HBA_MEM_FREE(pIUBuffer->pBuffer);
        pIUBuffer->pBuffer = NULL;
    }
    HBA_MEM_FREE(pIUBuffer);
}

/* ����յ������ݰ��Ƿ���SOP��� */
BOOL hbaDrvIsSop(RECV_DMA_BUFFER * pRecvDmaBuffer)
{
    R_CTRL *ctrl, t;

    ctrl = (R_CTRL *)pRecvDmaBuffer;
    t.r0.value = HbaUlongByteSwap(ctrl->r0.value);

    return (t.r0.u.sop == 1);
}

/* ����յ������ݰ��Ƿ���EOP��� */
BOOL hbaDrvIsEop(RECV_DMA_BUFFER * pRecvDmaBuffer)
{
    R_CTRL *ctrl, t;

    ctrl = (R_CTRL *)pRecvDmaBuffer;
    t.r0.value = HbaUlongByteSwap(ctrl->r0.value);

    return (t.r0.u.eop == 1);
}

void hbaDrvSetEop(RECV_DMA_BUFFER * pRecvDmaBuffer, BOOL isEop)
{
    R_CTRL *ctrl, t;

    ctrl = (R_CTRL *)pRecvDmaBuffer;
    
    t.r0.value = HbaUlongByteSwap(ctrl->r0.value);
    t.r0.u.eop = isEop;
    ctrl->r0.value = HbaUlongByteSwap(t.r0.value);
}

/*ȡ�ý��յ������ݵĳ��ȣ�����������ͷ��8���ֽ� */
UINT32 hbaDrvGetRecvBufLen(RECV_DMA_BUFFER *pRecvDmaBuffer)
{
    R_CTRL *c, t;

    c = (R_CTRL *)pRecvDmaBuffer;
    t.r0.value = HbaUlongByteSwap(c->r0.value);
    return t.r0.u.length;
}

void hbaDrvSetRecvBufLen(RECV_DMA_BUFFER *pRecvDmaBuffer, UINT32 dataLen)
{
    R_CTRL *ctrl, t;

    ctrl = (R_CTRL *)pRecvDmaBuffer;

    t.r0.value = HbaUlongByteSwap(ctrl->r0.value);
    t.r0.u.length = dataLen;
    ctrl->r0.value = HbaUlongByteSwap(t.r0.value);
}

BOOL hbaDrvGetRecvBufSeqErr(RECV_DMA_BUFFER *pRecvDmaBuffer)
{
    R_CTRL *ctrl, t;

    ctrl = (R_CTRL *)pRecvDmaBuffer;
    t.r0.value = HbaUlongByteSwap(ctrl->r0.value);

    return (t.r0.u.seq_err == 1);
}

/* ȡ�÷��ͻ�������ݵĳ��ȣ�����������ͷ��8���ֽ� */
int hbaDrvGetSendBufLen(SEND_DMA_BUFFER * pSendDmaBuffer)
{
    W_CTRL *ctrl, t;

    ctrl = (W_CTRL *)pSendDmaBuffer;
    t.w0.value = HbaUlongByteSwap(ctrl->w0.value);

    return (t.w0.u.length - sizeof(W_CTRL));
}

BOOL hbaDrvChkSendCompleted(SEND_DMA_BUFFER * pSendDmaBuffer)
{
    W_CTRL *ctrl, t;
    
    ctrl = (W_CTRL *)pSendDmaBuffer;
    t.w0.value = HbaUlongByteSwap(ctrl->w0.value);
    return (t.w0.u.length == 0);    
}

UINT32 hbaDrvGetChannelIDFromRecvMsg(RECV_DMA_BUFFER * pRecvDmaBuffer)
{
    R_CTRL *ctrl, t;

    ctrl = (R_CTRL *)pRecvDmaBuffer;
    t.r1.value = HbaUlongByteSwap(ctrl->r1.value);

    return t.r1.u.channel_num;
}

/* this function must be called in coreOS before the opening of device */
void hbaDrvInit(void)
{
    /* extern int pciMaxBus; */
    int i;
    
    memset(gHbaDevCB, 0, sizeof(gHbaDevCB));
    for (i=0; i < MAX_DEVICE_NUM; i++)
    {
        gHbaDevCB[i].recvTaskId = ERROR;
        gHbaDevCB[i].sentCheckTaskId = ERROR;
        gHbaDevCB[i].periodSelfCheckTaskId = ERROR;

        /*��ֹ��������֡*/
        gHbaDevCB[i].wdtLoaderPeriodEnab = FC_WDT_LOADER_PERIOD_DISABLE;

#ifdef HBA_INCLUDE_ELS
        
        gHbaDevCB[i].hbaElsCycleCheckTaskId = ERROR;
        gHbaDevCB[i].hbaElsRecvTaskId = ERROR;
        
#endif

        gHbaDevCB[i].status = HBA_DEV_STATUS_NONE;
        
#ifdef AE653_BUILD
        
        /* for vxworks653, taskSpawn cannot be executed successfully in System Call handler, so the tasks is created in init phase */
        hbaDevStartTasks(&gHbaDevCB[i]);
        
#endif
    }

    /* TODO: Ϊʲô��Ҫ���??? */
    /*pciMaxBus=1;*/

    bHbaDrvInited = TRUE;
}

/*static */ 
VOID hbaDevAllocLists(HBA_DEV_CB *dc)
{
    int i;

    if (dc->status     != HBA_DEV_STATUS_NONE)
    {
        return;
    }
    /* ���Ϳ��ж���*/
    listInit(&dc->list_send_idle_share, LIST_PROTECT);
    dc->semSendShareBufferValid = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    
    /* ���տ��ж��� */
    listInit(&dc->list_recv_idle_share, LIST_PROTECT);
    dc->semRecvShareBufferValid = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

    /* */
    for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
    {
        listInit(&dc->list_SentWaitAck[i], LIST_PROTECT);
        listInit(&dc->list_toRecv[i], LIST_PROTECT);
    }

    /* ����ͨ������ */    
    for (i=0; i<MAX_SEND_CHANNEL_NUM; i++)
    {
        listInit(&dc->asmSendChannels[i].list_send_idle_private, LIST_PROTECT);
        
        dc->asmSendChannels[i].semSendBufferValid = semBCreate(SEM_Q_FIFO, SEM_EMPTY);        
    }
    listInit(&dc->rawSendChannel.list_send_idle_private, LIST_PROTECT);
    dc->rawSendChannel.semSendBufferValid = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

    /* ����ͨ������ */    
    for (i=0; i<MAX_RECV_CHANNEL_NUM; i++)
    {
        listInit(&dc->asmRecvChannels[i].list_recved, LIST_PROTECT);
        
        dc->asmRecvChannels[i].semListRecvedLock  = semBCreate(SEM_Q_FIFO, SEM_FULL);    
        dc->asmRecvChannels[i].semRecvBufferValid = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    }
    listInit(&dc->rawRecvChannel.list_recved, LIST_PROTECT);
    dc->rawRecvChannel.semRecvBufferValid = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

    for (i=0; i<MAX_RECV_CHANNEL_NUM; i++)
    {
        listInit(&dc->asmRecvChannels[i].list_currentIU, LIST_PROTECT);
    }
    
}


/*static */ 
VOID hbaDevFreeLists(HBA_DEV_CB *dc)
{
    int i;    

    if (dc->status     != HBA_DEV_STATUS_CREATED)
    {
        return;
    }

    /* ���Ϳ��ж���*/
    listExit(&dc->list_send_idle_share);
    if (dc->semSendShareBufferValid)
    {
        semDelete(dc->semSendShareBufferValid);
        dc->semSendShareBufferValid = NULL;
    }
        
    /* ���տ��ж��� */
    listExit(&dc->list_recv_idle_share);
    if (dc->semRecvShareBufferValid)
    {
        semDelete(dc->semRecvShareBufferValid);
        dc->semRecvShareBufferValid = NULL;
    }

    /* ��FPGA���ͺͽ����йصĶ��� */
    for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
    {
        listExit(&dc->list_SentWaitAck[i]);
        listExit(&dc->list_toRecv[i]);
    }

    /* ����ͨ������ */    
    for (i=0; i<MAX_SEND_CHANNEL_NUM; i++)
    {
        listExit(&dc->asmSendChannels[i].list_send_idle_private);

        if (dc->asmSendChannels[i].semSendBufferValid)
        {
            semDelete(dc->asmSendChannels[i].semSendBufferValid);
            dc->asmSendChannels[i].semSendBufferValid = NULL;
        }
    }
    listExit(&dc->rawSendChannel.list_send_idle_private);
    if (dc->rawSendChannel.semSendBufferValid)
    {
        semDelete(dc->rawSendChannel.semSendBufferValid);
        dc->rawSendChannel.semSendBufferValid = NULL;
    }
    

    /* ����ͨ������ */    
    for (i=0; i<MAX_RECV_CHANNEL_NUM; i++)
    {
        listExit(&dc->asmRecvChannels[i].list_recved);

        if (dc->asmRecvChannels[i].semRecvBufferValid)
        {
            semDelete(dc->asmRecvChannels[i].semListRecvedLock);
            dc->asmRecvChannels[i].semListRecvedLock = NULL;
            
            semDelete(dc->asmRecvChannels[i].semRecvBufferValid);
            dc->asmRecvChannels[i].semRecvBufferValid = NULL;
        }
    }
    listExit(&dc->rawRecvChannel.list_recved);
    if (dc->rawRecvChannel.semRecvBufferValid)
    {
        semDelete(dc->rawRecvChannel.semRecvBufferValid);
        dc->rawRecvChannel.semRecvBufferValid = NULL;
    }

    for (i=0; i<MAX_RECV_CHANNEL_NUM; i++)
    {
        listExit(&dc->asmRecvChannels[i].list_currentIU);
    }    
    
}

/*static */ 
int hbaDevAllocDmaBuffers(HBA_DEV_CB *dc)
{
    int i;
    int p;
    UINT8 * pSendDmaBufBaseAddr = NULL;
    UINT8 * pRecvDmaBufBaseAddr = NULL;
    UINT8 * pSendBufBaseAddr = NULL;
    UINT8 * pRecvBufBaseAddr = NULL;
    SEND_BUFFER * pSendBuf = NULL;
    RECV_BUFFER * pRecvBuf = NULL;    
    UINT8 * pDmaBuf = NULL;
    UINT32  allRecvDmaSize = 0;
    UINT32  allSendDmaSize = 0;

    if (dc->status != HBA_DEV_STATUS_CREATED)
    {
        /* ״̬��Ч */
        return ERROR;
    }

    
    /* ���䷢�ͺͽ��ջ��� */
    allSendDmaSize = (MAX_SEND_BUFFER_NUM * (MAX_SEND_BUFER_LEN + 1024) + 1024);
    pSendDmaBufBaseAddr = (UINT8 *)DMA_BUF_MALLOC(allSendDmaSize);

    /*printf("pSendDmaBufBaseAddr= %p, to %p, size = %d\n", 
        pSendDmaBufBaseAddr, 
        pSendDmaBufBaseAddr + allSendDmaSize, 
        allSendDmaSize);*/
    
    allRecvDmaSize = (MAX_RECV_BUFFER_NUM_P0 * (MAX_RECV_BUFER_LEN_P0 + 1024)) +
                     (MAX_RECV_BUFFER_NUM_P1 * (MAX_RECV_BUFER_LEN_P1 + 1024)) +
                     (MAX_RECV_BUFFER_NUM_P2 * (MAX_RECV_BUFER_LEN_P2 + 1024)) +
                     (MAX_RECV_BUFFER_NUM_P3 * (MAX_RECV_BUFER_LEN_P3 + 1024)) +
                     1024;
    
    pRecvDmaBufBaseAddr = (UINT8 *)DMA_BUF_MALLOC(allRecvDmaSize);

    
    /*printf("pRecvDmaBufBaseAddr = %p, to %p, size = %d\n", 
        pRecvDmaBufBaseAddr, 
        pRecvDmaBufBaseAddr + allRecvDmaSize, 
        allRecvDmaSize);*/
    
    /*
    pSendBufBaseAddr = (UINT8 *)malloc(MAX_SEND_BUFFER_NUM * sizeof(SEND_BUFFER));
    pRecvBufBaseAddr = (UINT8 *)malloc(MAX_RECV_BUFFER_NUM * sizeof(RECV_BUFFER));
    */
    pSendBufBaseAddr = (UINT8 *)HBA_MALLOC(MAX_SEND_BUFFER_NUM * sizeof(SEND_BUFFER));
    pRecvBufBaseAddr = (UINT8 *)HBA_MALLOC(MAX_RECV_BUFFER_NUM * sizeof(RECV_BUFFER));

    if ((pSendDmaBufBaseAddr == NULL) ||
        (pRecvDmaBufBaseAddr == NULL) ||
        (pSendBufBaseAddr == NULL) ||
        (pRecvBufBaseAddr == NULL))
    {
        if (pSendDmaBufBaseAddr != NULL)
        {
            DMA_BUF_FREE(pSendDmaBufBaseAddr);
            pSendDmaBufBaseAddr = NULL;
        }

        if (pRecvDmaBufBaseAddr != NULL)
        {
            DMA_BUF_FREE(pRecvDmaBufBaseAddr);
            pRecvDmaBufBaseAddr = NULL;
        }

        if (pSendBufBaseAddr != NULL)
        {
            HBA_MEM_FREE(pSendBufBaseAddr);
            pSendBufBaseAddr = NULL;
        }

        if (pRecvBufBaseAddr != NULL)
        {
            HBA_MEM_FREE(pRecvBufBaseAddr);
            pRecvBufBaseAddr = NULL;
        }

        /*printf("hbaDevInitBuffer:  malloc memory fail. \n");*/
        return ERROR;
        
    }

    dc->pSendDmaBufBaseAddr = pSendDmaBufBaseAddr;
    dc->pRecvDmaBufBaseAddr = pRecvDmaBufBaseAddr;
    dc->pSendBufBaseAddr = pSendBufBaseAddr;
    dc->pRecvBufBaseAddr = pRecvBufBaseAddr;

    hbaDevClearSendBufferInFPGA(dc);
    hbaDevClearRecvBufferInFPGA(dc);

    /* ׼�����ͻ���, ȫ���ŵ����ж��� */
    pSendBuf = (SEND_BUFFER * )pSendBufBaseAddr;
    pDmaBuf = (UINT8 * )((((UINT32)(pSendDmaBufBaseAddr)) + 1024 -1) & (~(1024-1)));    /* 1024 byte align */
    for (i=0; i<MAX_SEND_BUFFER_NUM; i++)
    {
        SEND_DMA_BUFFER * pSendDmaBuf = NULL;
        SEND_DMA_BUFFER_HEADER * pSendDmaBufHeader = NULL;

        pSendDmaBuf = (SEND_DMA_BUFFER * )(pDmaBuf + 1024);        
        pSendDmaBufHeader = (SEND_DMA_BUFFER_HEADER * )((UINT8 *)pSendDmaBuf - sizeof(SEND_DMA_BUFFER_HEADER));

#if 0    /* �ָ���������ض��������������Ƿ�������Խ����� */
        
        pData = (UINT32 * )pDmaBuf;
        for (j = 0; j<256; j++)
        {
            pData[j] = 0xCAFEBEEF;
        }
        
#endif

        pSendDmaBufHeader->signature = SEND_BUFFER_SIGNATURE;
        pSendDmaBufHeader->pSendBuffer = pSendBuf;

        /* ����w0��w1Ϊ��ʼֵ */
        pSendDmaBuf->w0 = 0;
        pSendDmaBuf->w1 = 0;

        HBA_CACHE_FLUSH(pSendDmaBuf, sizeof(W_CTRL));

        hbaDevAddSendBufferToFPGA(dc, pSendDmaBuf, i);
        
        pSendBuf->bufferIndex = i;
        pSendBuf->allocatee = SEND_BUFFER_ALLOCATEE_SHARE;
        pSendBuf->ch = INVALID_CHANNEL_NO;
        pSendBuf->pBuffer = pSendDmaBuf;

        listAddNodeToListTail(pSendBuf, &dc->list_send_idle_share);
        
        /* 16 byte use as �ֽ��������������һЩ�ض������ݣ�������������Ƿ���Խ��д�� */
        pDmaBuf = pDmaBuf + MAX_SEND_BUFER_LEN + 1024;
        pSendBuf ++;
    }

    /* printf("hbaDevInitBuffer:  pRecvBufBaseAddr from %p to %p. \n", 
                pRecvDmaBufBaseAddr, 
                pRecvDmaBufBaseAddr + allRecvDmaSize); 
    */
    /* ׼�����ջ���, ȫ���ŵ����ж��� */
    pRecvBuf = (RECV_BUFFER * )pRecvBufBaseAddr;
    pDmaBuf = (UINT8 * )((((UINT32)pRecvDmaBufBaseAddr) + 1024 -1) & (~(1024-1)));    /* 1024 byte align */
    
    /* �ӽ��տ��ж����з��䲻ͬ���ȼ���buffer���ŵ���ͬ���ȼ����Ӧ�Ľ��ն����� */
    for (p = 0; p < MAX_PRIORITY_LEVEL_NUM; p++)
    {
        int bufCount = 0;
        int bufSize = 0;

        if (p == PRIORITY_LEVEL_0)
        {
            bufCount = MAX_RECV_BUFFER_NUM_P0;
            bufSize  = MAX_RECV_BUFER_LEN_P0;
        }
        else if (p == PRIORITY_LEVEL_1)
        {
            bufCount = MAX_RECV_BUFFER_NUM_P1;
            bufSize  = MAX_RECV_BUFER_LEN_P1;
        }
        else if (p == PRIORITY_LEVEL_2)
        {
            bufCount = MAX_RECV_BUFFER_NUM_P2;
            bufSize  = MAX_RECV_BUFER_LEN_P2;
        }
        else /*if (p == PRIORITY_LEVEL_3)*/
        {
            bufCount = MAX_RECV_BUFFER_NUM_P3;
            bufSize  = MAX_RECV_BUFER_LEN_P3;
        }

        /* printf("hbaDevInitBuffer:  Recv Buffer, priority =%d. \n", p); */
        
        /* ���ý���buffer����С*/
        hwRegisterRxDmaBufSize((REG_HW *)dc->pMembaseCsr, p, bufSize);
        
        for (i=0; i<bufCount; i++)
        {
            RECV_DMA_BUFFER * pRecvDmaBuf = NULL;
            RECV_DMA_BUFFER_HEADER * pRecvDmaBufHeader = NULL;
            
            pRecvDmaBuf = (RECV_DMA_BUFFER * )(pDmaBuf + 1024);
            pRecvDmaBufHeader = (RECV_DMA_BUFFER_HEADER * )((UINT8 *)pRecvDmaBuf - sizeof(RECV_DMA_BUFFER_HEADER));

#if 0    /* �ָ���������ض��������������Ƿ�������Խ����� */
            
            pData = (UINT32 * )pDmaBuf;
            for (j = 0; j<256; j++)
            {
                pData[j] = 0xDEADBEEF;
            }
            
#endif
            pRecvDmaBufHeader->signature = RECV_BUFFER_SIGNATURE;
            pRecvDmaBufHeader->pRecvBuffer = pRecvBuf;

            
            /* ����r0��r1Ϊ��ʼֵ */
            pRecvDmaBuf->r0 = 0;
            pRecvDmaBuf->r1 = 0;

            HBA_CACHE_FLUSH(pRecvDmaBuf, sizeof(R_CTRL));
            
            
            pRecvBuf->pBuffer = pRecvDmaBuf;
            pRecvBuf->bufferSize = bufSize;
            pRecvBuf->bufferIndex = i;
            pRecvBuf->priority = p;

            /* printf("hbaDevInitBuffer:  i = %d. pRecvBuf=%p, pRecvDmaBuf=%p\n", i, pRecvBuf, pRecvDmaBuf); */
            
            /* �Ǽǽ���buffer */
            hbaDevAddRecvBufferToFPGA(dc, pRecvBuf->pBuffer, p, i);

            /* ѹ���� */
            hbaDevAddRecvBufferToFPGARecvFifo(dc, pRecvBuf);

            listAddNodeToListTail(pRecvBuf, &dc->list_toRecv[p]);

            /* 16 byte use as �ֽ��������������һЩ�ض������ݣ�������������Ƿ���Խ��д�� */
            pDmaBuf = pDmaBuf + bufSize + 1024;    
            pRecvBuf ++;
        }
    }

    
    return OK;
}

void hbaDevFreeDmaBuffers(HBA_DEV_CB *dc)
{
    
    if (dc->pSendDmaBufBaseAddr != NULL)
    {
        DMA_BUF_FREE(dc->pSendDmaBufBaseAddr);
        dc->pSendDmaBufBaseAddr = NULL;
    }

    if (dc->pRecvDmaBufBaseAddr != NULL)
    {
        DMA_BUF_FREE(dc->pRecvDmaBufBaseAddr);
        dc->pRecvDmaBufBaseAddr = NULL;
    }

    if (dc->pSendBufBaseAddr != NULL)
    {
        HBA_MEM_FREE(dc->pSendBufBaseAddr);
        dc->pSendBufBaseAddr = NULL;
    }

    if (dc->pRecvBufBaseAddr != NULL)
    {
        HBA_MEM_FREE(dc->pRecvBufBaseAddr);
        dc->pRecvBufBaseAddr = NULL;
    }
}



/* ע��RAWģʽ��ͨ�� */
STATUS hbaDevRegisterRawChannels(HBA_DEV_CB *dc)
{
    int ret, direct, mode, index, priority, asmid, fcid, msg_recover, switch_sid;
    REG_HW *reg_hw;
    
    /* RAWģʽ�ķ���ͨ��ʼ���ǿ��ŵģ��������� ����ֻ���ý���ͨ�� */
    reg_hw = (REG_HW *)dc->pMembaseCsr;
    direct = HOST_READ;
    mode = RAW_MODE;
    index = 0;
    priority = PRIORITY_LEVEL_RAW_MSG;
    asmid = 0;
    fcid = 0;
    msg_recover = 0;

    switch_sid = 0; /* ��config�ļ���ȡ�� */
    hwInitSwitchId(reg_hw, switch_sid);
    hwInitElsChannel(reg_hw);
    ret = hwCreateChannel(reg_hw, direct, mode, index, priority, asmid, fcid, msg_recover);
    if (ret)
    {
        return ERROR;
    }

    return OK;
}

/* ע��BLOCKģʽ��ͨ�� */
STATUS hbaDevRegisterAsmChannels(HBA_DEV_CB *dc, UINT sendAsmMsgIDCount, FC_MSG_SEND_ITEM * pSendAsmCfg, UINT recvAsmMsgIDCount, FC_MSG_RECV_ITEM * pRecvAsmCfg)
{
    int ret, i, direct, mode, index, priority, asmid, fcid, msg_recover, sid;
    int sendAsmChannelCount = 0;
    int recvAsmChannelCount = 0;
    
    for (i = 0; i < sendAsmMsgIDCount; i++)
    {
        if (pSendAsmCfg[i].msg_priority > PRIORITY_LEVEL_3)    /* 2018-4-4: modified by huilin */
        { 
            /*printf("Send Channel : msgId=%u, invalid msg priority %d\n", 
                    pSendAsmCfg[i].msg_id, 
                    pSendAsmCfg[i].msg_priority);*/
            
            pSendAsmCfg[i].msg_priority = PRIORITY_LEVEL_HIGH_ASM_MSG;
        }

        if (g_hbaDebug & HBA_DBG_CONFIG)
        {
            printf("Send Channel : msgId=%u,  msg_priority=%d, msg_dst_id=0x%x\n", 
                pSendAsmCfg[i].msg_id, 
                pSendAsmCfg[i].msg_priority,
                pSendAsmCfg[i].msg_dst_id);
        }
        
        /* create channel */
        direct = HOST_WRITE;
        mode = ASM_MODE;
        index = i;
        
        asmid     = pSendAsmCfg[i].msg_id;
        priority = pSendAsmCfg[i].msg_priority;        
        fcid     = pSendAsmCfg[i].msg_dst_id;
        sid     =  pSendAsmCfg[i].msg_src_id;
        msg_recover = 0;        
        
        ret = hwCreateChannel((REG_HW *)dc->pMembaseCsr, direct, mode, index, priority, asmid, fcid, msg_recover);
        if (ret)
        {
            /*printf("hwCreateChannel fail for send msgID %d\n", pSendAsmCfg[i].msg_id);*/
            break;
        }

        /* ��¼ͨ������ */
        dc->asmSendChannels[sendAsmChannelCount].msgId = pSendAsmCfg[i].msg_id;
        dc->asmSendChannels[sendAsmChannelCount].priority = pSendAsmCfg[i].msg_priority;
        dc->asmSendChannels[sendAsmChannelCount].did = pSendAsmCfg[i].msg_dst_id;
        /*dc->asmSendChannels[sendAsmChannelCount].bIsStream = ((pSendAsmCfg[i].msg_type==4)? TRUE:FALSE);*/
        if (pSendAsmCfg[i].msg_type == MSG_TYPE_STREAM_MSG)
        {
            dc->asmSendChannels[sendAsmChannelCount].bIsStream = TRUE;
        }
        else
        {
            dc->asmSendChannels[sendAsmChannelCount].bIsStream = FALSE;
        }

        sendAsmChannelCount++;        
    }
    
    dc->asmSendChannelCount = sendAsmChannelCount;
    
    if (g_hbaDebug & HBA_DBG_CONFIG)
    {
        printf("Send Channel count = %u\n", dc->asmSendChannelCount);
    }    
    for (i = 0; i < recvAsmMsgIDCount; i++)
    {
        /* create channel */
        direct = HOST_READ;
        mode = ASM_MODE;
        index = i;

        if (pRecvAsmCfg[i].msg_type == MSG_TYPE_STREAM_MSG) /* ����Ϣ */
        {
            priority = PRIORITY_LEVEL_STREAM_MSG;
        }
        else if (pRecvAsmCfg[i].msg_type == MSG_TYPE_URGENCY_MSG) /* ������Ϣ */
        {
            priority = PRIORITY_LEVEL_URGENCY_MSG;
        }
         else /* ������Ϣ */
        {
            priority = PRIORITY_LEVEL_EVENT_MSG;
        }
        
        asmid = pRecvAsmCfg[i].msg_id;
        fcid = pRecvAsmCfg[i].msg_src_id;
        msg_recover = pRecvAsmCfg[i].msg_recover;

        if (g_hbaDebug & HBA_DBG_CONFIG)
        {
            printf("Recv Channel : msgId=%u,  msg_type=%d,  msg_src_id=0x%0x\n", 
                pRecvAsmCfg[i].msg_id, 
                pRecvAsmCfg[i].msg_type,
                pRecvAsmCfg[i].msg_src_id);
        }
        ret = hwCreateChannel((REG_HW *)dc->pMembaseCsr, direct, mode, index, priority, asmid, fcid, msg_recover);
        if (ret)
        {
            /*printf("hwCreateChannel fail for recv msgID %d\n", pRecvAsmCfg[i].msg_id);*/
            break;
        }

        /* ��¼ͨ������ */
        dc->asmRecvChannels[recvAsmChannelCount].msgId = pRecvAsmCfg[i].msg_id;
        dc->asmRecvChannels[recvAsmChannelCount].sid = pRecvAsmCfg[i].msg_src_id;
        dc->asmRecvChannels[recvAsmChannelCount].priority = priority;
        dc->asmRecvChannels[recvAsmChannelCount].maxIUSize = pRecvAsmCfg[i].msg_max_len;
        
#if 0
        
        dc->asmRecvChannels[recvAsmChannelCount].msg_recv_type = pRecvAsmCfg[i].msg_recv_type;
#endif

        /*dc->asmRecvChannels[recvAsmChannelCount].bIsStream =((pRecvAsmCfg[i].msg_type==MSG_TYPE_STREAM_MSG)? TRUE:FALSE);*/
        if ( pRecvAsmCfg[i].msg_type==MSG_TYPE_STREAM_MSG )
        {
            dc->asmRecvChannels[recvAsmChannelCount].bIsStream = TRUE;
        }
        else
        {
            dc->asmRecvChannels[recvAsmChannelCount].bIsStream = FALSE;
        }
        /*dc->asmRecvChannels[recvAsmChannelCount].nMaxReservedIUNum = ((pRecvAsmCfg[i].msg_type==MSG_TYPE_STREAM_MSG)? 
                                                                    MAX_PRESERVE_STRM_IU_COUNT : MAX_PRESERVE_MSG_COUNT);*/
        if ( pRecvAsmCfg[i].msg_type==MSG_TYPE_STREAM_MSG )
        {
            dc->asmRecvChannels[recvAsmChannelCount].nMaxReservedIUNum = MAX_PRESERVE_STRM_IU_COUNT;
        }
        else
        {
            dc->asmRecvChannels[recvAsmChannelCount].nMaxReservedIUNum = MAX_PRESERVE_MSG_COUNT;
        }
#ifdef USE_MSG_COVER
        
        /*dc->asmRecvChannels[recvAsmChannelCount].bMsgCover = (msg_recover>0)? TRUE:FALSE;*/    /* ֧����Ϣ���� */
        if ( msg_recover>0 )    
        {
            dc->asmRecvChannels[recvAsmChannelCount].bMsgCover = TRUE;
        }
        else
        {
            dc->asmRecvChannels[recvAsmChannelCount].bMsgCover = FALSE;
        }
        
#endif

        
        dc->asmRecvChannels[recvAsmChannelCount].tickSOP = 0;
        dc->asmRecvChannels[recvAsmChannelCount].nIULen = 0;
        dc->asmRecvChannels[recvAsmChannelCount].nIUCount = 0;
        
        
        recvAsmChannelCount ++;
    }
    
    dc->asmRecvChannelCount = recvAsmChannelCount;

    if (g_hbaDebug & HBA_DBG_CONFIG)
    {
        printf("Recv Channel count = %u\n", dc->asmRecvChannelCount);
    }
    return OK;
}

/*�Ƿ���Ч��FCID*/


/*���FCID ����ֵ 0-�Ƿ�FCID 1-���� 2-�ಥ 3-�㲥*/
UINT32 HbaDevGetTypeByFcid(unsigned int fcid)
{
    if (fcid == 0xFFFFFF)
    {
        /*�㲥*/
        return FCID_TYPE_BROADCAST;
    }
    if (fcid >= FCID_MULTICAST_MIN && fcid <= FCID_MULTICAST_MAX)
    {
        /*�鲥*/
        return FCID_TYPE_MULTICAST;
    }
    if (fcid > 0 && fcid < FCID_SINGLECASE_MAX)
    {
        /*����*/
        return FCID_TYPE_SINGLE;
    }
    /*�Ƿ�FCID*/
    return FCID_TYPE_INVALID;
}


BOOL HbaDevIsValidFcid(UINT32 fcid)
{
    return (HbaDevGetTypeByFcid(fcid) == FCID_TYPE_INVALID ? FALSE : TRUE);
}


/*�����ͼ����ȷ��*/
UINT32 hbaDevCheckConfig(HBA_DEV_CB *dc)
{
    FC_PORT_CONFIG *pc;
    FC_MSG_SEND_ITEM *send_item, *si;
    FC_MSG_RECV_ITEM *recv_item, *ri;
    UINT32 send_item_count = 0, recv_item_count = 0;
    FCUINT wdtSendPeriod = 0, wdtCheckPeriod = 0;
    INT32 i, j;
    
    
     ASSERT(dc != NULL);

    pc = &dc->configBlock.port_config;
    send_item = &dc->configBlock.send_item[0];
    recv_item = &dc->configBlock.recv_item[0];
    

    if (!HbaDevIsValidFcid(pc->port_id))
    {
        return FC_INVALID_FCID;
    }

    /*WDT��ʱ���� �� WDT�������� ����Ӧ��С��10ms��������ڱ�����ڼ������� */
    wdtSendPeriod  = pc->wdt_loader_period; /* WDT�������� */
    wdtCheckPeriod = pc->nc_wdt_period;     /* WDT������� */
    if (wdtCheckPeriod < 10 || wdtSendPeriod < 10 || (wdtCheckPeriod <= wdtSendPeriod))
    {        
        return FC_INVALID_WDT_PERIOD;
    }

    
    /*��������ɫ*/
    if ((pc->role != ROLE_NC) && (pc->role != ROLE_BNC) && (pc->role != ROLE_NRT))
    {
        return FC_INVALID_NM_ROLE;
    }
    
    /*ʱ��ͬ����ɫ*/
    if ((pc->clk_sync_role != CLK_SYNC_ROLE_SERVER_MASTER) && 
        (pc->clk_sync_role != CLK_SYNC_ROLE_CLIENT))
    {
        return FC_INVALID_TM_ROLE;
    }

    
    /*ʱ��ͬ������ ��λ���� һ������Ϊ50ms*/
    if (pc->clk_sync_period == 0)
    {
        return FC_INVALID_CLK_SYNC_PERIOD;
    }


    /* ����ͨ���ͷ���ͨ����Ŀ */
    send_item_count = pc->block_txmsg_num + pc->nonblock_txmsg_num;
    recv_item_count = pc->block_rxmsg_num + pc->nonblock_rxmsg_num;

    if (send_item_count == 0)
    {
        if (g_hbaDebug & HBA_DBG_CONFIG)
            printf("hbaDevCheckConfig : send channel number is 0.\n"); /* �澯�����������ô���Ҳ�������������� */
    }
    if (send_item_count > MAX_SEND_CHANNEL_NUM)
    {
        if (g_hbaDebug & HBA_DBG_CONFIG)
            printf("hbaDevCheckConfig : invalid send channel number is %d.\n", send_item_count); 
        return FC_SEND_CHANNEL_BEYOND;
    }

    if (recv_item_count == 0)
    {
        if (g_hbaDebug & HBA_DBG_CONFIG)
            printf("hbaDevCheckConfig : recv channel number is 0.\n"); /* �澯�����������ô���Ҳ��������������*/
    }

    
    if (recv_item_count > MAX_RECV_CHANNEL_NUM)
    {
        if (g_hbaDebug & HBA_DBG_CONFIG)
            printf("hbaDevCheckConfig : invalid recv channel number is %d.\n", recv_item_count);
        return FC_RECV_CHANNEL_BEYOND;
    }

    /* ����ͨ������ */
    for (i = 0; i < send_item_count; ++i)
    {
        si = &send_item[i];
        
        /*������Ϣ����*/
        if ((si->msg_type != MSG_TYPE_URGENCY_MSG) && 
            (si->msg_type != MSG_TYPE_EVENT_MSG) && 
            (si->msg_type != MSG_TYPE_STREAM_MSG))
        {
            printf("FC_INVALID_TX_MSG_TYPE: i=%d, msg_type = %d\n", i, si->msg_type);
            return FC_INVALID_TX_MSG_TYPE;
        }

        /*������Ϣ����*/
        if ((si->msg_priority != PRIORITY_LEVEL_0) && 
            (si->msg_priority != PRIORITY_LEVEL_1) && 
            (si->msg_priority != PRIORITY_LEVEL_2) && 
            (si->msg_priority != PRIORITY_LEVEL_3))
        {
            printf("FC_INVALID_TX_MSG_PRIORITY: i=%d, msg_priority = %d\n", i, si->msg_priority);
            return FC_INVALID_TX_MSG_PRIORITY;
        }
        
        /*����ԴFCID*/
        if (!HbaDevIsValidFcid(si->msg_src_id))
        {
            printf("FC_INVALID_TX_MSG_SRC_ID: i=%d, msg_src_id = 0x%x\n", i, si->msg_src_id);
            return FC_INVALID_TX_MSG_SRC_ID;
        }
        /*����Ŀ��FCID*/
        if (!HbaDevIsValidFcid(si->msg_dst_id))
        {
            printf("FC_INVALID_TX_MSG_DST_ID: i=%d, msg_dst_id = 0x%x\n", i, si->msg_dst_id);
            return FC_INVALID_TX_MSG_DST_ID;
        }        
        
    }

    /* ����ͨ�� */
    for (i = 0; i < recv_item_count; ++i)
    {
        ri = &recv_item[i];
        /*���ճ���*/
        if (ri->msg_max_len == 0 || ri->msg_max_len > FC_ASM_IU_LENGTH_MAX)
        {
            return FC_RX_MSG_MAX_LEN_BEYOND;
        }
        /*������Ϣ����*/
        if ((ri->msg_type != MSG_TYPE_URGENCY_MSG) && 
            (ri->msg_type != MSG_TYPE_EVENT_MSG) && 
            (ri->msg_type != MSG_TYPE_STREAM_MSG))
        {
            return FC_INVALID_RX_MSG_TYPE;
        }
        
        /*����ԴFCID*/
        if (!HbaDevIsValidFcid(ri->msg_src_id))
        {
            return FC_INVALID_RX_MSG_SRC_ID;
        }
        /*������Ϣ���Ǳ�־*/
        if ((ri->msg_recover != MSG_NO_RECOVER) && 
            (ri->msg_recover != MSG_RECOVER))
        {
            return FC_INVALID_RX_MSG_RECOVER;
        }
    }
    

    return FC_SUCCESS;
}
INT32 hbaDevLoadConfig(HBA_DEV_CB *dc)
{
    int ret = DEV_SUCCESS;
    
    ASSERT(dc);

    if (dc->status != HBA_DEV_STATUS_CREATED)
    {
        return DEV_INVALID_OP;
    }
    
    if (dc->configMode == FC_CONFIG_MODE_PROJECT)
    {
        /* ����ģʽ */
        hbaDevInitConfigDataForEnginMode(dc);
    } 
    else 
    {
        /* FLASH ģʽ */
        ret = hbaDevInitConfigDataForFlashMode(dc);
    }

    return ret;
}

/*
����:
   bForceOffLine: ָ���Ƿ�ִ�� offline-online���� 
*/
INT32 hbaDevReset(HBA_DEV_CB *dc, BOOL bForceOffLine)
{
    int i;

    ASSERT(dc);

    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }
    /* �����û���������ݣ���ֱ�ӷ��سɹ� */
    if (dc->status == HBA_DEV_STATUS_CREATED)
    {
        return DEV_SUCCESS;
    }

    /* ��λ֮ǰ����Ҫ��ֹͣ */    
    if (dc->status == HBA_DEV_STATUS_STARTED)
    {
        
        hbaDevStop(dc, bForceOffLine);
    }
    else
    {
        /* ֮ǰû�б�start������ͨ��hwResetFpga()�����offline��online���� */
        /*hwResetFpga((REG_HW *)dc->pMembaseCsr, (bForceOffLine? FORCE_OFFLINE : NO_FORCE_OFFLINE ));*/
        if ( bForceOffLine > 0 )
        {
            hwResetFpga((REG_HW *)dc->pMembaseCsr, FORCE_OFFLINE);
        }
        else
        {
            hwResetFpga((REG_HW *)dc->pMembaseCsr, NO_FORCE_OFFLINE);
        }
    }

    /* ���ͳ������ */
    hbaDevClearDeviceStat(dc);


    /* ���ELS�й����� */
#if 0 /* Huilin */        
    dc->recvE1_0203Flag = 0;
#else
    /*����������NC�ڵ��FCIDΪ��Ч��FCID*/
    dc->ncFcid = FC_FCID_EMPTY;

    /*ASM���ͽ��տ��� 0-��ֹASM���ͽ��� 1-����ASM���ͽ���*/
    dc->asmRunControl = FC_ASM_RUN_DISABLE;

    /*����NC�ڵ�ȴ������б��NC�ڵ㷢������֡��������*/
    dc->wdtInitCounter = 2;
#endif

    memset(dc->elsKeyRecvList,0, sizeof(dc->elsKeyRecvList));
    

    /* 1.----������еĶ����еĽڵ�*/
    listEmptyList(&dc->list_send_idle_share);
    listEmptyList(&dc->list_recv_idle_share);

    /* ��FPGA���ͺͽ����йصĶ��� */
    for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
    {
        listEmptyList(&dc->list_SentWaitAck[i]);
        listEmptyList(&dc->list_toRecv[i]);
    }

    /* ����ͨ������ */    
    for (i=0; i<MAX_SEND_CHANNEL_NUM; i++)
    {
        listEmptyList(&dc->asmSendChannels[i].list_send_idle_private);
    }
    listEmptyList(&dc->rawSendChannel.list_send_idle_private);

    /* ����ͨ������ */    
    for (i=0; i<MAX_RECV_CHANNEL_NUM; i++)
    {
        listEmptyList(&dc->asmRecvChannels[i].list_recved);
    }
    listEmptyList(&dc->rawRecvChannel.list_recved);


    /* 2.----�������ASM ���� */
    /* ��շ������� */
    for (i=0; i<dc->asmSendChannelCount; i++)
    {
        dc->asmSendChannels[i].msgId = 0;
        dc->asmSendChannels[i].priority = 0;        
    }
    dc->asmSendChannelCount = 0;


    for (i=0; i<dc->asmRecvChannelCount; i++)
    {
        dc->asmRecvChannels[i].msgId = 0;
        dc->asmRecvChannels[i].priority = 0;
    }
    dc->asmRecvChannelCount = 0;

    if (bForceOffLine)
    {
        /* ��ջص�����*/
        dc->pRecvCallBackFunc = NULL;
        dc->pIntCallbackFunc = NULL;
    }
    
    /* 3.---- �ͷ����е��ڴ� */
    hbaDevFreeDmaBuffers(dc);

    dc->status = HBA_DEV_STATUS_CREATED;

    return DEV_SUCCESS;
}

SEND_BUFFER * hbaDevAllocSendBufferFromSharePool(HBA_DEV_CB *dc, int timeout)
{
    SEND_BUFFER * pSendBuf = NULL;
    int iRet; 
    ULONG tickFrom = tickGet();
    int waitTime = 0;

    ASSERT(dc);
    
    while(1)
    {
        /* get the last pack which is not sent and not full */
        pSendBuf = listRemoveNodeFromListHead(&dc->list_send_idle_share);
        if (pSendBuf != NULL) 
        {
            return pSendBuf;
        }
        /* ����ʣ��ɵȴ���ʱ�� */
        if (timeout == WAIT_FOREVER)
        {
            waitTime = WAIT_FOREVER;
        }
        else if (timeout == NO_WAIT)
        {
            return NULL;
        }
        else
        {            
            waitTime = timeout - (tickGet() - tickFrom);
            if (waitTime <= 0)
            {
                return NULL;
            }
        }
        
        iRet = semTake(dc->semSendShareBufferValid, waitTime);
        if (iRet == ERROR)
        {
            return NULL;
        }

        /* ����Ѿ�ֹͣ�����ٷ����ڴ棬ֱ���˳� */
        if (dc->bToStop == TRUE)
        {
            return NULL;
        }
    }    
    return NULL;
}


void hbaDevFreeSendBuffer(HBA_DEV_CB *dc, SEND_BUFFER * pSendBuf)
{
    W_CTRL * wctrl;

    if (pSendBuf == NULL)
    {
        return;
    }
    /* ���r0, r1*/
    wctrl = (W_CTRL *)pSendBuf->pBuffer;    
    wctrl->w0.value = 0;
    wctrl->w1.value = 0;    
    
    pSendBuf->ch = INVALID_CHANNEL_NO;

    /* ����owner����buffer�Ż���Ӧ��IDLE���� */
    if (pSendBuf->allocatee == SEND_BUFFER_ALLOCATEE_SHARE)
    {
        listAddNodeToListTail(pSendBuf, &dc->list_send_idle_share);
        /* ����RAWͨ���ϵȴ�buffer������ */
        semGive(dc->semSendShareBufferValid);

#if 0
        
        /* �������е�ͨ���ϵȴ�buffer������ */
        for (i=0; i<dc->asmSendChannelCount; i++)
        {
            semGive(dc->asmSendChannels[i].semSendBufferValid);
        }
        semGive(dc->rawSendChannel.semSendBufferValid);
        
#endif
        
    }
    else if (pSendBuf->allocatee == SEND_BUFFER_ALLOCATEE_RAW)
    {
        listAddNodeToListTail(pSendBuf, &dc->rawSendChannel.list_send_idle_private);

        /* ����RAWͨ���ϵȴ�buffer������ */
        semGive(dc->rawSendChannel.semSendBufferValid);
    }
    else /* ASM buffer */
    {
        int ch = -1;

        ch = pSendBuf->allocatee;
        listAddNodeToListTail(pSendBuf, &dc->asmSendChannels[ch].list_send_idle_private);

        /* ����ASMͨ���ϵȴ�buffer������ */
        semGive(dc->asmSendChannels[ch].semSendBufferValid);
    }
}

void hbaDevFreeRecvBuffer(HBA_DEV_CB *dc, RECV_BUFFER *pRecvBuf)
{
    R_CTRL * rctrl;
    
    if (dc == NULL || pRecvBuf == NULL)
    {
        return;
    }

    /* TODO: ���: �û��治Ӧ���Ѿ�����list_toRecv������,  ���Ժ���ӡ� */

    /* ���r0, r1*/
    rctrl = (R_CTRL *)pRecvBuf->pBuffer;    
    rctrl->r0.value = 0;
    rctrl->r1.value = 0;    

    HBA_CACHE_FLUSH (pRecvBuf->pBuffer, sizeof(R_CTRL));    /* Huilin: 12-18 */

    if (pRecvBuf->priority >= MAX_PRIORITY_LEVEL_NUM)
    {
        pRecvBuf->priority = PRIORITY_LEVEL_3;
    }

    /* ����ԭ�Ӳ��� */
    semTake(dc->semRecvListLock, WAIT_FOREVER);
    
    /* ���ظ�buffer��FPGA����������*/
    hbaDevAddRecvBufferToFPGARecvFifo(dc, pRecvBuf);
        
    listAddNodeToListTail(pRecvBuf, &dc->list_toRecv[pRecvBuf->priority] );    

    semGive(dc->semRecvListLock);
    
    return;
}


int hbaDevClearSendBufferInFPGA(HBA_DEV_CB *dc)
{
    int i;

    ASSERT (dc != NULL);
    
    for (i = 0; i < MAX_TX_DMA_BUF_NUM; ++i)
    {
        hwRegisterTxDmaBuf((REG_HW *)dc->pMembaseCsr, i, 0x00000000);
    }
    
    return DEV_SUCCESS;
}

int hbaDevClearRecvBufferInFPGA(HBA_DEV_CB *dc)
{
    int index, priority;

    ASSERT (dc != NULL);

    for (priority = 0; priority < MAX_PRIORITY_LEVEL_NUM; ++priority)
    {
        for (index = 0; index < MAX_RX_DMA_BUF_NUM_PER_PRIO; ++index)
        {
            hwRegisterRxDmaBuf((REG_HW *)dc->pMembaseCsr, priority, index, 0x00000000);
        }
    }
    
    return DEV_SUCCESS;
}

int hbaDevAddSendBufferToFPGA(HBA_DEV_CB *dc, SEND_DMA_BUFFER * pDmaBuf, int index)
{    
    ASSERT (dc != NULL);
    ASSERT (pDmaBuf != NULL);
    ASSERT (index >= 0 && index < 4096);    
    ASSERT (dc->status == HBA_DEV_STATUS_CREATED);
    
    hwRegisterTxDmaBuf((REG_HW *)dc->pMembaseCsr, index, (int)pDmaBuf);
    
    return DEV_SUCCESS;
}

int hbaDevAddRecvBufferToFPGA(HBA_DEV_CB *dc, RECV_DMA_BUFFER * pDmaBuf, int priority, int index)
{    
    ASSERT (dc != NULL);
     ASSERT (pDmaBuf != NULL);
    ASSERT (priority >= 0 && priority < MAX_PRIORITY_LEVEL_NUM);
    ASSERT (index >= 0 && index < MAX_RX_DMA_BUF_NUM_PER_PRIO);    
    ASSERT (dc->status == HBA_DEV_STATUS_CREATED);
    
    hwRegisterRxDmaBuf((REG_HW *)dc->pMembaseCsr, priority, index, (int)pDmaBuf);
    
    return DEV_SUCCESS;
}

int hbaDevAddSendBufferToFPGASendFifo(HBA_DEV_CB *dc, SEND_BUFFER *pSendBuf)
{
     int ch, dma_read_num, buf_num, channel_num, priority, raw_flag;
     W0 *w0;
    W1 *w1;

    ASSERT (dc != NULL);
     ASSERT (pSendBuf != NULL);
    ASSERT (dc->status != HBA_DEV_STATUS_NONE);


     ch = pSendBuf->ch;
    w0 = (W0 *)&pSendBuf->pBuffer->w0;
    w1 = (W1 *)&pSendBuf->pBuffer->w1;
    if (w0->u.length % MAX_BYTES_PER_DMA)
    {
        dma_read_num = (w0->u.length / MAX_BYTES_PER_DMA) + 1;
    }
    else
    {
        dma_read_num = w0->u.length / MAX_BYTES_PER_DMA;
    }
    
     if ((ch >=0) && (ch<dc->asmSendChannelCount))
    {
        buf_num = pSendBuf->bufferIndex;
        channel_num = ch;
        priority = dc->asmSendChannels[ch].priority;
        raw_flag = 0;
     }
    else
    {
        buf_num = pSendBuf->bufferIndex;
        channel_num = ch;
        priority = PRIORITY_LEVEL_RAW_MSG;
        raw_flag = 1;
    }

    /*print_w_ctrl((W_CTRL *)pSendBuf->pBuffer);*/

    w0->value = HbaUlongByteSwap(w0->value);
    w1->value = HbaUlongByteSwap(w1->value);

    HBA_CACHE_FLUSH(pSendBuf->pBuffer, MAX_SEND_BUFER_LEN); /* 2018-4-8: added by Huilin */

    /* print_w_ctrl((W_CTRL *)pSendBuf->pBuffer); */

     hwPushBufDesc((REG_HW *)dc->pMembaseCsr, dma_read_num, buf_num, channel_num, priority, raw_flag);
    
    return DEV_SUCCESS;
}

int hbaDevAddRecvBufferToFPGARecvFifo(HBA_DEV_CB *dc, RECV_BUFFER *pRecvBuf)
{
    int priority, buf_num_of_1st, buf_num_of_2nd, buf_num_of_3rd, valid_buf_num;

    ASSERT (dc != NULL);
     ASSERT (pRecvBuf != NULL);
    ASSERT (dc->status != HBA_DEV_STATUS_NONE);


     priority = pRecvBuf->priority;
    buf_num_of_1st = pRecvBuf->bufferIndex;
    buf_num_of_2nd = 0;
    buf_num_of_3rd = 0;
    valid_buf_num = 1;
     hwPushCredit((REG_HW *)dc->pMembaseCsr, priority, buf_num_of_1st, buf_num_of_2nd, buf_num_of_3rd, valid_buf_num);
    
    return DEV_SUCCESS;
}

/* ������Ϣ����ʹ�� */
INT32 hbaDevSetDiscardEnab(HBA_DEV_CB *dc, UINT32 enab)
{
    ASSERT (dc != NULL);

    if(bUseMsgDiscard == TRUE)
    {
        /* ������Ϣ����ʹ�� */
        hwSetDiscardEnab((REG_HW *)(dc->pMembaseCsr), enab);
    }
    else
    {
        hwSetDiscardEnab((REG_HW *)(dc->pMembaseCsr), 0);
    }

    return DEV_SUCCESS;
}

int hbaDevSetPortFcid(HBA_DEV_CB *dc, UINT port, UINT fcid)
{

     hwSetPortFcid((REG_HW *)dc->pMembaseCsr, fcid);
    
    return DEV_SUCCESS;
}

int hbaDevGetPortFcid(HBA_DEV_CB *dc, UINT port, UINT *value)
{    
    *value = hwGetPortFcid((REG_HW *)dc->pMembaseCsr);
    return DEV_SUCCESS;
}

int hbaDevSetPortSpeed(HBA_DEV_CB *dc, UINT port, UINT speed)
{
     hwSetPortSpeed((REG_HW *)dc->pMembaseCsr, speed);    
    return DEV_SUCCESS;
}

int hbaDevGetPortSpeed(HBA_DEV_CB *dc, UINT port, UINT *value)
{    
     *value = hwGetPortSpeed((REG_HW *)dc->pMembaseCsr);
    return DEV_SUCCESS;
}

int hbaDevSetPortBBCredit(HBA_DEV_CB *dc, UINT port, UINT bbCredit)
{
     hwSetPortCredit((REG_HW *)dc->pMembaseCsr, bbCredit);
    return DEV_SUCCESS;
}

int hbaDevGetPortBBCredit(HBA_DEV_CB *dc, UINT port, UINT *value)
{
     *value = hwGetPortCredit((REG_HW *)dc->pMembaseCsr);
     return DEV_SUCCESS;
}

int hbaDevSetPortGtxLoopBack(HBA_DEV_CB *dc, UINT port, UINT gtx_loopback)
{
     hwSetPortGtxLoopBack((REG_HW *)dc->pMembaseCsr, gtx_loopback);
    return DEV_SUCCESS;
}

int hbaDevGetPortGtxLoopBack(HBA_DEV_CB *dc, UINT port, UINT *value)
{
     *value = hwGetPortGtxLoopBack((REG_HW *)dc->pMembaseCsr);
     return DEV_SUCCESS;
}

/*����ʱ��ͬ������*/
void hbaDevSetClkSyncPeriod(HBA_DEV_CB *dc, int clkSyncPeriod)
{
    REG_HW *reg_hw;

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    hwSetClkSyncPeriod(reg_hw, clkSyncPeriod);
}

/*���wdt�������ںͼ�������Ƿ�Ϸ�*/
int hbaDevCheckWdtPeriod(HBA_DEV_CB *dc)
{
    FCUINT wdtSendPeriod = 0;
    FCUINT wdtCheckPeriod = 0;

    wdtSendPeriod = dc->configBlock.port_config.wdt_loader_period;
    wdtCheckPeriod = dc->configBlock.port_config.nc_wdt_period;

    return ((wdtCheckPeriod > wdtSendPeriod) ? DEV_SUCCESS : DEV_WDT_PERIOD_ERR);
}


int hbaCloseAllChannel(HBA_DEV_CB *dc)
{
     int ret;
    
    ret = DEV_SUCCESS;
     if (dc == NULL)
    {
        ret = DEV_HANDLE_ERR;
        return ret;
     }
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
          ret= DEV_INVALID_OP;
        return ret;
    }

#if 0
    
     count = dc->asmSendChannelCount;
     for (i = 0; i < count; ++i)
    {
        asm_send_ch = &dc->asmSendChannels[i];
        /* �ȴ������������ݷ���������˳�  */
     }

    raw_send_ch = &dc->rawSendChannel;
    /* �ȴ������������ݷ���������˳�  */    
    
     count = dc->asmRecvChannelCount;
     for (i = 0; i < count; ++i)
    {
        asm_recv_ch = &dc->asmRecvChannels[i];
        /*hwSetChannelInActive((REG_HW *)dc->pMembaseCsr, i, BLOCK_MODE);*/
        /* drain fifo */
     }
    raw_recv_ch = &dc->rawRecvChannel;
    /*hwSetChannelInActive((REG_HW *)dc->pMembaseCsr, 0, RAW_MODE); *//* raw index ? */
    
#endif

    /* �������ͨ�������� */
    hwClearAllChannel((REG_HW *)dc->pMembaseCsr);
    
     return ret;
}

/* �ɹ��󷵻�ͨ���ţ�ʧ��ʱ����-1*/
int hbaDevGetRecvChannelNoFromMsgID(HBA_DEV_CB *dc, UINT32 msgID)
{
    int i;

     if (dc == NULL)
    {
        return -1;
     }
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return -1;
    }
    
    for (i = 0; i < dc->asmRecvChannelCount; i++)
    {
        if (dc->asmRecvChannels[i].msgId == msgID)
        {
            return i;
        }
    }

    return -1;
}

/* �ɹ��󷵻�ͨ���ţ�ʧ��ʱ����-1*/
int hbaDevGetSendChannelNoFromMsgID(HBA_DEV_CB *dc, UINT32 msgID)
{
    int i;

     if (!dc)
    {
        return -1;
     }
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return -1;
    }
    for (i = 0; i < dc->asmSendChannelCount; i++)
    {
        if (dc->asmSendChannels[i].msgId == msgID)
        {
            return i;
        }
    }

    return -1;
}

/* send ASM or RAW buffer */
int hbaDevSendMsg(HBA_DEV_CB *dc, int priority, SEND_BUFFER * pSendBuffer)
{
    dc->sentBytes =dc->sentBytes + hbaDrvGetSendBufLen(pSendBuffer->pBuffer);
    dc->sendBuffers ++;

    
    
    /* ����DMA buffer �ύ��FPGA���� */
    hbaDevAddSendBufferToFPGASendFifo(dc, pSendBuffer);

    if (g_hbaDebug & HBA_DBG_SEND)
    {
        printf("Send buffer %p, priority=%d, w0=0x%08x, w1=0x%x\n", pSendBuffer, priority, pSendBuffer->pBuffer->w0, pSendBuffer->pBuffer->w1);
    }
    /* ���뷢�����ȷ�϶��� */
    listAddNodeToListTail(pSendBuffer, &dc->list_SentWaitAck[priority]);    

    return DEV_SUCCESS;
}

/*
    ����0: ��ʾ���ݻ�û�н���
    ������������ʾ���ص�ʵ�ʳ���
    ���ظ�������ʾ����ĳ��Ȳ�����ʵ����Ҫ���ٳ���
 */
int hbaDevGetUIFromRecvBufList(HBA_DEV_CB *dc, UINT32 ch, UINT8 * pDataOut, UINT32 len)
{
    int uiLen = 0;
    BOOL bEop = FALSE;
    RECV_BUFFER * pRecvBuf = NULL;
    LIST_STR * list = NULL;

    /* ��ס�������У� ������Ըö��н��и�IU��صĲ��� */
    /* taskLock(); */
    semTake(dc->asmRecvChannels[ch].semListRecvedLock, WAIT_FOREVER);

    list = &dc->asmRecvChannels[ch].list_recved;
    
    /* ����Ƿ���EOP��֡�� ���û���򷵻�"û�н���" */
    /* ��������UI��Ҫ�ĳ��� */
    if (list->semList != NULL)
    {
        semTake(list->semList, WAIT_FOREVER);
    }
    pRecvBuf = (RECV_BUFFER *)list->listHead;
    while (pRecvBuf != NULL)
    {
        uiLen =uiLen + hbaDrvGetRecvBufLen(pRecvBuf->pBuffer);
        if (hbaDrvIsEop(pRecvBuf->pBuffer))
        {
            bEop = TRUE; 
            break;
        }

        /* ��һ��buffer */
        pRecvBuf = (RECV_BUFFER *)((pRecvBuf->node.next));
    }

    if (list->semList != NULL)
    {
        semGive(list->semList);
    }
    /* û�����ݻ���û�н�β */
    if (bEop == FALSE)
    {
        semGive(dc->asmRecvChannels[ch].semListRecvedLock);
        return 0;
    }

    /* ������Ȳ������򷵻س��ȵĸ�ֵ */
    if (uiLen > len)
    {
        semGive(dc->asmRecvChannels[ch].semListRecvedLock);
        return -uiLen;
    }

    /* ȡ�����ݣ��������������ͷ�buffer��ֱ��EOP */
    uiLen = 0;
    bEop = FALSE;

    pRecvBuf = (RECV_BUFFER *)listRemoveNodeFromListHead(list);
    while (pRecvBuf != NULL)
    {
        int buflen = hbaDrvGetRecvBufLen(pRecvBuf->pBuffer);
        bEop = hbaDrvIsEop(pRecvBuf->pBuffer);

        /* printf("pRecvBuf=%p, buflen=%d, bEop=%d\n", pRecvBuf, buflen , bEop); */        
        
        hbaDrvMemCopy(&pDataOut[uiLen], &pRecvBuf->pBuffer->data[0], buflen);
        
        uiLen = uiLen + buflen;
        
        hbaDevFreeRecvBuffer(dc, pRecvBuf);
        if (bEop)
        {
            break;
        }
        /* ��һ��buffer */
        pRecvBuf = (RECV_BUFFER *)listRemoveNodeFromListHead(list);
    }
        
    if (list->semList != NULL)
    {
        semGive(list->semList);
    }
    if (uiLen > 0)
    {
        if (dc->asmRecvChannels[ch].nIUCount > 0)
        {
            dc->asmRecvChannels[ch].nIUCount --;
        }
    }

    semGive(dc->asmRecvChannels[ch].semListRecvedLock);
    
    return uiLen;
}

void hbaDevRemoveOneIUFromRecvBufList(HBA_DEV_CB *dc, UINT32 ch)
{
    ASM_RECV_CHANNEL * pAsmRecvChannel = NULL;
    RECV_BUFFER *pRecvBufferTemp;
    
    pAsmRecvChannel = &dc->asmRecvChannels[ch];

    /* ��ס�������У� �����������ط��Ըö��н��и�IU��صĲ��� */
    semTake(pAsmRecvChannel->semListRecvedLock, WAIT_FOREVER);

    pRecvBufferTemp = (RECV_BUFFER *)listRemoveNodeFromListHead(&pAsmRecvChannel->list_recved);
    while (pRecvBufferTemp != NULL)
    {
        BOOL isEop = FALSE;

        isEop = hbaDrvIsEop(pRecvBufferTemp->pBuffer);
        
        /* ���ս���IU buffer */
        hbaDevFreeRecvBuffer(dc, pRecvBufferTemp);

        if (isEop)
        {
            if (pAsmRecvChannel->nIUCount > 0)
            {
                pAsmRecvChannel->nIUCount --;
            }
            break;
        }

        pRecvBufferTemp = (RECV_BUFFER *)listRemoveNodeFromListHead(&pAsmRecvChannel->list_recved);
    }
    semGive(pAsmRecvChannel->semListRecvedLock);
}

int hbaDiscardCurrentRecvingIU(HBA_DEV_CB *dc, ASM_RECV_CHANNEL * pAsmRecvChannel)
{
    RECV_BUFFER *pRecvBufferTmp;
    int count;
    
    /* ������IU */
    pRecvBufferTmp = (RECV_BUFFER *)listRemoveNodeFromListHead(&pAsmRecvChannel->list_currentIU);
    while(pRecvBufferTmp != NULL)
    {
        count = 1;
        /* recycle the buffer */
        hbaDevFreeRecvBuffer(dc, pRecvBufferTmp);
        
        pRecvBufferTmp = (RECV_BUFFER *)listRemoveNodeFromListHead(&pAsmRecvChannel->list_currentIU);
    }

    /* IU��tickֵ��0 */
    pAsmRecvChannel->tickSOP = 0;
    pAsmRecvChannel->nIULen = 0;

    return count;    
}


void hbaDevAddOneIUToRecvBufList(HBA_DEV_CB *dc, UINT32 ch)
{
    ASM_RECV_CHANNEL * pAsmRecvChannel = NULL;
    
    pAsmRecvChannel = &dc->asmRecvChannels[ch];    
    
#ifdef USE_MSG_DISCARD
    
    if (!pAsmRecvChannel->bMsgCover)
    {
        /* ����Ƿ�ﵽ�����Ϣ����, ����ﵽ�����ɾ����ǰ�µ�IU�����˳� */
        if (pAsmRecvChannel->nIUCount >= pAsmRecvChannel->nMaxReservedIUNum)
        {
            if (hbaDiscardCurrentRecvingIU(dc, pAsmRecvChannel) > 0)
            {
                if (bDiscard)
                {
                    HbaDevEventNotify(dc, IC_DISCARD_MSG, pAsmRecvChannel->msgId);
                }

                pAsmRecvChannel->discardIuCount ++;
                pAsmRecvChannel->totalIuCount ++;

                dc->dicardIUs ++;
                dc->recvIUs ++;        
            }
            /* ֪ͨ���ջص������հ� */
            if (dc->pRecvCallBackFunc)
            {
                /* �ص���ʽ, ֪ͨ�ϲ�Ӧ���յ�ASM��Ϣ */
                /*if(pAsmRecvChannel->msg_recv_type)*/
                {
                    (*dc->pRecvCallBackFunc)((FCHANDLE)dc, pAsmRecvChannel->msgId);
                }
            }
            return;
        }
    }
    
#endif

#ifdef USE_MSG_COVER
    
    if (pAsmRecvChannel->nIUCount >= pAsmRecvChannel->nMaxReservedIUNum)
    {
        /* ����ͨ���Ƿ���Ҫ��Ϣ���� */
        if (pAsmRecvChannel->bMsgCover)
        {
            hbaDevRemoveOneIUFromRecvBufList(dc, ch);
            
            /* �����жϻص�����֪ͨ */
            if (bDiscard)
            {
                HbaDevEventNotify(dc, IC_COVER_MSG, pAsmRecvChannel->msgId);
            }

            pAsmRecvChannel->coverIuCount ++;
            dc->coverIUs ++;
        }
    }
    
#endif

    /* ����ǰ�����IU�ӵ��ɽ��ն��� */
    semTake(pAsmRecvChannel->semListRecvedLock, WAIT_FOREVER);

    listAddListToListTail(&pAsmRecvChannel->list_recved, &pAsmRecvChannel->list_currentIU);
    pAsmRecvChannel->nIUCount ++;
    
    semGive(pAsmRecvChannel->semListRecvedLock);
    
    /* printf("Recv IU with len = %d \n", pAsmRecvChannel->nIULen); */
    
    listEmptyList(&pAsmRecvChannel->list_currentIU);
    pAsmRecvChannel->tickSOP = 0;
    pAsmRecvChannel->nIULen = 0;
    
    pAsmRecvChannel->totalIuCount ++;
    dc->recvIUs ++;
    
    /* notifiy the upper application to recv the IU */
    if (dc->pRecvCallBackFunc)
    {
        /* �ص���ʽ, ֪ͨ�ϲ�Ӧ���յ�ASM��Ϣ */
        /*if(pAsmRecvChannel->msg_recv_type)*/
        {
            (*dc->pRecvCallBackFunc)((FCHANDLE)dc, pAsmRecvChannel->msgId);
        }
    }
    
    semGive(pAsmRecvChannel->semRecvBufferValid);
}

BOOL hbaDevFillRecvIUList(HBA_DEV_CB *dc, UINT32 ch, RECV_BUFFER *pRecvBuffer)
{
    UINT32 ret;
    ASM_RECV_CHANNEL *pAsmRecvChannel = NULL;
    RECV_BUFFER *pRecvBufferLast = NULL;
    int bufLen = 0;
    BOOL isEop = FALSE;
    
    pAsmRecvChannel = &dc->asmRecvChannels[ch];    
    
#ifdef USE_IU_TIMEOUT
    
    /* ���IU�����Ƿ�ʱ�������ʱ��������IU */
    if (! listIsListEmpty(&pAsmRecvChannel->list_currentIU))
    {
        int tick;
        tick = tickGet() - pAsmRecvChannel->tickSOP;
        if (tick >= dc->recvIUTimeoutTick)
        {
            /*
            printf("*** IU timeout, tick=%d,  maxTimeoutTick=%d, list_currentIU.count = %d\n", 
                tick, dc->recvIUTimeoutTick, pAsmRecvChannel->list_currentIU.count);
            */
            
            HbaDevEventNotify(dc, IC_IU_TIMEOUT, pAsmRecvChannel->msgId);
                        
            if (hbaDiscardCurrentRecvingIU(dc, pAsmRecvChannel) > 0)
            {            
                /* ͳ��ֵ�� 1 */
                pAsmRecvChannel->IuTmroutException ++;
                dc->exceptionIUs ++;
            }
        }
    }
    
#endif

    bufLen = hbaDrvGetRecvBufLen(pRecvBuffer->pBuffer);
    isEop = hbaDrvIsEop(pRecvBuffer->pBuffer);

    /*���ASM���Ʊ�ǽ�ֹ���������յ���ASM���ݻ�����*/
    ret = HbaDevIoState(dc, IO_STATE_MODE_ASM);
    if (ret)
    {
        printf("asm control disable asm channel[msgid=0x%08x sid=0x%08x] bufLen=%d]\n", pAsmRecvChannel->msgId, pAsmRecvChannel->sid, bufLen);

        hbaDiscardCurrentRecvingIU(dc, pAsmRecvChannel);
        hbaDevFreeRecvBuffer(dc, pRecvBuffer);

        return FALSE;
    }


    /* �������һ��SeqErr�Ļ��棬��ǰ��IUӦ�ö��� */
    if (hbaDrvGetRecvBufSeqErr(pRecvBuffer->pBuffer))
    {
        /* the msgID is not registerd */
        /* printf("Seq err, channel ID  %u,  bufLen=%d\n", ch, bufLen ); */

        /*HbaDevEventNotify(dc, IC_IU_SEQ_ERR, pAsmRecvChannel->msgId);*/

        hbaDiscardCurrentRecvingIU(dc, pAsmRecvChannel);        
        
        pAsmRecvChannel->IuSeqException ++;    
        dc->exceptionIUs ++;
        
        /* Dicard the message and recycle the buffer */
        hbaDevFreeRecvBuffer(dc, pRecvBuffer);

        /* ����������һ���� */
        return FALSE;                
    }

    if ((pAsmRecvChannel->nIULen + bufLen) > pAsmRecvChannel->maxIUSize)
    {
        /* �յ���IU���ݳ��ȳ���IUBuffer����? ������IU !!! */
        /*printf("*** IU length beyond, maxIUSize = %d, nDataLen=%d,  bufLen=%d\n", 
                pAsmRecvChannel->maxIUSize, pAsmRecvChannel->nIULen, bufLen);
        */
        HbaDevEventNotify(dc, IC_IU_LENGTH_INVALID, pAsmRecvChannel->msgId);
        
        if (hbaDiscardCurrentRecvingIU(dc, pAsmRecvChannel) > 0)
        {
            /* ͳ��ֵ�� 1 */
            pAsmRecvChannel->IuLenException ++;    
            dc->exceptionIUs ++;
        }
    }

    pRecvBufferLast = (RECV_BUFFER *)listGetLastNodeFromList(&pAsmRecvChannel->list_currentIU);
    if (pRecvBufferLast == NULL)
    {
        /* IU ������SOP��ʼ��������ֱ����һ��SOP���� */
        if (!hbaDrvIsSop(pRecvBuffer->pBuffer))
        {
            /* printf("*** discard IU for hbaDrvIsSop() is FALSE \n"); */
                
            /* recycle the buffer */
            hbaDevFreeRecvBuffer(dc, pRecvBuffer);
            return FALSE;
        }
        else
        {
            /* IU��һ���ڵ� */
            listAddNodeToListTail(pRecvBuffer, &pAsmRecvChannel->list_currentIU);
            
            /* record the tick of sop of IU */
            pAsmRecvChannel->tickSOP = tickGet();
            pAsmRecvChannel->nIULen = pAsmRecvChannel->nIULen + bufLen;
        }
    }
    else
    {
        /* ǰ���а��IU���������յ��µ�sop���͸ö���ǰ���յ������� */
        if (hbaDrvIsSop(pRecvBuffer->pBuffer))
        {
            /* ����ǰ���յ������� */
            hbaDiscardCurrentRecvingIU(dc, pAsmRecvChannel);        
        
            pAsmRecvChannel->IuSeqException ++;    
            dc->exceptionIUs ++;


            /* ����IU��һ���ڵ㴦�� */
            listAddNodeToListTail(pRecvBuffer, &pAsmRecvChannel->list_currentIU);
            
            /* record the tick of sop of IU */
            pAsmRecvChannel->tickSOP = tickGet();
            pAsmRecvChannel->nIULen = pAsmRecvChannel->nIULen + bufLen;
        }
        else
        {
            UINT32 lastBufLen = hbaDrvGetRecvBufLen(pRecvBufferLast->pBuffer);
            
            /* ������һ��buffer��װ�µ�ǰbuffer���򿽱���ǰbuffer�����buffer�У����ͷŵ�ǰbuffer, ���򿽱�ֱ�Ӽӵ����� */
            if ((lastBufLen + bufLen) > (pRecvBufferLast->bufferSize - 8))    /* 8 byte for r0,r1*/
            {
                listAddNodeToListTail(pRecvBuffer, &pAsmRecvChannel->list_currentIU);    
                /* printf("+"); */
            }
            else
            {
                /* ����buffer���ݵ� ���һ��buffer �У����ͷ��½��յ�buffer */
                dc->recvMoveBytes =dc->recvMoveBytes + bufLen;
                
#ifndef NO_DATA_MEMCPY
                
                hbaDrvMemCopy(&pRecvBufferLast->pBuffer->data[lastBufLen], &pRecvBuffer->pBuffer->data[0], bufLen);
                
#endif
                
                /* printf("-"); */
                hbaDrvSetRecvBufLen(pRecvBufferLast->pBuffer, lastBufLen + bufLen);        
                hbaDrvSetEop(pRecvBufferLast->pBuffer, isEop);    

                /* �ͷ����buffer */
                hbaDevFreeRecvBuffer(dc, pRecvBuffer);
            }
            pAsmRecvChannel->nIULen =pAsmRecvChannel->nIULen + bufLen;
        }
    }

    /* �����EOP, �����IU���������� �ӵ�����ȡ���б���*/
    if (isEop)
    {        
        hbaDevAddOneIUToRecvBufList(dc, ch);
    }

    return TRUE;
}


int bPrintR0R1 = 0;

BOOL hbaDevRecvOneBuffer(HBA_DEV_CB *dc)
{
    int i;
    BOOL bDataRecved = FALSE;
    int dataLen = 0;

    for (i = MAX_PRIORITY_LEVEL_NUM - 1; i >= 0; --i)
    {
        RECV_BUFFER *pRecvBuffer = NULL;

        pRecvBuffer = (RECV_BUFFER *)listGetFirstNodeFromList(&dc->list_toRecv[i]);
        if (pRecvBuffer == NULL)
        {
            /* the list is empty */
            continue;
        }

        /* Check whether the data in the buffer has been sent */
        HBA_CACHE_INVAL(pRecvBuffer->pBuffer, pRecvBuffer->bufferSize);
        dataLen = hbaDrvGetRecvBufLen(pRecvBuffer->pBuffer);
        if (dataLen > 0)
        {
            bDataRecved = TRUE;
        }
        else
        {
            bDataRecved = FALSE;
        }

        if (bDataRecved != TRUE)    /* no data is received in this list*/
        {
            continue;
        }
        if (dataLen > (pRecvBuffer->bufferSize - 8))
        {
            printf("Invalid length in recv buffer, priority=%d, dataLen=%d, bufferSize=%d, w0=0x%08x\n",i, dataLen, pRecvBuffer->bufferSize, pRecvBuffer->pBuffer->r0);
            hbaDevFreeRecvBuffer(dc, pRecvBuffer);
            continue;
        }
        /* pRecvBuffer->pBuffer->r0 = byte_convert(pRecvBuffer->pBuffer->r0); */
        
        if (g_hbaDebug & HBA_DBG_RECV)
        {
            printf("Recv a buffer with PRIORITY=%d, len=%d, r0=0x%08x\n", i, hbaDrvGetRecvBufLen(pRecvBuffer->pBuffer), pRecvBuffer->pBuffer->r0);
        }
        dc->recvBuffers ++;
        dc->recvBytes =dc->recvBytes + dataLen;

        pRecvBuffer = listRemoveNodeFromListHead(&dc->list_toRecv[i]);

#if 0    /* ���Դ��룬ֱ�ӻ��ղ������û� */
        
        hbaDevFreeRecvBuffer(dc, pRecvBuffer);
        break;
        
#endif

        if (bPrintR0R1)
        {
            printRecvDmaR0R1(pRecvBuffer->pBuffer);        
        }

        if (PRIORITY_LEVEL_RAW_MSG == i)        
        {
            dc->recvRawBuffers ++;
            
            if (listGetFirstNodeFromList(&dc->list_toRecv[PRIORITY_LEVEL_RAW_MSG]) == NULL)
            {
                /* RAWͨ����bufferʹ�����ˣ����һ��buffer�����ͷţ������봦�� */
                hbaDevFreeRecvBuffer(dc, pRecvBuffer);
                /* ����������һ���� */
                break;
            }
            else
            {
                listAddNodeToListTail(pRecvBuffer, &dc->rawRecvChannel.list_recved );
                semGive(dc->rawRecvChannel.semRecvBufferValid);
            }
        }
        else /* is ASM message */
        {
            ASM_RECV_CHANNEL * pAsmRecvChannel = NULL;
            UINT32 msgID = 0;
            UINT32 ch = hbaDrvGetChannelIDFromRecvMsg(pRecvBuffer->pBuffer);
            if (ch >= dc->asmRecvChannelCount)
            {
                /* the msgID is not registerd */
                /*printf("Undefined channel ID  %u. \n", ch );*/

#if 0    
                
                d(((UINT8 *)pRecvBuffer->pBuffer - 1024), 512, 4);
                
#endif
                /* Dicard the message and recycle the buffer */
                hbaDevFreeRecvBuffer(dc, pRecvBuffer);

                /* ����������һ���� */
                break;                
            }

            pAsmRecvChannel = &dc->asmRecvChannels[ch];

            msgID = pAsmRecvChannel->msgId;
            pAsmRecvChannel->recvBuffers ++;
            pAsmRecvChannel->recvBytes =pAsmRecvChannel->recvBytes + dataLen;

            
            hbaDevFillRecvIUList(dc, ch, pRecvBuffer);
            

        }
        break;
    }

    return bDataRecved;
}

STATUS hbaDevCheckFpga(HBA_DEV_CB *dc)
{
    /* TODO */
    return OK;
}

/* ���˿ڵ�link״̬ */
STATUS hbaDevCheckLink(HBA_DEV_CB *dc)
{
    REG_HW *reg_hw;
    int port_status[FC_PORT_NUM_MAX];
    
    reg_hw = (REG_HW *)dc->pMembaseCsr;
    hwGetPortStatus(reg_hw, port_status, FC_PORT_NUM_MAX);
    /* �����˿�ֻҪ��һ��link״̬�������ģ��ͷ���OK */
    if ((port_status[FC_PORT_0] == 1) || (port_status[FC_PORT_1] == 1))
    {
        return OK;
    }
    return ERROR;
}

int hbaDevRecvTask(HBA_DEV_CB *dc)
{
    BOOL bDataRecved = FALSE;        
    int  iDataRecvCount = 0;        /* ����Sleep�䴦��İ����� */
    
    while (1)
    {

#ifdef AE653_BUILD
        
        if ((dc->status != HBA_DEV_STATUS_STARTED) || (dc->bToStop == TRUE))
        {
            taskDelay(5);
            continue;
        }
        
#else    
        
        if (dc->bToStop)
        {
            break;
        }
        
#endif
        
        do
        {
            bDataRecved = hbaDevRecvOneBuffer(dc);
            if (bDataRecved == TRUE)
            {
                iDataRecvCount++;
            }
        } while (bDataRecved == TRUE && (iDataRecvCount < 256));

        
        if (dc->bUseInterrupt)
        {
            /* �����ж� */
            hbaDevHwIntEnable(dc);
            hbaDevIntEnable(dc);
        }

        semTake(dc->semRecv, 1); 
        
        iDataRecvCount = 0;    
    }
    
    dc->recvTaskId = ERROR;

    return 0;
}

int hbaDevSentCheckTask(HBA_DEV_CB *dc)
{
    int i;
    
    while(1)
    {
#ifdef AE653_BUILD
        
        if ((dc->status != HBA_DEV_STATUS_STARTED) || (dc->bToStop == TRUE))
        {
            taskDelay(5);
            continue;
        }
        
#else        
        
        if (dc->bToStop)
        {
            break;
        }
        
#endif

        for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
        {
            int  iCheckCount = 0;
            
            do
            {
                SEND_BUFFER *pSendBuffer = NULL;
                BOOL bSent = FALSE;

                pSendBuffer = (SEND_BUFFER *)listGetFirstNodeFromList(&dc->list_SentWaitAck[i]);
                if (pSendBuffer == NULL)
                {
                    /* the list is empty */
                    break;
                }

                iCheckCount ++;
                /* Check whether the data in the buffer has been sent */
                
                bSent = hbaDrvChkSendCompleted(pSendBuffer->pBuffer);
                
                if (bSent == FALSE)
                {
                    /* the buffer is not been sent now, skip to check other list  */
                    break;
                }
                
                /* the data has been sent, the free the buffer */
                dc->sendCmptBuffers ++;
                    
                pSendBuffer = listRemoveNodeFromListHead(&dc->list_SentWaitAck[i]);

#ifdef _CHECK_SEND_STREAM_STATE_

                /* ���������ͣ� ��Ҫ�������ȷ�������Ƿ������ */
                if (pSendBuffer->bStream)
                {
                    dc->asmSendChannels[pSendBuffer->ch].ackSeqNo = pSendBuffer->seqNo;
                }
                
#endif
                
                /* �ͷŷ���buffer */
                hbaDevFreeSendBuffer(dc, pSendBuffer);
            
            }while(iCheckCount < 2048);    /* ÿ���������м��buffer�Ĵ���Ϊ2048*/
        }
        semTake(dc->semSentCheck, 1); 
    }
    dc->sentCheckTaskId = ERROR;

    return 0;
}

/*1 �ڴ�1ms  ����ʱ�����ڴ����λ�ö�д����*/
STATUS hbaDevCheckMemory(HBA_DEV_CB *dc)
{
#ifndef AE653_BUILD
    
    char *pBuf = NULL;
    UINT *pData = NULL;
    int i;

    /* Test memory alloc & read & write */
    pBuf = (char *)HBA_MALLOC(0x40000 * 4);  /* 1M memory for test */
    if (pBuf == NULL)
    {
        return ERROR;
    }
    pData = (UINT *)pBuf;
    for (i = 0; i < 0x10000; i++)
    {
        pData[0] = 0x11111111;
        pData[1] = 0x22222222;
        pData[2] = 0x44444444;
        pData[3] = 0x88888888;
        
        pData =pData + 4; /* ����4��UINT */
    }

    pData = (UINT *)pBuf;
    for (i = 0; i<0x10000; i++)
    {
        if ((pData[0] != 0x11111111) || 
            (pData[1] != 0x22222222) ||
            (pData[2] != 0x44444444) ||
            (pData[3] != 0x88888888))
        {
            HBA_MEM_FREE(pBuf);
            return ERROR;
        }

        pData =pData + 4; /* ����4��UINT */
    }

    HBA_MEM_FREE(pBuf);
    
#endif    
    return OK;
}

/*
�շ�����(���ݽ�����)/1ms/    ����
���ڼ���Ƿ��л��������ʳ������޵ģ����������ǰ��ͺ����ǩ����д�����ƻ��ˣ����߶�������ȡ��ǩ��������
*/
UINT32 hbaDevCheckIoBufWrite(HBA_DEV_CB *dc)
{
    UINT32 ret;
    /*@@@@*/
    ret = 0;
    return ret;
}

UINT32 hbaDevCheckIoBufRead(HBA_DEV_CB *dc)
{
    UINT32 ret;
    /*@@@@*/
    ret = 0;
    return ret;
}

/*4 �ӿڼĴ���(PCIEͨѶ) 1ms ����
������ʼʱ������д���ԣ�ֱ�Ӻͼ�ӼĴ���������Ҫ����ȫ���ļĴ�����*/
STATUS hbaDevCheckRegisterIo(HBA_DEV_CB *dc)
{
    STATUS ret;

    ret = OK;
    return ret;
}

/*    
5 ��ȡFPGA�ļĴ�����ȡ���¶�ֵ
*/            
UINT32 hbaDevCheckTemp(HBA_DEV_CB *dc)
{
    UINT32 ret;
    REG_HW *reg_hw;
    FCINT value, low, high;

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    value = hwGetTemperature(reg_hw);
    /*����*/
    low = SC_TEMP_VALUE - SC_TEMP_THRESHOLD;
    /*����*/
    high = SC_TEMP_VALUE + SC_TEMP_THRESHOLD;
    if (!((value >= low) && (value <= high)))
    {
        /*printf("temperature value=%d, low=%d, high=%d!\n", value, low, high);*/
        ret = IC_TEMP_FAILED;
    }
    else 
    {
        ret = IC_TEMP_SUCCESS;
    }
    return ret;
}

/*
6 ��ȡFPGA�ļĴ�����ȡ�õ�ѹֵ
*/
UINT32 hbaDevCheckVoltage(HBA_DEV_CB *dc)
{
    UINT32 ret;
    REG_HW * reg_hw;
    FCINT value, low, high;

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    value = hwGetVoltage(reg_hw);
    
    /*����*/
    low = SC_VOLTAGE_VALUE - SC_VOLTAGE_THRESHOLD;
    
    /*����*/ 
    high = SC_VOLTAGE_VALUE + SC_VOLTAGE_THRESHOLD;
    if (!((value >= low) && (value <= high)))
    {
        ret = IC_VOLTAGE_FAILED;
    }
    else 
    {
        ret = IC_VOLTAGE_SUCCESS;
    }
    
    return ret;
}

STATUS hbaDevCheckFlashRW(HBA_DEV_CB *dc)
{
#ifdef HBA_INCLUDE_FLASH    
    unsigned char * pBuf = NULL;
    unsigned char * pBuf2 = NULL;
    UINT * pData = NULL;    
    int    i, j;
    int tick;

#define FLASH_TEST_SIZE     4096 /* 0x100000 */
#define FLASH_TEST_ADRS        0x500000

    pBuf = (unsigned char *)HBA_MALLOC(FLASH_TEST_SIZE); 
    if (pBuf == NULL)
    {
        return ERROR;
    }
    pBuf2 = (unsigned char *)HBA_MALLOC(FLASH_TEST_SIZE); 
    if (pBuf2 == NULL)
    {
        HBA_MEM_FREE(pBuf);
        return ERROR;
    }

    pData = (UINT *)pBuf;
    j = tickGet() % 4;
    for (i = 0; i<(FLASH_TEST_SIZE/16); i++)
    {
        pData[0] = g_intArr[j++];
        pData[1] = g_intArr[j++];
        pData[2] = g_intArr[j++];
        pData[3] = g_intArr[j++];
        
        pData =pData + 4; /* ����4��UINT */
        j %= 4;
    }

    tick = tickGet();
    if (hbaDevFlashWrite(dc, FLASH_TEST_ADRS, pBuf, FLASH_TEST_SIZE)!= OK)
    {
        HBA_MEM_FREE(pBuf);
        HBA_MEM_FREE(pBuf2);
        return ERROR;
    }

    /*printf("write tick=%d,sec=%d!\n", (tickGet()-tick), (tickGet()-tick)/sysClkRateGet());*/
    tick = tickGet();

    if (hbaDevFlashRead(dc, FLASH_TEST_ADRS, pBuf2, FLASH_TEST_SIZE)!= OK)
    {
        HBA_MEM_FREE(pBuf);
        HBA_MEM_FREE(pBuf2);
        return ERROR;
    }

    /*printf("read tick=%d,sec=%d!\n", tickGet()-tick, (tickGet()-tick)/sysClkRateGet());*/

    if (memcmp(pBuf2, pBuf, FLASH_TEST_SIZE)!=0)
    {
        HBA_MEM_FREE(pBuf);
        HBA_MEM_FREE(pBuf2);
        return ERROR;
    }
    HBA_MEM_FREE(pBuf);
    HBA_MEM_FREE(pBuf2);
    return OK;    
#else

    return ERROR;

#endif
}

/*
��ȡFPGA�ļĴ�����ȡ��2���˿ڵ���·״ֵ̬��
�ú��������жϴ������б����ã���˲��ܵ���printf�Ⱥ�����*/
UINT32 hbaDevCheckLinkStatus(HBA_DEV_CB *dc)
{
    int ps[FC_PORT_NUM_MAX];    
    REG_HW *reg_hw;
    
    reg_hw = (REG_HW *)dc->pMembaseCsr;
    hwGetPortStatus(reg_hw, ps, FC_PORT_NUM_MAX);

    /*�����˿�ֻҪ��һ��link״̬�������ģ���������*/
    if (ps[FC_PORT_0] == 1 || ps[FC_PORT_1] == 1)
    {
        return IC_LINK_STATUS_SUCCESS;
    }
    return IC_LINK_STATUS_FAILED;
}

UINT32 hbaDevGetStatByType(REG_HW * reg_hw, UINT32 type)
{
    STATISTICS_CONTROL status;
    UINT32 tempValue = 0;    

    status.value = 0;
    status.u.start = 0;
    status.u.type = type;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, status.value);
    
    hw_delay(100); /* �ȴ�100 CPU���ڣ���FPGA׼�������� */    
    
    tempValue = ReadRegisterUlong(&reg_hw->STATISTICS_DATA);

    return tempValue;
}

/*
��ȡFPGA�ļĴ�����ȡ��ͳ��ֵ
*/
FCUINT hbaDevCheckStatistics(HBA_DEV_CB *dc)
{
    FCUINT ret = 0;
    REG_HW *reg_hw;
    STATISTICS_CONTROL status;    
    int i;
    int portBaseAddr = 0;

    semTake(dc->semStatLock, WAIT_FOREVER);
    
    reg_hw = (REG_HW *)dc->pMembaseCsr;

    /*set snapshot*/
    status.value = 0;
    status.u.start = 1;
    WriteRegisterUlong(&reg_hw->STATISTICS_CONTROL, status.value);
    
    taskDelay(1);

    /*get stat*/
    dc->fpgaStatInfo.recvFrameNumTotal =dc->fpgaStatInfo.recvFrameNumTotal + hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_FRAME_NUM);
    dc->fpgaStatInfo.recvIUNumTotal =dc->fpgaStatInfo.recvIUNumTotal + hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_IU_NUM);
    dc->fpgaStatInfo.recvErrorIUNumTotal =dc->fpgaStatInfo.recvErrorIUNumTotal + hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_ERROR_IU_NUM);
    dc->fpgaStatInfo.recvDiscardFrameNumTotal =dc->fpgaStatInfo.recvDiscardFrameNumTotal + hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_DISCARD_IU_NUM);
    dc->fpgaStatInfo.recvInvalidFrameNumTotal =dc->fpgaStatInfo.recvInvalidFrameNumTotal + hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_RECV_INVALID_FRAME_NUM);

    dc->fpgaStatInfo.sendFrameNumTotal =dc->fpgaStatInfo.sendFrameNumTotal + hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_SEND_FRAME_NUM);
    dc->fpgaStatInfo.sendIUNumTotal =dc->fpgaStatInfo.sendIUNumTotal + hbaDevGetStatByType(reg_hw, FPGA_STAT_TYPE_SEND_IU_NUM);

    for (i = 0; i < FC_PORT_NUM_MAX; i++)
    {
        if (i == 0)
        {
            portBaseAddr = FPGA_STAT_PORT_0_BASE;
        }
        else
        {
            portBaseAddr = FPGA_STAT_PORT_1_BASE;
        }
        dc->portStatInfo[i].RxUndersizeFrameCnt   =dc->portStatInfo[i].RxUndersizeFrameCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_UNDERSIZE_FRAME);
        dc->portStatInfo[i].RxOversizeFrameErrCnt =dc->portStatInfo[i].RxOversizeFrameErrCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_OVERSIZE_FRAME);
        dc->portStatInfo[i].RxAllFrameCnt         =dc->portStatInfo[i].RxAllFrameCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_ALL_FRAME);
        dc->portStatInfo[i].RxValidFrameCnt       =dc->portStatInfo[i].RxValidFrameCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_VALID_FRAME);
        dc->portStatInfo[i].RxWordCnt             =dc->portStatInfo[i].RxWordCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_FRAME_LEN);
        dc->portStatInfo[i].RxRRDYCnt             =dc->portStatInfo[i].RxRRDYCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_RRDY);
        dc->portStatInfo[i].RxKErrCnt             =dc->portStatInfo[i].RxKErrCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_RX_K_ERR);
        dc->portStatInfo[i].LinkChgUp2DownCnt     =dc->portStatInfo[i].LinkChgUp2DownCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_LNK_CHG_UP2DWN);
        dc->portStatInfo[i].TxAllFrameCnt         =dc->portStatInfo[i].TxAllFrameCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_TX_ALL_FRAME);
        dc->portStatInfo[i].TxValidFrameCnt       =dc->portStatInfo[i].TxValidFrameCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_TX_VALID_FRAME);
        dc->portStatInfo[i].TxWordCnt             =dc->portStatInfo[i].TxWordCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_TX_FRAME_LEN);
        dc->portStatInfo[i].TxRRDYCnt             =dc->portStatInfo[i].TxRRDYCnt + hbaDevGetStatByType(reg_hw, portBaseAddr + PORT_STAT_TX_RRDY);
    }
    semGive(dc->semStatLock);
    
    return ret;
}

/*�ϵ��Լ�*/
STATUS hbaDevPuSelfCheck(HBA_DEV_CB *dc)
{
    STATUS st = OK;
    
#ifndef AE653_BUILD

    FCUINT ret;
    FC_BIT_RESULT *bitResult;

    bitResult = &dc->bitResult;
    do
    {
        /*1 �ڴ�1ms  ����ʱ�����ڴ����λ�ö�д����*/
        st = hbaDevCheckMemory(dc);
        if (st == ERROR)
        {
            bitResult->memory = BIT_FAILURE;
            break;
        }
        bitResult->memory = BIT_SUCCESS;
        
        /*2 �ӿڼĴ���(PCIEͨѶ) 1ms ����
        ������ʼʱ������д���ԣ�ֱ�Ӻͼ�ӼĴ���������Ҫ����ȫ���ļĴ�����*/
        st = hbaDevCheckRegisterIo(dc);
        if (st == ERROR)
        {
            bitResult->reg = BIT_FAILURE;
            break;
        }
        bitResult->reg = BIT_SUCCESS;
    
        /*3 �¶�*/
        ret = hbaDevCheckTemp(dc);
        if (ret == IC_TEMP_FAILED)
        {
            bitResult->temperature = BIT_FAILURE;
            st = ERROR;
            break;
        }
        st = OK;
        bitResult->temperature = BIT_SUCCESS;

        /*4 ��ѹ*/
        ret = hbaDevCheckVoltage(dc);
        if (ret == IC_VOLTAGE_FAILED)
        {
            bitResult->voltage = BIT_FAILURE;
            st = ERROR;
            break;
        }
        st = OK;
        bitResult->voltage = BIT_SUCCESS;        

        /*5 Flash��д10ms ����/�ֶ�����ͼ�Ĺ̶�λ��*/
        st = hbaDevCheckFlashRW(dc);
        if (st == ERROR)
        {
            bitResult->flash = BIT_FAILURE;
            break;
        }        
        st = OK;
        bitResult->flash = BIT_SUCCESS;
    } while (0);

    /* ��ѯ��·״̬*/
    dc->linkStatus = hbaDevCheckLinkStatus(dc);

#endif

    return st;
}

void hbaDevManualSelfCheck(HBA_DEV_CB *dc)
{
    STATUS st;
    UINT32 ret;
    FC_BIT_RESULT *bitResult;
    
    bitResult = &dc->bitResult;
    
    /*Flash��д����/�ֶ�����ͼ�Ĺ̶�λ��*/
    st = hbaDevCheckFlashRW(dc);
    /*bitResult->reg = st == ERROR ? BIT_FAILURE : BIT_SUCCESS;*/
    if ( st == ERROR )
      {
          bitResult->reg=BIT_FAILURE;
      }
    else
      {
          bitResult->reg=BIT_SUCCESS;
      }
    
    /*�¶�*/
    ret = hbaDevCheckTemp(dc);
    if (ret == IC_TEMP_FAILED)
    {
        bitResult->temperature = BIT_FAILURE;
    }
    else
    {
        bitResult->temperature = BIT_SUCCESS;
    }
    
    /*��ѹ*/
    ret = hbaDevCheckVoltage(dc);
    if (ret == IC_VOLTAGE_FAILED)
    {
        bitResult->voltage = BIT_FAILURE;
    }
    else
    {
        bitResult->voltage = BIT_SUCCESS;    
    }
}

/*���緢����Լ�*/
void hbaDevNetSelfCheck(HBA_DEV_CB *dc)
{
    UINT32 ret;
    FC_BIT_RESULT *bitResult;
    
    bitResult = &dc->bitResult;

    /*�¶�*/
    ret = hbaDevCheckTemp(dc);
    if (ret == IC_TEMP_FAILED)
    {
        bitResult->temperature = BIT_FAILURE;
    }
    else
    {
        bitResult->temperature = BIT_SUCCESS;
    }
    
    /*��ѹ*/
    ret = hbaDevCheckVoltage(dc);
    if (ret == IC_VOLTAGE_FAILED)
    {
        bitResult->voltage = BIT_FAILURE;
    }
    else
    {
        bitResult->voltage = BIT_SUCCESS;    
    }
}

/* 1- link up,  0-link down */
UINT32 hbaDevGetPortLinkStatus(HBA_DEV_CB *dc, int port)
{
    int port_status[FC_PORT_NUM_MAX];    
    REG_HW *reg_hw;
    
    reg_hw = (REG_HW *)dc->pMembaseCsr;
    hwGetPortStatus(reg_hw, port_status, FC_PORT_NUM_MAX);

    return port_status[port];
}

/* �����¶�ֵ*/
INT32 hbaDevGetTemp(HBA_DEV_CB *dc)
{
    REG_HW *reg_hw;
    FCINT value;

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    value = hwGetTemperature(reg_hw);

    return value;
}

/* 0 - OK, 1- ERROR */
STATUS hbaDevGetWorkStatus(HBA_DEV_CB *dc)
{
    STATUS st;
    UINT32 ret;
    FC_BIT_RESULT *bitResult;
    
    bitResult = &dc->bitResult;
    
    /*Flash��д����/�ֶ�����ͼ�Ĺ̶�λ��*/
    st = hbaDevCheckFlashRW(dc);
    bitResult->reg = st == ERROR ? BIT_FAILURE : BIT_SUCCESS;

    /* �շ���������д */
    ret = hbaDevCheckIoBufWrite(dc);
    if (ret == IC_IO_BUF_WRITE_FAILED) 
    {
        return ERROR;
    }
    else
    {
        ret = hbaDevCheckIoBufRead(dc);
        if (ret == IC_IO_BUF_READ_FAILED) 
        {
            return ERROR;
        }
    }
    
    /*�¶�*/
    ret = hbaDevCheckTemp(dc);
    if (ret == IC_TEMP_FAILED)
    {
        return ERROR;
    }
    
    /*��ѹ*/
    ret = hbaDevCheckVoltage(dc);
    if (ret == IC_VOLTAGE_FAILED)
    {
        return ERROR;
    }

    return OK;
}

int hbaDevPeriodSelfCheckTask(HBA_DEV_CB *dc)
{
    UINT32 waitTick, link_status, linkStatusChgCount;
    
    waitTick = HbaDrvMilliSecond2Tick(FC_SELF_CHECK_PERIOD);
    while (1)
    {
        
#ifdef AE653_BUILD
        
        if (dc->status != HBA_DEV_STATUS_STARTED || dc->bToStop == TRUE)
        {
            taskDelay(5);
            continue;
        }
        
#else    
        
        if (dc->bToStop)
        {
            break;
        }
        
        if (dc->status != HBA_DEV_STATUS_STARTED)
        {
            taskDelay(10);
            continue;
        }
        
#endif
        
        /*�����·״̬
        �жϴ��������Ҳ���޸�linkStatus��linkStatusChgCount, Ϊ����ͬʱ���ʣ���δ��벻�ܱ��жϡ�
        */    
        /*lockKey = intLock();*/

        dc->bLinkStatusChecking = TRUE;

        link_status = hbaDevCheckLinkStatus(dc);
        if (dc->linkStatus != link_status)
        {
            dc->linkStatus = link_status;
            dc->linkStatusChgCount ++;
        }
        linkStatusChgCount = dc->linkStatusChgCount;
        dc->linkStatusChgCount = 0;

        dc->bLinkStatusChecking = FALSE;
        
        if (linkStatusChgCount)
        {
            INT32 ps[FC_PORT_NUM_MAX];
            REG_HW*  reg_hw;

            reg_hw = (REG_HW *)dc->pMembaseCsr;
            hwGetPortStatus(reg_hw, ps, FC_PORT_NUM_MAX);

            /* Huilin: ���������·�Ͽ����������·״̬������ */
            if (ps[FC_PORT_0] == FC_PORT_STATUS_LINK_DOWN) 
            {
                memset(&dc->swLinkStatusTbl.Status[0], 0, sizeof(FCUCHAR) * FC_SW_PORT_NUM_MAX);
                memset(&dc->swAppVersion[0], 0, sizeof(SW_IMPSoftWareVersion));
                memset(&dc->swBspVersion[0], 0, sizeof(SW_IMPSoftWareVersion));    
            }
            if (ps[FC_PORT_1] == FC_PORT_STATUS_LINK_DOWN)
            {
                memset(&dc->swLinkStatusTbl.Status[1], 0, sizeof(FCUCHAR) * FC_SW_PORT_NUM_MAX);
                memset(&dc->swAppVersion[1], 0, sizeof(SW_IMPSoftWareVersion));
                memset(&dc->swBspVersion[1], 0, sizeof(SW_IMPSoftWareVersion));    
            }    

            HbaDevEventNotify(dc, dc->linkStatus, linkStatusChgCount);
        }
    
        /*��ȡͳ����Ϣ*/
        hbaDevCheckStatistics(dc);

        /*�ӳ�*/
        semTake(dc->semPeriodSelfCheck, waitTick);
        
    }

    dc->periodSelfCheckTaskId = ERROR;    
    
    return OK;
}

int iIntCounter = 0;
int ilinkStatusChgCount = 0;
void hbaDevIntHandler(HBA_DEV_CB *dc)
{
    /* logMsg("%s: enter \n", (int)__FUNCTION__, 0,0,0,0,0); */
    /* INTERRUPT  intrp; */
    UINT32 linkStatus;
    int link_change = 0;
    
    iIntCounter ++;

    link_change = hwGetLinkChangePending((REG_HW *)dc->pMembaseCsr);
    /* ����Ƿ�����·�仯���ж� */
    if (link_change && (dc->bLinkStatusChecking == FALSE))
    {
        /* ���Ĵ�����·�Ƿ�仯������仯�����޸���·��־����������·�仯���� */
        linkStatus = hbaDevCheckLinkStatus(dc);
        if (dc->linkStatus != linkStatus)
        {
            dc->linkStatus = linkStatus;            
            dc->linkStatusChgCount ++;

            ilinkStatusChgCount ++;
        }
            
        /* �����·�仯��������0���������ڼ��ĺ������ص����жϺ��� */
        if (dc->linkStatusChgCount > 0)
        {
            semGive(dc->semPeriodSelfCheck); 
        }
    }

    /* �ر��жϺ� */
    hbaDevIntDiable(dc);
    /* �ر��жϣ������pendingλ */
    hbaDevHwIntDiable(dc);

    /* ���Ѵ������� */
    semGive(dc->semRecv); 

    /* logMsg("%s: exit \n", (int)__FUNCTION__, 0,0,0,0,0); */
}
    
STATUS hbaDevIntConnect (HBA_DEV_CB *dc)
{
    STATUS ret = OK; 
#if 0    
    /* ret = intConnect ( (VOIDFUNCPTR *)(int)(dc->irq), (VOIDFUNCPTR)hbaDevIntHandler, (int) dc);  */
    ret = pciIntConnect ( (VOIDFUNCPTR *)(int)(dc->irq), (VOIDFUNCPTR)hbaDevIntHandler, (int) dc);
    if (ret != OK)
    {
        /*printf("pciIntConnect() Fail, irq=%d\n", dc->irq);*/
    }
#endif    
    return ret;
}

STATUS hbaDevIntDisconnect (HBA_DEV_CB *dc)
{
    STATUS ret = OK; 
#if 0    
    ret = pciIntDisconnect ( (VOIDFUNCPTR *)(int)(dc->irq), (VOIDFUNCPTR)hbaDevIntHandler);
#endif
    
    return ret;
}

STATUS hbaDevIntEnable (HBA_DEV_CB *dc)
{                                                                      
    STATUS ret = OK;  
#if 1        
    ret = intEnable ((int)dc->irq);
#endif    
    return ret;                                           
}                                           


STATUS hbaDevIntDiable(HBA_DEV_CB *dc)
{                                                                      
    STATUS ret = OK;  
#if 1        
    ret = intDisable ((int)dc->irq);
#endif    
    return ret;                                           
}        

STATUS hbaDevHwIntEnable (HBA_DEV_CB *dc)
{                                                                      
    STATUS ret = OK;  
    hwSetIntrptEnable((REG_HW *)dc->pMembaseCsr, 1);
    return ret;                                           
}                                           

STATUS hbaDevHwIntDiable(HBA_DEV_CB *dc)
{                                                                      
    STATUS ret = OK;  
    hwSetIntrptEnable((REG_HW *)dc->pMembaseCsr, 0);
    return ret;                                           
}        

/* for API */
STATUS hbaDevEnableInterrupt(HBA_DEV_CB *dc)
{
    /* �ҽ��жϴ����� */
    hbaDevIntConnect (dc);

    /* ���ж� */
    hbaDevIntEnable(dc);
    
    /* �����Ѿ�ʹ���жϱ��*/
    dc->bUseInterrupt = TRUE;

    return OK;
}

/*-------------------------------------------------------------------------*/
/* �豸�����ӿ� */
UINT32 hbaDevCreate(HBA_DEV_CB **pdc, UINT32 Device_Id)
{
    int BusNo = 0;        /* bus number */
    int DeviceNo = 0;    /* device number */
    int FuncNo = 0;        /* function number */
    UINT32 membaseCsr = 0;
    UINT8 irq;
        
    if (!bHbaDrvInited)
    {
        hbaDrvInit();
    }

    if (Device_Id >= MAX_DEVICE_NUM)
    {
        return FC_DEVICE_ID_INVALID;
    }

    if (gHbaDevCB[Device_Id].status != HBA_DEV_STATUS_NONE)
    {
        return FC_DEVICE_STATE_INVALID;
    }
    
    
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN

    if (pciFindDevice(
            0x000010ee,    /* vendor ID */
            0x00007014,    /* device ID */
            Device_Id,    /* desired instance of device */
            &BusNo,
            &DeviceNo,
            &FuncNo) != OK)
        {
            /* not found */
            return FC_DEVICE_NOT_FOUNT;
        }
    
        pciConfigInLong (BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_0, &membaseCsr);    
        pciConfigInByte (BusNo, DeviceNo, FuncNo, PCI_CFG_DEV_INT_LINE, &irq);
    
#else

    if (pcieFindDevice(
            0x000010ee,    /* vendor ID */
            0x00007014,    /* device ID */
            Device_Id,    /* desired instance of device */
            &BusNo,
            &DeviceNo,
            &FuncNo) != OK)
    {
           /* not found */
        return FC_DEVICE_NOT_FOUNT;
    }
    
    pcieConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_0, &membaseCsr);    
    pcieConfigInByte(BusNo, DeviceNo, FuncNo, PCI_CFG_DEV_INT_LINE, &irq);

#endif

    gHbaDevCB[Device_Id].BusNo         = BusNo;
    gHbaDevCB[Device_Id].DeviceNo     = DeviceNo;
    gHbaDevCB[Device_Id].FuncNo        = FuncNo;
    gHbaDevCB[Device_Id].pMembaseCsr = (UINT8 *)membaseCsr;    
    gHbaDevCB[Device_Id].irq        = irq;
    
    gHbaDevCB[Device_Id].deviceId     = Device_Id;

    /* �����������м��ź��� */
    hbaDevAllocLists(&gHbaDevCB[Device_Id]);

    /* ͳ�����ݵ��ź��� */
    gHbaDevCB[Device_Id].semStatLock = semBCreate(SEM_Q_FIFO, SEM_FULL);

    gHbaDevCB[Device_Id].semRecvListLock = semBCreate(SEM_Q_FIFO, SEM_FULL);

    /* ��ʼ�������ź��� */
    gHbaDevCB[Device_Id].semRecv = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    gHbaDevCB[Device_Id].semSentCheck = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    
    gHbaDevCB[Device_Id].semPeriodSelfCheck = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    
#ifdef HBA_INCLUDE_ELS
    
    gHbaDevCB[Device_Id].semElsCycleCheck = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    gHbaDevCB[Device_Id].semElsRecv = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    
#endif    

    /* �����Ƿ�ʹ���ж� */
    gHbaDevCB[Device_Id].bUseInterrupt = bUseInterrupt;

    /* ��λFPGA, �� MAC  */
    hwResetFpga((REG_HW *)gHbaDevCB[Device_Id].pMembaseCsr, FORCE_OFFLINE);

    gHbaDevCB[Device_Id].status = HBA_DEV_STATUS_CREATED;
    *pdc = &gHbaDevCB[Device_Id];
    
    return FC_SUCCESS;
}
    
/* �ر������豸�����ͷ��豸��Դ */
INT32 hbaDevDestroy(HBA_DEV_CB *dc)
{    

    ASSERT(dc != NULL);
    
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }

    /* ��λ�豸 */
    hbaDevReset(dc, TRUE);
    
    /* �ͷŶ��� */
    hbaDevFreeLists(dc);

    /* ͳ�����ݵ��ź��� */
    if (dc->semStatLock != NULL)
    {
        semDelete(dc->semStatLock);
        dc->semStatLock = NULL;
    }

    if (dc->semRecvListLock != NULL)
    {
        semDelete(dc->semRecvListLock);
        dc->semRecvListLock = NULL;
    }
    
    /* �ͷ��������ź��� */
    if (dc->semRecv != NULL)
    {
        semDelete(dc->semRecv);
        dc->semRecv = NULL;
    }
    
    if (dc->semSentCheck != NULL)
    {
        semDelete(dc->semSentCheck);
        dc->semSentCheck = NULL;
    }
    
    if (dc->semPeriodSelfCheck != NULL)
    {
        semDelete(dc->semPeriodSelfCheck);
        dc->semPeriodSelfCheck = NULL;
    }
    
#ifdef HBA_INCLUDE_ELS
    
    if (dc->semElsCycleCheck != NULL)
    {
        semDelete(dc->semElsCycleCheck);
        dc->semElsCycleCheck = NULL;
    }

    if (dc->semElsRecv != NULL)
    {
        semDelete(dc->semElsRecv);
        dc->semElsRecv = NULL;
    }
    
#endif

    dc->status = HBA_DEV_STATUS_NONE;
    return DEV_SUCCESS;
}

/*���豸*/
 UINT32 hbaDevOpen(HBA_DEV_CB **pdc, UINT32 Device_Id)
{
    if (!bHbaDrvInited)
    {
        hbaDrvInit();
        bHbaDrvInited = TRUE;
    }

    if (Device_Id >= MAX_DEVICE_NUM)
    {
        return FC_DEVICE_ID_INVALID;
    }

    if (gHbaDevCB[Device_Id].status == HBA_DEV_STATUS_NONE)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    *pdc = &gHbaDevCB[Device_Id];
    
    return FC_SUCCESS;
}

void hbaDevClose(HBA_DEV_CB *dc)
{
    /*do nothing */
}

/* �豸������ʼ���ӿ� */
INT32 hbaDevInitialize(HBA_DEV_CB *dc)
{
    UINT32 port, fcid, speed, credit, send_item_count, recv_item_count;
    FC_PORT_CONFIG *pc;
    FC_MSG_SEND_ITEM *send_item;
    FC_MSG_RECV_ITEM *recv_item;
    REG_HW *reg_hw;
    
    ASSERT(dc);
    
    if (dc->status != HBA_DEV_STATUS_CREATED)
    {
        return DEV_INVALID_OP;
    }

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    
    /* ��λFPGA */
    hwResetFpga(reg_hw, NO_FORCE_OFFLINE);
    
    /* ���������ͨ�������� */
    hwClearAllChannel(reg_hw);
    hwInitElsChannel(reg_hw);
    
    hwInitOxid(reg_hw);

    /*����������NC�ڵ��FCIDΪ��Ч��FCID*/
    dc->ncFcid = FC_FCID_EMPTY;

    /*ASM���ͽ��տ��� 0-��ֹASM���ͽ��� 1-����ASM���ͽ���*/
    dc->asmRunControl = FC_ASM_RUN_ENAB;

    /*����NC�ڵ�ȴ������б��NC�ڵ㷢������֡��������*/
    dc->wdtInitCounter = 2;

    pc = &dc->configBlock.port_config;
    send_item = &dc->configBlock.send_item[0];
    recv_item = &dc->configBlock.recv_item[0];
    send_item_count = pc->block_txmsg_num + pc->nonblock_txmsg_num;
    recv_item_count = pc->block_rxmsg_num + pc->nonblock_rxmsg_num;

    if ((send_item_count > MAX_SEND_CHANNEL_NUM)  || (recv_item_count > MAX_RECV_CHANNEL_NUM))
    {
        return DEV_CONFIG_DATA_INVALID;
    }
    
    port = 0;
    fcid = pc->port_id;
    speed = PORT_SPEED_2G;
    credit = pc->credit_num;

    /*���ö˿�*/
    hbaDevSetPortFcid(dc, port, fcid);

    /*��������*/
    hbaDevSetPortSpeed(dc, port, speed);

    /*��������*/
    hbaDevSetPortBBCredit(dc, port, credit);

    /*����ʱ��ͬ������*/
    hbaDevSetClkSyncPeriod(dc, dc->configBlock.port_config.clk_sync_period);
    
#if 1/*liujin added for rtc*/
    /*����ʱ��ͬ��ʹ��*/
    if(dc->configBlock.port_config.clk_sync_role == CLK_SYNC_ROLE_SERVER_MASTER)
    {
        hbaDevSetRTCRxTx(dc, 0, 1);    
    }
    else
    {
        hbaDevSetRTCRxTx(dc, 1, 0);    
    }    
#endif
    /*���WDT�������ںͼ������*/
    if(hbaDevCheckWdtPeriod(dc) != DEV_SUCCESS)
    {
        return DEV_OTHER_FAILURE;
    }

    if (g_hbaDebug & HBA_DBG_CONFIG)
    {
        printf("hbaDevInitialize: port_id = 0x%x,  speed = %d, credit = %d\n", fcid, speed, credit);
    }

    /* ����RAW�շ�ͨ�� */
    if (hbaDevRegisterRawChannels(dc) != OK)
    {
        return DEV_OTHER_FAILURE;
    }
    
    /* ����ASM�շ�ͨ�� */
    if (hbaDevRegisterAsmChannels(dc, send_item_count, send_item, recv_item_count, recv_item) != OK) 
    {
        return DEV_OTHER_FAILURE;
    }

    /* ����ASM�շ�DMA���� */
    if (hbaDevAllocDmaBuffers(dc)!= OK)
    {
        return DEV_OTHER_FAILURE;
    }
    
    if (g_hbaDebug & HBA_DBG_CONFIG)
    {
        printf("hbaDevAllocDmaBuffers OK\n");
    }

    /* stop��������³�ʼ����������run */
    dc->bToStop = FALSE;    

#ifdef USE_IU_TIMEOUT
    
    /* ����IU timcout��tick�� */
    dc->recvIUTimeoutTick = (RECV_IU_TIMEOUT * sysClkRateGet()) / 1000;
    
#endif
    
    dc->status = HBA_DEV_STATUS_INITED;
        
    return DEV_SUCCESS;
}

/* ��ȡ���ؽӿڵ�ǰ�Ĺ���״̬ */
INT32 hbaDevGetDevState(HBA_DEV_CB *dc, UINT32 *cardSts, UINT32 count)
{
    REG_HW *reg_hw;
    
    ASSERT(dc != NULL);
    
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    hwGetPortStatus(reg_hw, (int *)cardSts, count);

    return DEV_SUCCESS;
}

/* ��ȡ��Ӳ���汾��Ϣ */
INT32 hbaDevGetVersion(HBA_DEV_CB *dc, UINT32 * version)
{
    int value;
    REG_HW *reg_hw;
    
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }
    reg_hw = (REG_HW *)dc->pMembaseCsr;
    value = hwGetFpgaVersion(reg_hw);
    *version = (MAJOR_VER << 24) | (MINOR_VER<<16) | ((value & 0xFF) << 8) | FIRMWARE_VER;
    
    return DEV_SUCCESS;
}

void hbaDevWakeupAllRecv(HBA_DEV_CB *dc)
{
    int i;
    
    ASSERT(dc != NULL);


    /* �������е�ͨ���ϵȴ�buffer������ */
    for (i=0; i<dc->asmRecvChannelCount; i++)
    {
        semGive(dc->asmRecvChannels[i].semRecvBufferValid);
    }
    semGive(dc->rawRecvChannel.semRecvBufferValid);
}

void hbaDevWakeupAllSend(HBA_DEV_CB *dc)
{
    int i;
    
    ASSERT(dc != NULL);

    semGive(dc->semSendShareBufferValid);

#if 1
    /* �������е�ͨ���ϵȴ�buffer������ */
    for (i=0; i<dc->asmSendChannelCount; i++)
    {
        semGive(dc->asmSendChannels[i].semSendBufferValid);
    }
    semGive(dc->rawSendChannel.semSendBufferValid);
#endif        
}

void hbaDevWakeupAllDevTasks(HBA_DEV_CB *dc)
{
    
    ASSERT(dc != NULL);

    if (dc->semRecv)
    {
        semGive(dc->semRecv);
    }
    if (dc->semSentCheck)
    {
        semGive(dc->semSentCheck);
    }
    if (dc->semPeriodSelfCheck)
    {
        semGive(dc->semPeriodSelfCheck);
    }

#ifdef HBA_INCLUDE_ELS    
    if (dc->semElsCycleCheck)
    {
        semGive(dc->semElsCycleCheck);
    }
    if (dc->semElsRecv)
    {
        semGive(dc->semElsRecv);
    }
#endif    

}

INT32 hbaDevStartTasks(HBA_DEV_CB *dc)
{
    /* ���������߳� */
    dc->recvTaskId = 
        (HBA_RCV_TASK_NAME, 
                    HBA_RCV_TASK_PRIORITY, 
                    0, 
                    HBA_RCV_TASK_STACKSIZE, 
                    hbaDevRecvTask, (int)dc, 
                    0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (dc->recvTaskId == ERROR)
    {
        printf("hbaDevRun: taskSpawn %s fail.\n", HBA_RCV_TASK_NAME);
        return DEV_OTHER_FAILURE;
    }
    /*printf("hbaDevRun: taskSpawn %s OK.\n", HBA_RCV_TASK_NAME);*/

    dc->sentCheckTaskId = taskSpawn ( HBA_SENT_CHECK_TASK_NAME, 
                    HBA_SENT_CHECK_TASK_PRIORITY, 
                    0, 
                    HBA_SENT_CHECK_TASK_STACKSIZE, 
                    hbaDevSentCheckTask, (int)dc, 
                    0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (dc->sentCheckTaskId == ERROR)
    {
        printf("hbaDevRun: taskSpawn %s fail.\n", HBA_SENT_CHECK_TASK_NAME);
        return DEV_OTHER_FAILURE;
    }
    /*printf("hbaDevRun: taskSpawn %s OK.\n", HBA_SENT_CHECK_TASK_NAME);*/
    
    /*�����Լ�˿ڵ�link״̬*/
    dc->periodSelfCheckTaskId = taskSpawn(
                    HBA_PERIOD_CHECK_TASK_NAME, 
                    HBA_PERIOD_CHECK_TASK_PRIORITY, 
                    0, 
                    HBA_PERIOD_CHECK_TASK_STACKSIZE, 
                    hbaDevPeriodSelfCheckTask,
                    (int)dc,
                    0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (dc->periodSelfCheckTaskId == ERROR)
    {
        printf("hbaDevRun: taskSpawn %s fail.\n", HBA_PERIOD_CHECK_TASK_NAME);
        return DEV_OTHER_FAILURE;
    }

#ifdef HBA_INCLUDE_ELS
    
    /* ���ڷ���ELS֡ */
    dc->hbaElsCycleCheckTaskId = taskSpawn(
                    HBA_ELS_CYCLE_CHECK_TASK_NAME,
                    HBA_ELS_CYCLE_CHECK_TASK_PRIORITY, 
                    0, 
                    HBA_ELS_CYCLE_CHECK_TASK_STACKSIZE, 
                    hbaElsCycleCheckTask, (int)dc,
                    0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (dc->hbaElsCycleCheckTaskId == ERROR)
    {
        printf("hbaDevRun: taskSpawn %s fail.\n", HBA_ELS_CYCLE_CHECK_TASK_NAME);
        return DEV_OTHER_FAILURE;
    }
    
    /* ELS���ջص� */
    dc->hbaElsRecvTaskId = taskSpawn(
                    HBA_ELS_RECV_TASK_NAME,
                    HBA_ELS_RECV_TASK_PRIORITY, 
                    0, 
                    HBA_ELS_RECV_TASK_STACKSIZE, 
                    hbaElsRecvTask, (int)dc,
                    0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (dc->hbaElsRecvTaskId == ERROR)
    {
        printf("hbaDevRun: taskSpawn %s fail.\n", HBA_ELS_RECV_TASK_NAME);
        return DEV_OTHER_FAILURE;
    }

#endif

    return DEV_SUCCESS;
}

/* �豸ͨ��ʹ�� */
INT32 hbaDevRun(HBA_DEV_CB *dc)
{
    INT32 ret;
    REG_HW *reg_hw;
    
    if (dc->status != HBA_DEV_STATUS_INITED)
    {
        return DEV_INVALID_OP;
    }

    /* ֹͣ�������Reset�����³�ʼ������start */
    if (dc->bToStop)    
    {
        /*printf("After hbaDevStop(), must reset and reinitialize again before hbaDevRun().\n");*/
        return DEV_INVALID_OP;
    }

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    /* dc->bToStop = FALSE; */

#ifndef AE653_BUILD    

    ret = hbaDevStartTasks(dc);
    
#else
    
    ret = DEV_SUCCESS;
    
#endif


    if (dc->bUseInterrupt)
    {
        /* �ҽ��жϴ����� */
        hbaDevIntConnect (dc);
        
        /* ���ж� */
        hbaDevIntEnable(dc);
    }

    hwSetPortRxEnab(reg_hw, 1);
    
    dc->status = HBA_DEV_STATUS_STARTED;

    return ret;
}

/*
  ����:
   bForceOffLine: ָ���Ƿ�ִ�� offline-online���� 
*/
UINT32 hbaDevStop(HBA_DEV_CB *dc, BOOL bForceOffLine)
{
    INT32 ret;

    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return DEV_INVALID_OP;
    }

    dc->bToStop = TRUE;

    /* �ر��ж� */
    if (dc->bUseInterrupt)
    {
        hbaDevIntDiable(dc);
        
        /* ж���жϴ����� */
        hbaDevIntDisconnect (dc);
    }
    
    hwSetPortRxEnab((REG_HW *)(dc->pMembaseCsr), 0);
    
    /* �ر�����ͨ����λFPGA */
    ret = hbaCloseAllChannel(dc);
    if (ret != DEV_SUCCESS)
    {
        return ret;
    }
    
    /* ��λFPGA */
    /*hwResetFpga((REG_HW *)dc->pMembaseCsr, (bForceOffLine? FORCE_OFFLINE : NO_FORCE_OFFLINE ));*/

  if ( bForceOffLine >0 )
      {
          hwResetFpga((REG_HW *)dc->pMembaseCsr, FORCE_OFFLINE);
      }
  else
      {
          hwResetFpga((REG_HW *)dc->pMembaseCsr, NO_FORCE_OFFLINE);
      }


    /*wakeup all thread suppended for sending or receving*/
    hbaDevWakeupAllRecv(dc);
    hbaDevWakeupAllSend(dc);

    /* notify and wait the recv task to exit */
    hbaDevWakeupAllDevTasks(dc);

#ifndef AE653_BUILD    
    
    while(1)
    {
        if (dc->recvTaskId == ERROR)
        {
            break;
        }
        taskDelay(1);
    }
    /*printf("%s task exit OK.\n", HBA_RCV_TASK_NAME);*/

    while(1)
    {
        if (dc->sentCheckTaskId == ERROR)
        {
            break;
        }
        taskDelay(1);
    }
    /*printf("%s task exit OK.\n", HBA_SENT_CHECK_TASK_NAME);*/

    while(1)
    {
        if (dc->periodSelfCheckTaskId == ERROR)
        {
            break;
        }
        taskDelay(1);
    }
    /*printf("%s task exit OK.\n", HBA_PERIOD_CHECK_TASK_NAME);*/

#ifdef HBA_INCLUDE_ELS    

    while(1)
    {
        if (dc->hbaElsCycleCheckTaskId == ERROR)
        {
            break;
        }
        taskDelay(1);
    }
    /*printf("%s task exit OK.\n", HBA_ELS_CYCLE_CHECK_TASK_NAME);*/

    while(1)
    {
        if (dc->hbaElsRecvTaskId == ERROR)
        {
            break;
        }
        taskDelay(1);
    }
    /*printf("%s task exit OK.\n", HBA_ELS_RECV_TASK_NAME);*/
    dc->status = HBA_DEV_STATUS_INITED;
#endif

#else 
    /* in vxworks653 */
    dc->status = HBA_DEV_STATUS_INITED;

    hbaDevWakeupAllDevTasks(dc);
    
    taskDelay(50);
    
#endif
    return DEV_SUCCESS;

}

/*������������������������������������������������ͨ�Ź���������������������������������������������������������*/

/* �������ݿ���Ϣ */
UINT32 hbaDevSendAsmMsg(HBA_DEV_CB *dc, UINT32 msgID, UINT8 *pData, UINT32 length, int timeout)
{
    W_CTRL *ctrl;
    SEND_BUFFER * pSendBuffer = NULL;
    int ch = -1;
    int leftLen = length;
    int offset = 0;
    int maxDataPerBuf = (MAX_SEND_BUFER_LEN - ((UINT32)&(((SEND_DMA_BUFFER*)0)->data)));

    ch = hbaDevGetSendChannelNoFromMsgID(dc, msgID);
    if (ch == -1)
    {
        return FC_MSG_ID_INVALID;
    }
    
    while(leftLen)
    {
        int len = 0;

#ifdef USE_SEND_SHARE_BUFFER    
        pSendBuffer = hbaDevAllocSendBufferFromSharePool(dc, timeout);
#endif
        
        if (pSendBuffer == NULL)
        {
            return FC_SEND_MSG_BUFFER_EMPTY;
        }
        pSendBuffer->ch = ch;
        len = min(maxDataPerBuf, leftLen);

        hbaDrvMemCopy(&pSendBuffer->pBuffer->data[0], &pData[offset], len);

        ctrl = (W_CTRL *)pSendBuffer->pBuffer;
        ctrl->w0.value = 0;
        ctrl->w0.u.length = len + sizeof(W_CTRL); /* ����w0 w1�ĳ���8���ֽ� */
        if (leftLen == length)
        {
            ctrl->w0.u.sop = 1;
        }
        else
        {
            ctrl->w0.u.sop = 0;
        }
        
        if (leftLen == len)
        {
            ctrl->w0.u.eop = 1;
        }
        else
        {
            ctrl->w0.u.eop = 0;
        }

        if (g_hbaDebug & HBA_DBG_SEND)
        {
            printf("sop=%d, eop=%d\n", ctrl->w0.u.sop, ctrl->w0.u.eop);
        }
        ctrl->w0.u.mode = ASM_MODE;

        ctrl->w1.value = 0;
        if (length == MAX_IU_LEN)
        {
            ctrl->w1.u.length = 0; /*  16M ʱ�� asm��length����Ϊ0 */
        }
        else
        {
            ctrl->w1.u.length = length;
        }
        ctrl->w1.u.priority = dc->asmSendChannels[ch].priority;
        ctrl->w1.u.l = 0;
        
        if (dc->asmSendChannels[ch].bIsStream)
        {
            pSendBuffer->bStream = TRUE;
        }
        else
        {
            pSendBuffer->bStream = FALSE;
        }
        
        dc->asmSendChannels[ch].sendBuffers ++;
        dc->asmSendChannels[ch].sendBytes = dc->asmSendChannels[ch].sendBytes + len;
        
        if (hbaDevSendMsg(dc, dc->asmSendChannels[ch].priority, pSendBuffer) != DEV_SUCCESS)
        {
            return FC_FAILURE;
        }
        offset = offset + len;
        leftLen = leftLen - len;
    }
    
    dc->sentIUs ++;
    
    return FC_SUCCESS;
}

/*�������ݿ���Ϣ*/
UINT32 hbaDevSendRawMsg(HBA_DEV_CB *dc, UINT8 *pData, UINT32 length, int timeout)
{
    UINT32 ret;
    SEND_BUFFER * pSendBuffer = NULL;
    W_CTRL *ctrl;
    int maxDataPerBuf = (MAX_SEND_BUFER_LEN - ((UINT32)&(((SEND_DMA_BUFFER*)0)->data)));
    
    if (pData == NULL)
    {
        return RAW_PARAMS_INVALID;
    }

    if (length == 0 || length > maxDataPerBuf)
    {
        return RAW_MSG_LEN_INVALID;
    }

    /*�ж��Ƿ�����IO*/
    ret = HbaDevIoState(dc, IO_STATE_MODE_RAW);
    if (ret)
    {
        return ret;
    }

#ifdef USE_SEND_SHARE_BUFFER    
    pSendBuffer = hbaDevAllocSendBufferFromSharePool(dc, timeout);
#endif

    if (pSendBuffer == NULL)
    {
        return RAW_MSG_BUFFER_EMPTY;
    }
    pSendBuffer->ch = RAW_CHANNNEL_NO;

    ctrl = (W_CTRL *)pSendBuffer->pBuffer;    
    hbaDrvMemCopy(&pSendBuffer->pBuffer->data[0], pData, length);
    ctrl->w0.value = 0;
    ctrl->w1.value = 0;
    ctrl->w0.u.length = length + sizeof(W_CTRL);
    pSendBuffer->bStream = FALSE;
    
    if (hbaDevSendMsg(dc, PRIORITY_LEVEL_RAW_MSG, pSendBuffer) != DEV_SUCCESS)
    {
        return RAW_OTHER_FAILURE;
    }
    dc->sentRawBuffers ++;
    
    return DEV_SUCCESS;
}


UINT32 hbaDevRecvAsmMsg(HBA_DEV_CB *dc, UINT msgID, UINT8 * pMsg, UINT * nLen, int timeout)
{
    int ch = -1;    
    ULONG tickFrom = tickGet();
    int waitTime = 0;

    ch = hbaDevGetRecvChannelNoFromMsgID(dc, msgID);
    if (ch == -1)
    {
        return FC_MSG_ID_INVALID;
    }
    
    /* without IU buffer */
    {
        int uiLen = 0;
        while(1)
        {
            int iret = OK;
            UINT bufLen = *nLen;
            
            /* ��list_recved������buffer ���һ��IU */                        
            uiLen = hbaDevGetUIFromRecvBufList( dc,
                                                ch, 
                                                pMsg, 
                                                bufLen);
            if (uiLen == 0)
            {
                /* ��û�н�β�������ȴ� */
            }
            else if (uiLen > 0)
            {
                break;
            } 
            else /* (uiLen < 0) */
            {
                /* ���Ȳ�������һ��IU */
                return FC_RECV_LENGTH_TOO_SMALL;
            }

            /* ����ʣ��ɵȴ���ʱ�� */
            if (timeout == WAIT_FOREVER)
            {
                waitTime = WAIT_FOREVER;
            }
            else if (timeout == NO_WAIT)
            {
                return FC_RECV_NO_DATA;
            }
            else
            {            
                waitTime = timeout - (tickGet() - tickFrom);
                if (waitTime <= 0)
                {
                    return FC_RECV_ASM_TIMEOUT;
                }
            }
            
            iret = semTake(dc->asmRecvChannels[ch].semRecvBufferValid, waitTime);
            if (iret == ERROR)
            {
                return FC_FAILURE;
            }
            if (dc->bToStop == TRUE)
            {
                return FC_DEV_CLOSED;
            }
        }

        *nLen = uiLen;
        
        /*
        printf("uiLen =%d\n", uiLen);
        */

        return FC_SUCCESS;
    }
}




INT32 hbaDevRecvRawMsg(HBA_DEV_CB *dc, UINT8 *pMsg, UINT *nLen, int timeout)
{
    int bufLen = 0, waitTime = 0;
    ULONG tickFrom = tickGet();
    RECV_BUFFER *pRecvBuffer = NULL;

    ASSERT(dc != NULL);
    if (pMsg == NULL)
    {
        return RAW_PARAMS_INVALID;
    }
    /* ��鳤���Ƿ���Ч */
    if (nLen == NULL || *nLen == 0)
    {
        return RAW_MSG_LEN_INVALID;
    }
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return DEV_INVALID_OP;
    }

    /* ѭ���ȴ���ֱ��������������һ��buffer���˳� */
    while(1)
    {
        pRecvBuffer = (RECV_BUFFER *)listGetFirstNodeFromList(&dc->rawRecvChannel.list_recved);
        if (pRecvBuffer == 0)
        {
            int iret = OK;
            
            /* ����ʣ��ɵȴ���ʱ�� */
            if (timeout == WAIT_FOREVER)
            {
                waitTime = WAIT_FOREVER;
            }
            else if (timeout == NO_WAIT)
            {
                return RAW_RECV_NO_DATA;
            }
            else
            {            
                waitTime = timeout - (tickGet() - tickFrom);
                if (waitTime <= 0)
                {
                    return RAW_RECV_TIMEOUT;
                }
            }    
            
            iret = semTake(dc->rawRecvChannel.semRecvBufferValid, waitTime);
            if (iret == ERROR)
            {
                return RAW_OTHER_FAILURE;
            }    
            if (dc->bToStop == TRUE)
            {
                return DEV_ALL_CLOSED;
            }
        }
        else
        {
            break;
        }
    }

    pRecvBuffer = (RECV_BUFFER *)listGetFirstNodeFromList(&dc->rawRecvChannel.list_recved);
    bufLen = hbaDrvGetRecvBufLen(pRecvBuffer->pBuffer);
    if (bufLen > *nLen)
    {
        return RAW_MSG_LEN_INVALID;
    }
    
    hbaDrvMemCopy(pMsg, &pRecvBuffer->pBuffer->data[0], bufLen);
    *nLen = bufLen;

    pRecvBuffer = (RECV_BUFFER *)listRemoveNodeFromListHead(&dc->rawRecvChannel.list_recved);
    /* ���ս���buffer */
    hbaDevFreeRecvBuffer(dc, pRecvBuffer);
    
    return DEV_SUCCESS;
}

INT32 hbaDevRegMsgHandler(HBA_DEV_CB *dc, FC_ASM_RECVMSG_FUNCPTR func)
{
    ASSERT(dc != NULL);
    
    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }
    dc->pRecvCallBackFunc = func;

    return DEV_SUCCESS;
}

INT32 hbaDevUnRegMsgHandler(HBA_DEV_CB *dc)
{

    if (dc->status == HBA_DEV_STATUS_NONE)
    {
        return DEV_INVALID_OP;
    }
    dc->pRecvCallBackFunc = NULL;

    return DEV_SUCCESS;
}

int iCheckFlashWrite = 0;
INT32 hbaDevFlashConfig(HBA_DEV_CB *dc, CONFIG_BLOCK *cb, UINT32 majorSchemeNum, UINT32 minorSchemeNum)
{
    int ret;
    UINT32 schemeAddress;
    int len=0;
    UINT8 *pBuf = NULL;  /*��ΪFLASH Ҫ256 ���룬��CONFIG_BLOCKû�ж��룬���Լӱ�������*/
    UINT8 *pBuf2 = NULL;

    ASSERT(dc);
    
    pBuf = (UINT8*)HBA_MALLOC(FC_MINOR_SCHEME_SIZE);
    if(pBuf == NULL)
    {
        /*printf("malloc error!\n");*/
        return DEV_FLASH_WR_FAIL;
    }

    pBuf2 = (UINT8*)HBA_MALLOC(FC_MINOR_SCHEME_SIZE);
    if(pBuf2 == NULL)
    {
        /*printf("malloc error!\n");*/
        HBA_MEM_FREE(pBuf);
        return DEV_FLASH_WR_FAIL;
    }

    /* Flash ģʽ*/
    len = sizeof(CONFIG_BLOCK);
    schemeAddress = FC_SCHEME_ADDRESS + (majorSchemeNum * FC_MAJOR_SCHEME_SIZE) +( minorSchemeNum * FC_MINOR_SCHEME_SIZE);

    len = sizeof(CONFIG_BLOCK);
    memcpy(pBuf, cb, len);
    ret = hbaDevFlashWrite(dc,  schemeAddress, (UINT8 *)pBuf, FC_MINOR_SCHEME_SIZE);

    if(g_hbaDebug & HBA_DBG_CONFIG)
    {
        printf("write flash scheme return %d, Addr=0x%x, majorScheme=%d, minorScheme=%d!\n", ret, schemeAddress, majorSchemeNum, minorSchemeNum);
    }

    if (ret == -1)
    {
        HBA_MEM_FREE(pBuf);
        HBA_MEM_FREE(pBuf2);
        return DEV_FLASH_WR_FAIL;
    }

    if(iCheckFlashWrite)
    {
        ret = hbaDevFlashRead(dc,  schemeAddress, (UINT8 *)pBuf2, FC_MINOR_SCHEME_SIZE);
        if (ret == -1)
        {
            /*printf("Read flash scheme return %d, Addr=0x%x, majorScheme=%d, minorScheme=%d!\n", ret, schemeAddress, majorSchemeNum, minorSchemeNum);*/
            
            HBA_MEM_FREE(pBuf);
            HBA_MEM_FREE(pBuf2);
            return DEV_FLASH_WR_FAIL;
        }

        if (memcmp(pBuf, pBuf2, FC_MINOR_SCHEME_SIZE) != 0)
        {
            /*printf("Compare flash scheme return %d, Addr=0x%x, majorScheme=%d, minorScheme=%d!\n", ret, schemeAddress, majorSchemeNum, minorSchemeNum);*/
            
            HBA_MEM_FREE(pBuf);
            HBA_MEM_FREE(pBuf2);
            return DEV_FLASH_WR_FAIL;
        }
    }

    HBA_MEM_FREE(pBuf);
    HBA_MEM_FREE(pBuf2);
    
    return DEV_SUCCESS;
}


void hbaDevInitConfigDataForEnginMode(HBA_DEV_CB *dc)
{
    UINT32 majorScheme, minorScheme;
    BLUE_PRINT *bluePrint;
    CONFIG_BLOCK *configBlock;

    ASSERT(dc);
    ASSERT(dc->configMode == CONFIG_MODE_PROJECT);

    /* ���ݴ�С�汾�Ŵ���ͼ�Ӷ�λ�����ÿ��λ�� */
    majorScheme = dc->majorScheme;
    minorScheme = dc->minorScheme;
    bluePrint = &gBluePrint[majorScheme];

    printf("abc=%d\n", abc);

    configBlock = &bluePrint->config_block[minorScheme];

    /* �������ÿ鵽dc�� */
    memcpy(&dc->configBlock, configBlock, sizeof(CONFIG_BLOCK));
}

INT32 hbaDevInitConfigDataForFlashMode(HBA_DEV_CB *dc)
{
    int ret;
    CONFIG_BLOCK *cb;
    UINT32 majorSchemeNum, minorSchemeNum;
    UINT32 schemeAddr;

    int len = 0;

    /* Flash ģʽ*/
    majorSchemeNum = dc->majorScheme;
    minorSchemeNum = dc->minorScheme;
    
    /*minorSchemeNum = 0;*/
    cb = &dc->configBlock;
    len = sizeof(CONFIG_BLOCK);
    schemeAddr = FC_SCHEME_ADDRESS + (majorSchemeNum* FC_MAJOR_SCHEME_SIZE) + (minorSchemeNum*FC_MINOR_SCHEME_SIZE);

    if(g_hbaDebug & HBA_DBG_CONFIG)
    {
        printf("read flash scheme start Addr=0x%x, majorScheme=%d, minorScheme=%d, len=%d!\n", schemeAddr, majorSchemeNum, minorSchemeNum, len);
    }
    
    ret = hbaDevFlashRead(dc, schemeAddr, (UINT8 *)cb, len);
    if(g_hbaDebug & HBA_DBG_CONFIG)
    {
        printf("read flash scheme return %d, Addr=0x%x, majorScheme=%d, minorScheme=%d!\n", ret, schemeAddr, majorSchemeNum, minorSchemeNum);
    }
    if (ret == -1)
    {
        return DEV_FLASH_WR_FAIL;
    }
    
    
    return DEV_SUCCESS;
}

/*ȡ������ڵ�ͳ����Ϣ*/
void hbaDevGetLocalStatistics(HBA_DEV_CB *dc, NetStatistics *pNetStatistics)
{
    int i;
    
    semTake(dc->semStatLock, WAIT_FOREVER);
    
    memset(pNetStatistics, 0, sizeof(NetStatistics));
    
    for (i = 0; i < FC_PORT_NUM_MAX; i++)
    {
        pNetStatistics->RxMinFrameErrCnt[i] = (UINT32)(dc->portStatInfo[i].RxUndersizeFrameCnt);
        pNetStatistics->RxMaxFrameErrCnt[i] = (UINT32)(dc->portStatInfo[i].RxOversizeFrameErrCnt);
        pNetStatistics->RxFrameCnt[i]         = (UINT32)(dc->portStatInfo[i].RxValidFrameCnt);
        pNetStatistics->RxWordCnt[i]         = (UINT32)(dc->portStatInfo[i].RxWordCnt);
        pNetStatistics->RxRRDYCnt[i]         = (UINT32)(dc->portStatInfo[i].RxRRDYCnt);
        
        pNetStatistics->RxPSMErrCnt[i]         = (UINT32)(dc->portStatInfo[i].RxAllFrameCnt - 
                                                        dc->portStatInfo[i].RxValidFrameCnt - 
                                                        dc->portStatInfo[i].RxUndersizeFrameCnt -
                                                        dc->portStatInfo[i].RxOversizeFrameErrCnt);
        
        pNetStatistics->TxFrameCnt[i]         = (UINT32)(dc->portStatInfo[i].TxValidFrameCnt);
        pNetStatistics->TxWordCnt[i]         = (UINT32)(dc->portStatInfo[i].TxWordCnt);
        pNetStatistics->TxKErrCnt[i]         = (UINT32)(dc->portStatInfo[i].TxKErrCnt);
        pNetStatistics->TxRRDYCnt[i]         = (UINT32)(dc->portStatInfo[i].TxRRDYCnt);
    }

    /* Clear the stat data after reading */
    /* memset(&dc->portStatInfo, 0, sizeof(dc->portStatInfo)); */
    
    semGive(dc->semStatLock);

    return;
}

/*ת������ڵ�ͳ����Ϣ��������*/
void hbaDevConvertStatistics(NetStatistics *pNetStatistics)
{
    int i;
    
    for (i = 0; i < FC_PORT_NUM_MAX; i++)
    {
        pNetStatistics->RxMinFrameErrCnt[i] = HbaUlongByteSwap(pNetStatistics->RxMinFrameErrCnt[i]);
        pNetStatistics->RxMaxFrameErrCnt[i] = HbaUlongByteSwap(pNetStatistics->RxMaxFrameErrCnt[i]);
        pNetStatistics->RxFrameCnt[i]         = HbaUlongByteSwap(pNetStatistics->RxFrameCnt[i]);
        pNetStatistics->RxWordCnt[i]         = HbaUlongByteSwap(pNetStatistics->RxWordCnt[i]);
        pNetStatistics->RxRRDYCnt[i]         = HbaUlongByteSwap(pNetStatistics->RxRRDYCnt[i]);
        
        pNetStatistics->RxPSMErrCnt[i]         = HbaUlongByteSwap(pNetStatistics->RxPSMErrCnt[i]);
        
        pNetStatistics->TxFrameCnt[i]         = HbaUlongByteSwap(pNetStatistics->TxFrameCnt[i]);
        pNetStatistics->TxWordCnt[i]         = HbaUlongByteSwap(pNetStatistics->TxWordCnt[i]);
        pNetStatistics->TxKErrCnt[i]         = HbaUlongByteSwap(pNetStatistics->TxKErrCnt[i]);
        pNetStatistics->TxRRDYCnt[i]         = HbaUlongByteSwap(pNetStatistics->TxRRDYCnt[i]);
    }

    return;
}


void hbaDevClearDeviceStat(HBA_DEV_CB *dc)
{
    int ch;
    
    dc->sentBytes = 0;
    dc->recvBytes = 0;
    dc->recvMoveBytes = 0;
    dc->sentIUs = 0;
    dc->recvIUs = 0;
    dc->dicardIUs = 0;
    dc->coverIUs = 0;
    dc->exceptionIUs = 0;
    dc->sentRawBuffers = 0;
    dc->recvRawBuffers = 0;
    dc->sendBuffers = 0;
    dc->recvBuffers = 0;    
    
    dc->sendCmptBuffers = 0;

    memset(&dc->fpgaStatInfo, 0, sizeof(dc->fpgaStatInfo));
    memset(&dc->portStatInfo, 0, sizeof(dc->portStatInfo));

    for (ch=0; ch<dc->asmRecvChannelCount; ch++)
    {
        dc->asmRecvChannels[ch].totalIuCount = 0;
        dc->asmRecvChannels[ch].discardIuCount = 0;  /*������IU ����*/
        dc->asmRecvChannels[ch].coverIuCount = 0;       /*���ǵ�IU ����*/

        dc->asmRecvChannels[ch].IuLenException = 0;     /*IU�����쳣�ĸ���ͳ��*/
        dc->asmRecvChannels[ch].IuSeqException = 0;
        dc->asmRecvChannels[ch].IuTmroutException = 0;        
    
        dc->asmRecvChannels[ch].recvBuffers = 0;
        dc->asmRecvChannels[ch].recvBytes = 0;
    }

    for (ch=0; ch<dc->asmSendChannelCount; ch++)
    {
        dc->asmSendChannels[ch].sendBuffers = 0;
        dc->asmSendChannels[ch].sendBytes = 0;
    }    
    
}

INT32 hbaDevIsOnNet(HBA_DEV_CB *dc)
{
    FCUCHAR net_status;
    FCUINT port_id;

    if (dc->asmRunControl == FC_ASM_RUN_ENAB)
    {
        port_id = dc->configBlock.port_config.port_id & 0xFF;
        if (port_id >= FC_SW_PORT_NUM_MAX)
        {
            /*printf("port_id = 0x%08x SW_PORT_NUM = %d\n",port_id,SW_PORT_NUM);*/
            return DEV_OTHER_FAILURE;
        }
        net_status = dc->onNetTbl.Status[port_id];
        if (net_status == 0)
        {
            /*printf("port_id = 0x%08x net_status = 0\n",port_id);*/
            return DEV_OTHER_FAILURE;
        }
    }
    return DEV_SUCCESS;
}

/*�ж��豸��IO״̬*/
UINT32 HbaDevIoState(HBA_DEV_CB *dc, UINT32 mode)
{
    /*�豸û������*/
    if (dc->status != HBA_DEV_STATUS_STARTED)
    {
        return FC_DEVICE_STATE_INVALID;
    }

    /*�˿���linkdown*/
    if (dc->linkStatus != IC_LINK_STATUS_SUCCESS)
    {
        return FC_PORT_LINK_DOWN;
    }

    if (mode == IO_STATE_MODE_ASM)
    {
        /*ASM�����ǽ�ֹ��*/
        if (dc->asmRunControl != FC_ASM_RUN_ENAB)
        {
            return FC_ASM_RUN_INVALID;
        }
    }
    else
    {
        /*RAW*/

    }

    return FC_SUCCESS;
}


/******************************************************************************
* ���Ժ���                                                                                                                                                                                       *
******************************************************************************/
#define HBA_SHOW_DEVCB                 0x00000001
#define HBA_SHOW_LIST                 0x00000002
#define HBA_SHOW_STAT                 0x00000004
#define HBA_SHOW_CHANNL             0x00000008
#define HBA_SHOW_RECV_CHANNL_STAT     0x00000010
#define HBA_SHOW_SEND_CHANNL_STAT     0x00000020
#define HBA_SHOW_PORT_STAT          0x00000040
#define HBA_SHOW_ELS_INFO           0x00000080

int hbaDrvPrintSendBuffer(LIST_NODE *ptr,  UINT32 opaque)
{
    SEND_BUFFER *pSendBuf = (SEND_BUFFER *)ptr;

    if (opaque == 3)
    {
        printf("    Buffer %p, bufferIndex %d, DMABuffer %p\n", ptr, pSendBuf->bufferIndex, pSendBuf->pBuffer);
    }
    else
    {
        printf("    Buffer %p, bufferIndex %d \n", ptr, pSendBuf->bufferIndex);
    }
    
    return 0;
}


int hbaDrvPrintRecvBuffer(LIST_NODE *ptr,  UINT32 opaque)
{
    RECV_BUFFER * pRecvBuf = (RECV_BUFFER *)ptr;

    if (opaque == 3)
    {
        printf("    Buffer %p, bufferIndex %d, DMABuffer %p\n", ptr, pRecvBuf->bufferIndex, pRecvBuf->pBuffer);
    }
    else
    {
        printf("    Buffer %p, bufferIndex %d \n", ptr, pRecvBuf->bufferIndex);
    }
    
    return 0;
}

void hbaDrvShowDeviceListCount(HBA_DEV_CB *dc)
{
    int i;
    
    printf("\n  ------------- send ---------------- \n");

    /* ���Ϳ��ж��� */
    printf("  list_send_idle_share : %d  \n", dc->list_send_idle_share.count);
    printf("\n");
    
    /* ����ȷ�϶��� */
    for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
    {
        printf("  list_SentWaitAck[%d] : %d\n", i, dc->list_SentWaitAck[i].count);
    }
    printf("\n");


    printf("\n  ------------- Recv ---------------- \n");

    /* ���ն��� */
    printf("  list_recv_idle_share : %d  \n", dc->list_recv_idle_share.count);
    printf("\n");
        
    /* �������ö��� */
    for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
    {
        printf("  list_toRecv[%d] : %d  \n", i, dc->list_toRecv[i].count);
    }
    printf("\n");


    /* ����ͨ�������ն��� */    
    printf("  rawRecvChannel.list_recved : %d  \n\n", dc->rawRecvChannel.list_recved.count);

    for (i=0; i<dc->asmRecvChannelCount; i++)
    {
        /*
        if (listIsListEmpty(&dc->asmRecvChannels[i].list_recved))
            continue;
        */
        
        printf("  asmRecvChannels[%d].list_recved : %d,  list_currentIU : %d \n", 
                i, dc->asmRecvChannels[i].list_recved.count, dc->asmRecvChannels[i].list_currentIU.count); /* 2018-4-12: huilin modified */
    }
    printf("\n");
}


void hbaDrvShowDeviceList(HBA_DEV_CB *dc, int detail)
{
    int i;
    int count;

    if (detail == 0)
    {
        hbaDrvShowDeviceListCount(dc);
        return;
    }
    
    /* ���Ϳ��ж��� */

    if ((detail == 1) || (detail == -1))
    {
        printf("\n  list_send_idle_share : \n");
        count = listFuncForeach(&dc->list_send_idle_share, hbaDrvPrintSendBuffer, 3, 0);
        printf("   --- total: %d  \n\n", count);
    }

    if ((detail == 2) || (detail == -1))
    {
        /* ����ȷ�϶��� */
        for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
        {
            printf("  list_SentWaitAck[%d] : \n", i);
            count = listFuncForeach(&dc->list_SentWaitAck[i], hbaDrvPrintSendBuffer, 3, 0);
            printf("   --- total: %d  \n\n", count);
        }
    }

    if ((detail == 3) || (detail == -1))
    {
        /* ����ͨ��˽�ж��� */    
        if (!listIsListEmpty(&dc->rawSendChannel.list_send_idle_private))
        {
            printf("  rawSendChannel.list_send_idle_private : \n");
            count = listFuncForeach(&dc->rawSendChannel.list_send_idle_private, hbaDrvPrintSendBuffer, 3, 0);
            printf("   --- total: %d  \n\n", count);
        }
    
        for (i=0; i<dc->asmSendChannelCount; i++)
        {
            if (listIsListEmpty(&dc->asmSendChannels[i].list_send_idle_private))
                {
                    continue;
                }        
            printf("  asmSendChannels[%d].list_send_idle_private : \n", i);
            count = listFuncForeach(&dc->asmSendChannels[i].list_send_idle_private, hbaDrvPrintSendBuffer, 3, 0);
            printf("   --- total: %d  \n\n", count);
        }
    }
    
    /* ���ն��� */
    if ((detail == 4) || (detail == -1))
    {
        printf("\n  list_recv_idle_share : \n");
        count = listFuncForeach(&dc->list_recv_idle_share, hbaDrvPrintRecvBuffer, 3, 0);    
        printf("   --- total: %d  \n\n", count);

        for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
        {
            printf("  list_toRecv[%d] : \n", i);
            count = listFuncForeach(&dc->list_toRecv[i], hbaDrvPrintRecvBuffer, 3, 0);
            printf("   --- total: %d  \n\n", count);
        }
    }

    if ((detail == 5) || (detail == -1))
    {
        /* ����ͨ�������ն��� */    
        if (!listIsListEmpty(&dc->rawRecvChannel.list_recved))
        {
            printf("  rawRecvChannel.list_recved : \n");
            count = listFuncForeach(&dc->rawRecvChannel.list_recved, hbaDrvPrintRecvBuffer, 3, 0);
            printf("   --- total: %d  \n\n", count);
        }
            
        for (i=0; i<dc->asmRecvChannelCount; i++)
        {
            if (!listIsListEmpty(&dc->asmRecvChannels[i].list_recved))
            {

                printf("  asmRecvChannels[%d].list_recved : \n", i);
                count = listFuncForeach(&dc->asmRecvChannels[i].list_recved, hbaDrvPrintRecvBuffer, 3, 0);
                printf("   --- total: %d  \n\n", count);
            }

            /* 2018-4-12: added by Huilin */
            if (!listIsListEmpty(&dc->asmRecvChannels[i].list_currentIU))
            {
                printf("  asmRecvChannels[%d].list_current_iu : \n", i);
                count = listFuncForeach(&dc->asmRecvChannels[i].list_currentIU, hbaDrvPrintRecvBuffer, 3, 0);
                printf("   --- total: %d  \n\n", count);
            }

        }
    }
    
}


void hbaDrvShowDeviceCB(HBA_DEV_CB *dc, int detail)
{
    printf("  status   = %d\n", dc->status);
    printf("  deviceId = %u\n", dc->deviceId);
    
    printf("  BusNo    = %u\n", dc->BusNo);
    printf("  DeviceNo = %u\n", dc->DeviceNo);
    printf("  FuncNo   = %u\n", dc->FuncNo);

    printf("  pMembaseCsr   = %p\n", dc->pMembaseCsr);
    printf("  irq           = %d\n", (int)dc->irq);
    
    printf("  FpgaVersion   = 0x%08x\n", hwGetFpgaVersion((REG_HW *)dc->pMembaseCsr));

    printf("  pSendDmaBufBaseAddr   = %p\n", dc->pSendDmaBufBaseAddr);
    printf("  pRecvDmaBufBaseAddr   = %p\n", dc->pRecvDmaBufBaseAddr);
    printf("  pSendBufBaseAddr   = %p\n", dc->pSendBufBaseAddr);

    printf("  pIntCallbackFun   = 0x%08x\n", (UINT)dc->pIntCallbackFunc);
    printf("  pRecvCallBackFunc  = 0x%08x\n", (UINT)dc->pRecvCallBackFunc);

    /*printf("  linkStatus   = 0x%x(%s)\n", dc->linkStatus, (dc->linkStatus==IC_LINK_STATUS_SUCCESS)? "STATUS_SUCCESS":"STATUS_FAILED");*/
    if ( dc->linkStatus==IC_LINK_STATUS_SUCCESS )
    {
        printf("  linkStatus   = 0x%x(%s)\n", dc->linkStatus,"STATUS_SUCCESS");
    }
    else
    {
        printf("  linkStatus   = 0x%x(%s)\n", dc->linkStatus,"STATUS_FAILED");
    }
    printf("  bToStop   = %d\n", (int)dc->bToStop);
    printf("  recvTaskId   = %d\n", dc->recvTaskId);
    printf("  sentCheckTaskId   = %d\n", dc->sentCheckTaskId);
}

void hbaDrvShowSendChannelStat(HBA_DEV_CB *dc, int detail)
{
    int ch;
    int from, to;
    
    if (detail == -1)
    {
        from = 0;
        to      = dc->asmSendChannelCount - 1;
    }
    else
    {
        if (detail >= dc->asmSendChannelCount)
        {
            printf("Invalid channel %d\n", detail);
            return;
        }
        
        from = detail; 
        to      = detail;
    }
    
    for (ch = from; ch <= to; ch++)
    {
        printf("[Send channel %d]\n", ch);
        printf("    sendBytes   = %s \n", UInt64toStr2(dc->asmSendChannels[ch].sendBytes));
        printf("    sendBuffers = %s \n", UInt64toStr2(dc->asmSendChannels[ch].sendBuffers));            
    }        
}
    
void hbaDrvShowRecvChannelStat(HBA_DEV_CB *dc, int detail)
{
    int ch;
    int from, to;
    
    if (detail == -1)
    {
        from = 0;
        to      = dc->asmRecvChannelCount - 1;
    }
    else
    {
        if (detail >= dc->asmRecvChannelCount)
        {
            printf("Invalid channel %d\n", detail);
            return;
        }
        
        from = detail; 
        to      = detail;
    }
        
    for (ch = from; ch <= to; ch++)
    {
        ASM_RECV_CHANNEL * pAsmRecvChannel = NULL;

        pAsmRecvChannel = &dc->asmRecvChannels[ch];    
        
        printf("[recv channel %d]\n", ch);

        printf("    totalIuCount = %s \n", UInt64toStr2(pAsmRecvChannel->totalIuCount));
        printf("    coverIuCount = %s \n", UInt64toStr2(pAsmRecvChannel->coverIuCount));
        printf("    discardIuCount = %s \n", UInt64toStr2(pAsmRecvChannel->discardIuCount));

        printf("    IuLenException = %s \n", UInt64toStr2(pAsmRecvChannel->IuLenException));
        printf("    IuSeqException = %s \n", UInt64toStr2(pAsmRecvChannel->IuSeqException));        
        printf("    IuTmroutException = %s \n", UInt64toStr2(pAsmRecvChannel->IuTmroutException));
        
        printf("    recvBuffers = %s \n", UInt64toStr2(pAsmRecvChannel->recvBuffers));
        printf("    recvBytes = %s \n", UInt64toStr2(pAsmRecvChannel->recvBytes));
    }    
}

void hbaDrvShowDeviceStat(HBA_DEV_CB *dc, int detail)
{
    printf("  ------------Driver Stats ------------\n");
    printf("    sentBytes = %s \n", UInt64toStr2(dc->sentBytes));
    printf("    recvBytes = %s \n", UInt64toStr2(dc->recvBytes));
    printf("    sentIUs = %s \n",   UInt64toStr2(dc->sentIUs));
    printf("    recvIUs = %s \n",   UInt64toStr2(dc->recvIUs));
    printf("    dicardIUs = %s \n", UInt64toStr2(dc->dicardIUs));
    printf("    coverIUs = %s \n",   UInt64toStr2(dc->coverIUs));
    printf("    exceptionIUs = %s \n",   UInt64toStr2(dc->exceptionIUs));
    printf("    sentRawBuffers = %s \n", UInt64toStr2(dc->sentRawBuffers));
    printf("    recvRawBuffers = %s \n", UInt64toStr2(dc->recvRawBuffers));
    printf("    sendBuffers = %s \n", UInt64toStr2(dc->sendBuffers));
    printf("    recvBuffers = %s \n", UInt64toStr2(dc->recvBuffers));

    printf("    sendCmptBuffers = %s \n", UInt64toStr2(dc->sendCmptBuffers));


    printf("  ------------ FPGA Stats ------------\n");
    printf("    fpga recv Frame Num = %s \n", UInt64toStr2(dc->fpgaStatInfo.recvFrameNumTotal));
    printf("    fpga recv IU Num = %s \n", UInt64toStr2(dc->fpgaStatInfo.recvIUNumTotal));
    printf("    fpga recv Error IU Num = %s \n",   UInt64toStr2(dc->fpgaStatInfo.recvErrorIUNumTotal));
    printf("    fpga recv error Frame Num = %s \n",   UInt64toStr2(dc->fpgaStatInfo.recvDiscardFrameNumTotal));
    printf("    fpga recv Invalid Frame Num = %s \n", UInt64toStr2(dc->fpgaStatInfo.recvInvalidFrameNumTotal));
    printf("    fpga send Frame Num = %s \n", UInt64toStr2(dc->fpgaStatInfo.sendFrameNumTotal));
    printf("    fpga send IU Num = %s \n",   UInt64toStr2(dc->fpgaStatInfo.sendIUNumTotal));
}

void hbaDrvShowPortStat(HBA_DEV_CB *dc, int detail)
{
    int i;

    for (i=0; i < FC_PORT_NUM_MAX; i++)
    {
        printf("    RxUndersizeFrameCnt  [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].RxUndersizeFrameCnt));
        printf("    RxOversizeFrameErrCnt[%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].RxOversizeFrameErrCnt));
        printf("    RxAllFrameCnt        [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].RxAllFrameCnt));
        printf("    RxValidFrameCnt      [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].RxValidFrameCnt));
        printf("    RxWordCnt            [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].RxWordCnt));
        printf("    RxRRDYCnt            [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].RxRRDYCnt));
        printf("    RxKErrCnt            [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].RxKErrCnt));
        
        /* printf("    LinkChgUp2DownCnt    [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].LinkChgUp2DownCnt)); */
        
        printf("    TxAllFrameCnt        [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].TxAllFrameCnt));
        printf("    TxValidFrameCnt      [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].TxValidFrameCnt));
        printf("    TxWordCnt            [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].TxWordCnt));
        printf("    TxRRDYCnt            [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].TxRRDYCnt));
        printf("    TxKErrCnt            [%d] = %s \n", i, UInt64toStr2(dc->portStatInfo[i].TxKErrCnt));
    }
}

void hbaDrvShowDeviceChannel(HBA_DEV_CB *dc, int detail)
{
    int i;

    printf("  PortId               = 0x%x \n", dc->configBlock.port_config.port_id);
    printf("  Credit number        = %d \n",   dc->configBlock.port_config.credit_num);
    printf("  NM Role              = %d \n",   dc->configBlock.port_config.role);
    printf("  clk_sync_role        = %d \n",   dc->configBlock.port_config.clk_sync_role);
    printf("  WDT Check period     = %d \n",   dc->configBlock.port_config.nc_wdt_period);
    printf("  WDT Send period      = %d \n",   dc->configBlock.port_config.wdt_loader_period);
    printf("  clk_sync_period      = %d \n",   dc->configBlock.port_config.clk_sync_period);
    printf("\n");
    
    printf("  ASM Send channel count %d ---\n", dc->asmSendChannelCount);
    for (i=0; i<dc->asmSendChannelCount; i++)
    {
        printf("    [%d] : msgID=%d, did=0x%x, priority=%d, bIsStream=%d\n", 
                i, 
                dc->asmSendChannels[i].msgId, 
                dc->asmSendChannels[i].did,
                dc->asmSendChannels[i].priority,
                dc->asmSendChannels[i].bIsStream);
    }
    
    printf("  ASM Recv channel count %d ---\n", dc->asmRecvChannelCount);
    for (i=0; i<dc->asmRecvChannelCount; i++)
    {

        printf("    [%d] : msgID=%d, sid=0x%x, priority=%d, bIsStream=%d, maxIUSize=0x%x\n", 
                i, 
                dc->asmRecvChannels[i].msgId, 
                dc->asmRecvChannels[i].sid, 
                dc->asmRecvChannels[i].priority,
                dc->asmRecvChannels[i].bIsStream,
                dc->asmRecvChannels[i].maxIUSize);
#ifdef USE_MSG_COVER        
        printf("           bMsgCover=%d\n", dc->asmRecvChannels[i].bMsgCover);
#endif                
    }
}

/*��ӡ����NC��Ϣ*/
void hbaDrvShowElsInfo(HBA_DEV_CB *dc, int detail)
{
    FCUINT i;
    
    printf(" ncFcid = 0x%06x:\n", dc->ncFcid);
    
    printf(" Els onNetTbl:\n");
    for(i = 0; i < FC_SW_PORT_NUM_MAX; i++)
    {
        if(FC_NODE_STATE_ON_LINE == dc->onNetTbl.Status[i])
        {
            printf("    [%d]:OnNet\n", i);
        }
    }

    printf(" swLinkStatusTbl[0] :\n");
    for(i = 0; i < FC_SW_PORT_NUM_MAX; i++)
    {
        if(dc->swLinkStatusTbl.Status[0][i] == FC_PORT_STATUS_LINK_UP)
        {
            printf(" [%d]:Linkup\n", i);
        }
    }

    printf(" swLinkStatusTbl[1] :\n");
    for(i = 0; i < FC_SW_PORT_NUM_MAX; i++)
    {
        if(dc->swLinkStatusTbl.Status[1][i] == FC_PORT_STATUS_LINK_UP)
        {
            printf(" [%d]:Linkup\n", i);
        }
    }
    
}

void hbaDrvShowAll(int content, int detail)
{
    int i;

    if (!bHbaDrvInited)
    {
        printf("HbaDrv is not be initialized.\n");
        return;
    }
    
    for (i=0; i<MAX_DEVICE_NUM; i++)
    {
        if (gHbaDevCB[i].status != HBA_DEV_STATUS_NONE)
        {
            printf("===========================================\n");    
            printf("[HbaDevCB = %p]\n", &gHbaDevCB[i]);
            
            /* detail ûʹ�� */
            if (content == HBA_SHOW_DEVCB)
            {
                hbaDrvShowDeviceCB(&gHbaDevCB[i], detail);
            }
            /* detail ָ���ĸ����С�
              1:���Ϳ��ж��У�2:����ȷ�϶��У�3:����ͨ��˽�ж��У�4:���ն��� ��5:����ͨ�������ն��� ��-1:���ж���  */
            if (content == HBA_SHOW_LIST)
            {
                hbaDrvShowDeviceList(&gHbaDevCB[i], detail);
            }    
            /* detail ûʹ�� */
            if (content == HBA_SHOW_STAT)
            {
                hbaDrvShowDeviceStat(&gHbaDevCB[i], detail);
            }
            /* detail ûʹ�� */
            if (content == HBA_SHOW_CHANNL)
            {
                hbaDrvShowDeviceChannel(&gHbaDevCB[i], detail);
            }    
            /* detail ָ��ͨ���ţ�Ϊ-1ʱ��ʾ����ͨ�� */
            if (content == HBA_SHOW_RECV_CHANNL_STAT)
            {
                hbaDrvShowRecvChannelStat(&gHbaDevCB[i], detail);
            }
            /* detail ָ��ͨ���ţ�Ϊ-1ʱ��ʾ����ͨ�� */
            if (content == HBA_SHOW_SEND_CHANNL_STAT)
            {
                hbaDrvShowSendChannelStat(&gHbaDevCB[i], detail);
            }
            if (content == HBA_SHOW_PORT_STAT)
            {
                hbaDrvShowPortStat(&gHbaDevCB[i], detail);
            }
            if (content == HBA_SHOW_ELS_INFO)
            {
                hbaDrvShowElsInfo(&gHbaDevCB[i], detail);
            }
        }
    }
}

void hba_print_buf(int key, void *buf, int len)
{
    int i;
    unsigned char *b;

    b = (unsigned char *)buf;
    len = len > 1024 ? 1024 : len;    /* ����ӡ1024�ֽ� */
    printf("tick=%u key=%d buf=%p len=%d\n", tickGet(), key, buf, len);
    for (i = 0; i < len; ++i)
    {
        printf("%02x", b[i]);
        if ((i + 1) % 8 == 0) printf(" "); 
        if ((i + 1) % 32 == 0) printf("\n");
    }
    printf("\n");
}


void hba_print_w_ctrl(W_CTRL *t)
{
    printf("w0=0x%08x [length=%d eop=%d sop=%d mode=%d]\n", (int)t->w0.value, (int)t->w0.u.length,
           (int)t->w0.u.eop, (int)t->w0.u.sop, (int)t->w0.u.mode);
    printf("w1=0x%08x [length=%d priority=%d l=%d]\n", (int)t->w1.value, (int)t->w1.u.length,
           (int)t->w1.u.priority, (int)t->w1.u.l);
}

void hba_print_r_ctrl(R_CTRL *t)
{
    printf("r0=0x%08x [sop=%d eop=%d seq_err=%d ox_id_err=%d frame_err=%d length=%d]\n",
           (int)t->r0.value, (int)t->r0.u.sop, (int)t->r0.u.eop, (int)t->r0.u.seq_err, (int)t->r0.u.ox_id_err, (int)t->r0.u.frame_err, (int)t->r0.u.length);
    printf("r1=0x%08x [channel_num=%d]\n", (int)t->r1.value, (int)t->r1.u.channel_num);
}

