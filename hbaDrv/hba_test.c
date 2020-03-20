#include <vxworks.h>
#include <cacheLib.h>
#include "hba.h"
#include "spi.h"
#include "list.h"
#include "hw.h"
#include "utils.h"

extern int *g_hDev;

/*********************************************************************************************************
测试API
**********************************************************************************************************/




/* 声明 */
VOID printElsConfig(int key, FC_ELS_CONFIG *elsConfig);
VOID print_fc_port_config(int key, FC_PORT_CONFIG *fc_port_config);
VOID print_fc_msg_send_item(int key, FC_MSG_SEND_ITEM *item);
VOID print_fc_msg_recv_item(int key, FC_MSG_RECV_ITEM *item);

VOID printBuffer(int key, char *buf, int len)
{
    int idx;

    printf("buf=0x%08x len=%d key=%d\n", (int)buf, len, key);
    for (idx = 0; idx < len; ++idx) {
        printf("%02x ", (unsigned char)buf[idx]);
        if ((idx + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");    
}

/*static */
int hbaTestCheckRecvBuffer(LIST_NODE *ptr,  UINT32 opaque)
{
    RECV_BUFFER * pRecvBuf = (RECV_BUFFER *)ptr;
    UINT32 * pIndex = (UINT32 *)opaque;
    
    /* Check whether the data in the buffer has been sent */
    ASSERT(pRecvBuf->pBuffer != NULL);

    HBA_CACHE_INVAL(pRecvBuf->pBuffer, pRecvBuf->bufferSize);
        
    if (hbaDrvGetRecvBufLen(pRecvBuf->pBuffer) > 0)
    {
        printf("index %d, buffer %p, DMA buffer %p, with len=%d, w0=0x%08x\n", 
                (*pIndex), 
                pRecvBuf, 
                pRecvBuf->pBuffer, 
                hbaDrvGetRecvBufLen(pRecvBuf->pBuffer), 
                pRecvBuf->pBuffer->r0);
    }

    (*pIndex) ++;

    return 0;
}

/* 正常情况下接收到数据的buffer必须位于接收队列的前面。
   这个函数用来检查是不是有接收到的buffer 位于队列中间， 
   如果存在这种情况，则表示firmware与FPGA上的接收信用不匹配。
*/
void hbaTestCheckAllRecvBuffer(HBA_DEV_CB * pHbaDevCB)
{
    int i;
    int count = 0;

    ASSERT(pHbaDevCB != NULL);
    ASSERT(pHbaDevCB->status != HBA_DEV_STATUS_NONE);
    
    for (i=0; i<MAX_PRIORITY_LEVEL_NUM; i++)
    {
        UINT index = 0;
        
        printf("[PRIORITY %d]\n", i);
        count = listFuncForeach(&pHbaDevCB->list_toRecv[i], hbaTestCheckRecvBuffer, (UINT32)&index, 0);    
        printf("   --- total: %d  \n\n", count);
        
    }
}


#if 0
STATUS hbaTestElsMsgLoopBack(HBA_DEV_CB * pHbaDevCB)
{
    UINT8 szMsg[2048];
    UINT8 szMsg2[2048];
    UINT32 msgLen = 0;
    UINT32 msgLen2 = 0;
    int i;
    
    FRAME_HDR *pFrameHdr = NULL;
    UINT8 * payload = NULL;
    UINT8 s_id[3] = {0x10,0x00,0x01};
    UINT8 d_id[3] = {0x10,0x00,0x02};

    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
        return ERROR;

    hbaDevReset(pHbaDevCB, FALSE);

    /* load config */
    hbaDevInitialize(pHbaDevCB);
        

    hbaDevSetPortGtxLoopBack(pHbaDevCB, 0, 1);

    if (hbaDevRun(pHbaDevCB) != DEV_SUCCESS)
    {
        printf("FC_MSL_ASM_Run return fail.\n");
        return ERROR;
    }

    /* TODO: prepare raw message */
    pFrameHdr = (FRAME_HDR*)&szMsg[0];
    memset( pFrameHdr, 0, sizeof(FRAME_HDR));

    /* Fill out frame header for the LOGO */
   pFrameHdr->r_ctl = RCTL_EXT_LINK_DATA | RCTL_UNSOLICITED_CONTROL;
   memcpy( pFrameHdr->s_id, s_id, 3 );
   memcpy( pFrameHdr->d_id, d_id, 3 );
   pFrameHdr->word2.tp.type = TYPE_ELS;
   
   /* Frame Control */
   pFrameHdr->word2.f_ctl |= ( FCTL_FIRST_SEQ_OF_EXCH | 
                              FCTL_LAST_FRAME_OF_SEQ | 
                              FCTL_XFER_SEQ_INITIATIVE );
      
   /* Make up an ox_id, I'm not tracking the exchange anyway at this point */
   pFrameHdr->ox_id = 0;
   pFrameHdr->rx_id = 0xffff;
   
    /* Fill out the LOGO payload. */
    payload = ((UINT8*)pFrameHdr + sizeof(FRAME_HDR));

    for (i=0 ; i<1024; i++)
    {
        payload[i] = (UINT8)i;
    }

    msgLen = 1024;

    /* TODO:*/
    /*
    if (hbaDevSendRawMsg(pHbaDevCB, szMsg, msgLen, WAIT_FOREVER) != DEV_SUCCESS)
    {
        printf("hbaDevSendRawMsg  fail.\n");
        return ERROR;
    }

    if (hbaDevRecvRawMsg(pHbaDevCB, szMsg2, &msgLen2, WAIT_FOREVER) != DEV_SUCCESS)
    {
        printf("hbaDevRecvRawMsg  fail.\n");
        return ERROR;
    }

    if (msgLen!=msgLen2 || memcmp(szMsg,szMsg2,msgLen)!=0)
    {
        printf("Recv data is not the same with sent data.\n");
        return ERROR;
    }
    */
    

    hbaDevSetPortGtxLoopBack(pHbaDevCB, 0, 0);


    printf("hbaTestRawMsgLoopBack  Success.\n");

    return OK;
}


#endif


STATUS hbaTestAsmMsgLoopBack(HBA_DEV_CB * pHbaDevCB, UINT32 msgID)
{
    unsigned char szMsg[2048];
    unsigned char szMsg2[2048];
    unsigned int msgLen = 0;
    unsigned int msgLen2 = 0;
    INT32 ret;
    int i;
    

    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return ERROR;
    }
        
    hbaDevReset(pHbaDevCB, FALSE);
    

    /* 设置一个接收通道和一个发送通道 */
    pHbaDevCB->configBlock.recv_item[0].msg_id = msgID;
    pHbaDevCB->configBlock.recv_item[0].msg_type = 0;
    pHbaDevCB->configBlock.recv_item[0].msg_max_len = 0x1000000;
    pHbaDevCB->configBlock.recv_item[0].msg_recover = 0;
    pHbaDevCB->configBlock.recv_item[0].msg_src_id = 0x000003; 
    
    
    pHbaDevCB->configBlock.send_item[0].msg_id = msgID;
    pHbaDevCB->configBlock.send_item[0].msg_type = 0;
    pHbaDevCB->configBlock.send_item[0].msg_priority = PRIORITY_LEVEL_2;
    pHbaDevCB->configBlock.send_item[0].msg_src_id = 0x000003; 
    pHbaDevCB->configBlock.send_item[0].msg_dst_id = 0x000003;

    pHbaDevCB->configBlock.port_config.port_id = 0x000003;
    pHbaDevCB->configBlock.port_config.credit_num = 10;
    pHbaDevCB->configBlock.port_config.block_rxmsg_num = 1;    
    pHbaDevCB->configBlock.port_config.block_txmsg_num = 1;
    pHbaDevCB->configBlock.port_config.nonblock_rxmsg_num = 0;
    pHbaDevCB->configBlock.port_config.nonblock_txmsg_num = 0;
    
    if (pHbaDevCB->status == HBA_DEV_STATUS_CREATED)
    {
        hbaDevInitialize(pHbaDevCB);
    }

    hbaDevSetPortGtxLoopBack(pHbaDevCB, 0, 1);

    if (hbaDevRun(pHbaDevCB) != DEV_SUCCESS)
    {
        printf("FC_MSL_ASM_Run return fail.\n");
        return ERROR;
    }

    /* prepare ASM message */
    for (i=0; i<1024; i++)
    {
        szMsg[i] = (UINT8)i;
    }

    msgLen = 1024;
    if (hbaDevSendAsmMsg(pHbaDevCB, msgID, szMsg, msgLen, WAIT_FOREVER) != DEV_SUCCESS)
    {
        printf("FC_MSL_SendRawMsg  fail.\n");
        return ERROR;
    }

    if (hbaDevRecvAsmMsg(pHbaDevCB, msgID, szMsg2, &msgLen2, WAIT_FOREVER) != DEV_SUCCESS)
    {
        printf("FC_ASM_RecvRawMsg  fail.\n");
        return ERROR;
    }

    if (msgLen!=msgLen2 || memcmp(szMsg,szMsg2,msgLen)!=0)
    {
        printf("Recv data is not the same with sent data.\n");
        return ERROR;
    }
    

    hbaDevSetPortGtxLoopBack(pHbaDevCB, 0, 0);


    printf("hbaTestAsmMsgLoopBack  Success.\n");

    return OK;
}


STATUS hbaTestAsmMsg(HBA_DEV_CB * pHbaDevCB, UINT32 msgID)
{
    unsigned char szMsg[2048];
    unsigned char szMsg2[2048];
    unsigned int msgLen = 0;
    unsigned int msgLen2 = 0;
    int i;
    int ret = 0;
    

    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return ERROR;
    }
        
    hbaDevReset(pHbaDevCB, FALSE);
    

    /* 设置一个接收通道和一个发送通道 */
    pHbaDevCB->configBlock.recv_item[0].msg_id = msgID;
    pHbaDevCB->configBlock.recv_item[0].msg_type = 0;
    pHbaDevCB->configBlock.recv_item[0].msg_recover = 0;
    pHbaDevCB->configBlock.recv_item[0].msg_src_id = 0x000001; 
    
    pHbaDevCB->configBlock.send_item[0].msg_id = msgID;
    pHbaDevCB->configBlock.send_item[0].msg_type = 0;
    pHbaDevCB->configBlock.send_item[0].msg_priority = PRIORITY_LEVEL_2;
    pHbaDevCB->configBlock.send_item[0].msg_src_id = 0x000001; 
    pHbaDevCB->configBlock.send_item[0].msg_dst_id = 0x000002;

    pHbaDevCB->configBlock.port_config.port_id = 0x000001;
    /* pHbaDevCB->configBlock.port_config.port_speed = PORT_SPEED_1G; */
    pHbaDevCB->configBlock.port_config.credit_num = 10;
    pHbaDevCB->configBlock.port_config.block_rxmsg_num = 1;    
    pHbaDevCB->configBlock.port_config.block_txmsg_num = 1;
    pHbaDevCB->configBlock.port_config.nonblock_rxmsg_num = 0;
    pHbaDevCB->configBlock.port_config.nonblock_txmsg_num = 0;
    

    if (pHbaDevCB->status == HBA_DEV_STATUS_CREATED)
    {
        ret = hbaDevInitialize(pHbaDevCB);
        if (ret != DEV_SUCCESS)
        {
            printf("hbaDevInitialize return %d.\n", ret);
            return ERROR;
        }
    }


    
    ret = hbaDevRun(pHbaDevCB);
    if (ret != DEV_SUCCESS)
    {
        printf("hbaDevRun return %d.\n", ret);
        return ERROR;
    }

    /* prepare ASM message */
    for (i=0; i<1024; i++)
    {
        szMsg[i] = (UINT8)i;
    }

    msgLen = 1024;
    ret = hbaDevSendAsmMsg(pHbaDevCB, msgID, szMsg, msgLen, WAIT_FOREVER);
    if ( ret != DEV_SUCCESS)
    {
        printf("hbaDevSendAsmMsg return %d.\n", ret);
        return ERROR;
    }

    ret = hbaDevRecvAsmMsg(pHbaDevCB, msgID, szMsg2, &msgLen2, WAIT_FOREVER);
    if ( ret != DEV_SUCCESS)
    {
        printf("hbaDevRecvAsmMsg return %d.\n", ret);
        return ERROR;
    }

    if (msgLen!=msgLen2 || memcmp(szMsg,szMsg2,msgLen)!=0)
    {
        printf("Recv data is not the same with sent data.\n");
        return ERROR;
    }
    

    printf("hbaTestAsmMsg  Success.\n");

    return OK;
}



STATUS hbaTestAsmConfig(HBA_DEV_CB * pHbaDevCB, UINT32 msgID, UINT32 msg_src_id, UINT32 msg_dst_id )
{
    int i;
    int ret = 0;
    

    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return ERROR;
    }
        
    hbaDevReset(pHbaDevCB, FALSE);


    /* 设置一个接收通道和一个发送通道 */
    pHbaDevCB->configBlock.recv_item[0].msg_id = msgID;
    pHbaDevCB->configBlock.recv_item[0].msg_type = 4;
    pHbaDevCB->configBlock.recv_item[0].msg_max_len = 0x1000000;
    pHbaDevCB->configBlock.recv_item[0].msg_recover = 0;
    pHbaDevCB->configBlock.recv_item[0].msg_src_id = msg_dst_id; 
    
    pHbaDevCB->configBlock.send_item[0].msg_id = msgID;
    pHbaDevCB->configBlock.send_item[0].msg_type = 4;
    pHbaDevCB->configBlock.send_item[0].msg_priority = PRIORITY_LEVEL_2;
    pHbaDevCB->configBlock.send_item[0].msg_src_id = msg_src_id; 
    pHbaDevCB->configBlock.send_item[0].msg_dst_id = msg_dst_id;

    pHbaDevCB->configBlock.port_config.port_id = msg_src_id;
    pHbaDevCB->configBlock.port_config.port_type = 1;
    pHbaDevCB->configBlock.port_config.credit_num = 8;
    pHbaDevCB->configBlock.port_config.role = 1;
    pHbaDevCB->configBlock.port_config.clk_sync_role = 1;
    pHbaDevCB->configBlock.port_config.nc_wdt_period = 1500;
    pHbaDevCB->configBlock.port_config.wdt_loader_period = 300;
    pHbaDevCB->configBlock.port_config.clk_sync_period = 100;
    /*pHbaDevCB->configBlock.port_config.port_speed = PORT_SPEED_1G;*/
    pHbaDevCB->configBlock.port_config.block_rxmsg_num = 1;    
    pHbaDevCB->configBlock.port_config.block_txmsg_num = 1;
    pHbaDevCB->configBlock.port_config.nonblock_rxmsg_num = 0;
    pHbaDevCB->configBlock.port_config.nonblock_txmsg_num = 0;

    if (pHbaDevCB->status == HBA_DEV_STATUS_CREATED)
    {
        ret = hbaDevInitialize(pHbaDevCB);
        if (ret != DEV_SUCCESS)
        {
            printf("hbaDevInitialize return %d.\n", ret);
            return ERROR;
        }
    }
    
    ret = hbaDevRun(pHbaDevCB);
    if (ret != DEV_SUCCESS)
    {
        printf("hbaDevRun return %d.\n", ret);
        return ERROR;
    }
    
    return OK;
}



STATUS hbaTestAsmConfigMultiMsgID(HBA_DEV_CB * pHbaDevCB, UINT32 msgIDCount)
{
    int i;
    int ret = 0;
    

    if (pHbaDevCB->status == HBA_DEV_STATUS_NONE)
    {
        return ERROR;
    }
        
    hbaDevReset(pHbaDevCB, FALSE);
    

    /* 设置一个接收通道和一个发送通道 */
    for (i=0; i<msgIDCount; i++)
    {
        pHbaDevCB->configBlock.recv_item[i].msg_id = i+1;
        pHbaDevCB->configBlock.recv_item[i].msg_type = 0;
        pHbaDevCB->configBlock.recv_item[i].msg_max_len = 0x1000000;
        pHbaDevCB->configBlock.recv_item[i].msg_recover = 0;
        pHbaDevCB->configBlock.recv_item[i].msg_src_id = 0x100001; 
        
        pHbaDevCB->configBlock.send_item[i].msg_id = i+1;
        pHbaDevCB->configBlock.send_item[i].msg_type = 0;
        pHbaDevCB->configBlock.send_item[i].msg_priority = PRIORITY_LEVEL_2;
        pHbaDevCB->configBlock.send_item[i].msg_src_id = 0x100001; 
        pHbaDevCB->configBlock.send_item[i].msg_dst_id = 0x100001;
    }

    pHbaDevCB->configBlock.port_config.port_id = 0x100001;
    pHbaDevCB->configBlock.port_config.port_type = 1;
    pHbaDevCB->configBlock.port_config.credit_num = 8;
    pHbaDevCB->configBlock.port_config.role = 1;
    pHbaDevCB->configBlock.port_config.clk_sync_role = 1;
    pHbaDevCB->configBlock.port_config.nc_wdt_period = 1500;
    pHbaDevCB->configBlock.port_config.wdt_loader_period = 300;
    pHbaDevCB->configBlock.port_config.clk_sync_period = 100;
    /*pHbaDevCB->configBlock.port_config.port_speed = PORT_SPEED_1G;*/

    pHbaDevCB->configBlock.port_config.block_rxmsg_num = msgIDCount;    
    pHbaDevCB->configBlock.port_config.block_txmsg_num = msgIDCount;
    pHbaDevCB->configBlock.port_config.nonblock_rxmsg_num = 0;
    pHbaDevCB->configBlock.port_config.nonblock_txmsg_num = 0;
    

    if (pHbaDevCB->status == HBA_DEV_STATUS_CREATED)
    {
        ret = hbaDevInitialize(pHbaDevCB);
        if (ret != DEV_SUCCESS)
        {
            printf("hbaDevInitialize return %d.\n", ret);
            return ERROR;
        }
    }
    
    ret = hbaDevRun(pHbaDevCB);
    if (ret != DEV_SUCCESS)
    {
        printf("hbaDevRun return %d.\n", ret);
        return ERROR;
    }

    return OK;
}



STATUS hbaTestSendAsmMsg(HBA_DEV_CB * pHbaDevCB, UINT32 msgID, int count, int size)
{
    unsigned char *pMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    
    if (count == 0)
        count = 1;

    if (size == 0)
        size = 4;

    if (size > MAX_IU_LEN)
        size = MAX_IU_LEN;
    
    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestSendAsmMsg : malloc return NULL.\n");
        return ERROR;
    }

    /* prepare ASM message */
    for (i=0; i<MAX_IU_LEN; i++)
    {
        pMsg[i] = (UINT8)i;
    }

    for (i=0; i<count; i++)
    {
        msgLen = size;
        ret = hbaDevSendAsmMsg(pHbaDevCB, msgID, pMsg, msgLen, WAIT_FOREVER);
        if ( ret != DEV_SUCCESS)
        {
            free(pMsg);
            printf("hbaTestSendAsmMsg return %d.\n", ret);
            return ERROR;
        }
    }

    free(pMsg);
    printf("hbaTestSendAsmMsg  Success.\n");

    return OK;
}

STATUS hbaTestRecvAsmMsg(HBA_DEV_CB * pHbaDevCB, UINT32 msgID, int count)
{
    unsigned char * pMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    
    if (count == 0)
        count = 1;


    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestRecvAsmMsg : malloc return NULL.\n");
        return ERROR;
    }
    
    for (i=0; i<count; i++)
    {
        msgLen = MAX_IU_LEN;
        ret = hbaDevRecvAsmMsg(pHbaDevCB, msgID, pMsg, &msgLen, WAIT_FOREVER);
        if ( ret != DEV_SUCCESS)
        {
            free(pMsg);            
            printf("hbaTestRecvAsmMsg return %d.\n", ret);
            return ERROR;
        }
        else
        {
            if (count == 1)
            {
                printf("hbaTestRecvAsmMsg data length = %d.\n", msgLen);
            }
        }
    }

    free(pMsg);    
    printf("hbaTestRecvAsmMsg  Success.\n");

    return OK;
}



BOOL bSendExit = FALSE;
BOOL bRecvExit = FALSE;

int g_iMaxInPreiod = 1000;
int g_iSize = 10000;
STATUS hbaTestSendAsmMsgLoop(HBA_DEV_CB * pHbaDevCB, UINT32 msgID, UINT32 size)
{
    unsigned char *pMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    UINT32 count = 0;
    int iCountInPeriod = 0;
    
    if (size == 0)
        size = g_iSize;

    g_iSize = size;
    
    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestSendAsmMsgLoop : malloc return NULL.\n");
        return ERROR;
    }
    
    /* prepare ASM message */
    for (i=0; i<1024; i++)
    {
        pMsg[i] = (UINT8)i;
    }

    bSendExit = FALSE;
        
    while(1)
    {
        if (bSendExit)
            break;
        
        msgLen = g_iSize;
        ret = hbaDevSendAsmMsg(pHbaDevCB, msgID, pMsg, msgLen, WAIT_FOREVER);
        if ( ret != DEV_SUCCESS)
        {
            free(pMsg);
            printf("hbaTestSendAsmMsg return %d.\n", ret);
            return ERROR;
        }
        else
        {
            count ++;
            iCountInPeriod ++;

            if (iCountInPeriod >= g_iMaxInPreiod)
            {
                taskDelay(1);
                iCountInPeriod = 0;
            }
        }
    }


    free(pMsg);
    printf("hbaTestSendAsmMsg exit, sent %d message.\n", count);

    return OK;
}



char * g_pSendData = NULL;
char * g_pRecvData = NULL;
int   g_validLen = 0;

STATUS hbaTestSendAndWaitBackAsmMsgLoop(HBA_DEV_CB * pHbaDevCB, UINT32 msgID, UINT32 lenFrom, UINT32 lenTo)
{
    unsigned char *pMsg;
    unsigned char *pRecvMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    UINT32 count = 0;
    int iCountInPeriod = 0;
    int size = 0;

    
    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestSendAndWaitBackAsmMsgLoop : malloc return NULL.\n");
        return ERROR;
    }

    pRecvMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pRecvMsg == NULL)
    {
        printf("hbaTestSendAndWaitBackAsmMsgLoop : malloc return NULL.\n");
        free(pMsg);
        return ERROR;
    }

    

    bSendExit = FALSE;
        
    for (size = lenFrom; size <= lenTo; size ++)
    {
        if (bSendExit)
            break;

        /* prepare ASM message */
        for (i=0; i<size; i++)
        {
            /*pMsg[i] = (UINT8)(i-1);*/
            pMsg[i] = (UINT8)size;
        }
        

        if ((size % 1000) == 0)
            printf("Send Msg len = %d\n", size);
        
        ret = hbaDevSendAsmMsg(pHbaDevCB, msgID, pMsg, size, WAIT_FOREVER);
        if ( ret != DEV_SUCCESS)
        {
            printf("hbaTestSendAndWaitBackAsmMsgLoop: hbaDevSendAsmMsg return %d.\n", ret);
            free(pMsg);
            free(pRecvMsg);
            return ERROR;
        }
        else
        {


            while(1)
            {
                msgLen = MAX_IU_LEN;
                ret = hbaDevRecvAsmMsg(pHbaDevCB, msgID, pRecvMsg, &msgLen, WAIT_FOREVER);
                if ( ret != DEV_SUCCESS)
                {
                    printf("hbaTestSendAndWaitBackAsmMsgLoop: hbaDevRecvAsmMsg return %d.\n", ret);
                    free(pMsg);
                    free(pRecvMsg);
                    return ERROR;
                }

                if (msgLen != size)
                {
                    printf("hbaTestSendAndWaitBackAsmMsgLoop : compare length fail, sendlen=%d, recvlen%d.\n", size, msgLen);
                    continue;
                }

                if (memcmp(pRecvMsg, pMsg, msgLen) != 0)
                {
                    printf("hbaTestSendAndWaitBackAsmMsgLoop :compare content fail. msgLen=%d\n", msgLen);
                    {
                        int pos = 0, p1, p2;
                        int idx;

                        memcpy(g_pSendData, pMsg, msgLen);
                        memcpy(g_pRecvData, pRecvMsg, msgLen);
                        g_validLen = msgLen;
                        
                        for (pos = 0; pos < g_validLen; pos ++)
                        {
                            if (g_pSendData[pos] != g_pRecvData[pos] )
                            {
                                printf("  pos=%d\n", pos);
                                break;
                            }
                        }

                        p1 = max(0, pos - 16);
                        p2 = min(pos + 16, msgLen);

                        
                        printf("send data : %p\n", g_pSendData);
                        for (idx = p1; idx < p2; ++idx) {
                            printf("%02x ", (unsigned char)g_pSendData[idx]);
                            if ((idx + 1) % 16 == 0) {
                                printf("\n");
                            }
                        }
                        printf("\n");    

                        printf("recv data : %p \n", g_pRecvData);
                        for (idx = p1; idx < p2; ++idx) {
                            printf("%02x ", (unsigned char)g_pRecvData[idx]);
                            if ((idx + 1) % 16 == 0) {
                                printf("\n");
                            }
                        }
                        printf("\n");
                                            
                        
                    }
                    continue;
                }

                if ((size % 1000) == 0)
                    printf("Recv Msg len = %d, OK\n", size);

                break;
                
            }
        
            count ++;
            iCountInPeriod ++;

            if (iCountInPeriod >= g_iMaxInPreiod)
            {
                taskDelay(0);
                iCountInPeriod = 0;
            }
        }
    }


    printf("hbaTestSendAndWaitBackAsmMsgLoop exit, sent %d message.\n", count);

    free(pMsg);
    free(pRecvMsg);
    
    return OK;
}


STATUS hbaTestRecvAsmMsgLoop(HBA_DEV_CB * pHbaDevCB, UINT32 msgID)
{
    unsigned char * pMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    UINT32 count = 0;

    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestRecvAsmMsgLoop : malloc return NULL.\n");
        return ERROR;
    }
    
    bRecvExit = FALSE;
    
    while(1)
    {
        if (bRecvExit)
            break;
        
        msgLen = MAX_IU_LEN;
        ret = hbaDevRecvAsmMsg(pHbaDevCB, msgID, pMsg, &msgLen, 100);
        if ( ret != DEV_SUCCESS)
        {
            /* free(pMsg); */
            /* printf("hbaTestRecvAsmMsg return %d.\n", ret); */
            
            /* return ERROR; */
            
        }
        else
        {
            /* printf("hbaDevRecvAsmMsg return OK, len = %d.\n", msgLen); */
            
            count ++;
            /* taskDelay(1); */
        }
    }

    free(pMsg);
    printf("hbaTestRecvAsmMsgLoop  exit,  recv %d message.\n", count);

    return OK;
}

int iPrintRecvAndSend = 1;
UINT lastMsgLen=0;

STATUS hbaTestRecvAndBackAsmMsgLoop(HBA_DEV_CB * pHbaDevCB, UINT32 msgID)
{
    unsigned char * pMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    UINT32 count = 0;

    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestRecvAsmMsgLoop : malloc return NULL.\n");
        return ERROR;
    }
    
    bRecvExit = FALSE;
    
    while(1)
    {
        if (bRecvExit)
            break;
        
        msgLen = MAX_IU_LEN;
        ret = hbaDevRecvAsmMsg(pHbaDevCB, msgID, pMsg, &msgLen, WAIT_FOREVER);
        if ( ret != DEV_SUCCESS)
        {
            /* printf("hbaTestRecvAsmMsg return %d.\n", ret); */
            
            /* return ERROR; */
        }
        else
        {
            BOOL bCompareOK = TRUE;
            
            if (iPrintRecvAndSend)
                printf("hbaTestRecvAsmMsg return  OK,len=%d\n", msgLen); 

            lastMsgLen = msgLen;
            
               for (i=0; i<msgLen; i++)
               {
                   if (pMsg[i] != ((msgLen-1)&0xFF))
                   {
                       printf("Compare fail, i=%d, pMsg[i]=0x%02x, msgLen=0x%02x \n", i, (UINT)pMsg[i], msgLen);
                    bCompareOK = FALSE;
                    break;
                   }
               }

            if (bCompareOK == FALSE)
                continue;
                
            ret = hbaDevSendAsmMsg(pHbaDevCB, msgID, pMsg, msgLen, WAIT_FOREVER);
            count ++;
            /* taskDelay(1); */
        }
    }

    free(pMsg);
    printf("hbaTestRecvAsmMsgLoop  exit,  recv %d message.\n", count);

    return OK;
}



STATUS hbaTestSendRecvAsmMsg(HBA_DEV_CB * pHbaDevCB, UINT32 msgID, int size )
{
    if (size == 0)
        size = 4;
    
    if (taskSpawn ( "tTestRecv", 
                    10, 
                    0, 
                    409600, 
                    hbaTestRecvAsmMsgLoop, pHbaDevCB, 
                    msgID, 0, 0, 0, 0, 0, 0, 0, 0) == ERROR)
    {
        pHbaDevCB->bBuildInTesting = FALSE;
        return DEV_OTHER_FAILURE;
    }


    if (taskSpawn ( "tTestSend", 
                    10, 
                    0, 
                    409600, 
                    hbaTestSendAsmMsgLoop, pHbaDevCB, 
                    msgID, size, 0, 0, 0, 0, 0, 0, 0) == ERROR)
    {
        pHbaDevCB->bBuildInTesting = FALSE;
        return DEV_OTHER_FAILURE;
    }
    return OK;
}





STATUS hbaTestSendAsmMsgLoopMultiMsgID(HBA_DEV_CB * pHbaDevCB, UINT32 msgIDCount, UINT32 lenFrom, UINT32 lenTo)
{
    unsigned char * pMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    UINT32 count = 0;
    UINT len = 1;

    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestSendAsmMsgLoopMultiMsgID : malloc return NULL.\n");
        return ERROR;
    }
    
    bSendExit = FALSE;

    msgLen = lenFrom;
    while(1)
    {
        if (bSendExit)
            break;

        for (i=0; i<msgIDCount; i++)
        {
            
            ret = hbaDevSendAsmMsg(pHbaDevCB, pHbaDevCB->asmSendChannels[i].msgId, pMsg, msgLen, WAIT_FOREVER);
            if ( ret != DEV_SUCCESS)
            {
                /* free(pMsg); */
                /* printf("hbaTestRecvAsmMsg return %d.\n", ret); */
            
                /* return ERROR; */
            }
            else
            {
                count ++;
                /* taskDelay(1); */
            }
            
        }
        msgLen ++;

        if (msgLen > lenTo)
            break;
        
    }

    free(pMsg);
    printf("hbaTestSendAsmMsgLoopMultiMsgID  exit,  send %d message.\n", count);

    return OK;
}

/* 一个通道发送小包，另外一个通道发送最大包， 轮流发送*/
STATUS hbaTestSendAsmMsgLoopMultiMsgID2(HBA_DEV_CB * pHbaDevCB, UINT32 msgIDCount, UINT32 size)
{
    unsigned char *pMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    UINT32 count = 0;
    int iCountInPeriod = 0;
    int sendLen = 0;
    
    if (size == 0)
        size = g_iSize;

    g_iSize = size;
    
    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestSendAsmMsgLoop : malloc return NULL.\n");
        return ERROR;
    }
    
    /* prepare ASM message */
    for (i=0; i<1024; i++)
    {
        pMsg[i] = (UINT8)i;
    }

    bSendExit = FALSE;

    msgLen = g_iSize;
    while(1)
    {
        if (bSendExit)
            break;
        
        msgLen = g_iSize;
        

        for (i = 0; i<msgIDCount; i++)
        {
            if (i != 0)
            {
                sendLen = MAX_IU_LEN;
            }
            else
            {
                sendLen = msgLen;
            }
            ret = hbaDevSendAsmMsg(pHbaDevCB, pHbaDevCB->asmSendChannels[i].msgId, pMsg, msgLen, WAIT_FOREVER);
            if ( ret != DEV_SUCCESS)
            {
                free(pMsg);
                printf("hbaTestSendAsmMsg return %d.\n", ret);
                return ERROR;
            }
            else
            {
                count ++;
                iCountInPeriod ++;

                if (iCountInPeriod >= g_iMaxInPreiod)
                {
                    taskDelay(1);
                    iCountInPeriod = 0;
                }
            }
        }

        msgLen ++;
    }

    free(pMsg);
    printf("hbaTestSendAsmMsg exit, sent %d message.\n", count);

    return OK;
}

STATUS hbaTestRecvAsmMsgLoopMultiMsgID(HBA_DEV_CB * pHbaDevCB, UINT32 msgIDCount)
{
    unsigned char * pMsg;
    unsigned int msgLen = 0;
    int i;
    int ret = 0;
    UINT32 count = 0;

    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("hbaTestRecvAsmMsgLoop : malloc return NULL.\n");
        return ERROR;
    }
    
    bRecvExit = FALSE;
    
    while(1)
    {
        if (bRecvExit)
            break;

        for (i=0; i<msgIDCount; i++)
        {
            msgLen = MAX_IU_LEN;
            ret = hbaDevRecvAsmMsg(pHbaDevCB, i+1, pMsg, &msgLen, 0);
            if ( ret != DEV_SUCCESS)
            {
                /* free(pMsg); */
                /* printf("hbaTestRecvAsmMsg return %d.\n", ret); */
            
                /* return ERROR; */
            }
            else
            {
                count ++;
                /* taskDelay(1); */
            }
        }
    }

    free(pMsg);
    printf("hbaTestRecvAsmMsgLoop  exit,  recv %d message.\n", count);

    return OK;
}





int bExitPrintSpeed = 0;
int iPrintSpeedPeriod = 10;
void hbaTestPrintSpeedTask(HBA_DEV_CB *pHbaDevCB, int printSpeedPeriod)
{
    UINT64 sentBytes = 0;
    UINT64 recvBytes = 0;
    UINT64 moveBytes = 0;
    UINT64 sentIUs = 0;
    UINT64 recvIUs = 0;
    UINT64 dicardIUs = 0;    
    UINT64 coverIUs = 0;      
    UINT64 exceptionIUs = 0;      
    UINT64 sentRawBuffers = 0;
    UINT64 recvRawBuffers = 0;
    UINT64 sendBuffers = 0;
    UINT64 recvBuffers = 0;
    UINT64 sendCmptBuffers = 0;
    UINT32 lastSeconds = 0;
    UINT32 seconds = 0; 
        
    bExitPrintSpeed = 0;

    if (printSpeedPeriod == 0)
        iPrintSpeedPeriod = 10;
    else
        iPrintSpeedPeriod = printSpeedPeriod;

    while(1)
    {
        if (bExitPrintSpeed)
            break;

        seconds = tickGet()/sysClkRateGet();
        if (lastSeconds != 0 )
        {
            printf("  ------------ Stats (%d)------------\n", seconds - lastSeconds);
            printf("    sentBytes = %s \n", UInt64toStr2(pHbaDevCB->sentBytes - sentBytes));
            printf("    recvBytes = %s \n", UInt64toStr2(pHbaDevCB->recvBytes - recvBytes));
            printf("    moveBytes = %s \n", UInt64toStr2(pHbaDevCB->moveBytes - moveBytes));
            printf("    sentIUs = %s \n",   UInt64toStr2(pHbaDevCB->sentIUs - sentIUs));
            printf("    recvIUs = %s \n",   UInt64toStr2(pHbaDevCB->recvIUs - recvIUs));
            printf("    dicardIUs = %s \n",  UInt64toStr2(pHbaDevCB->dicardIUs - dicardIUs));
            printf("    coverIUs = %s \n",   UInt64toStr2(pHbaDevCB->coverIUs - coverIUs));
            printf("    exceptionIUs = %s \n", UInt64toStr2(pHbaDevCB->exceptionIUs - exceptionIUs));

            printf("    sentRawBuffers = %s \n", UInt64toStr2(pHbaDevCB->sentRawBuffers - sentRawBuffers));
            printf("    recvRawBuffers = %s \n", UInt64toStr2(pHbaDevCB->recvRawBuffers - recvRawBuffers));
            printf("    sendBuffers = %s \n", UInt64toStr2(pHbaDevCB->sendBuffers - sendBuffers));
            printf("    recvBuffers = %s \n", UInt64toStr2(pHbaDevCB->recvBuffers - recvBuffers));
            printf("    sendCmptBuffers = %s \n", UInt64toStr2(pHbaDevCB->sendCmptBuffers - sendCmptBuffers));
        }
        lastSeconds = seconds;
        
        
        sentBytes     =   pHbaDevCB->sentBytes;     
        recvBytes     =   pHbaDevCB->recvBytes;    
        moveBytes     =   pHbaDevCB->moveBytes;
        sentIUs     =   pHbaDevCB->sentIUs;         
        recvIUs     =   pHbaDevCB->recvIUs;     
        dicardIUs     =   pHbaDevCB->dicardIUs; 
        coverIUs     =   pHbaDevCB->coverIUs; 
        exceptionIUs =  pHbaDevCB->exceptionIUs; 
        sentRawBuffers =   pHbaDevCB->sentRawBuffers; 
        recvRawBuffers =   pHbaDevCB->recvRawBuffers; 
        sendBuffers =   pHbaDevCB->sendBuffers; 
        recvBuffers =   pHbaDevCB->recvBuffers; 
        sendCmptBuffers = pHbaDevCB->sendCmptBuffers;

        
        taskDelay(sysClkRateGet()*iPrintSpeedPeriod);
    }
}

/* Print recv and sent speed per second */
void hbaTestPrintSpeed(HBA_DEV_CB *pHbaDevCB)
{
    taskSpawn ( "tPrtSpeed", 
                5, 
                0, 
                4096, 
                hbaTestPrintSpeedTask, 
                pHbaDevCB, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}


int bExitCheckCPU = 0;
void testPrintSomething()
{
    bExitCheckCPU = 0;

    while(1)
    {
        if (bExitCheckCPU)
            break;

        printf(".");
        taskDelay(10);
    }
}
/* when no SPY command in system, use this function to check whether CPU occupy rate has arrived 100% */
void testCheckCPUBusy()
{
    taskSpawn ( "tTestCPU", 
                200, 
                0, 
                4096, 
                testPrintSomething, 
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}


/* testMemCpySpeed 1000, 0x100000 */
void testMemCpySpeed1(UINT count, UINT size)
{
    int i;
    char *pMsg1 = NULL;
    char *pMsg2 = NULL;
    UINT tickFrom, tick;    
    UINT64 bytes;
    UINT64 speed;
    
    pMsg1 = (char *)malloc(size);
    if (pMsg1 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        return;
    }

    pMsg2 = (char *)malloc(size);
    if (pMsg2 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        free(pMsg1);
        return;
    }

    tickFrom = tickGet();
    for (i=0; i<count; i++)
    {
        
        memcpy(pMsg1, pMsg2,  size);
        
        HBA_CACHE_INVAL(pMsg1, size);
        HBA_CACHE_FLUSH(pMsg2, size);
    }
    tick= tickGet() - tickFrom;
    bytes = ((UINT64)count) * ((UINT64)size);
    if (tick == 0)
        speed = bytes;
    else
        speed = bytes * sysClkRateGet() /tick;
    
    printf("copy %s bytes in %u ticks,", UInt64toStr2(bytes), tick);
    printf("speed %s byte/s\n,", UInt64toStr2(speed));

    free(pMsg1);
    free(pMsg2);
}

/* testMemCpySpeed2 1000, 0x100000 */
/* testMemCpySpeed2 100, 0x1000000 */
void testMemCpySpeed2(UINT count, UINT size)
{
    int i;
    char *pMsg1 = NULL;
    char *pMsg2 = NULL;
    UINT tickFrom, tick;    
    UINT64 bytes = 0;
    UINT64 speed = 0;
    
    pMsg1 = (char *)malloc(size);
    if (pMsg1 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        return;
    }

    pMsg2 = (char *)malloc(size);
    if (pMsg2 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        free(pMsg1);
        return;
    }

    tickFrom = tickGet();
    for (i=0; i<count; i++)
    {
        memcpy(pMsg1, pMsg2,  size);
    }
    tick= tickGet() - tickFrom;
    bytes = ((UINT64)count) * ((UINT64)size);
    if (tick == 0)
        speed = bytes;
    else
        speed = bytes * sysClkRateGet() /tick;
    

    printf("copy %s bytes in %u ticks,", UInt64toStr2(bytes), tick);
    printf("speed %s byte/s\n,", UInt64toStr2(speed));
    
    free(pMsg1);
    free(pMsg2);
}


void testMemCpySpeed3(UINT count, UINT size)
{
    int i, j;
    char *pMsg1 = NULL;
    char *pMsg2 = NULL;
    UINT tickFrom, tick;    
    UINT64 bytes = 0;
    UINT64 speed = 0;
    UINT32 words = 0;
    UINT32 *pSrc = NULL;
    UINT32 *pDst = NULL;
    
    pMsg1 = (char *)malloc(size);
    if (pMsg1 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        return;
    }

    pMsg2 = (char *)malloc(size);
    if (pMsg2 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        free(pMsg1);
        return;
    }
    pDst = (UINT32 *)pMsg1;
    pSrc = (UINT32 *)pMsg2;

    words = (size + 3) >> 2;
    
    tickFrom = tickGet();
    for (i=0; i<count; i++)
    {
        for (j=0; j<words; j++)
        {
            *pSrc = *pDst;
            pSrc ++;
            pDst ++;
        }
    }
    tick= tickGet() - tickFrom;
    bytes = ((UINT64)count) * ((UINT64)size);
    if (tick == 0)
        speed = bytes;
    else
        speed = bytes * sysClkRateGet() /tick;
    

    printf("copy %s bytes in %u ticks,", UInt64toStr2(bytes), tick);
    printf("speed %s byte/s\n,", UInt64toStr2(speed));
    
    free(pMsg1);
    free(pMsg2);
}


/* testMemCpySpeed4 1000, 0x100000 */
void testMemCpySpeed4(UINT count, UINT size)
{
#define MSGBUF_COUNT 512    
    int i, j;
    char *pMsg1[MSGBUF_COUNT];
    char *pMsg2 = NULL;
    UINT tickFrom, tick;    
    UINT64 bytes;
    UINT64 speed;

    for (i = 0; i<MSGBUF_COUNT; i++)
    {
        pMsg1[i] = (char *)malloc(size);
        if (pMsg1[i] == NULL)
        {
            printf("testMemCpySpeed : malloc return NULL.\n");
            return;
        }
    }

    pMsg2 = (char *)malloc(size);
    if (pMsg2 == NULL)
    {
        printf("testMemCpySpeed : malloc return NULL.\n");
        free(pMsg1);
        return;
    }

    tickFrom = tickGet();
    for (i=0; i<count; i++)
    {
        for (j=0; j<MSGBUF_COUNT; j++)
        {
            memcpy(pMsg1[j], pMsg2,  size);                
            HBA_CACHE_FLUSH(pMsg1[j], size);
        }

        
    }
    tick= tickGet() - tickFrom;
    bytes = ((UINT64)count) * ((UINT64)size * MSGBUF_COUNT);
    if (tick == 0)
        speed = bytes;
    else
        speed = bytes * sysClkRateGet() /tick;
    
    printf("copy %s bytes in %u ticks,", UInt64toStr2(bytes), tick);
    printf("speed %s byte/s\n,", UInt64toStr2(speed));

    for (i = 0; i<MSGBUF_COUNT; i++)
    {
        free(pMsg1[i]);
    }
    free(pMsg2);
}

#if 0
/*ELS测试*/
VOID testInitRawEnv(HBA_DEV_CB *pHbaDevCB)
{
    int ret, direct, mode, index, priority, asmid, fcid, msg_recover, sid;
    PRAW_FRAME_CTRL ctrl;
    
    direct = HOST_READ;
    mode = RAW_MODE;
    index = 0;
    priority = PRIORITY_LEVEL_RAW_MSG;
    asmid = 0;
    fcid = 0;
    msg_recover = 0;
    sid = 0;
    ret = hwCreateChannel((PREG_HW)pHbaDevCB->pMembaseCsr, direct, mode, index, priority, asmid, fcid, msg_recover);
    if (ret)
    {
        printf("hwCreateChannel return %d\n", ret);
        return ;
    }
    /* debug */
    {
        PORT_RX_ENAB en;
        en.value = ReadRegisterUlong((ULONG *)(pHbaDevCB->pMembaseCsr + 0xC));

        /* Redundant enable '0' disable '1' enable */
        en.u.redundancy_enab = 0;
        WriteRegisterUlong((ULONG *)(pHbaDevCB->pMembaseCsr + 0xC), en.value);
    }
    ctrl = &pHbaDevCB->rawFrameCtrl;
    ret = InitRawFrameList(ctrl);
    if (ret) {
        printf("InitRawFrameList return %d\n", ret);
        return ;
    }

    pHbaDevCB->pRawDataBlock = (UINT8 *)malloc(MAX_RECV_BUFER_LEN_ELS);
    if (pHbaDevCB->pRawDataBlock == NULL) {
        printf("malloc %d failed\n", MAX_RECV_BUFER_LEN_ELS);
        return ;
    }    
}

VOID testUnInitRawEnv(HBA_DEV_CB *pHbaDevCB)
{
    PRAW_FRAME_CTRL ctrl;

    ctrl = &pHbaDevCB->rawFrameCtrl;
    free(pHbaDevCB->pRawDataBlock);
    pHbaDevCB->pRawDataBlock = NULL;
    UnInitRawFrameList(ctrl);
}

/*单帧发送测试
   length-payload 长度
   count-发送的次数*/
VOID testElsSendFrame(HBA_DEV_CB *pHbaDevCB, int length, int count)
{
    int idx, ret = OK;
    FC_ELS_CONFIG elsConfig;

    printf("[testElsSendFrame]enter count=%d\n", count);
    if (!(length >= 4 && length < FC_ELS_PAYLOAD_MAX - FC_ELS_KEY_SIZE))
    {
        printf("[testElsSendFrame]length=%d error\n", length);
        return ;
    }
    memset(&elsConfig, 0, sizeof(FC_ELS_CONFIG));

    elsConfig.sid = 0x100001;     /* 源ID */
    elsConfig.did = 0x100000;     /* 目的ID */
    elsConfig.key[0] = 0xABCD1234;     /* 业务的key */
    elsConfig.length = length;        /* 不包含key长度的payload长度 */
    for (idx = 0; idx < length; ++idx)
    {
        elsConfig.payload[idx] = (char)idx; /* payload的内容 */
    }
    /*printElsConfig(3, &elsConfig); */
    for (idx = 0; idx < count; ++idx)
    {
        /* ret = hbaElsSend(pHbaDevCB, &elsConfig); */
        if (ret)
        {
            printf("[testElsSendFrame]count=%d idx=%d ret=%d\n", count, idx, ret);
            break;
        }
    }
    printf("[testElsSendFrame]leave send count is %d\n", idx);
}

int g_test_els_stop = 0;
int g_test_els_print = 100;

VOID testElsRecvFrame(HBA_DEV_CB *pHbaDevCB, int key, int count)
{
    int ret, idx;
    FC_ELS_CONFIG elsConfig;
    
    printf("[testElsRecvFrame]enter count=%d g_test_els_stop=%d\n", count, g_test_els_stop);
    elsConfig.key[0] = key;
    idx = 0;
    while (g_test_els_stop == 0 && idx < count)
    {
        ret = hbaElsRecv(pHbaDevCB, &elsConfig);
        if (ret)
        {
            /*printf("[testElsRecvFrame]hbaElsRecv return %d [idx=%d count=%d]\n", ret, idx, count);*/
            taskDelay(1);
            continue;
        }
        idx++;
        if (g_test_els_print)
        {
            g_test_els_print--;
            printf("[testElsRecvFrame]idx=%d\n", idx);
            printElsConfig(101, &elsConfig);
        }
    }
    printf("[testElsRecvFrame]leave recv frame is %d\n", idx);
}

VOID printElsConfig(int key, FC_ELS_CONFIG *elsConfig)
{
    int idx;
    printf("ELS_CONFIG[key=%d\n", key);
    printf("sid=0x%08x\n", elsConfig->sid);/* 源ID */
    printf("did=0x%08x\n", elsConfig->did);/* 目的ID */
    printf("key=0x%08x\n", elsConfig->key);/* 业务的key */
    printf("length=0x%08x\n", elsConfig->length);/* 不包含key长度的payload长度 */
    ASSERT(elsConfig->length + 4 <= FC_ELS_PAYLOAD_MAX);
    printBuffer(key, elsConfig->payload, elsConfig->length);
    printf("]\n");
}


/*测试端口的link状态的中断上报*/
int g_stop_check_port_status = 0;
/* 中断回调定义 */
VOID testPortStatusHandler(FC_HANDLE hDev, FCUINT intCode)
{
    printf("intCode=0x%08x\n");
}


VOID testPortStatus()
{
    if (g_hDev == NULL)
    {
        printf("g_hDev is NULL\n");
        return;
    }
    
    FC_NP_RegEvtHandler(g_hDev, testPortStatusHandler);
    while (g_stop_check_port_status == 0)
    {
        printf("g_stop_check_port_status=%d\n", g_stop_check_port_status);
        taskDelay(1000);
    }
    FC_NP_UnRegEvtHandler(g_hDev);
}

VOID print_config_block(int key, CONFIG_BLOCK *cb)
{
    int idx, count;
    FC_PORT_CONFIG *pc;
    FC_MSG_SEND_ITEM *send_item;
    FC_MSG_RECV_ITEM *recv_item;

    pc = &cb->port_config;
    print_fc_port_config(key, pc);
    
    count = pc->nonblock_txmsg_num + pc->block_txmsg_num;    
    for (idx = 0; idx < count; ++idx)
    {
        send_item = &cb->send_item[idx];
        print_fc_msg_send_item(key, send_item);
    }

    count = pc->nonblock_rxmsg_num + pc->block_rxmsg_num;
    for (idx = 0; idx < count; ++idx)
    {
        recv_item = &cb->recv_item[idx];
        print_fc_msg_recv_item(key, recv_item);
    }
}

VOID print_fc_port_config(int key, FC_PORT_CONFIG *fc_port_config)
{
    FC_PORT_CONFIG *c;
    c = fc_port_config;
    
    printf("[FC_PORT_CONFIG]key=%d\n", key);
    printf("port_id=%d\n", c->port_id);
    printf("port_type=%d\n", c->port_type);
    printf("credit_num=%d\n", c->credit_num);
    printf("role=%d\n", c->role);
    printf("clk_sync_role=%d\n", c->clk_sync_role);
    printf("nc_wdt_period=%d\n", c->nc_wdt_period);
    printf("wdt_loader_period=%d\n", c->wdt_loader_period);
    /*printf("clk_sync_period=%d\n", c->clk_sync_period);*/
    /*printf("date_sync_period=%d\n", c->date_sync_period);*/
    printf("nonblock_txmsg_num=%d\n", c->nonblock_txmsg_num);
    printf("nonblock_rxmsg_num=%d\n", c->nonblock_rxmsg_num);
    printf("block_txmsg_num=%d\n", c->block_txmsg_num);
    printf("block_rxmsg_num=%d\n", c->block_rxmsg_num);
}

VOID print_fc_msg_send_item(int key, FC_MSG_SEND_ITEM *item)
{
    printf("[FC_MSG_SEND_ITEM]key=%d\n", key);
    printf("msg_id=%d\n", item->msg_id);
    printf("msg_type=%d\n", item->msg_type);
    printf("msg_priority=%d\n", item->msg_priority);
    printf("msg_src_id=%d\n", item->msg_src_id);
    printf("msg_dst_id=%d\n", item->msg_dst_id);
}


VOID print_fc_msg_recv_item(int key, FC_MSG_RECV_ITEM *item)
{
    printf("[FC_MSG_RECV_ITEM]key=%d\n", key);
    printf("msg_id=%d\n", item->msg_id);
    printf("msg_type=%d\n", item->msg_type);
    printf("msg_src_id=%d\n", item->msg_src_id);
    printf("msg_recover=%d\n", item->msg_recover);
}

int testRtcControl()
{
    HBA_DEV_CB *pHbaDevCB = (HBA_DEV_CB*)g_hDev;
    hwRtcControl((PREG_HW )(pHbaDevCB->pMembaseCsr), 1, 100, 1, 1);
    
    return 0;
}



int testGetVoltage()
{
    int value;
    HBA_DEV_CB *pHbaDevCB = (HBA_DEV_CB*)g_hDev;
    value = hwGetVoltage((PREG_HW )(pHbaDevCB->pMembaseCsr));
    printf("Voltage=%d!\n", value);
    return value;
}

int testGetTemperature()
{
    int value;
    HBA_DEV_CB *pHbaDevCB = (HBA_DEV_CB*)g_hDev;
    value = hwGetTemperature((PREG_HW )(pHbaDevCB->pMembaseCsr));
    printf("Temperature=%d!\n", value);
    return value;
}


int test_UInt64toStr1(void)
{
    char szData[256];
    szData;
    return 0;
}

int test_UInt64toStr2(void)
{
    char szData[256] = "";
    szData;
    return 0;
}

int test_tLoopBackStart1(void)
{
    char testTaskName[30] = {0}; 
    testTaskName;
    return 0;
}

int test_tLoopBackStart2(voidn)
{
    char testTaskName[30]; 
    testTaskName;
    return 0;
}

#endif
