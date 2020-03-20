#ifndef __FC_UTILITY_H__
#define __FC_UTILITY_H__

#include <vxworks.h>

/*类型定义*/
typedef unsigned char   FCUCHAR;
typedef unsigned short  FCUSHORT;
typedef unsigned int      FCUINT;
typedef unsigned long   FCULONG;
typedef int                     FCINT;
typedef short                 FCSHORT;
typedef int                    *FCHANDLE;

/* 最大支持4个设备 */
#define MAX_DEVICE_NUM              4
/* 每个设备最大支持2个端口 */
#define MAX_PORT_NUM                  2

#define FC_SUCCESS                        0x00000000 /* 成功*/
#define FC_FAILURE                          0x00000001 /* 错误 */
#define FC_PARAMS_INVALID          0x00000002 /* 无效的参数  */
#define FC_LINK_DOWN                  0x00000003 /*端口linkdown*/
#define FC_INITIALISE_FAIL              0x00000004 /* 初始化失败 */
#define FC_SELF_CHECK_FAIL          0x00000005 /* 自检失败*/
#define FC_INVALID_OP                  0x00000006 /* 无效的操作，通常不满足执行条件  */
#define FC_DEV_CLOSED                 0x00000007 /* 设备已经关闭 */
#define FC_RECV_NO_DATA            0x00000008 /* 没有收到数据 */

/*自检返回值*/
#define BIT_SUCCESS                      0
#define BIT_FAILURE                        1

/*中断子码定义*/
/*电压从错误值变为正常值*/
#define IC_VOLTAGE_SUCCESS    0x100
/*电压错误*/
#define IC_VOLTAGE_FAILED          0x101
/*温度从错误值变为正常值*/
#define IC_TEMP_SUCCESS            0x102
/*温度错误*/
#define IC_TEMP_FAILED                  0x103
/*link状态从错误值变为正常值*/
#define IC_LINK_STATUS_SUCCESS 0x104
/*link状态错误*/
#define IC_LINK_STATUS_FAILED  0x105

/*扩大1000倍避免使用浮点*/
/*电压正常值*/
#define SC_VOLTAGE_VALUE            1000
/*电压阈值*/
#define SC_VOLTAGE_THRESHOLD   200
/*温度正常值*/
#define SC_TEMP_VALUE                  30000
/*温度阈值*/
#define SC_TEMP_THRESHOLD         70000

#define PORT_SPEED_1G                  1
#define PORT_SPEED_2G                  2

/* 接收回调定义 */
typedef unsigned int (* FC_NP_RECV_FUNCPTR)(INT32 *hDev, void *pBuffer, UINT nLen);

/* 设备配置参数 */
typedef struct _DEV_CONFIG
{
    INT32 fcid;
    INT32 credit_num;         /* 信用 1-16 */
    INT32 speed;                  /* 速率 0 自适应 1-1Gbps 2-2Gbps */
    INT32 did_filter_enab;    /* 接收方向DID过滤使能 */
    INT32 e_d_tov;      /* e_d_tov时间，单位是毫秒 */
    INT32 redundant_enab; /* 冗余使能 0-禁止 1-使能 */
    INT32 time_out;             /* 超时覆盖的时间，单位是毫秒 */
	FCUINT qdrBufUnitSize;     /*QDR每一小块BUF的大小*/
} DEV_CONFIG, *PDEV_CONFIG;

/* 时间结构体 */
typedef struct _FCTime {
    FCUINT hour;               /* 时  */
    FCUINT minute;           /* 分   */
    FCUINT second;          /* 秒   */
    FCUINT millisecond;     /* 毫秒 */
    FCUINT microsecond;  /* 微秒 */
    FCUINT nanosecond;   /* 纳秒 */
} FCTime, *PFCTime;

/* 日期结构体 */
typedef struct _FCDate {
    FCUINT year;         /*年*/
    FCUINT month;     /*月*/
    FCUINT day;          /*日*/
} FCDate, *PFCDate;

#endif /* __FC_UTILITY_H__ */
