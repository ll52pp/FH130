#ifndef _HBA_H
#define _HBA_H

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus */

#define HBA_INCLUDE_ELS                          /*包含ELS模块*/
#define HBA_INCLUDE_FLASH                        /*包含FLASH模块*/

#define USE_MSG_COVER                            /*支持消息覆盖*/
#define USE_MSG_DISCARD                          /*支持消息丢弃*/
#define USE_IU_TIMEOUT                           /*支持IU接收过程中超时丢弃*/

#define USE_SEND_SHARE_BUFFER                    /*发送使用share buffer*/

#include <vxworks.h>
#include "d_list.h"
#include "list.h"
#include "fc_asm.h"
#include "fc_api.h"

#ifdef HBA_INCLUDE_ELS
#include "hba_els.h"
#endif

/******************** typedefs *****************************************/
#ifdef VXWORKS
#ifndef __INCvxTypesOldh
typedef long long      INT64;        /*有符号64bit*/
typedef unsigned long long UINT64;   /*无符号64bit*/
typedef signed int     INT32;        /*有符号32bit*/
typedef unsigned int   UINT32;       /*无符号32bit*/
typedef signed short   INT16;        /*有符号16bit*/
typedef unsigned short UINT16;        /*无符号16bit*/
typedef signed char    INT8;          /*有符号8bit*/
typedef unsigned char  UINT8;         /*无符号8bit*/
typedef    int            BOOL;          /* BOOL类型 */

typedef void           VOID;         /* VOID类型 */

#endif    /* __INCvxTypesOldh */
#endif    /* VXWORKS */


typedef float          FLOAT;         /* 浮点类型*/
typedef unsigned       UBIT;          /*位域定义*/
typedef INT32 *        PINT32;        /*有符号32bit指针类型*/
typedef UINT32 *       PUINT32;       /*无符号32bit指针类型*/
typedef INT16 *        PINT16;        /*有符号16bit指针类型*/
typedef UINT16 *       PUINT16;       /*无符号16bit指针类型*/
typedef INT8 *         PINT8;         /*有符号8bit指针类型*/
typedef UINT8 *        PUINT8;        /*无符号8bit指针类型*/
typedef BOOL           BOOLEAN;       /* 布尔类型 */
typedef void  *        PVOID;         /* PVOID类型 */

/* 版本号定义 */
#define MAJOR_VER      1
#define MINOR_VER      0
#define FIRMWARE_VER   1



#define DMA_BUF_MALLOC     cacheDmaMalloc
#define DMA_BUF_FREE     cacheDmaFree

#ifdef AE653_BUILD

#define HBA_MALLOC         cacheDmaMalloc
#define HBA_MEM_FREE     cacheDmaFree

#else

#define HBA_MALLOC         malloc
#define HBA_MEM_FREE     free

#endif

#if 1
#define HBA_CACHE_INVAL(address, len)   cacheInvalidate(DATA_CACHE, (address), len)
#else
#define HBA_CACHE_INVAL(address, len)
#endif

#if 1
#define HBA_CACHE_FLUSH(address, len)      cacheFlush (DATA_CACHE, (address), (len))
#else
#define HBA_CACHE_FLUSH(address, len)
#endif

#define __DEBUG
#ifdef __DEBUG
#define ASSERT(expr) { if (!(expr)) logMsg("assert:%s(%u)\n", (int)__FILE__, __LINE__, 0, 0, 0, 0); }
#else
#define ASSERT(expr)
#endif



#define  HBA_RCV_TASK_NAME                  "tHbaRcv"
#define  HBA_RCV_TASK_PRIORITY              50
#define  HBA_RCV_TASK_STACKSIZE             40960

#define  HBA_SENT_CHECK_TASK_NAME           "tHbaSentChk"
#define  HBA_SENT_CHECK_TASK_PRIORITY       55
#define  HBA_SENT_CHECK_TASK_STACKSIZE      40960

#define  HBA_BIT_TASK_NAME                  "tHbaBit"
#define  HBA_BIT_TASK_PRIORITY              60
#define  HBA_BIT_TASK_STACKSIZE             40960

#define  HBA_PERIOD_CHECK_TASK_NAME         "tHbaPrdChk"
#define  HBA_PERIOD_CHECK_TASK_PRIORITY     60
#define  HBA_PERIOD_CHECK_TASK_STACKSIZE    40960

/* 周期发送ELS帧 */
#define  HBA_ELS_CYCLE_CHECK_TASK_NAME       "tHbaElsCycleCheck"
#define  HBA_ELS_CYCLE_CHECK_TASK_PRIORITY   60
#define  HBA_ELS_CYCLE_CHECK_TASK_STACKSIZE  40960

/* ELS接收回调 */
#define  HBA_ELS_RECV_TASK_NAME             "tHbaElsRecv"
#define  HBA_ELS_RECV_TASK_PRIORITY         60
#define  HBA_ELS_RECV_TASK_STACKSIZE        40960

#ifdef AE653_BUILD
#define MAX_DEVICE_NUM                        1
#else
#define MAX_DEVICE_NUM                        4
#endif


#define FC_PORT_0                            0
#define FC_PORT_1                            1
#define FC_PORT_NUM_MAX                        2

#define IO_STATE_MODE_RAW                   1 /*发送接收RAW数据帧*/
#define IO_STATE_MODE_ASM                   2 /*发送接收ASM数据*/

/* 优先级 */
#define PRIORITY_LEVEL_HIGH_ASM_MSG            PRIORITY_LEVEL_3
#define PRIORITY_LEVEL_LOW_ASM_MSG            PRIORITY_LEVEL_0

#define PRIORITY_LEVEL_STREAM_MSG            PRIORITY_LEVEL_0
#define PRIORITY_LEVEL_RAW_MSG                PRIORITY_LEVEL_1
#define PRIORITY_LEVEL_EVENT_MSG            PRIORITY_LEVEL_2
#define PRIORITY_LEVEL_URGENCY_MSG            PRIORITY_LEVEL_3



/* DMA 发送和接收 buffer有关定义 */

/* 发送 Buffer 统一成一个长度 */
#define MAX_SEND_BUFER_LEN                    (63 * 1024)    /*最大 511*128 字节, 约63K*/

/* 接收 Buffer的大小跟个数根据优先级不同来分别定义 */
/* 接收 Buffer大小允许设置的范围从4K - 128K, 最好设置成4K的倍数 */
#define MAX_RECV_BUFER_LEN_P0                 (64*1024)    /* ASM流， 以K对齐 */
#define MAX_RECV_BUFER_LEN_P1                 (8*1024)    /* ELS, 最小4K, 以K对齐 */
#define MAX_RECV_BUFER_LEN_P2                 (4*1024)    /* 事务块，最小4K, 以K对齐 */
#define MAX_RECV_BUFER_LEN_P3                 (4*1024)    /* 紧急块，最小4K, 以K对齐 */

#define MAX_RECV_BUFER_LEN_ELS            MAX_RECV_BUFER_LEN_P1

#ifdef AE653_BUILD

#define MAX_RECV_BUFFER_NUM_P0                32 /*156*/        /* 最大1024 */
#define MAX_RECV_BUFFER_NUM_P1              32
#define MAX_RECV_BUFFER_NUM_P2              32
#define MAX_RECV_BUFFER_NUM_P3                32

#define MAX_RECV_BUFFER_NUM                 (MAX_RECV_BUFFER_NUM_P0 + MAX_RECV_BUFFER_NUM_P1 + MAX_RECV_BUFFER_NUM_P2 + MAX_RECV_BUFFER_NUM_P3)
#define MAX_SEND_BUFFER_NUM                 256

#else

#define MAX_RECV_BUFFER_NUM_P0                512        /* 最大1024 */
#define MAX_RECV_BUFFER_NUM_P1              128
#define MAX_RECV_BUFFER_NUM_P2              128
#define MAX_RECV_BUFFER_NUM_P3                128

#define MAX_RECV_BUFFER_NUM                 (MAX_RECV_BUFFER_NUM_P0 + MAX_RECV_BUFFER_NUM_P1 + MAX_RECV_BUFFER_NUM_P2 + MAX_RECV_BUFFER_NUM_P3)
#define MAX_SEND_BUFFER_NUM                 512

#endif


/* 系统提供的最大DMA缓存数，不要修改! */
#define MAX_TX_DMA_BUF_NUM            4096
#define MAX_RX_DMA_BUF_NUM_PER_PRIO    1024

#define MAX_BYTES_PER_DMA            128


#define SEND_BUFFER_ALLOCATEE_ASM             0
#define SEND_BUFFER_ALLOCATEE_RAW             256
#define SEND_BUFFER_ALLOCATEE_SHARE         0xFFFFFFFF

#define SEND_BUFFER_SIGNATURE                0xFECAFECA
#define RECV_BUFFER_SIGNATURE                0xFECDFECD

#define FC_MINOR_SCHEME_SIZE               (32 * 1024) /*每个配置块的字节数*/
#define FC_MAJOR_SCHEME_SIZE               (FC_MINOR_SCHEME_MAX * FC_MINOR_SCHEME_SIZE) /*每个蓝图的字节数*/

/* 通道数定义 */
#define MAX_RECV_CHANNEL_NUM                256
#define MAX_SEND_CHANNEL_NUM                256

#define INVALID_CHANNEL_NO                    (-1)
#define RAW_CHANNNEL_NO                        256

#define MAX_PRESERVE_MSG_COUNT                     4    /* 每个(非流)通道允许保留的最大消息数, 超过后会导致消息覆盖或者丢弃 */
#define MAX_PRESERVE_STRM_IU_COUNT                 2    /* 每个流通道允许保留的最大IU数, 超过后会导致消息覆盖或者丢弃 */
#define MAX_PRIVATE_SEND_BUFFER_NUM_PER_MSG        4    /* 每个通道的私有的发送buffer数， 目前不用 */

#define INVALID_ASM_MSG_ID                  0


#define FCID_TYPE_INVALID               0           /* 无效地址 */
#define FCID_TYPE_SINGLE                1           /* 单播类型 */
#define FCID_TYPE_MULTICAST             2           /* 多播类型 */
#define FCID_TYPE_BROADCAST             3           /* 广播类型 */

#define FCID_BROADCAST                  0xFFFFFF  /*广播号*/
#define FCID_MULTICAST_MIN              0xFFFB00  /*组播号开始*/
#define FCID_MULTICAST_MAX              0xFFFBFF  /*组播号结束*/
#define FCID_SINGLECASE_MAX                0xFF0000  /*最大单播地址*/

/* IU buffer 收发及Buffer有关定义 */
#define MAX_IU_LEN                            0x1000000

#ifdef USE_IU_TIMEOUT
#define RECV_IU_TIMEOUT                     2000    /* IU接收超时定义，单位: ms */
#endif

/* BIT 测试结果 */
#define BIT_SUCCESS                              0
#define BIT_FAILURE                              1

/* 速率 */
#define PORT_SPEED_1G                            1
#define PORT_SPEED_2G                            2

/* buffer使用后FPGA是否主动丢包*/
#define MSG_DISCARD_DISABLE                        0     /* 不丢包 */    
#define MSG_DISCARD_ENABLE                        1     /* 丢包 */    

/*扩大1000倍避免使用浮点*/
#define SC_VOLTAGE_VALUE                         1000       /*电压正常值*/
#define SC_VOLTAGE_THRESHOLD                     200        /*电压阈值*/
#define SC_TEMP_VALUE                            30000      /*温度正常值*/
#define SC_TEMP_THRESHOLD                        90000      /*温度阈值*/

#define BIT_TYPE_MANULA                          0          /*手动自检*/
#define BIT_TYPE_POWER                           1          /*上电自检*/

#define FC_SELF_CHECK_PERIOD                     200        /*周期任务的周期值，毫秒*/


/*蓝图在FLASH 存放的基地址*/
#define FC_SCHEME_ADDRESS                        0


/* FC_MLS层驱动软件返回值定义 */
#define DEV_SUCCESS                     0   /* 设备操作成功 */
#define DEV_STS_ERR                    -1   /* 设备状态错误，通常由主机命令执行错误，复位错误引起 */
#define DEV_PORTID_ERR                 -2   /* 设备端口ID标识错误  */
#define DEV_HANDLE_ERR                 -3   /* 设备句柄错误 */
#define DEV_HEART_ERR                  -4   /* 设备心跳异常  */
#define DEV_CMD_INVALID                -5   /* 设备主机命令无效  */
#define DEV_CMD_FAIL                   -6   /* 设备主机命令未成功完成  */
#define DEV_CMD_TIMEOUT                -7   /* 设备主机命令超时  */
#define DEV_WD_FAILED                  -8   /* 保留 */
#define DEV_INVALID_OP                 -9   /* 设备无效操作，通常不满足执行条件  */
#define DEV_RST_CONFIG_ERR             -10  /* 设备复位收发控制逻辑异常  */
#define DEV_INTERFACE_ERR              -11  /* 设备主机接口异常  */
#define DEV_PARAMS_INVALID             -12  /* 设备操作参数无效  */
#define DEV_ALL_CLOSED                 -13  /* 设备关闭  */
#define DEV_IS_BUSY                    -14  /* 设备正在使用  */
#define DEV_NUMBER_INVALID             -15  /* 设备编号无效  */
#define DEV_INTCALLBACK_INVALID        -16  /* 设备中断回调函数无效  */
#define DEV_CONFIG_DATA_INVALID        -17  /* 网络配置表无效 */
#define DEV_FLASH_WR_FAIL               -18  /* FLASH WR 失败 */
#define DEV_NOT_SUPPORT                      -19  /* 功能不支持 */
#define DEV_PORT_LINK_DOWN               -20  /* 端口链路状态down */
#define DEV_WDT_PERIOD_ERR             -21    /* WDT 周期配置错误*/
#define DEV_OTHER_FAILURE              -99  /* 设备操作其他错误  */

#define ASM_MSG_ID_INVALID             -101 /* 通信消息ID无效  */
#define RAW_MSG_LEN_INVALID            -102 /* 通信消息长度无效 */
#define ASM_PARAMS_UNMATCH             -103 /* 通信参数匹配错误  */
#define ASM_STMSG_NUM_OVER             -104 /* 数据块消息发送配置表数目错误  */
#define ASM_LTMSG_NUM_OVER             -105 /* 流数据块消息发送配置表数目错误  */
#define ASM_SRMSG_NUM_OVER             -106 /* 数据块消息接收配置表数目错误  */
#define ASM_LRMSG_NUM_OVER             -107 /* 流数据块消息接收配置表数目错误  */
#define ASM_MSG_BUFER_FULL             -108 /* 消息发送缓冲区满  */
#define RAW_MSG_BUFFER_EMPTY           -109 /* 消息发送缓冲区空  */
#define ASM_BUFER_FREE_FAIL            -110 /* 消息收发缓冲区释放失败  */
#define ASM_BUFER_ALLOC_FAIL           -111 /* 消息收发缓冲区申请失败  */
#define ASM_OP_INVALID                 -112 /* 流数据块消息接收控制操作无效 */
#define RAW_PARAMS_INVALID             -113 /* 通信参数无效  */
#define ASM_MSG_UNACK                  -114 /* 保留 */
#define ASM_ACKMSG_ERROR               -115 /* 应答消息配置错误  */
#define ASM_BLK_MSG_LOGIC_ERR          -116 /* 保留  */
#define ASM_STREAM_RXBUF_REG_ERR       -117 /* 流数据块消息接收缓冲区注册错误  */
#define ASM_STREAM_RXBUF_UPDATE_ERR    -118 /* 流数据块消息接收缓冲区刷新错误  */
#define ASM_STREAM_RXBUF_COMPLETE_ERR  -119 /* 流数据块消息接收缓冲区切换错误  */
#define ASM_TXBUFF_ID_ERROR            -120  /* 流数据块消息发送缓冲区ID错误  */
#define RAW_RECV_TIMEOUT               -121  /* 接收数据超时  */
#define RAW_RECV_NO_DATA               -122  /* 没有数据被接收到  */
#define RAW_OTHER_FAILURE              -199 /* 通信消息处理其他错误  */

#define CLK_SYNC_MODE_INVALID          -201 /* 时钟同步角色无效 */
#define CLK_SYNC_PERIOD_INVALID        -202 /* 时钟同步周期无效 */
#define CLK_SYNC_BASE_INVALID          -203 /* 时钟同步基值无效 */
#define CLK_PARAMS_INVALID             -204 /* 时钟同步参数无效 */
#define CLK_SYS_RTC_ERR                -205 /* 系统RTC时钟错误,通常发生在日历时间刷新时发现新RTC比旧RTC小 */
#define CLK_SYNC_OTHER_FAILURE         -299 /* 时钟同步其他错误 */

#define NMG_MODE_INVALID               -301 /*网络管理模式错误*/
#define NMG_PARAMS_INVALID             -302 /*网络管理参数无效*/
#define NMG_INTERFACE_ERROR            -303 /*网络管理接口错误*/
#define NMG_OTHER_FAILURE              -399 /*其它网络管理错误*/

#if 1/*liujin added for rtc*/
#define CLK_SYNC_ROLE_SERVER_MASTER       1 /*网络时钟服务器，模块时钟客户端*/
#define CLK_SYNC_ROLE_CLIENT              2 /*网络时钟客户端*/
#endif

/* 和FPGA交互的读写控制域的定义 */
/* TX 方向 */
typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG reserve : 4; /* [28:31] : RW reserve */
        ULONG mode    : 1; /* [   27] : RW 0-stream 1-block */
        ULONG sop     : 1; /* [   26] : RW eop */
        ULONG eop     : 1; /* [   25] : RW sop */
        ULONG length  : 25;/* [ 0:24] : RW data length of buffer,unit in byte */
#else
        ULONG length  : 25;/* [ 0:24] : RW data length of buffer,unit in byte */
        ULONG eop     : 1; /* [   25] : RW sop */
        ULONG sop     : 1; /* [   26] : RW eop */
        ULONG mode    : 1; /* [   27] : RW 0-stream 1-block */
        ULONG reserve : 4; /* [28:31] : RW reserve */
#endif
    } u;
    ULONG value;
} W0;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG l        : 1; /* [   31] : RW L */
        ULONG priority : 7; /* [24:30] : RW priority */
        ULONG length   : 24;/* [ 0:23] : RW total length */
#else
        ULONG length   : 24;/* [ 0:23] : RW total length */
        ULONG priority : 7; /* [24:30] : RW priority */
        ULONG l        : 1; /* [   31] : RW L */
#endif
    } u;
    ULONG value;
} W1;

typedef struct
{
    W0 w0;
    W1 w1;
} W_CTRL;

/* RX 方向 */
typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG sop         : 1; /* [    31] : RW sop */
        ULONG eop         : 1; /* [    30] : RW eop */
        ULONG seq_err     : 1; /* [    29] : RW block sequence error, fpga set */
        ULONG ox_id_err   : 1; /* [    28] : RW block oxid error, 没有使用 */        
        ULONG frame_err   : 1; /* [    27] : RW frame mac error, fpga set */
        ULONG reserve     : 7; /* [20:26] : RW data length(except rctrl 8byte) of buffer, fpga set; max 512K - 8 */
        ULONG length      : 20;/* [ 0:19] : RW data length(except rctrl 8byte) of buffer, fpga set; max 512K - 8 */
#else
        ULONG length      : 20;/* [ 0:19] : RW data length(except rctrl 8byte) of buffer, fpga set; max 512K - 8 */
        ULONG reserve     : 7; /* [20:26] : RW data length(except rctrl 8byte) of buffer, fpga set; max 512K - 8 */
        ULONG frame_err   : 1; /* [    27] : RW frame mac error, fpga set */
        ULONG ox_id_err   : 1; /* [    28] : RW block oxid error */
        ULONG seq_err     : 1; /* [    29] : RW block sequence error, fpga set */
        ULONG eop         : 1; /* [    30] : RW eop */
        ULONG sop         : 1; /* [    31] : RW sop */
#endif
    } u;
    ULONG value;
} R0;

typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG reserve      : 24;/* [ 8:31] : RW reserve */
        ULONG channel_num : 8; /* [ 0: 7] : RW channel num */
#else        
        ULONG channel_num : 8; /* [ 0: 7] : RW channel num */
        ULONG reserve     : 24;/* [ 8:31] : RW reserve */
#endif
    } u;
    ULONG value;
} R1;

typedef struct
{
    R0 r0;
    R1 r1;
} R_CTRL;

typedef struct
{
    UINT32 msgId;
    UINT32 did;
    UINT32 priority; /* 0~3 */

    UINT32 seqNo;
    UINT32 ackSeqNo;
        
    /* 发送空闲队列，每个通道至少有一个缓存作为专用，
    保证当共有的缓存被其他通道用完时，该通道也能申请到缓存*/
    LIST_STR list_send_idle_private;

    /* 发送buffer申请等待的信号量 */
    SEM_ID semSendBufferValid;
        
    /* 要发送的数据先挂到这个队列 */
    /* LIST_STR  list_toSend; */

    BOOL bIsStream;

    /* 统计数据 */
    UINT64 sendBuffers;
    UINT64 sendBytes;
} ASM_SEND_CHANNEL;

typedef struct
{
    /* 发送空闲队列，每个通道至少有一个缓存作为专用，
    保证当共有的缓存被其他通道用完时，该通道也能申请到缓存*/
    LIST_STR list_send_idle_private;

    /*发送buffer申请等待的信号量*/
    SEM_ID  semSendBufferValid;
    
    /*已经收到的数据先放到这里*/
    /*LIST_STR  list_toSend;*/
} RAW_SEND_CHANNEL;

typedef struct
{
    LIST_NODE node;
    UINT8  *pBuffer;
    UINT32  nBufSize;
    UINT32  nDataLen;
    UINT32  tickSOP;
    int        type;    /*IU_BUFFER_TYPE_DYNAMIC,  IU_BUFFER_TYPE_PRIVATE*/
    UINT32     Index;    /*type=IU_BUFFER_TYPE_PRIVATE, 指示使用该IU buffer的通道；
                      type=IU_BUFFER_TYPE_DYNAMIC，该字段无用*/
} IU_BUFFER;

typedef struct
{
    UINT32 msgId;
    UINT32 sid;
    UINT32 priority;            /*0-low, 3-high */
    UINT32 maxIUSize;
    BOOL   bIsStream;           /*TRUE - Stream channel, FALSE -- BLock Channel*/
    UINT32 nMaxReservedIUNum;
    
#ifdef USE_MSG_COVER
    BOOL bMsgCover;                /* 消息覆盖 */
#endif

    LIST_STR  list_recved;        /* 已经收到的数据先放到这里, 存放Recv Buffer  */
    SEM_ID    semListRecvedLock;/* 当需要对list_recved中的IU进行(多个buffer)操作时，对list_recved进行保护，期间不允许其他任务对该列表进行操作 */
    

    LIST_STR  list_currentIU;    /* 当前正在接收的IU */
    UINT32    tickSOP;            /* 当前IU 接收第一个帧的tick值 */
    UINT32    nIULen;
    UINT32    nIUCount;            /* list_recved 中存放的IU 个数 */    

    SEM_ID  semRecvBufferValid;    /* 接收buffer有效的信号量 */

    /* 统计值 */
    UINT64 totalIuCount;      /* 共收到的IU 个数 */
    UINT64 discardIuCount;  /* 丢掉的IU 个数 */
    UINT64 coverIuCount;      /* 覆盖的IU 个数 */
    UINT64 IuLenException;    /* IU长度异常的个数统计 */
    UINT64 IuSeqException;    /* IU Sequence的个数统计 */
    UINT64 IuTmroutException;/* IU长度异常的个数统计 */
    UINT64 recvBuffers;
    UINT64 recvBytes;
    UINT32 msg_recv_type;    /*1-中断0-查询*/
    
} ASM_RECV_CHANNEL;

typedef struct
{
    LIST_STR list_recved;        /* 已经收到的数据先放到这里 */
    SEM_ID   semRecvBufferValid;/* 接收buffer有效的信号量 */
} RAW_RECV_CHANNEL;

typedef struct
{
    UINT32 w0;        
    UINT32 w1;
    UINT8 data[0];    
} SEND_DMA_BUFFER;

typedef struct
{
    UINT32 signature;        
    struct tagSEND_BUFFER *pSendBuffer;
    UINT32 reserved1;    
    UINT32 reserved2; 
} SEND_DMA_BUFFER_HEADER;

typedef struct tagSEND_BUFFER
{
    LIST_NODE node;   /* must be the first field */
    UINT bufferIndex; /* FPGA buffer Index */
    SEND_DMA_BUFFER * pBuffer;
    UINT32 allocatee; /* 指定buffer由哪个分配队列来源，0~255 for ASM private, 256 for RAW private,  0xFFFFFFFF for share,  used for buffer recycle */    
    int    ch;          /* 使用该发送buffer的通道号,即申请该buffer的通道号， 0~255 for ASM private, 256 for RAW private,  -1 没有被使用 */
    BOOL bStream;      /* 是否为流发送， 对于流发送可以确认其序号 */
    UINT32 seqNo;     /* 发送的序号，用于流发送； 对于块发送，该字段无效，填为0 */
    /* UINT tickStamp; */
} SEND_BUFFER;

typedef struct
{
    UINT32 r0;        
    UINT32 r1;
    UINT8 data[0];    
} RECV_DMA_BUFFER;

typedef struct
{
    UINT32 signature;        
    struct tagRECV_BUFFER *pRecvBuffer;
    UINT32 reserved1;
    UINT32 reserved2;
} RECV_DMA_BUFFER_HEADER;


typedef struct tagRECV_BUFFER
{
    LIST_NODE node;   /* must be the first field */
    UINT bufferIndex; /* FPGA buffer Index */
    RECV_DMA_BUFFER *pBuffer;
    UINT32 priority;
    UINT32 bufferSize;
    /* UINT tickStamp; */
} RECV_BUFFER;

enum
{
    HBA_DEV_STATUS_NONE,
    HBA_DEV_STATUS_CREATED,
    HBA_DEV_STATUS_INITED,
    HBA_DEV_STATUS_STARTED
};

#define FPGA_STAT_TYPE_RECV_FRAME_NUM          0x1
#define FPGA_STAT_TYPE_RECV_IU_NUM             0x2
#define FPGA_STAT_TYPE_RECV_ERROR_IU_NUM       0x3
#define FPGA_STAT_TYPE_RECV_DISCARD_IU_NUM     0x4
#define FPGA_STAT_TYPE_RECV_INVALID_FRAME_NUM  0x5
#define FPGA_STAT_TYPE_SEND_FRAME_NUM          0xB
#define FPGA_STAT_TYPE_SEND_IU_NUM             0xC

#define FPGA_STAT_PORT_0_BASE           0x30
#define FPGA_STAT_PORT_1_BASE           0x10

#define PORT_STAT_RX_UNDERSIZE_FRAME     0x0
#define PORT_STAT_RX_OVERSIZE_FRAME     0x1
#define PORT_STAT_RX_ALL_FRAME             0x2
#define PORT_STAT_RX_VALID_FRAME         0x3
#define PORT_STAT_RX_FRAME_LEN             0x4
#define PORT_STAT_LNK_CHG_UP2DWN         0x5
#define PORT_STAT_RX_RRDY                 0x6
#define PORT_STAT_RX_K_ERR                 0x7
#define PORT_STAT_TX_ALL_FRAME             0x8
#define PORT_STAT_TX_VALID_FRAME         0x9
#define PORT_STAT_TX_FRAME_LEN             0xA
#define PORT_STAT_TX_RRDY                 0xB

/*本地统计信息*/
typedef struct
{
    FCUINT64 recvFrameNum;     /*1 接收帧数*/
    FCUINT64 recvIuNum;        /*2 接收IU个数*/
    FCUINT64 recvIuErrNum;     /*3 接收错误帧数 IU标记不匹配/CRC错误/其他错误，帧头错误等*/
    FCUINT64 recvIuDiscardNum; /*4 接收丢弃的IU个数 接收端配置了丢弃标记后，发生的丢弃的IU个数*/
    FCUINT64 recvIuInvalidNum; /*5 接收无效的帧数 ASMID没有配置过，但是收到了*/
    FCUINT64 sendFrameNum;     /*6 发送帧数*/
    FCUINT64 sendIuNum;        /*7 发送IU个数*/
} LocalStatisticsInfo;

typedef struct
{
    UINT64 recvFrameNumTotal;
    UINT64 recvIUNumTotal;
    UINT64 recvErrorIUNumTotal;
    UINT64 recvDiscardFrameNumTotal;    /* 不是Iu数而是帧数 */
    UINT64 recvInvalidFrameNumTotal;

    UINT64 sendFrameNumTotal;
    UINT64 sendIUNumTotal;
} FPGA_STATISTICS_INFO;

typedef struct
{
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
    
} PORT_STATISTICS_INFO;

typedef struct tagHBA_DEV_CB
{
    int                          status;
    
    UINT32                       deviceId;

    int                          BusNo;        /* bus number */
    int                          DeviceNo;    /* device number */
    int                          FuncNo;        /* function number */

    BOOL                         bUseInterrupt;

    UINT32                       configMode;
    UINT32                       majorScheme;
    UINT32                       minorScheme;
    CONFIG_BLOCK                 configBlock;

    FCUINT                       asmRunControl; /*ASM发送接收控制 0-禁止ASM发送接收 1-允许ASM发送接收*/

    UINT8                        *pMembaseCsr; /* the membase for FPGA config */
    
    UINT8                         irq;         /* Interrupt Request Level */
    UINT8                         reserved[3]; /* 使对齐 */
    
    UINT8                        *pSendDmaBufBaseAddr; /* send DMA buffer base address, should be uncachable */
    UINT8                        *pRecvDmaBufBaseAddr; /* send DMA buffer base address, should be uncachable */

    UINT8                        *pSendBufBaseAddr;    /* send buffer base address, be cachable */
    UINT8                        *pRecvBufBaseAddr;    /* recv buffer base address, be cachable */
    
    FC_ASM_RECVMSG_FUNCPTR        pRecvCallBackFunc;    /*ASM接收回调*/
    FC_INT_FUNCPTR                pIntCallbackFunc;             /*中断回调*/
    
    /* 发送空闲队列，公用 */
    LIST_STR                      list_send_idle_share;
    SEM_ID                        semSendShareBufferValid;

    /* 接收空闲队列， 该队列没有必要*/
    LIST_STR                      list_recv_idle_share;
    SEM_ID                        semRecvShareBufferValid;

    /* 已经发送，等待FPGA发送完毕的队列，跟FPGA有关 */
    LIST_STR                      list_SentWaitAck[MAX_PRIORITY_LEVEL_NUM];   

    /* 待接收队列, 等到FPGA接收，跟FPGA有关 */
    LIST_STR                      list_toRecv[MAX_PRIORITY_LEVEL_NUM];    
    SEM_ID                        semRecvListLock;

    /* 通道定义: 256个接收通道, 256个发送通道, 1个raw接收通道, 1个raw 发送通道 */
    RAW_SEND_CHANNEL              rawSendChannel;
    ASM_SEND_CHANNEL              asmSendChannels[MAX_SEND_CHANNEL_NUM];
    UINT                          asmSendChannelCount;
    RAW_RECV_CHANNEL              rawRecvChannel;
    ASM_RECV_CHANNEL              asmRecvChannels[MAX_RECV_CHANNEL_NUM];
    UINT                          asmRecvChannelCount;
    
#ifdef USE_IU_TIMEOUT    
    /* IU 接收timeout时间 */
    UINT32                        recvIUTimeoutTick;
#endif

    /* 链路状态 */
    UINT32                        linkStatus;
    UINT32                        linkStatusChgCount;
    BOOL                          bLinkStatusChecking;

    int                           RawDataBufOffset;
    UINT8                        *pRawDataBuf;
    
    /* 自检 */
    BOOL                          bBuildInTesting;
    FC_BIT_RESULT                 bitResult;
    
    /*停止设备标记*/
    BOOL bToStop;

    /*任务ID*/
    int                           recvTaskId;
    SEM_ID                        semRecv;
    
    int                           sentCheckTaskId;
    SEM_ID                        semSentCheck;
    
    int                           periodSelfCheckTaskId;
    SEM_ID                        semPeriodSelfCheck;
    
#ifdef HBA_INCLUDE_ELS
    int                           hbaElsCycleCheckTaskId;
    SEM_ID                        semElsCycleCheck;
    
    int                           hbaElsRecvTaskId;
    SEM_ID                        semElsRecv;

#endif
    
    /* ELS帧处理 */
    RAW_FRAME_CTRL                rawFrameCtrl;
    UINT8                        *pRawDataBlock;
    UINT32                        wdtLoaderPeriodEnab; /*加载周期使能控制*/
    
    UINT32                        wdtTimeoutFlag;      /*WDT超时上报中断已经上报的标记，WDT超时中断只上报一次*/
    
#if 0 /* Huilin */    
    
    UINT32                        recvE1_0203Flag;     /*收到NC发送的心跳帧的标记*/
#endif    
    UINT32                        ncFcid;              /*NC节点的FCID*/
    UINT32                        elsKeyRecvList[FC_ELS_KEY_COUNT];
    CYCLE_DESC                    cycleDesc[MAX_TIMER_NUM];
    FC_ELS_CONFIG                 elsConfig[FC_ELS_KEY_COUNT];
    FC_ELS_CONFIG                 elsRecvConfig; /* huilin */
    
    OnNetTbl                      onNetTbl;           /*上下网表*/
    SwLinkStatusTbl               swLinkStatusTbl; /*交换机广播的端口链路状态表*/
    SW_IMPSoftWareVersion         swAppVersion[FC_PORT_NUM_MAX]; /*交换机的应用软件信息*/
    SW_IMPSoftWareVersion         swBspVersion[FC_PORT_NUM_MAX]; /*交换机的BSP*/

    INT32                         wdtInitCounter;  /*NC节点等待网络中别的NC节点发送心跳帧的周期数*/
    UINT32                        NcLinkdownTimes;
    LocalStatisticsInfo           localStatisticsInfo;/*本地统计信息*/

    /*统计数据*/
    UINT64                        sentBytes;
    UINT64                        recvBytes;
    UINT64                           moveBytes;
    UINT64                        sentIUs;
    UINT64                        recvIUs;
    UINT64                        dicardIUs;       /* 丢弃的IU数  */
    UINT64                        coverIUs;         /* 覆盖的IU 个数 */
    UINT64                        exceptionIUs;   /* 覆盖的IU 个数 */
    UINT64                        sentRawBuffers;
    UINT64                        recvRawBuffers;
    UINT64                        sendBuffers;
    UINT64                        recvBuffers;
    UINT64                        sendCmptBuffers;    /* 确认发送成功的buffer数 */
    UINT64                        recvMoveBytes;
    
    SEM_ID                        semStatLock;
    FPGA_STATISTICS_INFO          fpgaStatInfo;
    PORT_STATISTICS_INFO          portStatInfo[FC_PORT_NUM_MAX];
}HBA_DEV_CB;

int hbaDevClearSendBufferInFPGA(HBA_DEV_CB *dc);
int hbaDevClearRecvBufferInFPGA(HBA_DEV_CB *dc);
int hbaDevAddSendBufferToFPGA(HBA_DEV_CB *dc, SEND_DMA_BUFFER * pDmaBuf, int index);
int hbaDevAddRecvBufferToFPGA(HBA_DEV_CB *dc, RECV_DMA_BUFFER * pDmaBuf, int priority, int index);
int hbaDevAddSendBufferToFPGASendFifo(HBA_DEV_CB *dc, SEND_BUFFER *pSendBuf);
int hbaDevAddRecvBufferToFPGARecvFifo(HBA_DEV_CB *dc, RECV_BUFFER *pRecvBuf);

/*创建设备*/
UINT32 hbaDevCreate(HBA_DEV_CB **pdc, UINT32 Device_Id);

/*打开设备*/
 UINT32 hbaDevOpen(HBA_DEV_CB **pdc, UINT32 Device_Id);
 
void hbaDevClose(HBA_DEV_CB *dc);
INT32 hbaDevDestroy(HBA_DEV_CB *dc);
UINT32 hbaDevCheckConfig(HBA_DEV_CB *dc);
INT32 hbaDevInitialize(HBA_DEV_CB *dc);
INT32 hbaDevGetDevState(HBA_DEV_CB *dc, UINT32 *cardSts, UINT32 count);
INT32 hbaDevGetVersion(HBA_DEV_CB *dc, UINT32 * version);
INT32 hbaDevRun(HBA_DEV_CB *dc);
UINT32 hbaDevStop(HBA_DEV_CB *dc, BOOL bForceOffLine);
INT32 hbaDevReset(HBA_DEV_CB *dc, BOOL bForceOffLine);
UINT32 hbaDevSendAsmMsg(HBA_DEV_CB *dc,  UINT32 msgID, UINT8 *pData, UINT32 length, int timeout);
UINT32 hbaDevSendRawMsg(HBA_DEV_CB *dc, UINT8 *pData, UINT32 length, int timeout);
UINT32 hbaDevRecvAsmMsg(HBA_DEV_CB *dc, UINT msgID, UINT8 *pMsg, UINT *nLen, int timeout);
INT32 hbaDevRecvRawMsg(HBA_DEV_CB *dc, UINT8 *pMsg, UINT *nLen, int timeout);
INT32 hbaDevRegMsgHandler(HBA_DEV_CB *dc, FC_ASM_RECVMSG_FUNCPTR func);
INT32 hbaDevUnRegMsgHandler(HBA_DEV_CB *dc);
void hbaDevClearDeviceStat(HBA_DEV_CB *dc);

INT32 hbaDevFlashConfig(HBA_DEV_CB *dc, CONFIG_BLOCK *cb, UINT32 majorSchemeNum, UINT32 minorSchemeNum);
void  hbaDevInitConfigDataForEnginMode(HBA_DEV_CB *dc);
INT32 hbaDevInitConfigDataForFlashMode(HBA_DEV_CB *dc);
INT32 hbaDevLoadConfig(HBA_DEV_CB *dc);

int hbaDrvRegMemCopyFunc(FC_MEMCPY_FUNCPTR func);
UINT32 hbaDevGetPortLinkStatus(HBA_DEV_CB *dc, int port);
INT32 hbaDevGetTemp(HBA_DEV_CB *dc);
STATUS hbaDevGetWorkStatus(HBA_DEV_CB *dc);

/*设置时钟同步周期*/
void hbaDevSetClkSyncPeriod(HBA_DEV_CB *dc, int clkSyncPeriod);

/*上电自检*/
STATUS hbaDevPuSelfCheck(HBA_DEV_CB *dc);

/*手动自检*/
void hbaDevManualSelfCheck(HBA_DEV_CB *dc);

/*网络发起的自检*/
void hbaDevNetSelfCheck(HBA_DEV_CB *dc);

/*内存自检*/
STATUS hbaDevCheckMemory(HBA_DEV_CB *dc);

/*周期自检端口的link状态*/
int hbaDevPeriodSelfCheckTask(HBA_DEV_CB *dc);

/*收发缓存(数据交互区)*/
FCUINT hbaDevCheckIoBufWrite(HBA_DEV_CB *dc);
FCUINT hbaDevCheckIoBufRead(HBA_DEV_CB *dc);

/*ELS管理帧自环*/
STATUS hbaDevCheckElsRing(HBA_DEV_CB *dc);

/*接口寄存器(PCIE通讯) */
STATUS hbaDevCheckRegisterIo(HBA_DEV_CB *dc);

/*Flash读写*/
STATUS hbaDevCheckFlashRW(HBA_DEV_CB *dc);

/*取得2个端口的链路状态值*/
FCUINT hbaDevCheckLinkStatus(HBA_DEV_CB *dc);

/*ASM帧自环*/
STATUS hbaDevCheckAsmRing(HBA_DEV_CB *dc);

/* 时统管理接口 */
/*设置节点的同步角色*/
void hbaDevSyncModeSet(HBA_DEV_CB *hDev, FCUINT enab);

/*使能同步接收*/
void hbaDevSyncEnable(HBA_DEV_CB *hDev);

/*禁止同步接收*/
void hbaDevSyncDisable(HBA_DEV_CB *hDev);

void hbaDevSetRTCRxTx(HBA_DEV_CB *hDev, FCUINT rx_enab, FCUINT tx_enab);

INT32 hbaDevIsOnNet(HBA_DEV_CB *dc);

/*判断设备的IO状态*/
UINT32 HbaDevIoState(HBA_DEV_CB *dc, UINT32 mode);

/*设置时钟同步周期*/
void hbaDevSetClkSyncPeriod(HBA_DEV_CB *dc, int clkSyncPeriod);

/* 周期发送ELS帧 */
INT32 hbaElsCycleCheckTask(HBA_DEV_CB *dc);

/* 非NC节点的WDT定时检查周期*/
FCUINT hbaDevWdtCheckPeriodHandler(HBA_DEV_CB *dc);

/* NC节点的WDT加载周期*/
UINT hbaDevNcWdtLoaderPeriodHandler(HBA_DEV_CB *dc);

/* 日历同步周期send els frame clk_sync_role=2 period send =1 user send by api 3-not send*/
UINT hbaDevDateSyncPeriodHandler(HBA_DEV_CB *dc);

/* ELS接收回调 */
INT32 hbaElsRecvTask(HBA_DEV_CB *dc);

/* 填充业务key */
void FillOperationKey(UINT *key, INT32 count);

/* ELS接收 */
INT32 hbaElsRecv(HBA_DEV_CB *dc, FC_ELS_CONFIG *elsConfig);

/* 解析ELS帧为ELS_CONFIG结构 */
void hbaParseElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 *frame, UINT length, UINT port);

/* 构造ELS帧 */
void hbaConstructElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 * frame, UINT *length);

/********************************************************************************/
/*处理接收到的ELS帧*/
void hbaElsRecvHandler(HBA_DEV_CB *dc, UINT32 index, FC_ELS_CONFIG *ecRecv);

void hbaConstructE1_0102(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 config);
void hbaConstructE1_0104(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, FCINT SchemeNo);
void hbaConstructE1_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, OnNetTbl *onNetTbl);
void hbaConstructE1_0203(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 value, FCUCHAR *onNetTblStatus, FCDate * pFCDate);
void hbaConstructE1_0204(FC_ELS_CONFIG *elsConfig, UINT32 sid, FCDate *fcDate);
void hbaConstructE1_0205(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 config);
void hbaConstructE2_0103(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did);
void hbaConstructE2_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did);
void hbaConstructE2_0201(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did);
void hbaConstructE3_0201(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 value);
void hbaConstructE3_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did,  NetStatistics *pStatInfo);
void hbaConstructE4_0203(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 status);

void hba_print_buf(int key, void *buf, int len);

/*调试函数*/
void hba_print_w_ctrl(W_CTRL *t);
void hba_print_r_ctrl(R_CTRL *t);

#ifdef __cplusplus
}
#endif  /*__cplusplus*/

#endif  /*_HBA_H*/

