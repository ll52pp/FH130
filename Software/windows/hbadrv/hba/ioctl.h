/*++
文件名
    ioctl.h

描述
    设备控制命令
--*/

#ifndef __IOCTL_H__
#define __IOCTL_H__

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
// 打开卡
//
VOID IoCtrlDevOpen(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 关闭卡
//
VOID IoCtrlDevClose(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 配置设备
//
VOID IoCtrlDevEnab(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 设备复位
//
VOID IoCtrlDevReset(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 获取设备状态
//
VOID IoCtrlDevGetState(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 获取设备版本号
//
VOID IoCtrlDevGetVersion(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 注册接收回调例程
//
VOID IoCtrlDevRegRecvHandler(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 注销接收回调例程
//
VOID IoCtrlDevUnRegRecvHandler(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 注册事件回调例程
//
VOID IoCtrlDevRegEvtHandler(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 注销事件回调例程
//
VOID IoCtrlDevUnRegEvtHandler(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 获取设备统计信息
//
VOID IoCtrlDevGetStatistics(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 获取设备自检
//
VOID IoCtrlDevIBit(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 获取设备温度
//
VOID IoCtrlDevGetTemperature(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 获取设备电压
//
VOID IoCtrlDevGetVoltage(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 获取设备工作状态
//
VOID IoCtrlDevGetWorkStatus(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 获取RTC
//
VOID IoCtrlDevGetRtc(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 设置RTC
//
VOID IoCtrlDevSetRtc(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 监控开始
//
VOID IoCtrlDevMonitorStart(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 监控停止
//
VOID IoCtrlDevMonitorStop(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf);

//
// 对齐QDR buf的字节数
//
INT32 AlignQdrBufSize(IN INT32 size);

//
// 配置Qdr buffer
//
VOID IoCtrlConfigQdrBufParam(IN PFDO_DATA fdoData);
//
// 分配链表头
//
NTSTATUS IoCtrlAllocateListHeader(IN PFDO_DATA fdoData);

//
// 分配commonbuffer
//
NTSTATUS IoCtrlAllocateCommonBuffer(IN PFDO_DATA fdoData);

//
// 向FPGA注册DMA缓冲区
//
VOID IoCtrlRegisterDmaBuf(IN PFDO_DATA fdoData);

//
// 线程启动
//
NTSTATUS IoCtrlThreadStart(IN PFDO_DATA fdoData);

//
// 线程停止
//
NTSTATUS IoCtrlThreadStop(IN PFDO_DATA fdoData);

//
// 复位FPGA
//
INT32 IoCtrlReset(IN PFDO_DATA fdoData, IN INT32 mac_off_line);

//
// 释放dma缓冲区，解除R3映射关系
//
VOID IoCtrlFreeCommonBuffer(IN PFDO_DATA fdoData);

//
// 释放链表控制头
//
VOID IoCtrlFreeListHeader(IN PFDO_DATA fdoData);

//
// 释放中断接收响应的资源
//
VOID IoCtrlFreeIntRecv(IN PFDO_DATA fdoData);

//
// 释放中断事件响应的资源
//
VOID IoCtrlFreeIntEvt(IN PFDO_DATA fdoData);

//
// 周期自检的回调例程
//
KSTART_ROUTINE PeriodSelfCheckCallBack;

// 检查端口的状态
VOID IoCtrlCheckPortStatus(IN PFDO_DATA fdoData, IN ULONG *prev_p0_status, IN ULONG *prev_p1_status);

EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL EvtIoDeviceControl;

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, EvtIoDeviceControl)
#endif

#endif  // __IOCTL_H__