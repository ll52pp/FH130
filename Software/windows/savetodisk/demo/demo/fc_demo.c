#include "precomp.h"

FCHANDLE gDev;
HANDLE g_dev_demo_start_int_thread;
HANDLE g_dev_demo_start_int_event;
HANDLE g_dev_demo_start_loop_thread;
int g_dev_demo_stop_loop;
int g_save_disk;

FCM_DEMO_STATISTICS g_demo_stat;

int main(const int argc, const char *argv[])
{
    // 处理用户输入的命令
    gDev = NULL;
    g_dev_demo_start_int_event = INVALID_HANDLE_VALUE;
	g_dev_demo_start_int_thread = INVALID_HANDLE_VALUE;
	g_dev_demo_stop_loop = 0;
	g_save_disk = 0;
	g_dev_demo_start_loop_thread = INVALID_HANDLE_VALUE;
    memset(&g_demo_stat, 0, sizeof(FCM_DEMO_STATISTICS));

	Commands();
	printf("press any key exit\n");

	getchar();
	return 0;
}

// 显示命令提示
VOID Help()
{
	printf("++++++++++++++++++++FM130 TEST COMMAND++++++++++++++++++++\n");
    printf("| a - FCM_DevOpen           | b - FCM_DevClose           |\n");
    printf("| c - FCM_DevEnable         | d - FCM_DevReset           |\n");
    printf("| e - FCM_DevGetState       | f - FCM_DevGetVersion      |\n");
    printf("| g - FCM_DevRegMsgHandler  | h - FCM_DevUnRegMsgHandler |\n");
    printf("| i - FCM_DevRegEvtHandler  | j - FCM_DevUnRegEvtHandler |\n");
    printf("| k - FCM_GetNStatistics    | l - FCM_IBit               |\n");
    printf("| m - FCM_GetTemp           | n - FCM_GetVoltage         |\n");
    printf("| o - FCM_GetWorkStatus     | p - FCM_TM_GetRtc          |\n");
    printf("| q - FCM_TM_SetRtc         | r - FCM_DevStartMonitor    |\n");
    printf("| s - FCM_DevStopMonitor    | t - FCM_RecvData           |\n");
    printf("|--------------------------------------------------------|\n");
    printf("| u - FCM_DemoStartInt      | v - FCM_DemoStopInt        |\n");
    printf("| w - FCM_DemoStartLoop     | x - FCM_DemoStopLoop       |\n");
    printf("|--------------------------------------------------------|\n");
    printf("| y - clear screen          | z - exit                   |\n");
    printf("|--------------------------------------------------------|\n");
    printf("| 0 - print demo statistics | 1 - clear demo statistics  |\n");
    //printf("| 2 - print drv statistics  |                            |\n");
	if (g_save_disk == 0)
	{
	printf("| 3 - save disk switch      |                            |\n");
	}
	else
	{
	printf("| 3 + save disk switch      |                            |\n");
	}
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

// 接收用户输入，执行命令
VOID Commands()
{
    int cmd, stop, refresh;

    refresh = 1;
    stop = 0;
    fflush(stdin);
    while (stop == 0)
    {
        if (refresh == 1)
        {
            refresh = 0;
            Help();
        }
        cmd = getchar();
        fflush(stdin);
        cmd = tolower(cmd);

        switch (cmd)
        {
        case 'a':{ Test_FCM_DevOpen(); break; }
        case 'b':{ Test_FCM_DevClose(); break; }
        case 'c':{ Test_FCM_DevEnable(); break; }
        case 'd':{ Test_FCM_DevReset(); break; }
        case 'e':{ Test_FCM_DevGetState(); break; }
        case 'f':{ Test_FCM_DevGetVersion(); break; }
        case 'g':{ Test_FCM_DevRegMsgHandler(); break; }
        case 'h':{ Test_FCM_DevUnRegMsgHandler(); break; }
        case 'i':{ Test_FCM_DevRegEvtHandler(); break; }
        case 'j':{ Test_FCM_DevUnRegEvtHandler(); break; }
        case 'k':{ Test_FCM_GetNStatistics(); break; }
        case 'l':{ Test_FCM_IBit(); break; }
        case 'm':{ Test_FCM_GetTemp(); break; }
        case 'n':{ Test_FCM_GetVoltage(); break; }
        case 'o':{ Test_FCM_GetWorkStatus(); break; }
        case 'p':{ Test_FCM_TM_GetRtc(); break; }
        case 'q':{ Test_FCM_TM_SetRtc(); break; }
        case 'r':{ Test_FCM_DevStartMonitor(); break; }
        case 's':{ Test_FCM_DevStopMonitor(); break; }
        case 't':{ Test_FCM_RecvData(); break; }
        case 'u':{ Test_FCM_DemoStartInt(); break; }
        case 'v':{ Test_FCM_DemoStopInt(); break; }
        case 'w':{ Test_FCM_DemoStartLoop(); break; }
        case 'x':{ Test_FCM_DemoStopLoop(); break; }
        case 'y':{ system("cls"); refresh = 1; break; }
        case 'z':{ Quit(); stop = 1; break; }
        case '0':{ Test_PrintDemoStatistics(); break; }
        case '1':{ Test_ClearDemoStatistics(); break; }
        //case '2':{ Test_PrintDrvStatistics(); break; }
		case '3':{  g_save_disk = (g_save_disk + 1) % 2; break; }
        default: { refresh = 1; break; }
        }
    }
}

// 退出
VOID Quit()
{
    Test_FCM_DevStopMonitor();
	Test_FCM_DevReset();
    Test_FCM_DevClose();
}

// 打开设备
VOID Test_FCM_DevOpen()
{
    FCUINT ret, DevId;

    DevId = 0;
    ret = FCM_DevOpen(&gDev, DevId);
    if (ret)
    {
        printf("FCM_DevOpen failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevOpen success hDev=%p DevId=%d\n", gDev, DevId);
    }
}

// 关闭设备
VOID Test_FCM_DevClose()
{
    FCUINT ret;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_DevClose(gDev);
    if (ret)
    {
        printf("FCM_DevClose failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        gDev = NULL;
        printf("FCM_DevClose success\n");
    }
}

// 使能设备
VOID Test_FCM_DevEnable()
{
    FCUINT ret, fcid, credit_num;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    fcid = FCM_CONFIG_FCID;
    credit_num = FCM_CONFIG_CREDIT_NUM;
    ret = FCM_DevEnable(gDev, fcid, credit_num, DEV_CONFIG_SPEED);
    if (ret)
    {
        printf("FCM_DevEnab failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevEnab success fcid=0x%06x credit_num=%d\n", fcid, credit_num);
    }
}

// 复位设备
VOID Test_FCM_DevReset()
{
    FCUINT ret;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_DevReset(gDev);
    if (ret)
    {
        printf("FCM_DevReset failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevReset success\n");
    }
}

// 获取设备的N端口状态
VOID Test_FCM_DevGetState()
{
    FCUINT ret, state;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_DevGetState(gDev, &state);
    if (ret)
    {
        printf("FCM_DevGetState failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevGetState success state=%d\n", state);
    }
}

// 获取设备的N端口版本号
VOID Test_FCM_DevGetVersion()
{
    FCUINT ret, version;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_DevGetVersion(gDev, &version);
    if (ret)
    {
        printf("FCM_DevGetVersion failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevGetVersion success version=0x%08x\n", version);
    }
}

// 注册中断接收回调函数
VOID Test_FCM_DevRegMsgHandler()
{
    FCUINT ret;
    FC_NP_RECV_FUNCPTR func;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    func = RecvCallBack;
    ret = FCM_DevRegMsgHandler(gDev, func);
    if (ret)
    {
        printf("FCM_DevRegMsgHandler failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevRegMsgHandler success\n");
    }
}

// 注销中断接收回调函数
VOID Test_FCM_DevUnRegMsgHandler()
{
    FCUINT ret;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_DevUnRegMsgHandler(gDev);
    if (ret)
    {
        printf("FCM_DevUnRegMsgHandler failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevUnRegMsgHandler success\n");
    }
}

// 注册事件中断回调函数
VOID Test_FCM_DevRegEvtHandler()
{
    FCUINT ret;
    FC_INT_FUNCPTR func;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    func = EvtCallBack;
    ret = FCM_DevRegEvtHandler(gDev, func);
    if (ret)
    {
        printf("FCM_DevRegEvtHandler failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevRegEvtHandler success\n");
    }
}

// 注销事件中断回调函数
VOID Test_FCM_DevUnRegEvtHandler()
{
    FCUINT ret;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_DevUnRegEvtHandler(gDev);
    if (ret)
    {
        printf("FCM_DevUnRegEvtHandler failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevUnRegEvtHandler success\n");
    }
}

// 取得统计信息
VOID Test_FCM_GetNStatistics()
{
    FCUINT ret;
    PORT_STATISTICS_INFO stat[2];

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    memset(stat, 0, sizeof(PORT_STATISTICS_INFO) * 2);
    ret = FCM_GetNStatistics(gDev, stat);
    if (ret)
    {
        printf("FCM_GetNStatistics failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_GetNStatistics success\n");
        printf("port 0 statistics info\n");
        print_port_statistics_info(&stat[0]);
        printf("port 1 statistics info\n");
        print_port_statistics_info(&stat[1]);
    }
}

// 启动设备的N端口BIT操作
VOID Test_FCM_IBit()
{
    FCUINT ret;
    FC_BIT_RESULT_MANUAL bitResult;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    memset(&bitResult, 0, sizeof(FC_BIT_RESULT_MANUAL));
    ret = FCM_IBit(gDev, &bitResult);
    if (ret)
    {
        printf("FCM_IBit failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_IBit success\n");
        print_ibit(&bitResult);
    }
}

// 获取设备温度
VOID Test_FCM_GetTemp()
{
    FCUINT ret, temperature;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_GetTemp(gDev, &temperature);
    if (ret)
    {
        printf("FCM_GetTemp failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_GetTemp success temperature=%d\n", temperature);
    }
}

// 获取设备电压
VOID Test_FCM_GetVoltage()
{
    FCUINT ret, voltage;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_GetVoltage(gDev, &voltage);
    if (ret)
    {
        printf("FCM_GetVoltage failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_GetVoltage success voltage=%d\n", voltage);
    }
}

// 获取设备工作状态
VOID Test_FCM_GetWorkStatus()
{
    FCUINT ret, status;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_GetWorkStatus(gDev, &status);
    if (ret)
    {
        printf("FCM_GetWorkStatus failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_GetWorkStatus success status=%d\n", status);
    }
}

///////////////////////////////////////////////////////////////////////////////
// 通信管理接口
///////////////////////////////////////////////////////////////////////////////
// 请求有数据的缓冲区
VOID Test_FCM_RecvData()
{
    FCUINT ret, va_addr, nLen;
    FCUCHAR *buf;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    buf = (FCUCHAR *)&va_addr;
    nLen = sizeof(int);
    ret = FCM_RecvData(gDev, (void **)&buf, &nLen);
    if (ret)
    {
        printf("FCM_RecvData failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
		return;
    }
	if (nLen == 0)
	{
		printf("FCM_RecvData success but nLen=0\n");
		return;
	}
	printf("FCM_RecvData success buf=0x%08x nLen=%d\n", (int)buf, nLen);
	print_buf(buf, nLen);


	parse_buf(buf, nLen);


	// 释放缓冲区
	ret = FCM_ReleaseBuf(gDev, buf);
	if (ret)
	{
		printf("FCM_ReleaseBuf failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
	}
	else
	{
		printf("FCM_ReleaseBuf success\n");
	}
}

///////////////////////////////////////////////////////////////////////////////
// 时统管理接口
///////////////////////////////////////////////////////////////////////////////
// 获取设备时间
VOID Test_FCM_TM_GetRtc()
{
    FCUINT ret;
    FCTime time;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    memset(&time, 0, sizeof(FCTime));
    ret = FCM_TM_GetRtc(gDev, &time);
    if (ret)
    {
        printf("FCM_TM_GetRtc failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_TM_GetRtc success\n");
        print_fc_time(&time);
    }
}

// 设置设备时间
VOID Test_FCM_TM_SetRtc()
{
    FCUINT ret;
    FCTime t;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    t.hour = 10;
    t.minute = 11;
    t.second = 12;
    t.millisecond = 13;
    t.microsecond = 14;
    t.nanosecond = 15;
    ret = FCM_TM_SetRtc(gDev, &t);
    if (ret)
    {
        printf("FCM_TM_SetRtc failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_TM_SetRtc success\n");
        print_fc_time(&t);
    }
}

// 开始监控
VOID Test_FCM_DevStartMonitor()
{
    FCUINT ret;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_DevStartMonitor(gDev);
    if (ret)
    {
        printf("FCM_DevStartMonitor failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevStartMonitor success\n");
    }
}

// 停止监控
VOID Test_FCM_DevStopMonitor()
{
    FCUINT ret;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}
    ret = FCM_DevStopMonitor(gDev);
    if (ret)
    {
        printf("FCM_DevStopMonitor failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DevStopMonitor success\n");
    }
}

// 启动测试Int
VOID Test_FCM_DemoStartInt()
{
    UINT t_id;

	if (gDev != NULL)
	{
		printf("demo is running\n");
		return ;
	}
	if (g_dev_demo_start_loop_thread != INVALID_HANDLE_VALUE)
	{
		printf("loop recv is running\n");
		return ;
	}
	if (g_dev_demo_start_int_thread != INVALID_HANDLE_VALUE)
	{
		printf("int recv is running\n");
		return ;
	}
    g_dev_demo_start_int_thread = (HANDLE)_beginthreadex(NULL, 0, FCM_DemoStartInt, NULL, 0, &t_id);
    assert(g_dev_demo_start_int_thread != INVALID_HANDLE_VALUE);
    printf("FCM_DemoStartInt thread is running\n");
}

UINT CALLBACK FCM_DemoStartInt(PVOID context)
{
    FCUINT ret, DevId;
    int dev_open_flag, reg_recv_flag, reg_int_flag, dev_enab_flag, monitor_flag;
    ULONG fcid, credit_num;
    DWORD reason;
    FC_NP_RECV_FUNCPTR func_recv;
    FC_INT_FUNCPTR func_int;

    DevId = 0;
    dev_open_flag = reg_recv_flag = reg_int_flag = dev_enab_flag = monitor_flag = 0;
    g_dev_demo_start_int_event = CreateEvent(NULL, FALSE, FALSE, NULL);
    assert(g_dev_demo_start_int_event != INVALID_HANDLE_VALUE);
    if (g_dev_demo_start_int_event == INVALID_HANDLE_VALUE)
    {
        printf("CreateEvent failed err=0x%08x\n", GetLastError());
        return 0;
    }
    func_int = EvtCallBack;
    func_recv = RecvCallBack;
    do {
        // 打开设备
        ret = FCM_DevOpen(&gDev, DevId);
        if (ret)
        {
            printf("[%s]FCM_DevOpen failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        dev_open_flag = 1;
        // 注册中断事件处理
        ret = FCM_DevRegEvtHandler(gDev, func_int);
        if (ret)
        {
            printf("[%s]FCM_DevRegEvtHandler failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        reg_int_flag = 1;
        // 注册中断接收
        ret = FCM_DevRegMsgHandler(gDev, func_recv);
        if (ret)
        {
            printf("[%s]FCM_DevRegMsgHandler failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        reg_recv_flag = 1;
        // 使能设备
        fcid = FCM_CONFIG_FCID;
        credit_num = FCM_CONFIG_CREDIT_NUM;
        ret = FCM_DevEnable(gDev, fcid, credit_num, DEV_CONFIG_SPEED);
        if (ret)
        {
            printf("[%s]FCM_DevEnable failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        dev_enab_flag = 1;
        // 开始监控
        ret = FCM_DevStartMonitor(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevStartMonitor failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        monitor_flag = 1;
        // 等待停止信号
        reason = WaitForSingleObject(g_dev_demo_start_int_event, INFINITE);
        assert(reason == WAIT_OBJECT_0);
    } while (FALSE);

    if (monitor_flag == 1)
    {
        ret = FCM_DevStopMonitor(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevStopMonitor failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
    }
    if (dev_enab_flag == 1)
    {
        ret = FCM_DevReset(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevReset failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
    }
    if (reg_recv_flag == 1)
    {
        ret = FCM_DevUnRegMsgHandler(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevUnRegMsgHandler failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
    }
    if (reg_int_flag == 1)
    {
        ret = FCM_DevUnRegEvtHandler(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevUnRegEvtHandler failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
    }
    if (dev_open_flag == 1)
    {
        ret = FCM_DevClose(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevClose failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
		gDev = NULL;
    }
    printf("%s leave\n", __FUNCTION__);
    return 0;
}

// 停止测试int
VOID Test_FCM_DemoStopInt()
{
    DWORD reason;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}	
	if (g_dev_demo_start_int_thread == INVALID_HANDLE_VALUE)
	{
        printf("FCM_DemoStartInt is stop\n");
	}
    if (g_dev_demo_start_int_event == INVALID_HANDLE_VALUE)
    {
        printf("FCM_DemoStartInt is stop\n");
        return;
    }
    SetEvent(g_dev_demo_start_int_event);
    reason = WaitForSingleObject(g_dev_demo_start_int_thread, INFINITE);
    assert(reason == WAIT_OBJECT_0);
	CloseHandle(g_dev_demo_start_int_event);
	g_dev_demo_start_int_event = INVALID_HANDLE_VALUE;
	g_dev_demo_start_int_thread = INVALID_HANDLE_VALUE;
}

// 启动测试Loop
VOID Test_FCM_DemoStartLoop()
{
    UINT t_id;

	if (g_dev_demo_start_int_thread != INVALID_HANDLE_VALUE)
	{
		printf("int recv is running\n");
		return ;
	}
	if (g_dev_demo_start_loop_thread != INVALID_HANDLE_VALUE)
	{
		printf("loop recv is running\n");
		return ;
	}
    g_dev_demo_start_loop_thread = (HANDLE)_beginthreadex(NULL, 0, FCM_DemoStartLoop, NULL, 0, &t_id);
    assert(g_dev_demo_start_loop_thread != INVALID_HANDLE_VALUE);
    printf("FCM_DemoStartLoop thread is running\n");
}

UINT CALLBACK FCM_DemoStartLoop(PVOID context)
{
    FCUINT ret, DevId, va_addr, nLen;
    int dev_open_flag, reg_int_flag, dev_enab_flag, monitor_flag;
    ULONG fcid, credit_num;
	char *buf;
    FC_INT_FUNCPTR func_int;

    DevId = 0;
    dev_open_flag = reg_int_flag = dev_enab_flag = monitor_flag = 0;
	g_dev_demo_stop_loop = 0;
    func_int = EvtCallBack;

	if (g_save_disk == 1)
	{
		InitWriteGlobalVariable();
		CreateNewFile();
	}
	
    do {
        // 打开设备
        ret = FCM_DevOpen(&gDev, DevId);
        if (ret)
        {
            printf("[%s]FCM_DevOpen failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        dev_open_flag = 1;
        // 注册中断事件处理
        ret = FCM_DevRegEvtHandler(gDev, func_int);
        if (ret)
        {
            printf("[%s]FCM_DevRegEvtHandler failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        reg_int_flag = 1;
        // 使能设备
        fcid = FCM_CONFIG_FCID;
        credit_num = FCM_CONFIG_CREDIT_NUM;
        ret = FCM_DevEnable(gDev, fcid, credit_num, DEV_CONFIG_SPEED);
        if (ret)
        {
            printf("[%s]FCM_DevEnable failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        dev_enab_flag = 1;
        // 开始监控
        ret = FCM_DevStartMonitor(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevStartMonitor failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            break;
        }
        monitor_flag = 1;

		while (g_dev_demo_stop_loop == 0)
		{
		    buf = (char *)&va_addr;
		    nLen = 4;
			ret = FCM_RecvData(gDev, (void **)&buf, &nLen);
			if (ret)
			{
				printf("[%s]FCM_RecvData failed ret=0x%08x err=0x%08x\n", __FUNCTION__, ret, GetLastError());
				break;
			}
			if (nLen == 0)
			{
				// Sleep(100);
				continue;
			}
			parse_buf(buf, nLen);
			// 释放缓冲区
			ret = FCM_ReleaseBuf(gDev, buf);
			if (ret)
			{
				printf("[%s]FCM_ReleaseBuf failed ret=0x%08x err=0x%08x\n", __FUNCTION__, ret, GetLastError());
				break;
			}
		}
    } while (FALSE);

	if (g_save_disk == 1)
	{
		/* 写统计文件 */
		WriteStatisticsToFile(&g_demo_stat);

		/* 写索引文件 */
		WriteIndexFile();

		/* 监控退出，重设监控卡接收数据存盘用到的资源 */
		ResetWriteGlobalVariable();
	}
	
    if (monitor_flag == 1)
    {
        ret = FCM_DevStopMonitor(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevStopMonitor failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
    }
    if (dev_enab_flag == 1)
    {
        ret = FCM_DevReset(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevReset failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
    }
    if (reg_int_flag == 1)
    {
        ret = FCM_DevUnRegEvtHandler(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevUnRegEvtHandler failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
    }
    if (dev_open_flag == 1)
    {
        ret = FCM_DevClose(gDev);
        if (ret)
        {
            printf("[%s]FCM_DevClose failed ret=%d err=0x%08x\n", __FUNCTION__, ret, GetLastError());
            return 0;
        }
		gDev = NULL;
    }
    printf("%s leave\n", __FUNCTION__);
    return 0;
}

// 停止测试loop
VOID Test_FCM_DemoStopLoop()
{
	DWORD reason;

	if (gDev == NULL)
	{
		printf("gDev is NULL\n");
		return ;
	}	
	if (g_dev_demo_start_loop_thread == INVALID_HANDLE_VALUE)
	{
        printf("FCM_DemoStartLoop is stop\n");
	}
	if (g_dev_demo_stop_loop == 1)
	{
		printf("FCM_DemoStartLoop is stop\n");
	}
	g_dev_demo_stop_loop = 1;
    reason = WaitForSingleObject(g_dev_demo_start_loop_thread, INFINITE);
    assert(reason == WAIT_OBJECT_0);
	g_dev_demo_start_loop_thread = INVALID_HANDLE_VALUE;
}

// 打印统计信息
VOID Test_PrintDemoStatistics()
{
    int idx, count;
    PINT_EVT_DESC d;
    PFCM_DEMO_STATISTICS v;

    v = &g_demo_stat;
    printf("fcm demo statistics\n");
    printf("bytes=%I64d\n", v->bytes);
    printf("frame_num=%I64d\n", v->frame_num);
    printf("crc_err=%I64d\n", v->crc_err);
    printf("undersize=%I64d\n", v->undersize);
    printf("oversize=%I64d\n", v->oversize);
    printf("no_eof_err=%I64d\n", v->no_eof_err);
    printf("disp_err=%I64d\n", v->disp_err);
    printf("coding_err=%I64d\n", v->coding_err);
    count = INT_EVT_DESC_MAX;
    for (idx = 0; idx < count; ++idx)
    {
        d = &v->int_evt_desc[idx];
        if (d->intCode != 0)
        {
            printf("intCode=0x%08x param0=%d count=%d\n", d->intCode, d->param0, d->count);
        }
    }
	count = 256;
    for (idx = 0; idx < count; ++idx)
    {
        if (v->asm_counter[idx] != 0)
        {
            printf("asmid[%d]=%I64d\n", idx, v->asm_counter[idx]);
        }
    }
}

// 清空统计信息
VOID Test_ClearDemoStatistics()
{
    memset(&g_demo_stat, 0, sizeof(FCM_DEMO_STATISTICS));
}
/*
VOID Test_PrintDrvStatistics()
{
    FCUINT ret;

    if (gDev == NULL)
    {
        printf("gDev is NULL\n");
        return;
    }
    ret = FCM_DBG_DrvStastics(gDev);
    if (ret)
    {
        printf("FCM_DBG_DrvStastics failed ret=0x%08x err=0x%08x\n", ret, GetLastError());
    }
    else
    {
        printf("FCM_DBG_DrvStastics success\n");
    }
}*/

// 接收回调定义
FCUINT RecvCallBack(FCHANDLE hDev, void *buf, FCUINT length)
{
	FCUINT ret;

    parse_buf((char *)buf, length);
	// 释放缓冲区
	ret = FCM_ReleaseBuf(gDev, buf);
	if (ret)
	{
		printf("[%s]FCM_ReleaseBuf failed ret=0x%08x err=0x%08x\n", __FUNCTION__, ret, GetLastError());
	}
    return 0;
}

// 中断回调定义
FCUINT EvtCallBack(FCHANDLE hDev, FCUINT intCode, FCUINT param0)
{
    int idx, count;
    PINT_EVT_DESC d;

	assert(hDev != NULL);
    count = INT_EVT_DESC_MAX;
    idx = intCode - 0x100;
    if (!(idx >= 0 && idx < count))
    {
        printf("hDev=%p intCode=0x%08x param0=0x%08x\n", hDev, intCode, param0);
    }
    else
    {
        d = &g_demo_stat.int_evt_desc[idx];
        if (d->intCode == 0)
        {
            d->intCode = intCode;
        }
        else
        {
            assert(d->intCode == intCode && d->count > 0);
        }
        d->count++;
    }
    return 0;
}

VOID parse_buf(char *buf, int length)
{
	int frame_length, origin_len;
	char *frame_buf, *origin_buf;
	PFCM_DEMO_STATISTICS stat;
	FCM_RECORD_HEADER rec_header;
	PFCM_RECORD_HEADER prec_header;
	
	stat = &g_demo_stat;
	origin_len = length;
	origin_buf = buf;

	while (length > 0)
	{
		prec_header = (PFCM_RECORD_HEADER)buf;
		rec_header = *prec_header;
		rec_header.cfgID = htonl(rec_header.cfgID);
		rec_header.monitorID = htonl(rec_header.monitorID);
		rec_header.flag = htonl(rec_header.flag);
		rec_header.length = htonl(rec_header.length);
		if (rec_header.cfgID != FRAME_CFGID)
		{
			stat->cfgid_err++;
            print_record_header(&rec_header);
			assert(FALSE);
		}
		if (rec_header.monitorID != FRAME_MONITORID)
		{
			stat->monitorid_err++;
            print_record_header(&rec_header);
			assert(FALSE);
		}
		check_flag(rec_header.flag, stat);
		frame_length = rec_header.length - sizeof(FCM_RECORD_HEADER);
		frame_buf = (char *)(prec_header + 1);
		//print_record_header(rec_header);
		parse_frame(frame_buf, frame_length, stat);
		stat->bytes += frame_length;
		stat->frame_num++;

		buf += rec_header.length;
		length -= rec_header.length;
		assert(rec_header.length <= 2148+16);
		if (g_save_disk == 1)
		{
			ComputeFrameNum(&origin_buf, &origin_len, buf, rec_header.length);
		}
	}

	/*写数据文件*/
	if (g_save_disk == 1)
		WriteBufToDataFile(origin_buf, origin_len);
	assert(length == 0);
}

VOID check_flag(UINT32 flag, PFCM_DEMO_STATISTICS v)
{
    // assert(flag == 0);
    if (flag & FRAME_FLAG_CRC_ERR)

    {
        v->crc_err++;
    }
    if (flag & FRAME_FLAG_UNDERSIZE)
    {
        v->undersize++;
    }
    if (flag & FRAME_FLAG_OVERSIZE)
    {
        v->oversize++;
    }
    if (flag & FRAME_FLAG_NO_EOF_ERR)
    {
        v->no_eof_err++;
    }
    if (flag & FRAME_FLAG_DISP_ERR)
    {
        v->disp_err++;
    }
    if (flag & FRAME_FLAG_CODING_ERR)
    {
        v->coding_err++;
    }
}

VOID parse_frame(char *buf, int length, PFCM_DEMO_STATISTICS v)
{
	unsigned int eof;

	// 小端处理
	eof = 0;
	eof = (unsigned char)buf[length - 4];
	eof = (eof << 8) | (unsigned char)buf[length - 3];
	eof = (eof << 8) | (unsigned char)buf[length - 2];
	eof = (eof << 8) | (unsigned char)buf[length - 1];
	if (eof != 0xBC957575
	 && eof != 0xBCB57575
	 && eof != 0xBC95D5D5
	 && eof != 0xBCB5D5D5
	 && eof != 0xBC95F5F5)
	{
		printf("eof=0x%08x error\n", eof);
	}
	assert(eof == 0xBC957575 || eof == 0xBCB57575 || eof == 0xBC95D5D5 || eof == 0xBCB5D5D5 || eof == 0xBC95F5F5);
}

VOID print_buf(unsigned char *buf, int len)
{
    int i;
    
    printf("buf=%p len=%d\n", buf, len);
    for (i = 0; i < len; ++i)
    {
        printf("%02x", buf[i]);
        if ((i + 1) % 4 == 0)
        {
            printf(" ");
        }
        if ((i + 1) % 32 == 0)
        {
            printf("\n");
        }
    }
    if ((i + 1) % 32 != 0)
    {
        printf("\n");
    }
}

VOID print_port_statistics_info(PPORT_STATISTICS_INFO v)
{
    printf("RxUndersizeFrameCnt=%I64d\n", v->RxUndersizeFrameCnt);
    printf("RxOversizeFrameErrCnt=%I64d\n", v->RxOversizeFrameErrCnt);
    printf("RxAllFrameCnt=%I64d\n", v->RxAllFrameCnt);
    printf("RxValidFrameCnt=%I64d\n", v->RxValidFrameCnt);
    printf("RxWordCnt=%I64d(bytes=%I64d)\n", v->RxWordCnt, v->RxWordCnt * 4);
    printf("RxRRDYCnt=%I64d\n", v->RxRRDYCnt);
    printf("RxKErrCnt=%I64d\n", v->RxKErrCnt);
    printf("LinkChgUp2DownCnt=%I64d\n", v->LinkChgUp2DownCnt);
    printf("TxAllFrameCnt=%I64d\n", v->TxAllFrameCnt);
    printf("TxValidFrameCnt=%I64d\n", v->TxValidFrameCnt);
    printf("TxWordCnt=%I64d\n", v->TxWordCnt);
    printf("TxRRDYCnt=%I64d\n", v->TxRRDYCnt);
    printf("TxKErrCnt=%I64d\n", v->TxKErrCnt);
}

VOID print_ibit(PFC_BIT_RESULT_MANUAL v)
{
    printf("bit result manual[flash=%d buffer=%d temperature=%d voltage=%d]\n", v->flash, v->buffer, v->temperature, v->voltage);
}

VOID print_fc_time(FCTime *t)
{
    printf("FCTime[hour=%d minute=%d second=%d millisecond=%d microsecond=%d nanosecond=%d]\n",
        t->hour, t->minute, t->second, t->millisecond, t->microsecond, t->nanosecond);
}

VOID print_record_header(FCM_RECORD_HEADER *r)
{
	printf("FCM_RECORD_HEADER[length=%d flag=0x%08x cfgID=0x%08x monitorID=0x%08x\n", r->length, r->flag, r->cfgID, r->monitorID);
}
