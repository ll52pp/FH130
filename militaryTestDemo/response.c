/**************************************************************************************************
由于FH130, FH180等项目函数接口,宏定义等都不一样,本demo封装一层通用接口，
具体实现在接口中用宏隔离。 jin.liu 20180518
***************************************************************************************************/

#if 1/*__FH130_AUTO_TEST_DEMO__*/
/*这个文件中含有不同项目的宏定义等适配,必须放在最上面*/
#include "fcDemoTest.h"
#endif

#include "precomp.h"
#include "response.h"


static int bResponseTableInited = 0;
static RESPONSE_NODE * g_pResponseTable = NULL;

/*自检*/
void FH180Style_demoTestPBit(FCHANDLE hDev);

UINT ResponseCallBack(int context);

unsigned int CmdConfigDevHandler(FCHANDLE hDev);

void demoTestPBit(FCHANDLE hDev);

VOID HwSetEdtov(REG_HW *reg_hw, INT32 v);

/*没有角色的情况下，发送接收时钟原语*/
void TestSyncControl(UINT32 period, UINT32 recv_sync, UINT32 send_sync);

/*强制下网*/
void TestForceOffLine(FCHANDLE hDev, FCUINT fcid);

/*测试发送下网请求*/
void TestOffline(FCHANDLE hDev);

#if 1/*__FH130_AUTO_TEST_DEMO__*/
unsigned int demoSetConfigSchemeIndex(void);
unsigned int demoTestDeviceQueryAndOpen(FCHANDLE *hDev, FCUINT DevId);
unsigned int demoCheckBluePrintAndLoadConfig(FCHANDLE hDev, FCUINT majorScheme, FCUINT minorScheme);
#endif
#if 0

int InitResponseTable(void)
{
    g_pResponseTable = gResponseTable;

    bResponseTableInited = 1;

    return 0;
}

#else

int InitResponseTable(void)
{
    int i, j;
    int len = 0;
    char content = 'A';
    UINT32 msgID = 0;

    if (bResponseTableInited == 1)
    {
        return 0;
    }

    g_pResponseTable = (RESPONSE_NODE *)malloc(sizeof(RESPONSE_NODE) * FC_CHANNEL_NUM_MAX);
    if (g_pResponseTable == NULL)
    {
        return -1;
    }

    for (i = 0; i <FC_CHANNEL_NUM_MAX; i++)
    {
        msgID = i + 1;

        g_pResponseTable[i].asmid = msgID;

        if (msgID == 0x2)
        {
            len = 76;
            content = 'B';
        }
        else if (msgID == 0x3)
        {
            len = 76;
            content = 'C';
        }
        else if (msgID == 0x6)
        {
            len = 3072;
            content = 'A';
        }
        else if (msgID == 0x23)
        {
            len = 76;
            content = 'A';
        }
        else if (msgID == 0x35)
        {
            len = 2048;
            content = 'A';
        }
        else if (msgID == 0x36)
        {
            len = 1024;
            content = 'A';
        }
        else
        {
            len = 80;
            content = 'A';
        }

        for (j = 0; j<len; j++)
        {      
            g_pResponseTable[i].payload[j] = content;
        }

        g_pResponseTable[i].length = len;
    }

    bResponseTableInited = 1;

    return 0;
}
#endif

int GetResponseNodeById(int asmid, RESPONSE_NODE **node)
{
    int idx, count;

    count = FC_CHANNEL_NUM_MAX;
    *node = NULL;
    for (idx = 0; idx < count; ++idx)
    {
        RESPONSE_NODE *t = &g_pResponseTable[idx];
        
        if (t->asmid == asmid)
        {
            *node = t;
            return 0;
        }
    }
    return 1;
}

/*#define NET_ROLE FC_NET_ROLE_NCT*/
#define NET_ROLE FC_NET_ROLE_NRT

#define SEND_ASM_COUNT  1

int g_scheme_no, g_config_block_no, g_dev_count = 0, g_dev_id, g_dev_open_flag,
g_reg_evt_flag, g_dev_config_flag = 0;

FCHANDLE g_h_dev;

/*事件中断的回调*/
FCUINT EventCallback(FCHANDLE hDev, FCUINT intCode, FCUINT param0)
{
    switch (intCode)
    {
        case DEMO_IC_PORT_LINK_UP:
        {
            printf("int code=DEMO_IC_PORT_LINK_UP param0=%d\n", param0);
            break;
        }

        case DEMO_IC_PORT_LINK_DOWN:
        {
            printf("int code=IC_PORT_LINK_DOWN param0=%d\n", param0);
            break;
        }
        case DEMO_IC_VOLTAGE_GOOD:
        {
            printf("int code=DEMO_IC_VOLTAGE_GOOD param0=%d\n", param0);
            break;
        }
        case DEMO_IC_VOLTAGE_FAILED:
        {
            printf("int code=DEMO_IC_VOLTAGE_FAILED param0=%d\n", param0);
            break;
        }
        case DEMO_IC_TEMPERATURE_GOOD:
        {
            printf("int code=DEMO_IC_TEMPERATURE_GOOD param0=%d\n", param0);
            break;
        }
        case DEMO_IC_TEMPERATURE_FAILED:
        {
            printf("int code=DEMO_IC_TEMPERATURE_FAILED param0=%d\n", param0);
            break;
        }
        case DEMO_IC_RX_IU_DISCARD:
        {
            printf("int code=DEMO_IC_RX_IU_DISCARD param0=%d\n", param0);
            break;
        }
        case DEMO_IC_RX_IU_TIMEOUT:
        {
            printf("int code=DEMO_IC_RX_IU_TIMEOUT param0=%d\n", param0);
            break;
        }
        case DEMO_IC_RX_IU_LENGTH_INVALID:
        {
            printf("int code=DEMO_IC_RX_IU_LENGTH_INVALID param0=%d\n", param0);
            break;
        }
        case DEMO_IC_NCT_ON_NET:
        {
            printf("int code=DEMO_IC_NCT_ON_NET param0=%d\n", param0);
            break;
        }
        case DEMO_IC_ELS_RECV_NC_TIMEOUT:
        {
            printf("int code=DEMO_IC_ELS_RECV_NC_TIMEOUT param0=%d\n", param0);
            break;
        }
        case DEMO_IC_NET_NODE_STATE_TABLE_CHANGED:
        {
            printf("int code=DEMO_IC_NET_NODE_STATE_TABLE_CHANGED param0=%d\n", param0);
            break;
        }
        default:
        {
            printf("unknown int code=%d param0=%d\n", intCode, param0);
            break;
        };
    }
        return 0;
}

/*设备初始化*/
FCUINT DemoDevInit(void)
{
    FCUINT ret = FC_FAILURE;
    FCHANDLE hDev;

    ret = demoSetConfigSchemeIndex();
    if (ret != FC_SUCCESS)
    {
        printf("demoSetConfigSchemeIndex failed ret=%d\n", ret);
        return ret;
    }
    
    ret = demoTestDeviceQueryAndOpen(&g_h_dev, 0);
    if (ret != FC_SUCCESS)
    {
        printf("demoTestDeviceQueryAndOpen failed ret=%d\n", ret);
        return ret;
    }

    return ret;
}

#if 0
/*发送ASM帧*/
FCUINT DemoSendAsm()
{
    FCUINT ret, msgId, nLen;
    int i, iu_len_max, ch_idx, ch_count;
    unsigned int total_bytes, ch_bytes[FC_CHANNEL_NUM_MAX], total_iu_count, ch_iu_count[FC_CHANNEL_NUM_MAX];
    FCUCHAR *pMsg;
    /*TODO:配置块与方案的颠倒。*/
    FC_SCHEME *fs;
    FC_MSG_SEND_ITEM *send_item;
    FCHANDLE hDev;

    hDev = g_h_dev;
    ret = 0;
    if (g_dev_config_flag == 0)
    {
        printf("dev not config\n");
        return 0;
    }
    iu_len_max = 16 * 1024 * 1024;
    pMsg = (FCUCHAR *)malloc(iu_len_max);
    if (pMsg == NULL)
    {
        printf("malloc failed\n");
        return ret;
    }
    memset(pMsg, 0, iu_len_max);
    for (ch_idx = 0; ch_idx < FC_CHANNEL_NUM_MAX; ++ch_idx)
    {
        ch_iu_count[ch_idx] = 0;
        ch_bytes[ch_idx] = 0;
    }
    fs = &gBluePrint.config_block[g_config_block_no].scheme[g_scheme_no];
    ch_count = fs->port_config.stream_txmsg_num + fs->port_config.block_txmsg_num;
    total_iu_count = 0;
    total_bytes = 0;
    while (1)
    {
        for (i = 0; i < SEND_ASM_COUNT; ++i)
        {
            for (ch_idx = 0; ch_idx < ch_count; ++ch_idx)
            {
                send_item = &fs->send_item[ch_idx];
                msgId = send_item->msg_id;
                *(int *)pMsg = msgId;
                nLen = send_item->msg_max_len;
                ret = FC_NP_SendMsg(hDev, msgId, pMsg, nLen);
                if (ret)
                {
                    printf("send asm failed ret=0x%08x\n", ret);
                    break;
                }
                ch_iu_count[ch_idx]++;
                ch_bytes[ch_idx] += nLen;
            }
            if (ret) break;
        }
        for (ch_idx = 0; ch_idx < ch_count; ++ch_idx)
        {
            send_item = &fs->send_item[ch_idx];
            msgId = send_item->msg_id;
            total_iu_count += ch_iu_count[ch_idx];
            total_bytes += ch_bytes[ch_idx];
            /*printf("send msgId=0x%08x [iu_count=%u bytes=%u]\n", msgId, ch_iu_count[ch_idx], ch_bytes[ch_idx]);*/
        }
        /*printf("send sum[iu_count=%u bytes=%u]\n", total_iu_count, total_bytes);*/

        taskDelay(1);
    }
    free(pMsg);
    return ret;
}
FCUINT DemoRecvAsm()
{
    int ch_idx, ch_count, iu_len_max;
    unsigned int total_iu_count, total_bytes, ch_bytes[FC_CHANNEL_NUM_MAX], ch_iu_count[FC_CHANNEL_NUM_MAX];

    FCUINT ret, msgId, nLen;
    FCUCHAR *pMsg;
    /*TODO*/
    FC_SCHEME *fs;
    FC_MSG_RECV_ITEM *recv_item;
    FCHANDLE hDev;

    hDev = g_h_dev;
    if (g_dev_config_flag == 0)
    {
        return 0;
    }
    iu_len_max = 16 * 1024 * 1024;
    pMsg = (FCUCHAR *)malloc(iu_len_max);
    if (pMsg == NULL)
    {
        printf("malloc failed\n");
        return ret;
    }
    memset(pMsg, 0, iu_len_max);
    for (ch_idx = 0; ch_idx < FC_CHANNEL_NUM_MAX; ++ch_idx)
    {
        ch_iu_count[ch_idx] = 0;
        ch_bytes[ch_idx] = 0;
    }
    fs = &gBluePrint.config_block[g_config_block_no].scheme[g_scheme_no];
    ch_count = fs->port_config.stream_rxmsg_num + fs->port_config.block_rxmsg_num;
    do
    {
        for (ch_idx = 0; ch_idx < ch_count; ++ch_idx)
        {
            recv_item = &fs->recv_item[ch_idx];
            msgId = recv_item->msg_id;
            nLen = recv_item->msg_max_len;
            ret = FC_NP_RecvMsg(hDev, msgId, pMsg, &nLen);
            if (ret)
            {
                taskDelay(1);
                continue;
            }
            if (nLen == 0)
            {
                taskDelay(1);
                printf("nLen=0 ret=0x%08x\n", ret);
                continue;
            }
            ch_bytes[ch_idx] += nLen;
            ch_iu_count[ch_idx]++;
            printf("recv channel=%d iu=%d byte=%d\n", ch_idx, ch_iu_count[ch_idx], ch_bytes[ch_idx]);
        }
    } while (1);
    free(pMsg);

    total_iu_count = 0;
    total_bytes = 0;
    for (ch_idx = 0; ch_idx < ch_count; ++ch_idx)
    {
        recv_item = &fs->recv_item[ch_idx];
        msgId = recv_item->msg_id;

        total_iu_count += ch_iu_count[ch_idx];
        total_bytes += ch_bytes[ch_idx];
        printf("msgId=0x%08x [iu_count=%u bytes=%u]\n", msgId, ch_iu_count[ch_idx], ch_bytes[ch_idx]);
    }
    printf("sum[iu_count=%u bytes=%u]\n", total_iu_count, total_bytes);
    return 0;
}
#endif

void demo()
{
    FCUINT ret;
    int devCount = 0;

#if defined(__FH180_SYTLE_AUTO_TEST_DEMO__)
    /*查询设备*/
    ret = FC_NP_DevQuery(&devCount);
    if (ret)
    {
        printf("FC_NP_DevQuery failed ret=%d\n", ret);
        return;
    }
#endif    

    ret = DemoDevInit();
    if (ret)
        return;

    ret = CmdConfigDevHandler(g_h_dev);
    if (ret)
        return;

#if 0
    ret = DemoSendAsm(g_h_dev);
    if (ret) return;
    ret = DemoRecvAsm(g_h_dev);
    if (ret) return;
#endif
}

#if 0
void CmdNetManagerHandler(FCHANDLE hDev)
{
    FCUINT ret, nm_role, state;
    /*TODO*/
    FC_SCHEME *fs;

    if (g_dev_config_flag == 0)
    {
        return;
    }
    fs = &gBluePrint.config_block[g_config_block_no].scheme[g_scheme_no];
    nm_role = fs->port_config.nm_role;
    if (nm_role == FC_NET_ROLE_NCT)
    {
        printf("nm_role is NET_ROLE_NCT\n");
        /*设置WDT加载使能*/
        ret = FC_NM_SetWdtLoaderEnab(hDev, FC_WDT_LOADER_ENAB);
        if (ret)
        {
            printf("FC_NM_SetWdtLoaderEnab failed ret=0x%08x err=%d\n", ret, GetLastError());
            return;
        }
        g_wdt_loader_enab = 1;
    }
    else if (nm_role == FC_NET_ROLE_NRT)
    {
        /*查询NCT是否在线*/
        printf("nm_role is NET_ROLE_NRT\n");
        printf("NCT is online?");
        while (TRUE)
        {
            ret = FC_NM_NctIsOnLine(hDev, &state);
            if (ret)
            {
                printf("FC_NM_NctIsOnLine failed ret=%d err=%d\n", ret, GetLastError());
                return;
            }
            if (state == 1) break;
            Sleep(1000);
        }
        printf("ok\n");
        ret = FC_NM_OnLineRequest(hDev);
        if (ret)
        {
            printf("FC_NM_OnLineRequest failed ret=0x%08x\n", ret);
            return;
        }
        assert(ret == 0);
        g_online_flag = 1;
    }
    else if (nm_role == FC_NET_ROLE_BNCT)
    {
    }
    else
    {
        printf("nm_role=%d invalid\n", nm_role);
    }
    return;
}
void CmdRecvAsmHandler(FCHANDLE hDev)
{
    DWORD t_id, reason;

    if (g_recv_handle == INVALID_HANDLE_VALUE)
    {
        g_recv_handle = (HANDLE)_beginthreadex(NULL, 0, RecvCallBack, hDev, 0, &t_id);
        if (g_recv_handle == INVALID_HANDLE_VALUE)
        {
            printf("_beginthreadex failed err=%d\n", GetLastError());
            return;
        }
    }
    else
    {
        g_recv_stop_flag = 1;
        reason = WaitForSingleObject(g_recv_handle, INFINITE);
        if (reason == WAIT_OBJECT_0)
        {
            g_recv_handle = INVALID_HANDLE_VALUE;
            g_recv_stop_flag = 0;
        }
        else
        {
            printf("WaitForSingleObject failed reason=0x%08x\n", reason);
        }
    }
}
void CmdSendAsmHandler(FCHANDLE hDev)
{
    DWORD t_id, reason;

    if (g_send_handle == INVALID_HANDLE_VALUE)
    {
        g_send_handle = (HANDLE)_beginthreadex(NULL, 0, SendCallBack, hDev, 0, &t_id);
        if (g_send_handle == INVALID_HANDLE_VALUE)
        {
            printf("_beginthreadex failed err=%d\n", GetLastError());
            return;
        }
    }
    else
    {
        g_send_stop_flag = 1;
        reason = WaitForSingleObject(g_send_handle, INFINITE);
        if (reason == WAIT_OBJECT_0)
        {
            g_send_handle = INVALID_HANDLE_VALUE;
            g_send_stop_flag = 0;
        }
        else
        {
            printf("WaitForSingleObject failed reason=0x%08x\n", reason);
        }
    }
}
void CmdPortStateHandler(FCHANDLE hDev)
{
    FCUINT ret, status;

    ret = FC_NP_GetPortStatus(hDev, &status);
    if (ret)
    {
        printf("FC_NP_GetPortStatus failed ret=%d err=%d\n", ret, GetLastError());
        return;
    }
    if (status == FC_PORT_LINK_DOWN)
    {
        printf("port status LINK_DOWN\n");
    }
    else
    {
        printf("port status LINK_UP\n");
    }
}
void CmdStatisticsHandler(FCHANDLE hDev)
{
    int i;
    FCUINT ret;
    FC_PORT_STATISTICS_INFO psi[2];
    FC_STATISTICS_INFO si;

    /*取得端口统计信息*/
    ret = FC_NP_GetPortStatisticsInfo(hDev, psi);
    if (ret)
    {
        printf("FC_NP_GetPortStatisticsInfo failed ret=%d err=%d\n", ret, GetLastError());
        return;
    }
    for (i = 0; i < 2; ++i)
    {
        printf("port[%d]RxUndersizeFrameCnt=%I64d\n", i, psi[i].RxOversizeFrameErrCnt);
        printf("port[%d]RxAllFrameCnt=%I64d\n", i, psi[i].RxAllFrameCnt);
        printf("port[%d]RxValidFrameCnt=%I64d\n", i, psi[i].RxValidFrameCnt);
        printf("port[%d]RxWordCnt=%I64d\n", i, psi[i].RxWordCnt);
        printf("port[%d]RxRRDYCnt=%I64d\n", i, psi[i].RxRRDYCnt);
        printf("port[%d]RxKErrCnt=%I64d\n", i, psi[i].RxKErrCnt);
        printf("port[%d]LinkChgUp2DownCnt=%I64d\n", i, psi[i].LinkChgUp2DownCnt);
        printf("port[%d]TxAllFrameCnt=%I64d\n", i, psi[i].TxAllFrameCnt);
        printf("port[%d]TxValidFrameCnt=%I64d\n", i, psi[i].TxValidFrameCnt);
        printf("port[%d]TxWordCnt=%I64d\n", i, psi[i].TxWordCnt);
        printf("port[%d]TxRRDYCnt=%I64d\n", i, psi[i].TxRRDYCnt);
        printf("port[%d]TxKErrCnt=%I64d\n", i, psi[i].TxKErrCnt);
    }
    /*取得软件统计信息*/
    ret = FC_NP_GetStatisticsInfo(hDev, &si);
    if (ret)
    {
        printf("FC_NP_GetStatisticsInfo failed ret=%d err=%d\n", ret, GetLastError());
        return;
    }
    printf("TxByteCnt=%I64d\n", si.TxByteCnt);
    printf("TxIuCnt=%I64d\n", si.TxIuCnt);
    printf("RxByteCnt=%I64d\n", si.RxByteCnt);
    printf("RxIuCnt=%I64d\n", si.RxIuCnt);
    printf("RxDiscardByteCnt=%I64d\n", si.RxDiscardByteCnt);
    printf("RxDiscardIuCnt=%I64d\n", si.RxDiscardIuCnt);
    printf("RxSeqErrCnt=%I64d\n", si.RxSeqErrCnt);
    printf("RxOxidErrCnt=%I64d\n", si.RxOxidErrCnt);
    printf("RxFrameErrCnt=%I64d\n", si.RxFrameErrCnt);
}
void CmdSetRtc(FCHANDLE hDev)
{
#if 0
    FCUINT ret;
    FC_RTC rtc;
    SYSTEMTIME st;

    GetSystemTime(&st);
    rtc.date.u.year = st.wYear;
    rtc.date.u.month = st.wMonth;
    rtc.date.u.day = st.wDay;
    rtc.hour = st.wHour;
    rtc.minute = st.wMinute;
    rtc.second = st.wSecond;
    rtc.millisecond = st.wMilliseconds;
    rtc.microsecond = 1;
    rtc.nanosecond = 1;
    ret = FC_TM_SetRtc(hDev, &rtc);
    if (ret)
    {
        printf("FC_TM_SetRtc failed ret=%d err=%d\n", ret, GetLastError());
        return;
    }
    printf("set RTC success\n");
    printf("Date[year=%d month=%d day=%d]\n", rtc.date.u.year, rtc.date.u.month, rtc.date.u.day);
    printf("Time[hour=%d minute=%d second=%d millisecond=%d microsecond=%d nanosecond=%d]\n",
        rtc.hour, rtc.minute, rtc.second, rtc.millisecond, rtc.microsecond, rtc.nanosecond);
#endif
}
void CmdGetRtc(FCHANDLE hDev)
{
#if 0
    FCUINT ret;
    FC_RTC rtc;

    ret = FC_TM_GetRtc(hDev, &rtc);
    if (ret)
    {
        printf("FC_TM_GetRtc failed ret=%d err=%d\n", ret, GetLastError());
        return;
    }
    printf("get RTC success\n");
    printf("Date[year=%d month=%d day=%d]\n", rtc.date.u.year, rtc.date.u.month, rtc.date.u.day);
    printf("Time[hour=%d minute=%d second=%d millisecond=%d microsecond=%d nanosecond=%d]\n",
        rtc.hour, rtc.minute, rtc.second, rtc.millisecond, rtc.microsecond, rtc.nanosecond);
#endif
}
void CmdSetSyncEnab(FCHANDLE hDev, int enab)
{
    FCUINT ret;

    ret = FC_TM_SetSyncEnab(hDev, enab);
    if (ret)
    {
        printf("FC_TM_SetSyncEnab failed ret=%d err=%d\n", ret, GetLastError());
        return;
    }
}
void CmdExitHandler(FCHANDLE hDev)
{
    FCUINT ret, nm_role, state;
    /*TODO*/
    FC_SCHEME *fs;
    UINT32 reason;

    if (g_dev_config_flag != 1)
    {
        return;
    }
    fs = &gBluePrint.config_block[g_config_block_no].scheme[g_scheme_no];
    nm_role = fs->port_config.nm_role;
    if (g_send_handle != INVALID_HANDLE_VALUE)
    {
        g_send_stop_flag = 1;
        reason = WaitForSingleObject(g_send_handle, INFINITE);
        if (reason != WAIT_OBJECT_0)
        {
            printf("WaitForSingleObject failed reason=0x%08x\n", reason);
            return;
        }
        g_send_stop_flag = 0;
    }
    if (g_recv_handle != INVALID_HANDLE_VALUE)
    {
        g_recv_stop_flag = 1;
        reason = WaitForSingleObject(g_recv_handle, INFINITE);
        if (reason != WAIT_OBJECT_0)
        {
            printf("WaitForSingleObject failed reason=0x%08x\n", reason);
            return;
        }
        g_recv_stop_flag = 0;
    }
    if (nm_role == FC_NET_ROLE_NCT)
    {
        ret = FC_NM_SetWdtLoaderEnab(hDev, FC_WDT_LOADER_DISABLE);
        if (ret)
        {
            printf("FC_NM_SetWdtLoaderEnab failed ret=0x%08x err=%d\n", ret, GetLastError());
            return;
        }
        g_wdt_loader_enab = 0;
    }
    else if (nm_role == FC_NET_ROLE_NRT)
    {
        ret = FC_NM_NctIsOnLine(hDev, &state);
        if (ret)
        {
            printf("FC_NM_NctIsOnLine failed ret=%d err=%d\n", ret, GetLastError());
            return;
        }
        if (state == 1)
        {
            ret = FC_NM_OffLineRequest(hDev);
            if (ret)
            {
                printf("FC_NM_OffLineRequest failed ret=0x%08x err=%d\n", ret, GetLastError());
                return;
            }
        }
        g_online_flag = 0;
    }
    else if (nm_role == FC_NET_ROLE_BNCT)
    {
    }
    if (g_dev_config_flag == 1)
    {
        ret = FC_NP_DevReset(hDev, 1);
        if (ret)
        {
            printf("FC_NP_Reset failed ret=%d err=%d\n", ret, GetLastError());
            return;
        }
        g_dev_config_flag = 0;
    }
    printf("exit success\n");
}
unsigned int CALLBACK SendCallBack(void *context)
{
    UINT ret;
    INT32 i, ch_idx, ch_count, ch_iu_count[FC_CHANNEL_NUM_MAX];
    LONGLONG total_bytes, ch_bytes[FC_CHANNEL_NUM_MAX], total_iu_count;
    FCHANDLE hDev;
    FCUINT t_ret, msgId, nLen;
    FCUCHAR *pMsg;
    /*TODO*/
    FC_SCHEME *fs;
    FC_MSG_SEND_ITEM *send_item;

    hDev = (FCHANDLE)context;
    ret = 0;

    if (g_dev_config_flag == 0)
    {
        return 0;
    }
    pMsg = (FCUCHAR *)malloc(16 * 1024 * 1024);
    if (pMsg == NULL)
    {
        printf("malloc failed err=%d\n", GetLastError());
        return ret;
    }
    memset(pMsg, 0, 16 * 1024 * 1024);
    for (ch_idx = 0; ch_idx < FC_CHANNEL_NUM_MAX; ++ch_idx)
    {
        ch_iu_count[ch_idx] = 0;
        ch_bytes[ch_idx] = 0;
    }
    fs = &gBluePrint.config_block[g_config_block_no].scheme[g_scheme_no];
    ch_count = fs->port_config.stream_txmsg_num + fs->port_config.block_txmsg_num;
    for (i = 0; i < SEND_COUNT && g_send_stop_flag == 0; ++i)
    {
        for (ch_idx = 0; ch_idx < ch_count && g_send_stop_flag == 0; ++ch_idx)
        {
            send_item = &fs->send_item[ch_idx];
            msgId = send_item->msg_id;
            *(int *)pMsg = msgId;
            while (g_send_stop_flag == 0)
            {
                nLen = send_item->msg_max_len;
                t_ret = FC_NP_SendMsg(hDev, msgId, pMsg, nLen);
                if (t_ret)
                {
                    /*Sleep(50);*/
                    continue;
                }
                ch_iu_count[ch_idx]++;
                ch_bytes[ch_idx] += nLen;
                break;
            }
        }
    }
    free(pMsg);

    total_iu_count = 0;
    total_bytes = 0;
    printf("send complete send count=%d\n", SEND_COUNT);
    for (ch_idx = 0; ch_idx < ch_count; ++ch_idx)
    {
        send_item = &fs->send_item[ch_idx];
        msgId = send_item->msg_id;
        total_iu_count += ch_iu_count[ch_idx];
        total_bytes += ch_bytes[ch_idx];
        printf("msgId=0x%08x [iu_count=%d bytes=%I64d]\n", msgId, ch_iu_count[ch_idx], ch_bytes[ch_idx]);
    }
    printf("sum[iu_count=%I64d bytes=%I64d]\n", total_iu_count, total_bytes);
    g_send_handle = INVALID_HANDLE_VALUE;
    g_send_stop_flag = 0;
    return ret;
}
#endif

/* ------------------- 产测部分 --------------------------------*/
unsigned int CmdConfigDevHandler(FCHANDLE hDev)
{
    FCUINT ret;

    g_reg_evt_flag = 0;
    g_dev_config_flag = 0;
    do
    {
        /*注册事件回调*/
        ret = FC_NP_RegEvtHandler(hDev, EventCallback);
        if (ret)
        {
            printf("FC_NP_RegEvtHandler failed ret=0x%08x\n", ret);
            break;
        }
        g_reg_evt_flag = 1;

#if 1/*__FH130_AUTO_TEST_DEMO__*/
        ret = demoCheckBluePrintAndLoadConfig(hDev, g_config_block_no, g_scheme_no);
        if (ret != FC_SUCCESS)
        {
            printf("demoCheckBluePrintAndLoadConfig failed ret=0x%08x\n", ret);
            break;
        }
        g_dev_config_flag = 1;
#else
        /*设置模式*/
        ret = FC_NP_SetBluePrint(hDev, &gBluePrint);
        if (ret)
        {
            printf("FC_NP_SetBluePrint failed ret=0x%08x\n", ret);
            break;
        }
        /*配置设备*/
        {
            UINT32 tick;
            tick = tickGet();

            ret = FC_NP_LoadConfig(hDev, g_config_block_no, g_scheme_no);
            if (ret)
            {
                printf("FC_NP_LoadConfig failed ret=0x%08x\n", ret);
                break;
            }
            printf("tick=%d\n", (tickGet() - tick));
        }
#endif        
        /*TODO：仅为测试用设置e_d_tov值为2000*/
        HwSetEdtov(((HBA_DEV_CB *)hDev)->pMembaseCsr, 2000);
        /*HwSetRxDiscardTimeout(((HBA_DEV_CB *)hDev)->reg, 4);*//*jin.liu 20180316 add for discard_time*/
        printf("CmdConfigDevHandler success\n");
    } while (FALSE);

    if (ret)
    {
        if (g_reg_evt_flag == 1)
        {
            ret = FC_NP_UnRegEvtHandler(hDev);
            if (ret)
            {
                printf("FC_NP_UnRegEvtHandler failed ret=0x%08x\n", ret);
                return FC_FAILURE;
            }
        }
    }

    return FC_SUCCESS;
}

int g_wdt_loader_enab = 0;
int g_online_flag = 0;
int g_stop_response = 0;

#if defined(__FH180_SYTLE_AUTO_TEST_DEMO__)
void FH180Style_CmdNetManagerHandler(FCHANDLE hDev)
{
    FCUINT ret, nm_role, state;
    /*TODO*/
    FC_SCHEME *fs;

    fs = &gBluePrint.config_block[g_config_block_no].scheme[g_scheme_no];

    nm_role = fs->port_config.nm_role;
    if (nm_role == FC_NET_ROLE_NCT)
    {
        printf("nm_role is NET_ROLE_NCT\n");
        /*设置WDT加载使能*/
        ret = FC_NM_SetWdtPeriodEnab(hDev, FC_WDT_PERIOD_ENAB);
        if (ret)
        {
            printf("FC_NM_SetWdtLoaderEnab failed ret=0x%08x\n", ret);
            return;
        }
        g_wdt_loader_enab = 1;
    }
    else if (nm_role == FC_NET_ROLE_NRT)
    {
        /*查询NCT是否在线*/
        printf("nm_role is NET_ROLE_NRT\n");

        do
        {
            printf("NCT is online?\n");
            while (TRUE)
            {
                ret = FC_NM_NctIsOnLine(hDev, &state);
                if (ret != FC_SUCCESS)
                {
                    printf("FC_NM_NctIsOnLine failed ret=%d\n", ret);
                    printf("state=%d\n", state);
                    return;
                }
                if (state == 1)
                    break;

                printf(".");
                taskDelay(sysClkRateGet());
            }
            printf("ok\n");

            state = 0;
            ret = FC_NM_GetNodeState(hDev, 0, &state);
            if (ret)
            {
                printf("FC_NM_GetNodeState failed ret=%d\n", ret);
                return;
            }
            printf("FC_NM_GetNodeState success node state=%d\n", state);

            ret = FC_NM_OnLineRequest(hDev);
            if (ret != FC_SUCCESS)
            {
                printf("FC_NM_OnLineRequest failed ret=0x%08x\n", ret);
                /*return; */
            }
            taskDelay(sysClkRateGet());

            if (state == 1) 
                    {
                        break;
                    }
        } while (ret);


        g_online_flag = 1;
    }
    else if (nm_role == FC_NET_ROLE_BNCT)
    {
    }
    else
    {
        printf("nm_role=%d invalid\n", nm_role);
    }
    return;
}


UINT FH180Style_ResponseCallBack(int context)
{
    UINT ret;
    INT32 result, ch_idx, ch_count, iu_length_max, ch_iu_count[FC_CHANNEL_NUM_MAX], ch_err_count[FC_CHANNEL_NUM_MAX], ch_zero_count[FC_CHANNEL_NUM_MAX];
    UINT64 total_iu_count, total_bytes, ch_bytes[FC_CHANNEL_NUM_MAX], total_err_count, total_zero_count;
    FCUINT t_ret, msgId, send_len, recv_len;
    FCHANDLE hDev;
    FCUCHAR *pMsgSend, *pMsgRecv;
    RESPONSE_NODE *resp_item;
    /*TODO*/
    FC_SCHEME *fs;
    FC_MSG_RECV_ITEM *recv_item;

    hDev = (FCHANDLE)context;
    ret = 0;

    ch_count = FC_CHANNEL_NUM_MAX;
    iu_length_max = DEMO_MAX_IU_LENGTH + 4096;

    fs = &gBluePrint.config_block[g_config_block_no].scheme[g_scheme_no];
    /* ch_count = fs->port_config.stream_rxmsg_num + fs->port_config.block_rxmsg_num; */

    pMsgRecv = (FCUCHAR *)malloc(iu_length_max);
    if (pMsgRecv == NULL)
    {
        printf("malloc %d byte failed err=%d recv\n", iu_length_max);
        return ret;
    }

#if 0
    resp_item = (RESPONSE_NODE *)malloc(sizeof(RESPONSE_NODE));
    if (resp_item == NULL)
    {
        free(pMsgRecv);
        printf("malloc %d byte failed err=%d recv\n", resp_item);
        return ret;
    }

    memset(resp_item, 0, sizeof(RESPONSE_NODE));
#endif

    for (ch_idx = 0; ch_idx < FC_CHANNEL_NUM_MAX; ++ch_idx)
    {
        ch_iu_count[ch_idx] = 0;
        ch_bytes[ch_idx] = 0;
        ch_err_count[ch_idx] = 0;
        ch_zero_count[ch_idx] = 0;
    }

    ch_idx = -1;
    while (TRUE)
    {
        /* 轮循收包 */
        int loopCount = 0;

        while (TRUE)
        {
            if (g_stop_response)
            {
                break;
            }

            ch_idx = (ch_idx + 1) % ch_count;
            recv_item = &fs->recv_item[ch_idx];
            msgId = recv_item->msg_id;
            recv_len = recv_item->msg_max_len;

            t_ret = FC_NP_RecvMsg(hDev, msgId, pMsgRecv, &recv_len);
            if (t_ret != FC_SUCCESS)
            {
                if (t_ret == FC_BUF_TOO_SMALL)
                    printf("FC_NP_RecvMsg : FC_EA_RECV_BUF_TOO_SMALL\n");

                ch_err_count[ch_idx]++;
                continue;
            }
            if (recv_len == 0)
            {
                ch_zero_count[ch_idx]++;

                /* 连续收512次后如果都没收到包，则休息一个tick */
                loopCount++;
                if (loopCount >= 512)
                {
                    loopCount = 0;
                    /* taskDelay(1); */
                }

                continue;
            }

            /* 收到数据，跳出接收 */
            ch_bytes[ch_idx] += recv_len;
            ch_iu_count[ch_idx]++;

            break;
        }


        if (g_stop_response)
        {
            printf("recv package failed g_stop_response=%d\n", g_stop_response);
            break;
        }

        /* 已经收到包 */
        /*printf("recv package msgId=%d recv_len=%d\n", msgId, recv_len);*/
        result = GetResponseNodeById(msgId, &resp_item);
        if (result)
        {
            printf("GetResponseNodeById failed\n");
            break;
        }

        pMsgSend = resp_item->payload;
        send_len = resp_item->length;
        /*printf("GetResponseNodeById msgId=%d send_len=%d\n", msgId, send_len);*/
        do
        {
            if (g_stop_response)
            {
                break;
            }

            t_ret = FC_NP_SendMsg(hDev, msgId, pMsgSend, send_len);
            if (t_ret)
            {
                continue;
            }
            break;

        } while (TRUE);

        if (g_stop_response)
        {
            break;
        }

    }
    free(pMsgRecv);

    g_stop_response = 0;

    total_iu_count = 0;
    total_bytes = 0;
    total_err_count = 0;
    total_zero_count = 0;
    total_bytes = 0;
    for (ch_idx = 0; ch_idx < ch_count; ++ch_idx)
    {
        recv_item = &fs->recv_item[ch_idx];
        msgId = recv_item->msg_id;

        total_iu_count += ch_iu_count[ch_idx];
        total_bytes += ch_bytes[ch_idx];
        total_zero_count += ch_zero_count[ch_idx];
        total_err_count += ch_err_count[ch_idx];
        printf("msgId=0x%08x channel: iu_count=%d, bytes=%llu, err_count=%d, zero_count=%d\n", msgId, ch_iu_count[ch_idx], ch_bytes[ch_idx], ch_err_count[ch_idx], ch_zero_count[ch_idx]);
    }
    printf("--- sum : iu_count=%llu, bytes=%llu, err_count=%llu, zero_count=%llu\n", total_iu_count, total_bytes, total_err_count, total_zero_count);

    return ret;
}




/*FH180 自检*/
void FH180Style_demoTestPBit(FCHANDLE hDev)
{
    FCUINT ret, fcid;
    FC_PBIT_RESULT b;
    /*TODO*/
    FC_SCHEME *fs;

    /*获取节点上电自检信息*/
    fs = &gBluePrint.config_block[g_config_block_no].scheme[g_scheme_no];
    fcid = fs->port_config.port_id;
    ret = FC_NM_GetPBitResult(hDev, fcid, &b);
    if (ret)
    {
        printf("FC_NM_GetPBitResult failed ret=%d\n", ret);
        return;
    }
    printf("PowerBit[temperature=%d voltage=%d flash=%d reg=%d els_loop=%d asm_loop=%d]\n",
        b.temperature, b.voltage, b.flash, b.reg, b.els_loop, b.asm_loop);
}

#elif defined(__FH130_SYTLE_AUTO_TEST_DEMO__)

void FH130Style_CmdNetManagerHandler(FCHANDLE hDev)
{
    FCUINT ret, nm_role, state, onNetState = 0;
    /*TODO*/
    FC_PORT_CONFIG *pPortCfg = NULL;

    pPortCfg = &gBluePrint[g_config_block_no].config_block[g_scheme_no].port_config;
        
    nm_role = pPortCfg->role;
    if (nm_role == FC_NET_ROLE_NCT)
    {
        printf("nm_role is NET_ROLE_NCT\n");
        /*设置WDT加载使能*/
        ret = FC_NM_WDTEnable(hDev, FC_WDT_NET_MODE);
        if (ret != FC_SUCCESS)
        {
            printf("FC_NM_WDTEnable failed ret=0x%08x\n", ret);
            return;
        }
        g_wdt_loader_enab = 1;
    }
    else if (nm_role == FC_NET_ROLE_NRT)
    {
        /*查询NCT是否在线*/
        printf("nm_role is NET_ROLE_NRT\n");

        do
        {
            printf("NCT is online?\n");
            while (TRUE)
            {
                ret = FC_NM_NRT_NcIsOnNet(hDev, &state);
                if (ret != FC_SUCCESS)
                {
                    printf("FC_NM_NRT_NcIsOnNet failed ret=%d\n", ret);
                    printf("state=%d\n", state);
                    return;
                }
                
                if (state == 1)
                {
                    break;
                }

                printf(".");
                taskDelay(sysClkRateGet());
            }
            printf("ok\n");

            state = 0;
            ret = FC_NP_GetState(hDev, &state);
            if (ret != FC_SUCCESS)
            {
                printf("FC_NP_GetState failed ret=%d\n", ret);
                return;
            }
            printf("FC_NP_GetState success node state=%d\n", state);
            /*链路状态为link down*/
            if (state == 0) 
            {
                continue;
            }

            ret = FC_NM_NRT_OnNetReq(hDev);
            if (ret != FC_SUCCESS)
            {
                printf("FC_NM_NRT_OnNetReq failed ret=0x%08x\n", ret);
            }
            taskDelay(sysClkRateGet());

            ret = FC_NM_GetOnNetState(hDev, &onNetState);
            if (ret != FC_SUCCESS)
            {
                printf("FC_NM_GetOnNetState failed ret=0x%08x\n", ret);
            }

        } while (onNetState != 1);

        g_online_flag = 1;
    }
    else if (nm_role == FC_NET_ROLE_BNCT)
    {
    }
    else
    {
        printf("nm_role=%d invalid\n", nm_role);
    }
    return;
}


UINT FH130Style_ResponseCallBack(int context)
{
    UINT ret = 0;
    INT32 result, ch_idx, ch_count, iuLengthMax, ch_iu_count[FC_CHANNEL_NUM_MAX], ch_err_count[FC_CHANNEL_NUM_MAX], ch_zero_count[FC_CHANNEL_NUM_MAX];
    UINT64 total_iu_count, total_bytes, ch_bytes[FC_CHANNEL_NUM_MAX], total_err_count, total_zero_count;
    FCUINT t_ret, msgId, send_len, recv_len;
    FCHANDLE hDev;
    FCUCHAR *pMsgSend, *pMsgRecv;
    CONFIG_BLOCK *pConfigBlock = NULL;
    FC_MSG_RECV_ITEM *pRecvItem = NULL;
    RESPONSE_NODE *pRespItem = NULL;

    /*TODO*/

    hDev = (FCHANDLE)context;

    ch_count = FC_CHANNEL_NUM_MAX;
    iuLengthMax = DEMO_MAX_IU_LENGTH + 4096;

    pConfigBlock = &gBluePrint[g_config_block_no].config_block[g_scheme_no];
    /* ch_count = fs->port_config.stream_rxmsg_num + fs->port_config.block_rxmsg_num; */

    pMsgRecv = (FCUCHAR *)malloc(iuLengthMax);
    if (pMsgRecv == NULL)
    {
        printf("malloc %d byte failed err=%d recv\n", iuLengthMax);
        return ret;
    }

    for (ch_idx = 0; ch_idx < FC_CHANNEL_NUM_MAX; ++ch_idx)
    {
        ch_iu_count[ch_idx] = 0;
        ch_bytes[ch_idx] = 0;
        ch_err_count[ch_idx] = 0;
        ch_zero_count[ch_idx] = 0;
    }

    ch_idx = -1;
    while (TRUE)
    {
        /* 轮循收包 */
        int loopCount = 0;

        while (TRUE)
        {
            if (g_stop_response)
            {
                break;
            }

            ch_idx = (ch_idx + 1) % ch_count;
            pRecvItem = &pConfigBlock->recv_item[ch_idx];
            msgId = pRecvItem->msg_id;
            recv_len = pRecvItem->msg_max_len;

            t_ret = FC_NP_RecvMsg(hDev, msgId, pMsgRecv, &recv_len);
            if (t_ret != FC_SUCCESS)
            {
                if (t_ret == FC_RECV_LENGTH_TOO_SMALL)
                {
                    printf("FC_NP_RecvMsg : FC_RECV_LENGTH_TOO_SMALL\n");
                }

                ch_err_count[ch_idx]++;
                continue;
            }
            
            if (recv_len == 0)
            {
                ch_zero_count[ch_idx]++;

                /* 连续收512次后如果都没收到包，则休息一个tick */
                loopCount++;
                if (loopCount >= 512)
                {
                    loopCount = 0;
                    /* taskDelay(1); */
                }

                continue;
            }

            /* 收到数据，跳出接收 */
            ch_bytes[ch_idx] += recv_len;
            ch_iu_count[ch_idx]++;

            break;
        }


        if (g_stop_response)
        {
            printf("recv package failed g_stop_response=%d\n", g_stop_response);
            break;
        }

        /* 已经收到包 */
        /*printf("recv package msgId=%d recv_len=%d\n", msgId, recv_len);*/
        result = GetResponseNodeById(msgId, &pRespItem);
        if (result)
        {
            printf("GetResponseNodeById failed\n");
            break;
        }

        pMsgSend = pRespItem->payload;
        send_len = pRespItem->length;
        /*printf("GetResponseNodeById msgId=%d send_len=%d\n", msgId, send_len);*/
        do
        {
            if (g_stop_response)
            {
                break;
            }

            t_ret = FC_NP_SendMsg(hDev, msgId, pMsgSend, send_len);
            if (t_ret)
            {
                continue;
            }
            break;

        } while (TRUE);

        if (g_stop_response)
        {
            break;
        }

    }
    free(pMsgRecv);

    g_stop_response = 0;

    total_iu_count = 0;
    total_bytes = 0;
    total_err_count = 0;
    total_zero_count = 0;
    total_bytes = 0;
    for (ch_idx = 0; ch_idx < ch_count; ++ch_idx)
    {
        pRecvItem = &pConfigBlock->recv_item[ch_idx];
        msgId = pRecvItem->msg_id;

        total_iu_count += ch_iu_count[ch_idx];
        total_bytes += ch_bytes[ch_idx];
        total_zero_count += ch_zero_count[ch_idx];
        total_err_count += ch_err_count[ch_idx];
        
        printf("msgId=0x%08x channel: iu_count=%d, bytes=%llu, err_count=%d, zero_count=%d\n", msgId, ch_iu_count[ch_idx], ch_bytes[ch_idx], ch_err_count[ch_idx], ch_zero_count[ch_idx]);
    }
    
    printf("--- sum : iu_count=%llu, bytes=%llu, err_count=%llu, zero_count=%llu\n", total_iu_count, total_bytes, total_err_count, total_zero_count);

    return ret;
}


/*FH130 自检*/
void FH130Style_demoTestPBit(FCHANDLE hDev)
{
    FCUINT ret = FC_FAILURE;
    FC_BIT_RESULT_POWER b;
    
    ret = FC_NP_GetPuBitResult(hDev, &b);
    if (ret != FC_SUCCESS)
    {
        printf("FC_NP_GetPuBitResult failed ret=%d\n", ret);
        return;
    }

    printf("PowerBit[memory=%d reg=%d temperature=%d voltage=%d flash=%d ]\n",
        b.memory, b.reg, b.temperature, b.voltage, b.flash);

    return;
}


#endif

void CmdNetManagerHandler(FCHANDLE hDev)
{
#if defined(__FH130_SYTLE_AUTO_TEST_DEMO__)
    FH130Style_CmdNetManagerHandler(hDev);
#elif defined(__FH180_SYTLE_AUTO_TEST_DEMO__)
    FH180Style_CmdNetManagerHandler(hDev);
#endif

}

/* recv & response */
int TestResponse(FCHANDLE hDev)
{
    FCUINT t_id;
    int testTaskId = ERROR;

    g_stop_response = 0;

    if (InitResponseTable() == -1)
    {
        printf("InitResponseTable() failed. \n");
        return FC_FAILURE;
    }

    testTaskId = taskSpawn("tRspTask", 100, 0, 409600, (FUNCPTR)ResponseCallBack,
        (int)hDev, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (testTaskId == ERROR)
    {
        printf("taskSpawn ResponseCallBack error, ret=%d!\n", testTaskId);
        return FC_FAILURE;
    }
    printf("taskSpawn ResponseCallBack success \n");

    return FC_SUCCESS;
}


int demoNetRole = FC_NET_ROLE_NRT;
int demoTest()
{
    FCUINT ret;
    FCHANDLE hDev = NULL;
    int devCount = 0;

    /*调整时钟频率为1000次/秒*/
    sysClkRateSet(1000);

    ret = demoSetConfigSchemeIndex();
    if (ret != FC_SUCCESS)
    {
        printf("demoSetConfigSchemeIndex failed ret=%d\n", ret);
        return ret;
    }

#if 1/*__FH130_AUTO_TEST_DEMO__*/
    /*搜寻并打开设备,兼容不同项目*/
    ret = demoTestDeviceQueryAndOpen(&hDev, 0);
    if (ret != FC_SUCCESS)
    {
        printf("demoTestDeviceQueryAndOpen failed ret=%d\n", ret);
        return ret;
    }
#else
    /*查询设备*/
    ret = FC_NP_DevQuery(&devCount);
    if (ret)
    {
        printf("FC_NP_DevQuery failed ret=%d\n", ret);
        return ret;
    }

    if (devCount == 0)
    {
        printf("FC_NP_DevQuery : no device found\n");
        return ret;
    }

    ret = FC_NP_DevOpen(&hDev, 0);
    if (ret)
    {
        printf("FC_NP_DevOpen failed ret=%d\n", ret);
        return ret;
    }
#endif  /*__FH130_AUTO_TEST_DEMO__*/

#if 0
    ret = DemoDevConfig(hDev);
    if (ret)
    {
        return ret;
    }
#endif    
    ret = CmdConfigDevHandler(hDev);
    if(ret != FC_SUCCESS)
    {
        printf("CmdConfigDevHandler Failed!\n");
        return ret;
    }

#if 1/*__FH130_AUTO_TEST_DEMO__*/
    demoTestPBit(hDev);
#endif

    CmdNetManagerHandler(hDev);
    TestResponse(hDev);

}

UINT32 g_reg_base = 0x64100000;

/*没有角色的情况下，发送接收时钟原语*/
void TestSyncControl(UINT32 period, UINT32 recv_sync, UINT32 send_sync)
{
    UINT32 reg_RTC_CONTROL, v;

    reg_RTC_CONTROL = g_reg_base + 0x14;
    v = sysPciInLong(reg_RTC_CONTROL);
    printf("read  v=0x%08x\n", v);
    v = (v & 0xFFFF0000) | ((period - 1) & 0x0000FFFF);
    v = (v & 0xFFFEFFFF) | ((send_sync << 16) & 0x00010000);
    v = (v & 0xFFFDFFFF) | ((send_sync << 17) & 0x00020000);
    v = (v & 0xFFF7FFFF) | ((recv_sync << 19) & 0x00080000);
    printf("write v=0x%08x\n", v);
    sysPciOutLong(reg_RTC_CONTROL, v);
}

#if 0
/*测试强制下网*/
/*FH130只发送强制下网请求,不等待回复，FH180等待回复.*/
void TestForceOffLine(FCHANDLE hDev, FCUINT fcid)
{
    FCUINT ret;

    /*强制指定节点下线*/
    ret = FC_NM_ForceOffLine(hDev, fcid);
    if (ret)
    {
        printf("FC_NM_ForceOffLine failed ret=%d\n", ret);
        return;
    }
    printf("FC_NM_ForceOffLine success\n");
}

/*测试发送下网请求*/
void TestOffline(FCHANDLE hDev)
{
    FCUINT ret;

    /*下网请求*/
    ret = FC_NM_OffLineRequest(hDev);
    if (ret)
    {
        /*printf("FC_NM_OffLineRequest failed ret=%d\n", ret);*/
    }
    /*printf("FC_NM_OffLineRequest success\n");*/
}
#endif

#if 1/*__FH130_AUTO_TEST_DEMO__*/
unsigned int demoSetConfigSchemeIndex(void)
{

    if (demoNetRole == FC_NET_ROLE_NCT)
    {
        g_config_block_no = 0;
        g_scheme_no = 0;    
    }
    else if (demoNetRole == FC_NET_ROLE_BNCT)
    {
        g_config_block_no = 0;
        g_scheme_no = 1;
    }
    else if (demoNetRole == FC_NET_ROLE_NRT)
    {
        g_config_block_no = 0;
        g_scheme_no = 2;    
    }
    else
    {
        printf("net role=%d invalid\n", demoNetRole);
        return FC_FAILURE;
    }

    return FC_SUCCESS;
}

/*搜寻并打开对应设备*/
unsigned int demoTestDeviceQueryAndOpen(FCHANDLE *hDev, FCUINT DevId)
{
    unsigned int ret = FC_FAILURE;
    unsigned int devCount = 0;

#if defined(__FH130_SYTLE_AUTO_TEST_DEMO__)

    /*FH130 类型的项目没有Query操作*/
    ret = FC_NP_Open(hDev, DevId);
    if (ret != FC_SUCCESS)
    {
        printf("FC_NP_Open failed ret=%d\n", ret);
        return ret;
    }
#elif defined(__FH180_SYTLE_AUTO_TEST_DEMO__)

    /*查询设备*/
    g_dev_count = 0;
    ret = FC_NP_DevQuery(&devCount);
    if (ret != FC_SUCCESS)
    {
        printf("FC_NP_DevQuery failed ret=%d\n", ret);
        return ret;
    }

    if (devCount == 0)
    {
        printf("FC_NP_DevQuery : no device found\n");
        return ret;
    }

    g_dev_count = devCount;
    ret = FC_NP_DevOpen(&hDev, DevId);
    if (ret)
    {
        printf("FC_NP_DevOpen failed ret=%d\n", ret);
        return ret;
    }
#else

    /*该项目的测试代码类型未适配*/
    printf("demoTestDeviceQueryAndOpen : Please Adapt Project Type!!!\n");
    ret =  FC_FAILURE;
    
#endif

    return ret;
}

unsigned int demoCheckBluePrintAndLoadConfig(FCHANDLE hDev, FCUINT majorScheme, FCUINT minorScheme)
{
    unsigned int ret = FC_FAILURE;
    UINT32 tick = 0;
    
    tick = tickGet();

#if defined(__FH180_SYTLE_AUTO_TEST_DEMO__)
    /*设置模式*/
    ret = FC_NP_SetBluePrint(hDev, &gBluePrint);
    if (ret)
    {
        printf("FC_NP_SetBluePrint failed ret=0x%08x\n", ret);
        return ret;
    }
#endif

    /*配置设备*/
    ret = FC_NP_LoadConfig(hDev, majorScheme, minorScheme);
    if (ret != FC_SUCCESS)
    {
        printf("FC_NP_LoadConfig failed ret=0x%08x\n", ret);
        return ret;
    }
    printf("tick=%d.\n", (tickGet() - tick));

    return ret;
}

/*demo 自检*/
void demoTestPBit(FCHANDLE hDev)
{

#if defined(__FH130_SYTLE_AUTO_TEST_DEMO__)
    FH130Style_demoTestPBit(hDev);
#elif defined(__FH180_SYTLE_AUTO_TEST_DEMO__)
    FH180Style_demoTestPBit(hDev);
#endif

    return ;
}

UINT ResponseCallBack(int context)
{
    UINT ret = FC_FAILURE;
    
#if defined(__FH130_SYTLE_AUTO_TEST_DEMO__)
    ret = FH130Style_ResponseCallBack(context);
#elif defined(__FH180_SYTLE_AUTO_TEST_DEMO__)
    ret = FH180Style_ResponseCallBack(context);
#endif

    return ret;
}

/*设置E_D_TOV时间 仅为FT测试用例使用*/
VOID HwSetEdtov(REG_HW *reg_hw, INT32 v)
{
	PORT_RX_ENAB x;

	if (v <= 10 || v >= 10000)
	{
		printf("invalid e_d_tov=%d\n", v);
		return;
	}
	x.value = ReadRegisterUlong(&reg_hw->PORT_RX_ENAB);
	x.u.e_d_tov = v;
	WriteRegisterUlong(&reg_hw->PORT_RX_ENAB, x.value);
}

#endif  /*__FH130_AUTO_TEST_DEMO__*/
