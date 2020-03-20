#include <vxworks.h>
#include <semLib.h>
#include "fc_api.h"

#define MAX_IU_LEN     0x1000000

extern BLUE_PRINT gBluePrint[];

/*����꣬��ʹ���жϽ��շ�ʽ����ASM��Ϣ*/
#define DEMO_USE_INT_ASM_RECV

FCUINT g_fcid;
int g_major_scheme, g_minor_scheme, g_nm_role, g_send_count, g_task_state, g_recvNumber;
unsigned char *g_send_msg, *g_recv_msg;
SEM_ID g_sem_manager_on_line;

/*����ID*/
int g_manager_task_id, g_send_task_id, g_recv_task_id;

/*�¼��жϻص�*/
FCUINT DemoEventNotify(FCHANDLE hDev, FCUINT intCode, FCUINT param0);

/*ASM���ջص�*/
FCUINT DemoRecvCallBack(FCHANDLE hDev, FCUINT msgId);

/*����ά���豸������״̬*/
int DemoManagerOnLine(FCHANDLE hDev);

/*��������*/
int DemoSendTask(FCHANDLE hDev);

/*��������*/
int DemoRecvTask(FCHANDLE hDev);

/*����Fcid*/
void SetFcid(FCUINT nmRole);

/*ֹͣ���񣬲���ӡͳ��*/
void DemoStop();

#define TASK_RUN                1    /*����*/
#define    TASK_STOP                2    /*ֹͣ*/

#define DEMO_WAIT_ONLINE_DELAY 1000    /*�ȴ����ߵ��ӳ٣�����*/
#define DEMO_MANAGER_DELAY     20  /*ά������״̬���ӳ٣�����*/
#define DEMO_SEND_DELAY        100 /*����ASM���ӳ٣�����*/
#define DEMO_RECV_DELAY        50  /*����ASM���ӳ٣�����*/
#define FC_ASM_IU_LENGTH_MAX   (16 * 1024 * 1024) /*ASM IU����ֽ�*/

#define NC_FCID        0x010000
#define BNC_FCID    0x010001
#define NRT_FCID    0x010002

/*����ת��Ϊtick�� ���ת��ֵΪ0������1tick*/
unsigned int HbaDemoMilliSecond2Tick(unsigned int milliSecond)
{
    unsigned int tick;

    /*�������С��1000����������0������ת��Ϊ���͵����*/
    tick = (milliSecond * sysClkRateGet()) / 1000;
    if (tick == 0)
    {
        /*��Сֵ��1tick*/
        tick = 1;
    }

    return tick;
}

int bDemoLoopBackExit = FALSE;
STATUS DemoSendAndWaitBackAsmMsgLoop(FCHANDLE hDev, UINT32 msgID, UINT32 lenFrom, UINT32 lenTo)
{
    unsigned char *pMsg;
    unsigned char *pRecvMsg;
    unsigned int msgLen = 0;
    int i;
    UINT32 ret = 0;
    UINT32 count = 0;
    int iCountInPeriod = 0;
    int size = 0;

    
    pMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pMsg == NULL)
    {
        printf("DemoSendAndWaitBackAsmMsgLoop : malloc return NULL.\n");
        return ERROR;
    }

    pRecvMsg = (unsigned char *)malloc(MAX_IU_LEN);
    if (pRecvMsg == NULL)
    {
        printf("DemoSendAndWaitBackAsmMsgLoop : malloc return NULL.\n");
        free(pMsg);
        return ERROR;
    }

    

    bDemoLoopBackExit = FALSE;
        
    for (size = lenFrom; size <= lenTo; size ++)
    {
        if (bDemoLoopBackExit)
            break;

        /* prepare ASM message */
        for (i=0; i<size; i++)
        {
            /*pMsg[i] = (UINT8)(i-1);*/
            pMsg[i] = (UINT8)size;
        }
        

        if ((size % 1000) == 0)
            printf("Send Msg len = %d\n", size);
        
        ret = FC_NP_SendMsg(hDev, msgID, pMsg, size);
        if ( ret != FC_SUCCESS)
        {
            printf("DemoSendAndWaitBackAsmMsgLoop: FC_NP_SendMsg return 0x%x.\n", ret);
            free(pMsg);
            free(pRecvMsg);
            return ERROR;
        }
        else
        {
            while(1)
            {
                while(1)
                {
                    msgLen = MAX_IU_LEN;
                    ret = FC_NP_RecvMsg(hDev, msgID, pRecvMsg, &msgLen);
                    if ( ret == FC_RECV_NO_DATA)
                    {
                        taskDelay(1);
                        continue;
                    }
                    if (ret != FC_SUCCESS)
                    {
                        printf("DemoSendAndWaitBackAsmMsgLoop: FC_NP_RecvMsg return 0x%x.\n", ret);
                        taskDelay(1);
                        continue;
                    }
                    break;
                }

                if (msgLen != size)
                {
                    printf("DemoSendAndWaitBackAsmMsgLoop : compare length fail, sendlen=%d, recvlen%d.\n", size, msgLen);
                    continue;
                }

                if (memcmp(pRecvMsg, pMsg, msgLen) != 0)
                {
                    printf("hbaTestSendAndWaitBackAsmMsgLoop :compare content fail. msgLen=%d\n", msgLen);
                    {
                        int pos = 0, p1, p2;
                        int idx;

                        for (pos = 0; pos < msgLen; pos ++)
                        {
                            if (pMsg[pos] != pRecvMsg[pos] )
                            {
                                printf("  pos=%d\n", pos);
                                break;
                            }
                        }

                        p1 = max(0, pos - 16);
                        p2 = min(pos + 16, msgLen);

                        
                        printf("send data : %p\n", pMsg);
                        for (idx = p1; idx < p2; ++idx) {
                            printf("%02x ", (unsigned char)pMsg[idx]);
                            if ((idx + 1) % 16 == 0) {
                                printf("\n");
                            }
                        }
                        printf("\n");    

                        printf("recv data : %p \n", pRecvMsg);
                        for (idx = p1; idx < p2; ++idx) {
                            printf("%02x ", (unsigned char)pRecvMsg[idx]);
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

            if (iCountInPeriod >= 1000)
            {
                taskDelay(0);
                iCountInPeriod = 0;
            }
        }
    }


    printf("DemoSendAndWaitBackAsmMsgLoop exit, sent %d message.\n", count);

    free(pMsg);
    free(pRecvMsg);
    
    return OK;
}

/*�¼��жϻص�*/
FCUINT DemoEventNotify(FCHANDLE hDev, FCUINT intCode, FCUINT param0)
{
    FCUINT ret, nmRole, fcState;

    switch (intCode)
    {
        case IC_VOLTAGE_SUCCESS:
        {
            /*��ѹ�Ӵ���ֵ��Ϊ����ֵ*/
            printf("intCode=IC_VOLTAGE_SUCCESS param0=0x%08x\n", param0);
            break;
        }
        case IC_VOLTAGE_FAILED :
        {
            /*��ѹ����*/
            printf("intCode=IC_VOLTAGE_FAILED param0=0x%08x\n", param0);
            break;
        }
        case IC_TEMP_SUCCESS :
        {
            /*�¶ȴӴ���ֵ��Ϊ����ֵ*/
            printf("intCode=IC_TEMP_SUCCESS param0=0x%08x\n", param0);
            break;
        }
        case IC_TEMP_FAILED :
        {
            /*�¶ȴ���*/
            printf("intCode=IC_TEMP_FAILED param0=0x%08x\n", param0);
            break;
        }
        case IC_LINK_STATUS_SUCCESS :
        {
            /*link״̬�Ӵ���ֵ��Ϊ����ֵ*/

            /*�����ź�����֪ͨά������״̬�������鱾�ؽڵ������״̬*/
            semGive(g_sem_manager_on_line);
            printf("intCode=IC_LINK_STATUS_SUCCESS param0=0x%08x\n", param0);

            break;
        }
        case IC_LINK_STATUS_FAILED :
        {
            /*link״̬����*/
            printf("intCode=IC_LINK_STATUS_FAILED param0=0x%08x\n", param0);
            break;
        }
        case IC_IO_BUF_WRITE_FAILED :
        {
            /*�շ�������д����*/
            printf("intCode=IC_IO_BUF_WRITE_FAILED param0=0x%08x\n", param0);
            break;
        }
        case IC_IO_BUF_READ_FAILED :
        {
            /*�շ�������������*/
            printf("intCode=IC_IO_BUF_READ_FAILED param0=0x%08x\n", param0);
            break;
        }
        case IC_DISCARD_MSG :
        {
            /*��Ϣ����*/
            printf("intCode=IC_DISCARD_MSG param0=0x%08x\n", param0);
            break;
        }
        case IC_COVER_MSG :
        {
            /*��Ϣ����*/
            printf("intCode=IC_COVER_MSG param0=0x%08x\n", param0);
            break;
        }
        case IC_IU_TIMEOUT :
        {
            /*IU��ʱ*/
            printf("intCode=IC_IU_TIMEOUT param0=0x%08x\n", param0);
            break;
        }
        case IC_IU_SEQ_ERR :
        {
            /*IU��ʱ*/
            printf("intCode=IC_IU_SEQ_ERR param0=0x%08x\n", param0);
            break;
        }
        case IC_IU_LENGTH_INVALID :
        {
            /*IU������Ч*/
            printf("intCode=IC_IU_LENGTH_INVALID param0=0x%08x\n", param0);
            break;
        }
        case IC_ELS_RECV_RECONSTRUCT :
        {
            /*�ع�*/
            printf("intCode=IC_ELS_RECV_RECONSTRUCT param0=0x%08x\n", param0);
            break;
        }
        case IC_ELS_RECV_NC_ON_NET :
        {
            /*NC����*/
            printf("intCode=IC_ELS_RECV_NC_ON_NET param0=0x%08x\n", param0);
            break;
        }
        case IC_ELS_RECV_NC_TIMEOUT :
        {
            /*WDT��ʱ*/
            printf("intCode=IC_ELS_RECV_NC_TIMEOUT param0=0x%08x\n", param0);

            ret = FC_NM_RoleGet(hDev, &nmRole);
            if (ret)
            {
                printf("FC_NM_RoleGet failed ret=0x%08x\n", ret);
                break;
            }
            printf("FC_NM_RoleGet success role=%d\n",nmRole);

            /*BNC�л�ΪNC*/
            if (nmRole == FC_NET_ROLE_BNC)
            {
#if 1
                fcState = FC_PORT_STATUS_LINK_DOWN;
                ret = FC_NP_GetState(hDev, &fcState);
                if (ret)
                {
                    printf("FC_NM_GetState failed ret=0x%08x\n", ret);
                    break;
                }
                printf("FC_NM_GetState success \n");

                if (fcState == FC_PORT_STATUS_LINK_DOWN)
                {
                    printf("BNC FC_PORT_STATUS_LINK_DOWN\n");
                    break;
                }
#endif
                ret = FC_NM_RoleSet(hDev, FC_NET_ROLE_NC);
                if (ret)
                {
                    printf("FC_NM_RoleSet failed ret=0x%08x\n", ret);
                    break;
                }
                printf("FC_NM_RoleSet success BNC ChangeTo NC\n", hDev);

                /*ʹ��WDT*/
                ret = FC_NM_WDTEnable(hDev, FC_WDT_NET_MODE);
                if (ret)
                {
                    printf("FC_NM_WDTEnable failed ret=0x%08x\n", ret);
                    break;
                }
                printf("FC_NM_WDTEnable success\n");
            }

            break;
        }
        case IC_ELS_RECV_RECONSTRUCT_SUCCESS :
        {
            /*�ع����*/
            printf("intCode=IC_ELS_RECV_RECONSTRUCT_SUCCESS param0=0x%08x\n", param0);
            break;
        }
        case IC_ELS_RECV_RECONSTRUCT_FAIL :
        {
            /*�ع�ʧ��*/
            printf("intCode=IC_ELS_RECV_RECONSTRUCT_FAIL param0=0x%08x\n", param0);
            break;
        }
        case IC_NC_CONFLICT :
        {
            /*NC��ͻ*/
            printf("intCode=IC_NC_CONFLICT param0=0x%08x\n", param0);

            ret = FC_NM_RoleGet(hDev, &nmRole);
            if (ret)
            {
                printf("FC_NM_RoleGet failed ret=0x%08x\n", ret);
                break;
            }
            printf("FC_NM_RoleGet success role=%d\n", nmRole);

            if (nmRole == FC_NET_ROLE_NC)
            {
                /*�ر�WDT*/
                ret = FC_NM_WDTEnable(hDev, FC_WDT_LOCAL_MODE);
                if (ret)
                {
                    printf("FC_NM_WDTEnable failed ret=0x%08x\n", ret);
                    break;
                }

                printf("FC_NM_WDTEnable success\n", hDev);
                ret = FC_NM_RoleSet(hDev, FC_NET_ROLE_BNC);
                if (ret)
                {
                    printf("FC_NM_RoleSet failed ret=0x%08x\n", ret);
                    break;
                }
                printf("FC_NM_RoleSet success NC ChangeTo BNC\n");
            }
            break;
        }
        case IC_NC_CHANGED :
        {
            /*NC�л�*/
            printf("intCode=IC_NC_CHANGED param0=0x%08x\n", param0);
            break;
        }
        default:
        {
            printf("unknown intCode=0x%08x param0=0x%08x\n", intCode, param0);
            break;
        }
    }
    
    return 0;
}

/*���Ժ��� nmRole ��������ɫ sendCount ���ʹ���*/
void vx_main(int nmRole, int sendCount)
{
    FCUINT ret, devId, fcid;
    FCHANDLE hDev;
    CONFIG_BLOCK *cb;
    char tt;

    devId = 0;
    g_nm_role = nmRole;
    g_send_count = sendCount;
    g_task_state = TASK_RUN;
    g_recvNumber = 0;

    sysClkRateSet(1000);
    
    /*���䷢���ڴ�*/
    g_send_msg = (unsigned char *)malloc(FC_ASM_IU_LENGTH_MAX);
    if (g_send_msg == NULL)
    {
        printf("malloc send msg failed\n");
        return;
    }
    memset(g_send_msg, 0, FC_ASM_IU_LENGTH_MAX);

    /*��������ڴ�*/
    g_recv_msg = (unsigned char *)malloc(FC_ASM_IU_LENGTH_MAX);
    if (g_recv_msg == NULL)
    {
        printf("malloc recv msg failed\n");
        return;
    }
    memset(g_recv_msg, 0, FC_ASM_IU_LENGTH_MAX);

    /*��ʼ���ź��� */
    g_sem_manager_on_line = semBCreate(SEM_Q_FIFO, SEM_FULL);
    if (g_sem_manager_on_line == NULL)
    {
        printf("semBCreate failed\n");
        return;
    }

    /*���豸*/
    ret = FC_NP_Open(&hDev, devId);
    if (ret)
    {
        printf("FC_NP_Open failed ret=0x%08x\n", ret);
        return;
    }
    printf("FC_NP_Open success hDev=%p\n", hDev);

    /*ע���¼�������*/
    ret = FC_NP_RegEvtHandler(hDev, DemoEventNotify);
    if (ret)
    {
        printf("FC_NP_RegEvtHandler failed ret=0x%08x\n", ret);
        return;
    }
    printf("FC_NP_RegEvtHandler success\n");
#if 0 /* def DEMO_USE_INT_ASM_RECV */
    /*ע��ASM��Ϣ������*/
    ret = FC_NP_RegMsgHandler(hDev, DemoRecvCallBack);
    if (ret)
    {
        printf("FC_NP_RegMsgHandler failed ret=0x%08x\n", ret);
        return;
    }
    printf("FC_NP_RegMsgHandler success\n");
#endif
    /*����FC�ڵ����ASMͨ��ģʽ*/
    ret = FC_NP_ConfigMode(hDev, FC_CONFIG_MODE_PROJECT);
    if (ret)
    {
        printf("FC_NP_ConfigMode failed ret=0x%08x\n", ret);
        return;
    }
    printf("FC_NP_ConfigMode success\n");

    if (g_nm_role == FC_NET_ROLE_NC)
    {
        g_major_scheme = 0;
        g_minor_scheme = 0;
    }
    else if (g_nm_role == FC_NET_ROLE_BNC)
    {
        g_major_scheme = 0;
        g_minor_scheme = 1;
    } else if (g_nm_role == FC_NET_ROLE_NRT)
    {
        g_major_scheme = 0;
        g_minor_scheme = 2;
    }

    /*����FC�ڵ����ASM����*/
    ret = FC_NP_LoadConfig(hDev, g_major_scheme, g_minor_scheme);
    if (ret)
    {
        printf("FC_NP_LoadConfig failed ret=0x%08x\n", ret);
        return;
    }
    printf("FC_NP_LoadConfig success\n");

    ret = FC_NP_AsmRunControl(hDev, FC_ASM_RUN_ENAB);
    if (ret)
    {
        printf("FC_NP_AsmRunControl failed ret=%d\n", ret);
    }
    printf("FC_NP_AsmRunControl success\n");

    DemoSendAndWaitBackAsmMsgLoop(hDev, 1, 10, 0x100000);
#if 0
    /*��ȡ��������ɫ*/
    ret = FC_NM_RoleGet(hDev, &g_nm_role);
    if (ret)
    {
        printf("FC_NM_RoleGet failed ret=0x%08x\n", ret);
        return;
    }
    printf("FC_NM_RoleGet success role=%d\n", g_nm_role);

    if (g_nm_role == FC_NET_ROLE_NC)
    {
        ret = FC_NM_WDTEnable(hDev, FC_WDT_NET_MODE);
        if (ret)
        {
            printf("NC FC_NM_WDTEnable failed ret=0x%08x\n", ret);
            return;
        }
        printf("NC FC_NM_WDTEnable success\n");

        g_fcid = NRT_FCID;
    }
    else
    {
        g_fcid = NC_FCID;
    }
#endif

#if 0 /*ndef DEMO_USE_INT_ASM_RECV*/
    g_recv_task_id = taskSpawn("demoRev", 100, 0, 40960, DemoRecvTask, hDev, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (g_recv_task_id == ERROR)
    {
        printf("taskSpawn DemoRecvTask failed\n");
        return;
    }
    printf("taskSpawn DemoRecvTask success\n");
#endif

#if 0
    tt = '-';
    do 
    {
        char t;
        FCUINT index, netNodeState;
        OnNetTbl netTbl;

        printf("[hDev=%d]wait g_fcid=0x%08x on line", hDev, g_fcid);
        printf("%c\r", tt);
        switch (tt)
        {
            case '-': tt = '\\'; break;
            case '\\': tt = '|'; break;
            case '|': tt = '/'; break;
            case '/': t = '-'; break;
            default: tt = '-'; break;
        }
        
        ret = FC_NM_GetOnNetTable(hDev, &netTbl);
        if (ret)
        {
            printf("FC_NM_GetOnNetTable failed ret=0x%08x\n", ret);
            return;
        }
        index = (unsigned char)g_fcid;
        netNodeState = netTbl.Status[index];
        if (netNodeState == FC_NODE_STATE_ON_LINE) break;
        taskDelay(HbaDemoMilliSecond2Tick(DEMO_WAIT_ONLINE_DELAY));
    } while (1);
    printf("[hDev=%d] g_fcid=0x%08x is online\n", hDev, g_fcid);


    g_manager_task_id = taskSpawn("demoMan", 100, 0, 40960, DemoManagerOnLine, hDev, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (g_manager_task_id == ERROR)
    {
        printf("taskSpawn DemoMainagerOnLine failed\n");
        return;
    }
    printf("taskSpawn DemoMainagerOnLine success\n");

    g_send_task_id = taskSpawn("demoSed", 100, 0, 40960, DemoSendTask, hDev, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (g_send_task_id == ERROR)
    {
        printf("taskSpawn DemoSendTask failed\n");
        return;
    }
    printf("taskSpawn DemoSendTask success\n");
#endif    
}

/*����ά���豸������״̬*/
int DemoManagerOnLine(FCHANDLE hDev)
{
    FCUINT ret, state, nmRole;

    while (g_task_state == TASK_RUN)
    {
        /*�ȴ��ź��� ������ �� ��ʱ*/
        semTake(g_sem_manager_on_line, HbaDemoMilliSecond2Tick(DEMO_MANAGER_DELAY));

        /*���˿ڵ�link״̬*/
        state = FC_PORT_STATUS_LINK_DOWN;
        ret = FC_NP_GetState(hDev, &state);
        if (ret)
        {
            printf("FC_NP_GetState failed ret=0x%08x\n", ret);
            break;
        }
        if (state == FC_PORT_STATUS_LINK_DOWN)
        {
            printf("FC_PORT_STATUS_LINK_DOWN\n");
            continue;
        }

        /*��ȡ��������ɫ*/
        ret = FC_NM_RoleGet(hDev, &nmRole);
        if (ret)
        {
            printf("FC_NM_RoleGet failed ret=0x%08x\n", ret);
            break;
        }
        /*printf("FC_NM_RoleGet success role=%d\n", nmRole);*/

        if (nmRole != FC_NET_ROLE_NC )
        {
            /*���NC����״̬*/
            state = FC_NODE_STATE_OFF_LINE;
            ret = FC_NM_NRT_NcIsOnNet(hDev, &state);
            if (ret)
            {
                printf("FC_NM_NRT_NcIsOnNet failed ret=0x%08x\n", ret);
                break;
            }

            if (state == FC_NODE_STATE_OFF_LINE)
            {
                /*NC�ڵ㲻����*/
                continue;
            }

            /*����Լ�������״̬*/
            state = FC_NODE_STATE_OFF_LINE;
            ret = FC_NM_GetOnNetState(hDev, &state);
            if (ret)
            {
                printf("FC_NM_GetOnNetState failed ret=0x%08x\n", ret);
                break;
            }
            if (state == FC_NODE_STATE_ON_LINE)
            {
                /*���ؽڵ��Ѿ�����*/
                continue;
            }

            /*������������*/
            ret = FC_NM_NRT_OnNetReq(hDev);
            if (ret)
            {
                printf("FC_NM_NRT_OnNetReq failed ret=0x%08x\n", ret);
                break;
            }
            printf("FC_NM_NRT_OnNetReq success \n");
        }
    }

    g_manager_task_id = ERROR;

    return 0;
}

/*��������*/
int DemoSendTask(FCHANDLE hDev)
{
    FCUINT i, j, send_count, ch_count, ret, msgId, nLen, nmRole, sendNumber, state;
    FCUCHAR *pMsg;
    FC_MSG_SEND_ITEM *item;
    CONFIG_BLOCK *cb;

    sendNumber = 0;
    send_count = g_send_count;
    cb = &gBluePrint[g_major_scheme].config_block[g_minor_scheme];
    nmRole = cb->port_config.role;
    ch_count = cb->port_config.block_txmsg_num + cb->port_config.nonblock_txmsg_num;
    pMsg = g_send_msg;

    while (1)
    {
        for (i = 0; i < send_count; ++i)
        {
            for (j = 0; j < ch_count; ++j)
            {
                item = &cb->send_item[j];
                msgId = item->msg_id;
                nLen = 1024;

                ret = FC_NM_RoleGet(hDev, &g_nm_role);
                if (ret)
                {
                    printf("FC_NM_RoleGet failed ret=0x%08x\n", ret);
                    return;
                }

                if (g_nm_role == FC_NET_ROLE_BNC)
                {
                    if (msgId == 4)
                    {
                        /*printf("[send]nmRole=ROLE_BNC msgId=4\n");*/
                        continue;
                    }
                }

                if (g_nm_role == FC_NET_ROLE_NRT)
                {
                    if (item->msg_dst_id == FC_NC_BNC_MULTICAST_ADDR)
                    {
                        nLen = 2048;
                    }
                }
                memset(pMsg, (unsigned char)msgId, nLen);

                while (1)
                {
                    taskDelay(HbaDemoMilliSecond2Tick(DEMO_SEND_DELAY));

                    if (g_task_state == TASK_STOP)
                    {
                        return;
                    }

                    /*����Լ�������״̬*/
                    state = FC_NODE_STATE_OFF_LINE;
                    ret = FC_NM_GetOnNetState(hDev, &state);
                    if (ret)
                    {
                        printf("FC_NM_GetOnNetState failed ret=0x%08x\n", ret);
                        break;
                    }
                    if (state == FC_NODE_STATE_OFF_LINE)
                    {
                        /*���ؽڵ㲻�����򲻷���*/
                        continue;
                    }

                    ret = FC_NP_SendMsg(hDev, msgId, pMsg, nLen);
                    if (ret)
                    {
                        continue;
                    }
                    printf("[send %d]sid=0x%08x did=0x%08x msgId=%d nLen=%d \n", ++sendNumber, item->msg_src_id, item->msg_dst_id, msgId, nLen);
                    break;
                }
            }
        }
        printf("Send ASM complete sendNumber=%d\n", sendNumber);
        break;
    }

    g_send_task_id = ERROR;

    return 0;
}

/*��������*/
int DemoRecvTask(FCHANDLE hDev)
{
    FCUINT ret, i, ch_count, msgId, nLen, recvNumber, state;
    FCUCHAR *pMsg;
    FC_MSG_RECV_ITEM *item;
    CONFIG_BLOCK *cb;

    recvNumber = 0;
    cb = &gBluePrint[g_major_scheme].config_block[g_minor_scheme];
    ch_count = cb->port_config.block_rxmsg_num + cb->port_config.nonblock_rxmsg_num;
    pMsg = g_recv_msg;

    while (1)
    {
        for (i = 0; i < ch_count; ++i)
        {
            item = &cb->recv_item[i];
            msgId = item->msg_id;
            nLen = 2048;

            if (g_task_state == TASK_STOP)
            {
                return;
            }

            /*����Լ�������״̬*/
            state = FC_NODE_STATE_OFF_LINE;
            ret = FC_NM_GetOnNetState(hDev, &state);
            if (ret)
            {
                printf("FC_NM_GetOnNetState failed ret=0x%08x\n", ret);
                break;
            }
            if (state == FC_NODE_STATE_OFF_LINE)
            {
                /*���ؽڵ㲻�����򲻷���*/
                continue;
            }

            do 
            {
                ret = FC_NP_RecvMsg(hDev, msgId, pMsg, &nLen);
                if (ret == 0)
                {
                    printf("[recv %d] sid=0x%08x msgId=%d nLen=%d\n", ++recvNumber, item->msg_src_id, msgId, nLen);
                }
            } while ((ret == 0) && (nLen > 0));
            if (ret)
            {
                continue;
            }
            if (nLen == 0)
            {
                continue;
            }
        }
        taskDelay(HbaDemoMilliSecond2Tick(DEMO_RECV_DELAY));
    }

    g_recv_task_id = ERROR;

    return 0;
}

/*ASM���ջص�*/
FCUINT DemoRecvCallBack(FCHANDLE hDev, FCUINT msgId)
{
    FCUINT ret, nLen;
    FCUCHAR *pMsg;

    pMsg = g_recv_msg;
    nLen = 2048;
    ret = FC_NP_RecvMsg(hDev, msgId, pMsg, &nLen);
    if (ret)
    {
        printf("FC_NP_RecvMsg Failed ret=0x%08x\n", ret);
        return ret;
    }
    printf("[Int recv %d] msgId=%d nLen=%d\n", ++g_recvNumber, msgId, nLen);

    return FC_SUCCESS;
    
}

/*����g_fcid*/
void SetFcid(FCUINT nmRole)
{
    if (nmRole == 1)
    {
        g_fcid = NC_FCID;
    }

    if (nmRole == 2)
    {
        g_fcid = BNC_FCID;
    }

    if (nmRole == 3)
    {
        g_fcid = NRT_FCID;
    }
}


/*ֹͣ���ͽ���*/
void DemoStop()
{
    g_task_state = TASK_STOP;

    hbaDrvShowAll(4, 0);
}
