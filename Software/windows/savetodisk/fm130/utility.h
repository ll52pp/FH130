#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "precomp.h"

#define DEV_NUM_MAX                        8
#define LIB_MAJOR_VER                      1
#define LIB_MINOR_VER                      0
#define PORT_SPEED_1G                      1
#define PORT_SPEED_2G                      2
#define PORT_LINK_DOWN                     0
#define PORT_LINK_UP                       1
// 端口配置参数
//#define DEV_CONFIG_SPEED                   PORT_SPEED_1G
#define DEV_CONFIG_DID_FILTER_ENAB         0
#define DEV_CONFIG_E_D_TOV                 100
#define DEV_CONFIG_REDUNDANT_ENAB          1
#define DEV_CONFIG_TIME_OUT                (1000) // 单位是ms
#define DEV_CONFIG_QDR_BUF_UNIT_SIZE       (64 * 1024)
#define SW_FCID                            0x00FFFFFD

#define THREAD_CTRL_RUN                    0
#define THREAD_CTRL_STOP                   1 
#define THREAD_STATE_STOP                  0
#define THREAD_STATE_RUN                   1

#define INT_CONTEXT_IDLE                   0      // 中断消息块空闲
#define INT_CONTEXT_USE                    1      // 中断消息块使用中
#define INT_RECV_BLOCK_MAX                 1024
#define INT_EVT_TYPE_MAX                   8
#define INT_EVT_PARAM_MAX                  4

///////////////////////////////////////////////////////////////////////////////
// 错误码定义
///////////////////////////////////////////////////////////////////////////////
#define HERR_PARAM_INVALID                 0x10000001
#define HERR_GUID_INVALID                  0x10000002
#define HERR_INSUFFICIENT_RESOURCE         0x10000003
#define HERR_MALLOC_FAILED                 0x10000004
#define HERR_GET_INTERFACE_FAILED          0x10000005
#define HERR_COPY_DATA_FAILED              0x10000006
#define HERR_NO_FOUND_DEVICE               0x10000007
#define HERR_GET_READ_HANDLE_FAILED        0x10000008
#define HERR_GET_WRITE_HANDLE_FAILED       0x10000009
#define HERR_GET_IOCTRL_HANDLE_FAILED      0x1000000A
#define HERR_DEVICE_IO_FAILED              0x1000000B
#define HERR_RESP_NG                       0x1000000C
#define IO_CTRL_RESP_OK                    0
#define IO_CTRL_RESP_NG                    0x00000001

///////////////////////////////////////////////////////////////////////////////
// IOCTRL接口定义
///////////////////////////////////////////////////////////////////////////////
// {A11B97B0-D010-41E2-8FD9-6249B6B4B2EF}
DEFINE_GUID(GUID_DEVINTERFACE_FM130, 0xa11b97b0, 0xd010, 0x41e2, 0x8f, 0xd9, 0x62, 0x49, 0xb6, 0xb4, 0xb2, 0xef);

#define HBA_CTL_CODE_BASE                  0x8000
#define HBA_CTL_CODE(_code)                CTL_CODE(HBA_CTL_CODE_BASE, (_code), METHOD_IN_DIRECT, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DEV_OPEN                     HBA_CTL_CODE(0x100)
#define IOCTL_DEV_CLOSE                    HBA_CTL_CODE(0x101)
#define IOCTL_DEV_ENAB                     HBA_CTL_CODE(0x102)
#define IOCTL_DEV_RESET                    HBA_CTL_CODE(0x103)
#define IOCTL_DEV_GET_STATE                HBA_CTL_CODE(0x104)
#define IOCTL_DEV_GET_VERSION              HBA_CTL_CODE(0x105)
#define IOCTL_DEV_REG_RECV_HANDLER         HBA_CTL_CODE(0x106)
#define IOCTL_DEV_UNREG_RECV_HANDLER       HBA_CTL_CODE(0x107)
#define IOCTL_DEV_REG_EVT_HANDLER          HBA_CTL_CODE(0x108)
#define IOCTL_DEV_UNREG_EVT_HANDLER        HBA_CTL_CODE(0x109)
#define IOCTL_DEV_GET_STATISTICS           HBA_CTL_CODE(0x10A)
#define IOCTL_DEV_IBIT                     HBA_CTL_CODE(0x10B)
#define IOCTL_DEV_GET_TEMPERATURE          HBA_CTL_CODE(0x10C)
#define IOCTL_DEV_GET_VOLTAGE              HBA_CTL_CODE(0x10D)
#define IOCTL_DEV_GET_WORK_STATUS          HBA_CTL_CODE(0x10E)
#define IOCTL_DEV_GET_RTC                  HBA_CTL_CODE(0x10F)
#define IOCTL_DEV_SET_RTC                  HBA_CTL_CODE(0x110)
#define IOCTL_DEV_MONITOR_START            HBA_CTL_CODE(0x111)
#define IOCTL_DEV_MONITOR_STOP             HBA_CTL_CODE(0x112)
// 调试
#define IOCTL_DEV_DBG_STATISTICS           HBA_CTL_CODE(0x900)

///////////////////////////////////////////////////////////////////////////////
// 内部结构体定义
///////////////////////////////////////////////////////////////////////////////
//
// 中断接收消息
//
typedef struct _CBN_INT_RECV_CONTEXT
{
    LONG volatile r3_index; // 应用层读取的位置
    LONG volatile r0_index; // 内核写入的位置
    INT32 volatile block[INT_RECV_BLOCK_MAX];
} CBN_INT_RECV_CONTEXT, *PCBN_INT_RECV_CONTEXT;

//
// 中断通知消息
//
typedef struct _CBN_EVT_DESC
{
    INT32 int_code;                // 中断码
    INT32 param[INT_EVT_PARAM_MAX];// 参数
} CBN_EVT_DESC, *PCBN_EVT_DESC;

typedef struct _CBN_INT_EVT_CONTEXT
{
    LONG volatile flag;
    CBN_EVT_DESC desc[INT_EVT_TYPE_MAX];
} CBN_INT_EVT_CONTEXT, *PCBN_INT_EVT_CONTEXT;

///////////////////////////////////////////////////////////////////////////////
//和FPGA交互的读写控制域的定义
///////////////////////////////////////////////////////////////////////////////
/* RX 方向 */
typedef union _R0
{
    struct
    {
        ULONG length : 32;
    } u;
    ULONG value;
} R0;

typedef union _R1
{
    struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
        ULONG reserve : 24;/* [ 8:31] : RW reserve */
        ULONG channel_num : 8; /* [ 0: 7] : RW channel num */
#else		
        ULONG channel_num : 8; /* [ 0: 7] : RW channel num */
        ULONG reserve : 24;/* [ 8:31] : RW reserve */
#endif
    } u;
    ULONG value;
} R1;

typedef struct _R_CTRL
{
    R0 r0;
    R1 r1;
} R_CTRL, *PR_CTRL;

//
// 卡的状态
//
typedef enum _ENUM_CARD_STATE {
    ECS_NONE = 0, // 初始状态
    ECS_OPEN,     // 打开状态
    ECS_CONFIG,   // 配置状态
    ECS_MONITOR   // 监视中状态
} ENUM_CARD_STATE;


//typedef struct _PORT_STATISTICS_INFO PORT_STATISTICS_INFO;
                                    
//
// 打开卡
//
typedef struct _DEV_OPEN_REQ
{
    int reserve;
} DEV_OPEN_REQ, *PDEV_OPEN_REQ;

typedef struct _DEV_OPEN_RESP
{
    int result;
} DEV_OPEN_RESP, *PDEV_OPEN_RESP;

//
// 关闭卡
//
typedef struct _DEV_CLOSE_REQ
{
    int reserve;
} DEV_CLOSE_REQ, *PDEV_CLOSE_REQ;

typedef struct _DEV_CLOSE_RESP
{
    int result;
} DEV_CLOSE_RESP, *PDEV_CLOSE_RESP;

//
// 设备使能
//
typedef struct _DEV_ENAB_REQ
{
    int credit_num;
    int speed;
    int did_filter_enab;
    int e_d_tov;
    int redundant_enab;
    int time_out;
    int qdr_buf_unit_size;
	int sw_fcid;
} DEV_ENAB_REQ, *PDEV_ENAB_REQ;

typedef struct _DEV_ENAB_RESP
{
    int result;
} DEV_ENAB_RESP, *PDEV_ENAB_RESP;

//
// 设备复位
//
typedef struct _DEV_RESET_REQ
{
    int reserve;
} DEV_RESET_REQ, *PDEV_RESET_REQ;

typedef struct _DEV_RESET_RESP
{
    int result;
} DEV_RESET_RESP, *PDEV_RESET_RESP;

//
// 取得端口状态
//
typedef struct _DEV_GET_STATE_REQ
{
    int reserve;
} DEV_GET_STATE_REQ, *PDEV_GET_STATE_REQ;

typedef struct _DEV_GET_STATE_RESP
{
    int result;
    ULONG p0_status;
    ULONG p1_status;
} DEV_GET_STATE_RESP, *PDEV_GET_STATE_RESP;

//
// 取得版本号
//
typedef struct _DEV_GET_VERSION_REQ
{
    int reserve;
} DEV_GET_VERSION_REQ, *PDEV_GET_VERSION_REQ;

typedef struct _DEV_GET_VERSION_RESP
{
    int result;
    int fpga_version;
    int drier_version;
} DEV_GET_VERSION_RESP, *PDEV_GET_VERSION_RESP;

//
// 注册接收回调例程
//
typedef struct _DEV_REG_RECV_HANDLER_REQ
{
    HANDLE handle_event;
} DEV_REG_RECV_HANDLER_REQ, *PDEV_REG_RECV_HANDLER_REQ;

typedef struct _DEV_REG_RECV_HANDLER_RESP
{
    int result;
    PCBN_INT_RECV_CONTEXT context;
} DEV_REG_RECV_HANDLER_RESP, *PDEV_REG_RECV_HANDLER_RESP;

//
// 注销接收回调例程
//
typedef struct _DEV_UNREG_RECV_HANDLER_REQ
{
    int reserve;
} DEV_UNREG_RECV_HANDLER_REQ, *PDEV_UNREG_RECV_HANDLER_REQ;

typedef struct _DEV_UNREG_RECV_HANDLER_RESP
{
    int result;
} DEV_UNREG_RECV_HANDLER_RESP, *PDEV_UNREG_RECV_HANDLER_RESP;

//
// 注册事件回调例程
//
typedef struct _DEV_REG_EVT_HANDLER_REQ
{
    HANDLE handle_event;
} DEV_REG_EVT_HANDLER_REQ, *PDEV_REG_EVT_HANDLER_REQ;

typedef struct _DEV_REG_EVT_HANDLER_RESP
{
    int result;
    PCBN_INT_EVT_CONTEXT context;
} DEV_REG_EVT_HANDLER_RESP, *PDEV_REG_EVT_HANDLER_RESP;

//
// 注销事件回调例程
//
typedef struct _DEV_UNREG_EVT_HANDLER_REQ
{
    int reserve;
} DEV_UNREG_EVT_HANDLER_REQ, *PDEV_UNREG_EVT_HANDLER_REQ;

typedef struct _DEV_UNREG_EVT_HANDLER_RESP
{
    int result;
} DEV_UNREG_EVT_HANDLER_RESP, *PDEV_UNREG_EVT_HANDLER_RESP;

//
// 取得统计信息
//
typedef struct _DEV_GET_STATISTICS_REQ
{
    int reserve;
} DEV_GET_STATISTICS_REQ, *PDEV_GET_STATISTICS_REQ;

typedef struct _DEV_GET_STATISTICS_RESP
{
    int result;
    PORT_STATISTICS_INFO info[2];
} DEV_GET_STATISTICS_RESP, *PDEV_GET_STATISTICS_RESP;

//
// 启动IBIT自检
//
typedef struct _DEV_IBIT_REQ
{
    int reserve;
} DEV_IBIT_REQ, *PDEV_IBIT_REQ;

typedef struct _DEV_IBIT_RESP
{
    int result;
    int flash;
    int buffer;
    int temperature;
    int voltage;
} DEV_IBIT_RESP, *PDEV_IBIT_RESP;

//
// 获取温度
//
typedef struct _DEV_GET_TEMPERATURE_REQ
{
    int reserve;
} DEV_GET_TEMPERATURE_REQ, *PDEV_GET_TEMPERATURE_REQ;

typedef struct _DEV_GET_TEMPERATURE_RESP
{
    int result;
    int temperature;
} DEV_GET_TEMPERATURE_RESP, *PDEV_GET_TEMPERATURE_RESP;

//
// 获取电压
//
typedef struct _DEV_GET_VOLTAGE_REQ
{
    int reserve;
} DEV_GET_VOLTAGE_REQ, *PDEV_GET_VOLTAGE_REQ;

typedef struct _DEV_GET_VOLTAGE_RESP
{
    int result;
    int voltage;
} DEV_GET_VOLTAGE_RESP, *PDEV_GET_VOLTAGE_RESP;

//
// 获取驱动工作状态是否正常
//
typedef struct _DEV_GET_WORK_STATUS_REQ
{
    int reserve;
} DEV_GET_WORK_STATUS_REQ, *PDEV_GET_WORK_STATUS_REQ;

typedef struct _DEV_GET_WORK_STATUS_RESP
{
    int result;
    int status;
} DEV_GET_WORK_STATUS_RESP, *PDEV_GET_WORK_STATUS_RESP;

//
// 获取RTC
//
typedef struct _DEV_GET_RTC_REQ
{
    int reserve;
} DEV_GET_RTC_REQ, *PDEV_GET_RTC_REQ;

typedef struct _DEV_GET_RTC_RESP
{
    int result;
    FCTime time;
} DEV_GET_RTC_RESP, *PDEV_GET_RTC_RESP;

//
// 设置RTC
//
typedef struct _DEV_SET_RTC_REQ
{
    FCTime time;
} DEV_SET_RTC_REQ, *PDEV_SET_RTC_REQ;

typedef struct _DEV_SET_RTC_RESP
{
    int result;
} DEV_SET_RTC_RESP, *PDEV_SET_RTC_RESP;

//
// 开始监控
//
typedef struct _DEV_MONITOR_START_REQ
{
    int reserve;
} DEV_MONITOR_START_REQ, *PDEV_MONITOR_START_REQ;

typedef struct _DEV_MONITOR_START_RESP
{
    int result;
} DEV_MONITOR_START_RESP, *PDEV_MONITOR_START_RESP;

//
// 停止监控
//
typedef struct _DEV_MONITOR_STOP_REQ
{
    int reserve;
} DEV_MONITOR_STOP_REQ, *PDEV_MONITOR_STOP_REQ;

typedef struct _DEV_MONITOR_STOP_RESP
{
    int result;
} DEV_MONITOR_STOP_RESP, *PDEV_MONITOR_STOP_RESP;

//
// 描述卡的结构体
//
typedef struct _DEV_INFO {
    USHORT number;
    USHORT reserve;
    TCHAR  path[MAX_PATH];
    struct {
        HANDLE read;
        HANDLE write;
        HANDLE ioctrl;
    } io;
    ENUM_CARD_STATE state;

    HANDLE int_evt_event;
    HANDLE int_evt_thread;
    FC_INT_FUNCPTR int_evt_func;
    int int_evt_ctrl;
    PCBN_INT_EVT_CONTEXT int_evt_cbn;

    HANDLE int_recv_event;
    HANDLE int_recv_thread;
    FC_NP_RECV_FUNCPTR int_recv_func;
    int int_recv_ctrl;
    PCBN_INT_RECV_CONTEXT int_recv_cbn;
} DEV_INFO, *PDEV_INFO;

typedef struct _DEV_MANAGER {
    int flag;
    DEV_INFO devInfo[DEV_NUM_MAX];
} DEV_MANAGER, *PDEV_MANAGER;

DEV_MANAGER gDevManager;

///////////////////////////////////////////////////////////////////////////////
// 内部例程定义
///////////////////////////////////////////////////////////////////////////////
#define CLOSE_HANDLE_AND_INVALID(_handle) { if ((_handle) != INVALID_HANDLE_VALUE) { CloseHandle((_handle)); (_handle) = INVALID_HANDLE_VALUE; } }
#define FREE_AND_NULL(_p) { if ((_p)) { free((_p)); (_p) = NULL; } }
//
// 枚举设备
//
int EnumDevice();

//
// 取得读写控制的句柄
//
int GetIoHandle(PDEV_INFO di);

//
// 根据序号取得设备信息
//
PDEV_INFO GetDevInfoByNumber(int number);

// 初始化设备管理
VOID InitDevManager();
// 关闭设备操作句柄
VOID CloseIoHandle(PDEV_INFO di);
// 启动中断接收处理
int IntRecvStart(PDEV_INFO di, FC_NP_RECV_FUNCPTR func);
// 停止中断接收处理
int IntRecvStop(PDEV_INFO di);
// 启动中断消息处理
int IntEvtStart(PDEV_INFO di, FC_INT_FUNCPTR func);
// 停止中断消息处理
int IntEvtStop(PDEV_INFO di);
// 中断接收处理回调例程
UINT CALLBACK IntRecvCallBack(PVOID context);
// 中断消息处理回调例程
UINT CALLBACK IntEvtCallBack(PVOID context);

#ifdef __cplusplus
}
#endif