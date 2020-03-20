/*++
文件名
constdef.h

描述
--*/

#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#define _BIG_ENDIAN                    1
#define _BYTE_ORDER                    0

// 版本
#define VERSION_MAJOR                  1
#define VERSION_MINOR                  0
#define VERSION_PATCH                  0

#define MEM_TAG_HBA                    '31mf'

#define NS_100                         (-1)               // 100ns
#define MICRO_SEC                      (10 * NS_100)      // 1us
#define MILLI_SEC                      (1000 * MICRO_SEC) // 1ms
#define MIN(_v0, _v1)                  ((unsigned int)(_v0) < (unsigned int)(_v1) ? (unsigned int)(_v0) : (unsigned int)(_v1))
#define MAX(_v0, _v1)                  ((unsigned int)(_v0) > (unsigned int)(_v1) ? (unsigned int)(_v0) : (unsigned int)(_v1))
#define ARRAY_COUNT(_value)            (sizeof(_value)/sizeof(_value[0]))

#define PORT_SPEED_1G                  1
#define PORT_SPEED_2G                  2

#define PORT_LINK_DOWN                 0
#define PORT_LINK_UP                   1

#define IO_CTRL_RESP_OK                0
#define IO_CTRL_RESP_NG                1
#define BIT_SUCCESS                    0
#define BIT_FAILURE                    1

#define FRAME_CFGID                    0x000000FC
#define FRAME_MONITORID                0x000000FB

#define DMA_NODE_OVERFLOW_SIZE         (4 * 1024)
#define DMA_BUF_ALIGN_SIZE             (4 * 1024)
#define DMA_GUARD_VALUE                0xDEADBEEF

#define QDR_BUF_SIZE                   (16 * 1024 * 1024)
#define QDR_FPGA_RESERVE_SIZE          (4 * 1024)
#define QDR_BUF_UNIT_SIZE_MIN          (64 * 1024)
#define QDR_BUF_UNIT_SIZE_MAX          (2 * 1024 * 1024)
#define DMA_NODE_COUNT                 1024

#define INT_RECV_BLOCK_MAX             1024
#define INT_EVT_TYPE_MAX               8
#define INT_EVT_PARAM_MAX              4

#define THREAD_CTRL_RUN                0
#define THREAD_CTRL_STOP               1 
#define THREAD_STATE_STOP              0
#define THREAD_STATE_RUN               1

#define INT_CONTEXT_IDLE               0 // 中断上下文空闲
#define INT_CONTEXT_USE                1 // 中断上下文使用中

#define INT_REG_IDLE                   0 // 没有注册中断
#define INT_REG_DOING                  1 // 正在注册中断
#define INT_REG_COMPLETE               2 // 已经注册中断

#define RECV_LIST_EMPTY                0x00000001
#define RECV_NO_DATA                   0x00000002
#define RECV_LENGTH_INVALID            0x00000004

// 中断子码定义
#define IC_VOLTAGE_SUCCESS             0x100 // 电压从错误值变为正常值
#define IC_VOLTAGE_FAILED              0x101 // 电压错误
#define IC_TEMP_SUCCESS                0x102 // 温度从错误值变为正常值
#define IC_TEMP_FAILED                 0x103 // 温度错误
#define IC_LINK_STATUS_SUCCESS         0x104 // link状态从错误值变为正常值
#define IC_LINK_STATUS_FAILED          0x105 // link状态错误
#define IC_IO_BUF_WRITE_FAILED         0x106 // 收发缓冲区写错误
#define IC_IO_BUF_READ_FAILED          0x107 // 收发缓冲区读错误

// 扩大1000倍避免使用浮点
#define SC_VOLTAGE_VALUE               1000  // 电压正常值
#define SC_VOLTAGE_THRESHOLD           200   // 电压阈值
#define SC_TEMP_VALUE                  40000 // 温度正常值
#define SC_TEMP_THRESHOLD              10000 // 温度阈值

// 读统计寄存器使用的偏移
#define FPGA_STAT_TYPE_RECV_FRAME_NUM         0x1
#define FPGA_STAT_TYPE_RECV_IU_NUM            0x2
#define FPGA_STAT_TYPE_RECV_ERROR_IU_NUM      0x3
#define FPGA_STAT_TYPE_RECV_DISCARD_IU_NUM    0x4
#define FPGA_STAT_TYPE_RECV_INVALID_FRAME_NUM 0x5
#define FPGA_STAT_TYPE_SEND_FRAME_NUM         0xB
#define FPGA_STAT_TYPE_SEND_IU_NUM            0xC

#define FPGA_STAT_PORT_0_BASE                 0x30
#define FPGA_STAT_PORT_1_BASE                 0x10

#define PORT_STAT_RX_UNDERSIZE_FRAME 	      0x0
#define PORT_STAT_RX_OVERSIZE_FRAME 	      0x1
#define PORT_STAT_RX_ALL_FRAME 			      0x2
#define PORT_STAT_RX_VALID_FRAME              0x3
#define PORT_STAT_RX_FRAME_LEN                0x4
#define PORT_STAT_LNK_CHG_UP2DWN              0x5
#define PORT_STAT_RX_RRDY                     0x6
#define PORT_STAT_RX_K_ERR                    0x7
#define PORT_STAT_TX_ALL_FRAME                0x8
#define PORT_STAT_TX_VALID_FRAME              0x9
#define PORT_STAT_TX_FRAME_LEN                0xA
#define PORT_STAT_TX_RRDY                     0xB

//
// FPGA的统计信息
//
typedef struct _FPGA_STATISTICS_INFO
{
	UINT64 recvFrameNumTotal;
	UINT64 recvIUNumTotal;
	UINT64 recvErrorIUNumTotal;
	UINT64 recvDiscardFrameNumTotal;
	UINT64 recvInvalidFrameNumTotal;
	UINT64 sendFrameNumTotal;
	UINT64 sendIUNumTotal;
} FPGA_STATISTICS_INFO, *PFPGA_STATISTICS_INFO;

//
// 端口统计信息
//
typedef struct _PORT_STATISTICS_INFO
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
} PORT_STATISTICS_INFO, *PPORT_STATISTICS_INFO;

//
// 手动自检结果
//
typedef struct _FC_BIT_RESULT_MANUAL
{
	UINT32 flash;        /* flash读写 */
	UINT32 buffer;		 /* 收发缓冲区读写 */
	UINT32 temperature;  /* 温度 */
	UINT32 voltage;      /* 电压 */
} FC_BIT_RESULT_MANUAL, *PFC_BIT_RESULT_MANUAL;

//
// 时间结构体
//
typedef struct _FCTime
{
	UINT32 hour;         /*时*/
	UINT32 minute;       /*分*/
	UINT32 second;       /*秒*/
	UINT32 millisecond;  /*毫秒*/
	UINT32 microsecond;  /*微秒*/
	UINT32 nanosecond;   /*纳秒*/
} FCTime, *PFCTime;

//
// 中断接收消息
//
// 1 R0生产数据，R3消费数据；R0的写位置是r0_index，R3的读位置是r3_index
// 2 r0_index和r3_index永远差一个节点
// 3 r0_index所在的节点一定是空的，只有r0_index的下一个节点也是空的，r0_index指向的节点才能写入数据，然后r0_index移动到下一个空节点
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
		ULONG length    : 32;
	} u;
	ULONG value;
} R0;

typedef union _R1
{
	struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
		ULONG reserve     : 24;/* [ 8:31] : RW reserve */
		ULONG channel_num : 8; /* [ 0: 7] : RW channel num */
#else		
		ULONG channel_num : 8; /* [ 0: 7] : RW channel num */
		ULONG reserve     : 24;/* [ 8:31] : RW reserve */
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
// 记录头
//
typedef struct _FCM_RECORD_HEADER
{
    UINT32 length;    /*记录头+帧长度(包括SOF CRC EOF)的字节数*/
    UINT32 flag;      /*错误标记*/
    UINT32 cfgID;     /*固定值0xFC000000*/
    UINT32 monitorID; /*固定值0xFB000000*/
} FCM_RECORD_HEADER, *PFCM_RECORD_HEADER;

//
// 链表控制
//
typedef struct _IO_LIST_CTRL
{
    WDFSPINLOCK lock;  // 操作链表的锁
    PLIST_ENTRY entry; // 双向链表的节点
} IO_LIST_CTRL, *PIO_LIST_CTRL;

//
// 链表节点定义
//
typedef struct _DMA_BUF_NODE
{
    R_CTRL r_ctrl;
    UINT8 data[1];
} DMA_BUF_NODE, *PDMA_BUF_NODE;

typedef struct _DMA_BUF_NODE_HEADER
{
    LIST_ENTRY entry;
    INT32 index;               // FPGA buffer Index
    INT32 dma_enabler_used;
    WDFDMAENABLER dma_enabler;
    PMDL mdl;
    PUCHAR va_r3;
    PUCHAR va_origin;          // 原始va地址
    PHYSICAL_ADDRESS la_origin;// 原始la地址
    PUCHAR va;                 // va地址(和FPGA交互)
    PHYSICAL_ADDRESS la;       // la地址(和FPGA交互)
} DMA_BUF_NODE_HEADER, *PDMA_BUF_NODE_HEADER;

//
// 卡的状态
//
typedef enum _ENUM_CARD_STATE
{
    ECS_NONE = 0, // 初始状态
    ECS_OPEN,     // 打开状态
    ECS_CONFIG,   // 配置状态
    ECS_MONITOR   // 监视中状态
} ENUM_CARD_STATE;

///////////////////////////////////////
// 内部使用的结构体定义
///////////////////////////////////////
//
// 配置参数
//
typedef struct _DEV_CONFIG
{
    int credit_num;
    int speed;
    int did_filter_enab;
    int e_d_tov;
    int redundant_enab;
    int time_out;
    int qdr_buf_unit_size;
	int sw_fcid;
} DEV_CONFIG, *PDEV_CONFIG;

//
// 设备的位置
//
typedef union _DEV_LOCATION
{
	struct
    {
		USHORT function : 3;
		USHORT device   : 5;
		USHORT bus      : 8;
	} u;
	USHORT value;
} DEV_LOCATION, *PDEV_LOCATION;

//
// 调试信息
//
typedef struct _DBG_CONTEXT
{
    UINT32 dbg_control;
    UINT32 reserve;
    LONGLONG delay_data_prev;
    LONGLONG delay_data_max;
    LONGLONG delay_data_count;
    LONGLONG delay_reg_count[128];
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
} DBG_CONTEXT, *PDBG_CONTEXT;

typedef struct _DBG_ADDR
{
    PUCHAR va;
    PHYSICAL_ADDRESS la;
} DBG_ADDR, *PDBG_ADDR;

//
// 设备对象的上下文
//
typedef struct _FDO_DATA
{
	WDFDEVICE               WdfDevice;       // 设备对象
	WDFQUEUE                ReadQueue;       // 读请求队列
	WDFQUEUE                WriteQueue;      // 写请求队列
	WDFQUEUE                IoctlQueue;      // 控制请求队列

	// 设备信息
	DEV_LOCATION            Location;        // 设备的位置
	BUS_INTERFACE_STANDARD  BusInterface;

	// 硬件资源
	PHYSICAL_ADDRESS        RegPhyAddr;      // BAR0 寄存器物理地址
	UINT32                  RegPhyLen;       // BAR0 寄存器物理地址长度
	struct _REG_HW         *Reg;             // BAR0 寄存器虚拟地址
	WDFINTERRUPT            Interrupt;       // 中断对象

	ENUM_CARD_STATE         State;           // 卡的状态 初始化/已经创建/复位/关闭
    DEV_CONFIG              DevConfig;

    IO_LIST_CTRL            RecvCtrl;

    // 中断接收处理
    LONG volatile           IntRecvFlag;
    PKEVENT                 IntRecvEvent;
    PCBN_INT_RECV_CONTEXT   IntRecvContext;
    PMDL                    IntRecvMdl;

    // 中断通知处理
    LONG volatile           IntEvtFlag;
    PKEVENT                 IntEvtEvent;
    PCBN_INT_EVT_CONTEXT    IntEvtContext;
    PMDL                    IntEvtMdl;
    
	// 读数据线程
	INT32 volatile          RecvThreadState;
	INT32 volatile          RecvThreadCtrl;
	PKTHREAD                RecvThreadObject;

    // 周期自检线程
    INT32 volatile          PeriodSelfCheckThreadState;
    INT32 volatile          PeriodSelfCheckThreadCtrl;
    PKTHREAD                PeriodSelfCheckThreadObject;

    FC_BIT_RESULT_MANUAL    BitResult;

	FPGA_STATISTICS_INFO    FpgaStatisticsInfo;
	PORT_STATISTICS_INFO    PortStatisticsInfo[2];

    DBG_CONTEXT             DbgContext;
    DBG_ADDR                DbgInitAddr[DMA_NODE_COUNT];
    DBG_ADDR                DbgCheckAddr[DMA_NODE_COUNT];
} FDO_DATA, *PFDO_DATA;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(FDO_DATA, FdoGetData)

#endif // __PUBLIC_H__