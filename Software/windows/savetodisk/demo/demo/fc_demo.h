#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define FCM_CONFIG_FCID         0x100000
#define FCM_CONFIG_CREDIT_NUM   8
#define INT_EVT_DESC_MAX        8
#define DEV_CONFIG_SPEED        PORT_SPEED_1G

typedef struct _INT_EVT_DESC
{
    int intCode;
    int param0;
    int count;
} INT_EVT_DESC, *PINT_EVT_DESC;

typedef struct _FCM_DEMO_STATISTICS
{
    UINT64 bytes;
    UINT64 frame_num;
	UINT64 cfgid_err;
	UINT64 monitorid_err;
    UINT64 crc_err;
    UINT64 undersize;
    UINT64 oversize;
    UINT64 no_eof_err;
    UINT64 disp_err;
    UINT64 coding_err;
    INT_EVT_DESC int_evt_desc[INT_EVT_DESC_MAX];
	UINT64 asm_counter[256];
} FCM_DEMO_STATISTICS, *PFCM_DEMO_STATISTICS;

// 显示命令提示
VOID Help();

// 退出
VOID Quit();

// 接收用户输入，执行命令
VOID Commands();
// 打开设备
VOID Test_FCM_DevOpen();
// 关闭设备
VOID Test_FCM_DevClose();
// 使能设备
VOID Test_FCM_DevEnable();
// 复位设备
VOID Test_FCM_DevReset();
// 获取设备的N端口状态
VOID Test_FCM_DevGetState();
// 获取设备的N端口版本号
VOID Test_FCM_DevGetVersion();
// 注册中断接收回调函数
VOID Test_FCM_DevRegMsgHandler();
// 注销中断接收回调函数
VOID Test_FCM_DevUnRegMsgHandler();
// 注册事件中断回调函数
VOID Test_FCM_DevRegEvtHandler();
// 注销事件中断回调函数
VOID Test_FCM_DevUnRegEvtHandler();
// 取得统计信息
VOID Test_FCM_GetNStatistics();
// 启动设备的N端口BIT操作
VOID Test_FCM_IBit();
// 获取设备温度
VOID Test_FCM_GetTemp();
// 获取设备电压
VOID Test_FCM_GetVoltage();
// 获取设备工作状态
VOID Test_FCM_GetWorkStatus();
///////////////////////////////////////////////////////////////////////////////
// 通信管理接口
///////////////////////////////////////////////////////////////////////////////
// 请求有数据的缓冲区
VOID Test_FCM_RecvData();
///////////////////////////////////////////////////////////////////////////////
// 时统管理接口
///////////////////////////////////////////////////////////////////////////////
// 获取设备时间
VOID Test_FCM_TM_GetRtc();
// 设置设备时间
VOID Test_FCM_TM_SetRtc();
// 开始监控
VOID Test_FCM_DevStartMonitor();
// 停止监控
VOID Test_FCM_DevStopMonitor();
// 启动测试int
VOID Test_FCM_DemoStartInt();
UINT CALLBACK FCM_DemoStartInt(PVOID context);
// 停止测试int
VOID Test_FCM_DemoStopInt();
// 启动测试loop
VOID Test_FCM_DemoStartLoop();
UINT CALLBACK FCM_DemoStartLoop(PVOID context);
// 停止测试loop
VOID Test_FCM_DemoStopLoop();
// 打印统计信息
VOID Test_PrintDemoStatistics();
// 清空统计信息
VOID Test_ClearDemoStatistics();
// VOID Test_PrintDrvStatistics();
// 接收回调定义
FCUINT RecvCallBack(FCHANDLE hDev, void *buf, FCUINT length);
// 中断回调定义
FCUINT EvtCallBack(FCHANDLE hDev, FCUINT intCode, FCUINT param0);
VOID check_flag(UINT32 flag, PFCM_DEMO_STATISTICS v);
VOID parse_buf(char *buf, int len);
VOID parse_frame(char *buf, int length, PFCM_DEMO_STATISTICS v);
VOID print_buf(unsigned char *buf, int len);
VOID print_ibit(PFC_BIT_RESULT_MANUAL v);
VOID print_port_statistics_info(PPORT_STATISTICS_INFO v);
VOID print_fc_time(FCTime *t);
VOID print_record_header(FCM_RECORD_HEADER *r);

#ifdef __cplusplus
}
#endif