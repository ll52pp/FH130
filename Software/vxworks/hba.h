#ifndef _HBA_H
#define _HBA_H

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus */

#include <vxworks.h>
#include "list.h"
#include "fc_utility.h"

/******************** typedefs *****************************************/
#ifdef VXWORKS
#ifndef __INCvxTypesOldh
typedef long long          INT64;  /*有符号64bit*/
typedef unsigned long long UINT64; /*无符号64bit*/
typedef signed int         INT32;  /*有符号32bit*/
typedef unsigned int       UINT32; /*无符号32bit*/
typedef signed short       INT16;  /*有符号16bit*/
typedef unsigned short     UINT16; /*无符号16bit*/
typedef signed char        INT8;   /*有符号8bit*/
typedef unsigned char      UINT8;  /*无符号8bit*/
typedef int                BOOL;   /* BOOL类型 */
typedef void               VOID;   /* VOID类型 */

#endif    /* __INCvxTypesOldh */
#endif    /* VXWORKS */

typedef float              FLOAT;  /* 浮点类型 */
typedef unsigned           UBIT;   /* 位域定义 */
typedef INT32 *            PINT32; /* 有符号32bit指针类型 */
typedef UINT32 *           PUINT32;/* 无符号32bit指针类型 */
typedef INT16 *            PINT16; /* 有符号16bit指针类型 */
typedef UINT16 *           PUINT16;/* 无符号16bit指针类型 */
typedef INT8 *             PINT8;  /* 有符号8bit指针类型 */
typedef UINT8 *            PUINT8; /* 无符号8bit指针类型 */
typedef BOOL               BOOLEAN;/* 布尔类型 */
typedef void *             PVOID;  /* PVOID类型 */

#define ASSERT(BOOL) \
{                                    \
    if (!(BOOL))  logMsg("ASSERT: %s(%u)\n", (int)__FILE__, (int)__LINE__,0,0,0,0); \
}

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
#define DEV_FLASH_WR_FAIL              -18  /* FLASH WR 失败 */
#define DEV_NOT_SUPPORT                -19  /* 功能不支持 */
#define DEV_PORT_LINK_DOWN             -20  /* 端口链路状态down */
#define DEV_OTHER_FAILURE              -99  /* 设备操作其他错误 */

#define ASM_MSG_ID_INVALID             -101 /* 通信消息ID无效  */
#define ASM_MSG_LEN_INVALID            -102 /* 通信消息长度无效 */
#define ASM_PARAMS_UNMATCH             -103 /* 通信参数匹配错误  */
#define ASM_STMSG_NUM_OVER             -104 /* 数据块消息发送配置表数目错误  */
#define ASM_LTMSG_NUM_OVER             -105 /* 流数据块消息发送配置表数目错误  */
#define ASM_SRMSG_NUM_OVER             -106 /* 数据块消息接收配置表数目错误  */
#define ASM_LRMSG_NUM_OVER             -107 /* 流数据块消息接收配置表数目错误  */
#define ASM_MSG_BUFER_FULL             -108 /* 消息发送缓冲区满  */
#define ASM_MSG_BUFFER_EMPTY           -109 /* 消息发送缓冲区空  */
#define ASM_BUFER_FREE_FAIL            -110 /* 消息收发缓冲区释放失败  */
#define ASM_BUFER_ALLOC_FAIL           -111 /* 消息收发缓冲区申请失败  */
#define ASM_OP_INVALID                 -112 /* 流数据块消息接收控制操作无效 */
#define ASM_PARAMS_INVALID             -113 /* 通信参数无效  */
#define ASM_MSG_UNACK                  -114 /* 保留 */
#define ASM_ACKMSG_ERROR               -115 /* 应答消息配置错误  */
#define ASM_BLK_MSG_LOGIC_ERR          -116 /* 保留  */
#define ASM_STREAM_RXBUF_REG_ERR       -117 /* 流数据块消息接收缓冲区注册错误  */
#define ASM_STREAM_RXBUF_UPDATE_ERR    -118 /* 流数据块消息接收缓冲区刷新错误  */
#define ASM_STREAM_RXBUF_COMPLETE_ERR  -119 /* 流数据块消息接收缓冲区切换错误  */
#define ASM_TXBUFF_ID_ERROR            -120  /* 流数据块消息发送缓冲区ID错误  */
#define ASM_RECV_TIMEOUT               -121  /* 接收数据超时  */
#define ASM_RECV_NO_DATA               -122  /* 没有数据被接收到  */
#define ASM_OTHER_FAILURE              -199 /* 通信消息处理其他错误  */

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

#if 0
#define HBA_CACHE_INVAL(address, len)  cacheInvalidate(DATA_CACHE, (address), len)
#define HBA_CACHE_FLUSH(address, len)  cacheFlush (DATA_CACHE, (address), (len))
#else
#define HBA_CACHE_INVAL(address, len)
#define HBA_CACHE_FLUSH(address, len)
#endif

#if 0
#define DMA_BUF_MALLOC malloc
#define DMA_BUF_FREE   free
#else
#define DMA_BUF_MALLOC cacheDmaMalloc
#define DMA_BUF_FREE   cacheDmaFree
#define HBA_MEM_MALLOC malloc
#define HBA_MEM_FREE   free
#endif

/* HBA卡的状态 */
enum
{
    HBA_DEV_STATUS_NONE = 0,
    HBA_DEV_STATUS_CREATED,
    HBA_DEV_STATUS_INITED,
    HBA_DEV_STATUS_STARTED
};

/*监控状态*/
enum
{
    HBA_MONITOR_STATUS_NONE = 0,
    HBA_MONITOR_STATUS_START,
    HBA_MONITOR_STATUS_STOP
};


/* HBA硬件的ID */
#define HBA_VENDOR_ID                    0x000010ee
#define HBA_DEVICE_ID                    0x00007014

/* 端口的状态 */
#define PORT_LINK_DOWN                   0
#define PORT_LINK_UP                     1

/* DMA相关配置*/
#define NODE_OVERFLOW_SIZE               (1 * 1024)
#define DMA_BUF_ALIGN_SIZE               (1 * 1024)
#define DMA_BUF_TOTAL_MAX                (32*1024*1024)

/* 和QDR有关的缓冲区的设置 */
#define QDR_BUFFER_MAX                   (16 * 1024 * 1024)
#define QDR_FPGA_RESERVED                (4 * 1024)
#define QDR_BUF_UNIT_SIZE_MIN			(64*1024)
#define QDR_BUF_UNIT_SIZE_MAX			(2*1024*1024)


/* 接收任务 */
#define  HBA_RECV_TASK_NAME              "tHbaRcv"
#define  HBA_RECV_TASK_PRIORITY          55
#define  HBA_RECV_TASK_STACKSIZE         (40 * 1024)

/*周期任务*/
#define  HBA_PERIOD_TASK_NAME              "tHbaPeriod"
#define  HBA_PERIOD_TASK_PRIORITY          55
#define  HBA_PERIOD_TASK_STACKSIZE         (40 * 1024)

/* 版本号定义 */
#define MAJOR_VER      1
#define MINOR_VER      0
#define FIRMWARE_VER   1

/* 接收通道 */
typedef struct
{
    LIST_STR list_recv;        /* 保存接收到的缓冲区的链表 */
    SEM_ID   semListRecvLock;  /* 操作接收链表的信号量 */
} RECV_CHANNEL;

/* 和FPGA交互的链表节点定义 */
typedef struct
{
    UINT32 r0;
    UINT32 r1;
    UINT8 data[0];
} DMA_BUFFER_NODE;

typedef struct
{
    LIST_NODE node;  /* must be the first field */
    UINT buffer_index; /* FPGA buffer Index */
    DMA_BUFFER_NODE *dma_buf_node;
} DMA_BUFFER_NODE_HEADER;

typedef struct
{
	void* pDmaBufNodeHeaderAddr;
	void* pDmaBufNodeAddr;
} DMA_BUFFER_ADDR_ELEMENT;

/* 统计信息 */
#define FPGA_STAT_TYPE_RECV_FRAME_NUM         0x1
#define FPGA_STAT_TYPE_RECV_IU_NUM            0x2
#define FPGA_STAT_TYPE_RECV_ERROR_IU_NUM      0x3
#define FPGA_STAT_TYPE_RECV_DISCARD_IU_NUM    0x4
#define FPGA_STAT_TYPE_RECV_INVALID_FRAME_NUM 0x5
#define FPGA_STAT_TYPE_SEND_FRAME_NUM         0xB
#define FPGA_STAT_TYPE_SEND_IU_NUM            0xC
#define FPGA_STAT_PORT_0_BASE                 0x30
#define FPGA_STAT_PORT_1_BASE                 0x10
#define PORT_STAT_RX_UNDERSIZE_FRAME          0x0
#define PORT_STAT_RX_OVERSIZE_FRAME           0x1
#define PORT_STAT_RX_ALL_FRAME                0x2
#define PORT_STAT_RX_VALID_FRAME              0x3
#define PORT_STAT_RX_FRAME_LEN                0x4
#define PORT_STAT_LNK_CHG_UP2DWN              0x5
#define PORT_STAT_RX_RRDY                     0x6
#define PORT_STAT_RX_K_ERR                    0x7
#define PORT_STAT_TX_ALL_FRAME                0x8
#define PORT_STAT_TX_VALID_FRAME              0x9
#define PORT_STAT_TX_FRAME_LEN                0xA
#define PORT_STAT_TX_RRDY                     0xB

typedef struct _FPGA_STATISTICS_INFO{
    UINT64 recvFrameNumTotal;
    UINT64 recvIUNumTotal;
    UINT64 recvErrorIUNumTotal;
    UINT64 recvDiscardFrameNumTotal;
    UINT64 recvInvalidFrameNumTotal;
    UINT64 sendFrameNumTotal;
    UINT64 sendIUNumTotal;
} FPGA_STATISTICS_INFO, *PFPGA_STATISTICS_INFO;

typedef struct _PORT_STATISTICS_INFO{
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

typedef struct tagHBA_DEV_CB
{
    UINT32       DeviceId;
    int          BusNo;            /* bus number */
    int          DeviceNo;         /* device number */
    int          FuncNo;           /* function number */
    BOOL         bUseInterrupt;
	BOOL         bManuCloseInterrupt; /*是否手动关闭了中断*/
    UINT8       *pMembaseCsr;      /* the membase for FPGA config */    
    UINT8        irq;              /* Interrupt Request Level */
    UINT8        reserved[3];
    int          status;           /* 卡的状态 */
    BOOL         bToStop;          /* 停止设备标记 */
    UINT8       *DmaBufBaseAddr;   /* send DMA buffer base address, should be uncachable */
    UINT8       *DmaBufHeaderAddr; /* recv buffer base address, be cachable */
	UINT32      DmaBufAddrIntervalSize;    /*驱动每个DMA 地址之间的间距，用于查找DMA地址 */	
    SEM_ID       semRegRecvCallbackLock;
    FC_NP_RECV_FUNCPTR pRecvCallbackFunc;  /* 中断回调 */
	DEV_CONFIG  devConfig;
    
    /* 从FPGA接收数据的队列 */
    LIST_STR     list_hw;
    SEM_ID       semListHwLock;
    RECV_CHANNEL recv_channel;
    
    /* 链路状态 */
    UINT32       linkStatus;
    UINT32       linkStatusChgCount;
	
	/*周期任务*/
	int          periodFmTaskId;
    SEM_ID       semPeriodSelfCheck;
    
    /* 接收任务ID */
    int          recvTaskId;
    SEM_ID       semRecv;
	
	/*监控控制*/
	int         monitorStatus;
	SEM_ID      semMonitorStart;

    /*停止监控后数据排干完成*/    
    SEM_ID       semDrainFpga;

	DMA_BUFFER_ADDR_ELEMENT *dmaBufAddrStatAry;
	
	/*统计变量*/
	UINT64 stat_recvDmaBufCnt;
	UINT64 stat_recvDmaBufValidLen;
	FPGA_STATISTICS_INFO fpgaStatInfo;
	PORT_STATISTICS_INFO portStatInfo[MAX_PORT_NUM];	
	
	/* QDR相关配置信息*/
	UINT32 qdrBufUnitSize;    /* QDR每一小块的大小，必须4K的倍数*/
	UINT32 qdrBufUnitNum;     /* QDR的小块的数目*/
	UINT32 drvBufUnitSize;    /*驱动每一小块BUFFER的大小,不能小于qdrBufUnitSize的大小*/
	UINT32 drvBufUnitNum;     /*驱动的小块的数目*/
} HBA_DEV_CB;

/*----------------------------- 设备管理接口 -----------------------------*/
/* 初始化卡 */
HBA_DEV_CB *hbaDevCreate(UINT32 DeviceId);
/* 关闭卡 */
INT32 hbaDevDestroy(HBA_DEV_CB *pHbaDevCB);

/*软复位卡*/
INT32 hbaDevReset(HBA_DEV_CB *pHbaDevCB);

/* 获取N端口的状态 */
INT32 hbaDevGetPortState(HBA_DEV_CB *pHbaDevCB, UINT32 *portStatus, UINT32 count);
/* 获取版本号 */
INT32 hbaDevGetVersion(HBA_DEV_CB *pHbaDevCB, UINT32 *version);
/* 配置FC节点卡 */
INT32 hbaDevConfig(HBA_DEV_CB *pHbaDevCB, PDEV_CONFIG dev_config);
/* 配置FC节点卡的速率 */
INT32 hbaDevConfigSpeed(HBA_DEV_CB *pHbaDevCB, INT32 speed);
/* 初始化卡 */
INT32 hbaDevInitialize(HBA_DEV_CB *pHbaDevCB);
/* 使设备可以接收数据 */
INT32 hbaDevRun(HBA_DEV_CB *pHbaDevCB);

/*设备开始监控*/
INT32 hbaDevStartMonitor(HBA_DEV_CB *pHbaDevCB);

/*设备停止监控*/
INT32 hbaDevStopMonitor(HBA_DEV_CB *pHbaDevCB);


/* 注册中断接收回调函数 */
INT32 hbaDevRegMsgHandler(HBA_DEV_CB *pHbaDevCB, FC_NP_RECV_FUNCPTR func);
/* 注销中断接收回调函数 */
INT32 hbaDevUnRegMsgHandler(HBA_DEV_CB *pHbaDevCB);
/*----------------------------- 通信管理接口 -----------------------------*/
/* 取得数据的地址和长度 */
INT32 hbaDevRecvData(HBA_DEV_CB *pHbaDevCB, void **ppBuffer, UINT *nLen);
/* 释放数据缓冲区 */
INT32 hbaDevReleaseBuf(HBA_DEV_CB *pHbaDevCB, void *pBuffer);
/*----------------------------- 时统管理接口-----------------------------*/
/* 获取RTC时间 */
VOID hbaDevGetRtc(HBA_DEV_CB *pHbaDevCB, FCTime *pFCTime);
/* 设置RTC时间 */
VOID hbaDevSetRtc(HBA_DEV_CB *pHbaDevCB, FCTime *pFCTime);
/* 获取日期和时间 */
VOID hbaDevGetDateTime(HBA_DEV_CB *pHbaDevCB, FCDate *pFCDate, FCTime *pFCTime);
/* 设置日期 */
VOID hbaDevSetDate(HBA_DEV_CB *pHbaDevCB, FCDate *pFCDate);
/*------------------------------- 内部函数-------------------------------*/
/* 向FPGA压入信用 */
VOID hbaDevPushCredits(HBA_DEV_CB *pHbaDevCB, int *credits, int valid_buf_num);
/* 向FPGA注册缓冲区的地址和索引 */
VOID hbaDevRegisterRxDmaBuf(HBA_DEV_CB *pHbaDevCB, int index, int dma_buf);
/* 设置使能，使端口能工作 */
VOID hbaDevSetPortRxEnab(HBA_DEV_CB *pHbaDevCB, int rx_enab);
/* 挂接中断处理函数 */
STATUS hbaDevIntConnect(HBA_DEV_CB *pHbaDevCB /*, UINT8 irq*/);
/* 中断使能控制 */
VOID hbaDevHwIntControl(HBA_DEV_CB *pHbaDevCB, int enab);
/* 中断处理例程 */
VOID hbaDevIntHandler(HBA_DEV_CB *pHbaDevCB);
/* 读取FPGA寄存器，取得2个端口的链路状态值 */
UINT32 hbaDevCheckLinkStatus(HBA_DEV_CB *pHbaDevCB);
STATUS hbaDevIntEnable (HBA_DEV_CB *pHbaDevCB);
STATUS hbaDevIntDiable(HBA_DEV_CB *pHbaDevCB);
/* 从FPGA接收数据的任务 */
INT32 hbaDevRecvTask(HBA_DEV_CB *pHbaDevCB);
/* 排干QDR缓冲区的数据 */
VOID hbaDevDrainFpga(HBA_DEV_CB *pHbaDevCB);
/* 从链表接收一个缓冲区的数据 */
int hbaDevRecvOneBuffer(HBA_DEV_CB *pHbaDevCB);
/* 释放缓冲区，使FPGA能够重新利用该缓冲区接收数据 */
VOID hbaDevFreeRecvBuffer(HBA_DEV_CB *pHbaDevCB, DMA_BUFFER_NODE_HEADER *node_header);
/* 初始化链表和锁 */
VOID hbaDevInitLists(HBA_DEV_CB *pHbaDevCB);
/* 释放链表和锁 */
VOID hbaDevFreeLists(HBA_DEV_CB * pHbaDevCB);

/*通过DMA BUFFER地址来获得节点头地址*/
void* hbaDevGetNodeHeaderAddr(HBA_DEV_CB * pHbaDevCB, void* pDmaBuf);

/*打开硬件中断*/
VOID hbaDevOpenHardInterrupt(HBA_DEV_CB *pHbaDevCB);

/*获取统计值*/
FCUINT hbaDevCheckStatistics(HBA_DEV_CB *pHbaDevCB);

/*周期任务，可以获取统计值*/
INT32 hbaDevPeriodTask(HBA_DEV_CB *pHbaDevCB);

#ifdef __cplusplus
}
#endif  /*__cplusplus*/

#endif  /*_HBA_H*/
