#pragma once

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// 类型定义
///////////////////////////////////////////////////////////////////////////////
typedef int            FCINT;
typedef unsigned int   FCUINT;
typedef unsigned char  FCUCHAR;
typedef int           *FCHANDLE;

//
// 接收回调定义
//
typedef FCUINT (*FC_NP_RECV_FUNCPTR)(FCHANDLE hDev, void *buf, FCUINT length);

//
// 中断回调定义
//
typedef FCUINT (*FC_INT_FUNCPTR)(FCHANDLE hDev, FCUINT intCode, FCUINT param0);

///////////////////////////////////////////////////////////////////////////////
// 常量定义
///////////////////////////////////////////////////////////////////////////////
#define FC_SUCCESS                      0x00000000
#define FC_FAILURE                      0x00000001
#define FC_INVALID_HANDLE               0x00000002
#define FC_INVALID_PARAMETER            0x00000003
#define FC_INVALID_DEV_STATE            0x00000004
#define FC_ENUM_DEV_FAILED              0x00000005
#define FC_OPEN_DEV_FAILED              0x00000006
#define FC_GET_DEV_INFO_FAILED          0x00000007
#define FC_GET_IO_HANDLE_FAILED         0x00000008
#define FC_DEV_READ_FAILED              0x00000009
#define FC_DEV_WRITE_FAILED             0x0000000A
#define FC_DEV_IOCTRL_FAILED            0x0000000B
#define FC_WAIT_OBJECT_FAILED           0x0000000C
#define FC_IOCTRL_RESP_NG               0x0000000D
#define FC_DEV_START_THREAD_FAILED      0x0000000E
#define FC_DEV_STOP_THREAD_FAILED       0x0000000F
#define FC_DEV_CREATE_EVENT_FAILED      0x00000010
#define FC_DEV_STATE_MONITOR            0x00000011

// 帧签名定义
#define FRAME_CFGID                     0x000000FC
#define FRAME_MONITORID                 0x000000FB

// 帧错误定义
#define FRAME_FLAG_CRC_ERR              0x00000001
#define FRAME_FLAG_UNDERSIZE            0x00000002
#define FRAME_FLAG_OVERSIZE             0x00000004
#define FRAME_FLAG_NO_EOF_ERR           0x00000008
#define FRAME_FLAG_DISP_ERR             0x00000010
#define FRAME_FLAG_CODING_ERR           0x00000020

// 中断子码定义
#define IC_VOLTAGE_SUCCESS              0x100      // 电压从错误值变为正常值
#define IC_VOLTAGE_FAILED               0x101      // 电压错误
#define IC_TEMP_SUCCESS                 0x102      // 温度从错误值变为正常值
#define IC_TEMP_FAILED                  0x103      // 温度错误
#define IC_LINK_STATUS_SUCCESS          0x104      // link状态从错误值变为正常值
#define IC_LINK_STATUS_FAILED           0x105      // link状态错误
#define IC_IO_BUF_WRITE_FAILED          0x106      // 收发缓冲区写错误
#define IC_IO_BUF_READ_FAILED           0x107      // 收发缓冲区读错误

//
// 手动自检结果
//
typedef struct _FC_BIT_RESULT_MANUAL {
    FCUINT flash;       /* flash读写 */
    FCUINT buffer;		/* 收发缓冲区读写 */
    FCUINT temperature; /* 温度 */
    FCUINT voltage;     /* 电压 */
} FC_BIT_RESULT_MANUAL, *PFC_BIT_RESULT_MANUAL;

//
// 时间结构体
//
typedef struct _FCTime {
    FCUINT hour;        /*时*/
    FCUINT minute;      /*分*/
    FCUINT second;      /*秒*/
    FCUINT millisecond; /*毫秒*/
    FCUINT microsecond; /*微秒*/
    FCUINT nanosecond;  /*纳秒*/
} FCTime, *PFCTime;

//
// 端口统计信息
//
typedef struct _PORT_STATISTICS_INFO {
    UINT64 RxUndersizeFrameCnt;
    UINT64 RxOversizeFrameErrCnt;
    UINT64 RxAllFrameCnt;
    UINT64 RxValidFrameCnt;
    UINT64 RxWordCnt;
    UINT64 RxRRDYCnt;
    UINT64 RxKErrCnt;
    UINT64 LinkChgUp2DownCnt;
    UINT64 TxAllFrameCnt;
    UINT64 TxValidFrameCnt;
    UINT64 TxWordCnt;
    UINT64 TxRRDYCnt;
    UINT64 TxKErrCnt;
} PORT_STATISTICS_INFO, *PPORT_STATISTICS_INFO;

//
// 记录头定义
//
typedef struct _FCM_RECORD_HEADER
{
    UINT32 length;    /*记录头+帧长度(包括SOF CRC EOF)的字节数*/
    UINT32 flag;      /*错误标记*/
    UINT32 cfgID;     /*固定值0xFC000000*/
    UINT32 monitorID; /*固定值0xFB000000*/
} FCM_RECORD_HEADER, *PFCM_RECORD_HEADER;

///////////////////////////////////////////////////////////////////////////////
// 设备管理接口
///////////////////////////////////////////////////////////////////////////////
//
// 打开设备
//
FCUINT FCM_DevOpen(
    FCHANDLE *hDev,
    FCUINT DevId
);

//
// 关闭设备
//
FCUINT FCM_DevClose(
    FCHANDLE hDev
);

//
// 使能设备
//
FCUINT FCM_DevEnable(
    FCHANDLE hDev,
    FCUINT fcid,
    FCUINT credit_num
);

//
// 复位设备
//
FCUINT FCM_DevReset(
    FCHANDLE hDev
);

//
// 获取设备的N端口状态
//
FCUINT FCM_DevGetState(
    FCHANDLE hDev,
    FCUINT *state
);

//
// 获取设备的N端口版本号
//
FCUINT FCM_DevGetVersion(
    FCHANDLE hDev,
    FCUINT *version
);

//
// 注册中断接收回调函数
//
FCUINT FCM_DevRegMsgHandler(
    FCHANDLE hDev,
    FC_NP_RECV_FUNCPTR func
);

//
// 注销中断接收回调函数
//
FCUINT FCM_DevUnRegMsgHandler(
    FCHANDLE hDev
);

//
// 注册事件中断回调函数
//
FCUINT FCM_DevRegEvtHandler(
    FCHANDLE hDev,
    FC_INT_FUNCPTR func
);

//
// 注销事件中断回调函数
//
FCUINT FCM_DevUnRegEvtHandler(
    FCHANDLE hDev
);

//
// 取得统计信息
//
FCUINT FCM_GetNStatistics(
    FCHANDLE hDev,
    PORT_STATISTICS_INFO *stat
);

//
// 启动设备的N端口BIT操作
//
FCUINT FCM_IBit(
    FCHANDLE hDev,
    FC_BIT_RESULT_MANUAL *bitResult
);

//
// 获取设备温度
//
FCUINT FCM_GetTemp(
    FCHANDLE hDev,
    FCUINT *temperature
);

//
// 获取设备电压
//
FCUINT FCM_GetVoltage(
    FCHANDLE hDev,
    FCUINT *voltage
);

//
// 获取设备工作状态
//
FCUINT FCM_GetWorkStatus(
    FCHANDLE hDev,
    FCUINT *status
);

///////////////////////////////////////////////////////////////////////////////
// 通信管理接口
///////////////////////////////////////////////////////////////////////////////
//
// 请求有数据的缓冲区
//
FCUINT FCM_RecvData(
    FCHANDLE hDev,
    void **ppBuffer,
    FCUINT *nLen
);

//
// 释放接收缓冲区
//
FCUINT FCM_ReleaseBuf(
    FCHANDLE hDev,
    void *pBuffer
);

///////////////////////////////////////////////////////////////////////////////
// 时统管理接口
///////////////////////////////////////////////////////////////////////////////
//
// 获取设备时间
//
FCUINT FCM_TM_GetRtc(
    FCHANDLE hDev,
    FCTime *time
);

//
// 设置设备时间
//
FCUINT FCM_TM_SetRtc(
    FCHANDLE hDev,
    FCTime *time
);

//
// 开始监控
//
FCUINT FCM_DevStartMonitor(
    FCHANDLE hDev
);

//
// 停止监控
//
FCUINT FCM_DevStopMonitor(
    FCHANDLE hDev
);

//
// 打印驱动的调试信息
//
FCUINT FCM_DBG_DrvStastics(
    FCHANDLE hDev
);

#ifdef __cplusplus
}
#endif