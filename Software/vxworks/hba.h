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
typedef long long          INT64;  /*�з���64bit*/
typedef unsigned long long UINT64; /*�޷���64bit*/
typedef signed int         INT32;  /*�з���32bit*/
typedef unsigned int       UINT32; /*�޷���32bit*/
typedef signed short       INT16;  /*�з���16bit*/
typedef unsigned short     UINT16; /*�޷���16bit*/
typedef signed char        INT8;   /*�з���8bit*/
typedef unsigned char      UINT8;  /*�޷���8bit*/
typedef int                BOOL;   /* BOOL���� */
typedef void               VOID;   /* VOID���� */

#endif    /* __INCvxTypesOldh */
#endif    /* VXWORKS */

typedef float              FLOAT;  /* �������� */
typedef unsigned           UBIT;   /* λ���� */
typedef INT32 *            PINT32; /* �з���32bitָ������ */
typedef UINT32 *           PUINT32;/* �޷���32bitָ������ */
typedef INT16 *            PINT16; /* �з���16bitָ������ */
typedef UINT16 *           PUINT16;/* �޷���16bitָ������ */
typedef INT8 *             PINT8;  /* �з���8bitָ������ */
typedef UINT8 *            PUINT8; /* �޷���8bitָ������ */
typedef BOOL               BOOLEAN;/* �������� */
typedef void *             PVOID;  /* PVOID���� */

#define ASSERT(BOOL) \
{                                    \
    if (!(BOOL))  logMsg("ASSERT: %s(%u)\n", (int)__FILE__, (int)__LINE__,0,0,0,0); \
}

/* FC_MLS�������������ֵ���� */
#define DEV_SUCCESS                     0   /* �豸�����ɹ� */
#define DEV_STS_ERR                    -1   /* �豸״̬����ͨ������������ִ�д��󣬸�λ�������� */
#define DEV_PORTID_ERR                 -2   /* �豸�˿�ID��ʶ����  */
#define DEV_HANDLE_ERR                 -3   /* �豸������� */
#define DEV_HEART_ERR                  -4   /* �豸�����쳣  */
#define DEV_CMD_INVALID                -5   /* �豸����������Ч  */
#define DEV_CMD_FAIL                   -6   /* �豸��������δ�ɹ����  */
#define DEV_CMD_TIMEOUT                -7   /* �豸�������ʱ  */
#define DEV_WD_FAILED                  -8   /* ���� */
#define DEV_INVALID_OP                 -9   /* �豸��Ч������ͨ��������ִ������  */
#define DEV_RST_CONFIG_ERR             -10  /* �豸��λ�շ������߼��쳣  */
#define DEV_INTERFACE_ERR              -11  /* �豸�����ӿ��쳣  */
#define DEV_PARAMS_INVALID             -12  /* �豸����������Ч  */
#define DEV_ALL_CLOSED                 -13  /* �豸�ر�  */
#define DEV_IS_BUSY                    -14  /* �豸����ʹ��  */
#define DEV_NUMBER_INVALID             -15  /* �豸�����Ч  */
#define DEV_INTCALLBACK_INVALID        -16  /* �豸�жϻص�������Ч  */
#define DEV_CONFIG_DATA_INVALID        -17  /* �������ñ���Ч */
#define DEV_FLASH_WR_FAIL              -18  /* FLASH WR ʧ�� */
#define DEV_NOT_SUPPORT                -19  /* ���ܲ�֧�� */
#define DEV_PORT_LINK_DOWN             -20  /* �˿���·״̬down */
#define DEV_OTHER_FAILURE              -99  /* �豸������������ */

#define ASM_MSG_ID_INVALID             -101 /* ͨ����ϢID��Ч  */
#define ASM_MSG_LEN_INVALID            -102 /* ͨ����Ϣ������Ч */
#define ASM_PARAMS_UNMATCH             -103 /* ͨ�Ų���ƥ�����  */
#define ASM_STMSG_NUM_OVER             -104 /* ���ݿ���Ϣ�������ñ���Ŀ����  */
#define ASM_LTMSG_NUM_OVER             -105 /* �����ݿ���Ϣ�������ñ���Ŀ����  */
#define ASM_SRMSG_NUM_OVER             -106 /* ���ݿ���Ϣ�������ñ���Ŀ����  */
#define ASM_LRMSG_NUM_OVER             -107 /* �����ݿ���Ϣ�������ñ���Ŀ����  */
#define ASM_MSG_BUFER_FULL             -108 /* ��Ϣ���ͻ�������  */
#define ASM_MSG_BUFFER_EMPTY           -109 /* ��Ϣ���ͻ�������  */
#define ASM_BUFER_FREE_FAIL            -110 /* ��Ϣ�շ��������ͷ�ʧ��  */
#define ASM_BUFER_ALLOC_FAIL           -111 /* ��Ϣ�շ�����������ʧ��  */
#define ASM_OP_INVALID                 -112 /* �����ݿ���Ϣ���տ��Ʋ�����Ч */
#define ASM_PARAMS_INVALID             -113 /* ͨ�Ų�����Ч  */
#define ASM_MSG_UNACK                  -114 /* ���� */
#define ASM_ACKMSG_ERROR               -115 /* Ӧ����Ϣ���ô���  */
#define ASM_BLK_MSG_LOGIC_ERR          -116 /* ����  */
#define ASM_STREAM_RXBUF_REG_ERR       -117 /* �����ݿ���Ϣ���ջ�����ע�����  */
#define ASM_STREAM_RXBUF_UPDATE_ERR    -118 /* �����ݿ���Ϣ���ջ�����ˢ�´���  */
#define ASM_STREAM_RXBUF_COMPLETE_ERR  -119 /* �����ݿ���Ϣ���ջ������л�����  */
#define ASM_TXBUFF_ID_ERROR            -120  /* �����ݿ���Ϣ���ͻ�����ID����  */
#define ASM_RECV_TIMEOUT               -121  /* �������ݳ�ʱ  */
#define ASM_RECV_NO_DATA               -122  /* û�����ݱ����յ�  */
#define ASM_OTHER_FAILURE              -199 /* ͨ����Ϣ������������  */

#define CLK_SYNC_MODE_INVALID          -201 /* ʱ��ͬ����ɫ��Ч */
#define CLK_SYNC_PERIOD_INVALID        -202 /* ʱ��ͬ��������Ч */
#define CLK_SYNC_BASE_INVALID          -203 /* ʱ��ͬ����ֵ��Ч */
#define CLK_PARAMS_INVALID             -204 /* ʱ��ͬ��������Ч */
#define CLK_SYS_RTC_ERR                -205 /* ϵͳRTCʱ�Ӵ���,ͨ������������ʱ��ˢ��ʱ������RTC�Ⱦ�RTCС */
#define CLK_SYNC_OTHER_FAILURE         -299 /* ʱ��ͬ���������� */

#define NMG_MODE_INVALID               -301 /*�������ģʽ����*/
#define NMG_PARAMS_INVALID             -302 /*������������Ч*/
#define NMG_INTERFACE_ERROR            -303 /*�������ӿڴ���*/
#define NMG_OTHER_FAILURE              -399 /*��������������*/

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

/* HBA����״̬ */
enum
{
    HBA_DEV_STATUS_NONE = 0,
    HBA_DEV_STATUS_CREATED,
    HBA_DEV_STATUS_INITED,
    HBA_DEV_STATUS_STARTED
};

/*���״̬*/
enum
{
    HBA_MONITOR_STATUS_NONE = 0,
    HBA_MONITOR_STATUS_START,
    HBA_MONITOR_STATUS_STOP
};


/* HBAӲ����ID */
#define HBA_VENDOR_ID                    0x000010ee
#define HBA_DEVICE_ID                    0x00007014

/* �˿ڵ�״̬ */
#define PORT_LINK_DOWN                   0
#define PORT_LINK_UP                     1

/* DMA�������*/
#define NODE_OVERFLOW_SIZE               (1 * 1024)
#define DMA_BUF_ALIGN_SIZE               (1 * 1024)
#define DMA_BUF_TOTAL_MAX                (32*1024*1024)

/* ��QDR�йصĻ����������� */
#define QDR_BUFFER_MAX                   (16 * 1024 * 1024)
#define QDR_FPGA_RESERVED                (4 * 1024)
#define QDR_BUF_UNIT_SIZE_MIN			(64*1024)
#define QDR_BUF_UNIT_SIZE_MAX			(2*1024*1024)


/* �������� */
#define  HBA_RECV_TASK_NAME              "tHbaRcv"
#define  HBA_RECV_TASK_PRIORITY          55
#define  HBA_RECV_TASK_STACKSIZE         (40 * 1024)

/*��������*/
#define  HBA_PERIOD_TASK_NAME              "tHbaPeriod"
#define  HBA_PERIOD_TASK_PRIORITY          55
#define  HBA_PERIOD_TASK_STACKSIZE         (40 * 1024)

/* �汾�Ŷ��� */
#define MAJOR_VER      1
#define MINOR_VER      0
#define FIRMWARE_VER   1

/* ����ͨ�� */
typedef struct
{
    LIST_STR list_recv;        /* ������յ��Ļ����������� */
    SEM_ID   semListRecvLock;  /* ��������������ź��� */
} RECV_CHANNEL;

/* ��FPGA����������ڵ㶨�� */
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

/* ͳ����Ϣ */
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
	BOOL         bManuCloseInterrupt; /*�Ƿ��ֶ��ر����ж�*/
    UINT8       *pMembaseCsr;      /* the membase for FPGA config */    
    UINT8        irq;              /* Interrupt Request Level */
    UINT8        reserved[3];
    int          status;           /* ����״̬ */
    BOOL         bToStop;          /* ֹͣ�豸��� */
    UINT8       *DmaBufBaseAddr;   /* send DMA buffer base address, should be uncachable */
    UINT8       *DmaBufHeaderAddr; /* recv buffer base address, be cachable */
	UINT32      DmaBufAddrIntervalSize;    /*����ÿ��DMA ��ַ֮��ļ�࣬���ڲ���DMA��ַ */	
    SEM_ID       semRegRecvCallbackLock;
    FC_NP_RECV_FUNCPTR pRecvCallbackFunc;  /* �жϻص� */
	DEV_CONFIG  devConfig;
    
    /* ��FPGA�������ݵĶ��� */
    LIST_STR     list_hw;
    SEM_ID       semListHwLock;
    RECV_CHANNEL recv_channel;
    
    /* ��·״̬ */
    UINT32       linkStatus;
    UINT32       linkStatusChgCount;
	
	/*��������*/
	int          periodFmTaskId;
    SEM_ID       semPeriodSelfCheck;
    
    /* ��������ID */
    int          recvTaskId;
    SEM_ID       semRecv;
	
	/*��ؿ���*/
	int         monitorStatus;
	SEM_ID      semMonitorStart;

    /*ֹͣ��غ������Ÿ����*/    
    SEM_ID       semDrainFpga;

	DMA_BUFFER_ADDR_ELEMENT *dmaBufAddrStatAry;
	
	/*ͳ�Ʊ���*/
	UINT64 stat_recvDmaBufCnt;
	UINT64 stat_recvDmaBufValidLen;
	FPGA_STATISTICS_INFO fpgaStatInfo;
	PORT_STATISTICS_INFO portStatInfo[MAX_PORT_NUM];	
	
	/* QDR���������Ϣ*/
	UINT32 qdrBufUnitSize;    /* QDRÿһС��Ĵ�С������4K�ı���*/
	UINT32 qdrBufUnitNum;     /* QDR��С�����Ŀ*/
	UINT32 drvBufUnitSize;    /*����ÿһС��BUFFER�Ĵ�С,����С��qdrBufUnitSize�Ĵ�С*/
	UINT32 drvBufUnitNum;     /*������С�����Ŀ*/
} HBA_DEV_CB;

/*----------------------------- �豸����ӿ� -----------------------------*/
/* ��ʼ���� */
HBA_DEV_CB *hbaDevCreate(UINT32 DeviceId);
/* �رտ� */
INT32 hbaDevDestroy(HBA_DEV_CB *pHbaDevCB);

/*��λ��*/
INT32 hbaDevReset(HBA_DEV_CB *pHbaDevCB);

/* ��ȡN�˿ڵ�״̬ */
INT32 hbaDevGetPortState(HBA_DEV_CB *pHbaDevCB, UINT32 *portStatus, UINT32 count);
/* ��ȡ�汾�� */
INT32 hbaDevGetVersion(HBA_DEV_CB *pHbaDevCB, UINT32 *version);
/* ����FC�ڵ㿨 */
INT32 hbaDevConfig(HBA_DEV_CB *pHbaDevCB, PDEV_CONFIG dev_config);
/* ����FC�ڵ㿨������ */
INT32 hbaDevConfigSpeed(HBA_DEV_CB *pHbaDevCB, INT32 speed);
/* ��ʼ���� */
INT32 hbaDevInitialize(HBA_DEV_CB *pHbaDevCB);
/* ʹ�豸���Խ������� */
INT32 hbaDevRun(HBA_DEV_CB *pHbaDevCB);

/*�豸��ʼ���*/
INT32 hbaDevStartMonitor(HBA_DEV_CB *pHbaDevCB);

/*�豸ֹͣ���*/
INT32 hbaDevStopMonitor(HBA_DEV_CB *pHbaDevCB);


/* ע���жϽ��ջص����� */
INT32 hbaDevRegMsgHandler(HBA_DEV_CB *pHbaDevCB, FC_NP_RECV_FUNCPTR func);
/* ע���жϽ��ջص����� */
INT32 hbaDevUnRegMsgHandler(HBA_DEV_CB *pHbaDevCB);
/*----------------------------- ͨ�Ź���ӿ� -----------------------------*/
/* ȡ�����ݵĵ�ַ�ͳ��� */
INT32 hbaDevRecvData(HBA_DEV_CB *pHbaDevCB, void **ppBuffer, UINT *nLen);
/* �ͷ����ݻ����� */
INT32 hbaDevReleaseBuf(HBA_DEV_CB *pHbaDevCB, void *pBuffer);
/*----------------------------- ʱͳ����ӿ�-----------------------------*/
/* ��ȡRTCʱ�� */
VOID hbaDevGetRtc(HBA_DEV_CB *pHbaDevCB, FCTime *pFCTime);
/* ����RTCʱ�� */
VOID hbaDevSetRtc(HBA_DEV_CB *pHbaDevCB, FCTime *pFCTime);
/* ��ȡ���ں�ʱ�� */
VOID hbaDevGetDateTime(HBA_DEV_CB *pHbaDevCB, FCDate *pFCDate, FCTime *pFCTime);
/* �������� */
VOID hbaDevSetDate(HBA_DEV_CB *pHbaDevCB, FCDate *pFCDate);
/*------------------------------- �ڲ�����-------------------------------*/
/* ��FPGAѹ������ */
VOID hbaDevPushCredits(HBA_DEV_CB *pHbaDevCB, int *credits, int valid_buf_num);
/* ��FPGAע�Ỻ�����ĵ�ַ������ */
VOID hbaDevRegisterRxDmaBuf(HBA_DEV_CB *pHbaDevCB, int index, int dma_buf);
/* ����ʹ�ܣ�ʹ�˿��ܹ��� */
VOID hbaDevSetPortRxEnab(HBA_DEV_CB *pHbaDevCB, int rx_enab);
/* �ҽ��жϴ����� */
STATUS hbaDevIntConnect(HBA_DEV_CB *pHbaDevCB /*, UINT8 irq*/);
/* �ж�ʹ�ܿ��� */
VOID hbaDevHwIntControl(HBA_DEV_CB *pHbaDevCB, int enab);
/* �жϴ������� */
VOID hbaDevIntHandler(HBA_DEV_CB *pHbaDevCB);
/* ��ȡFPGA�Ĵ�����ȡ��2���˿ڵ���·״ֵ̬ */
UINT32 hbaDevCheckLinkStatus(HBA_DEV_CB *pHbaDevCB);
STATUS hbaDevIntEnable (HBA_DEV_CB *pHbaDevCB);
STATUS hbaDevIntDiable(HBA_DEV_CB *pHbaDevCB);
/* ��FPGA�������ݵ����� */
INT32 hbaDevRecvTask(HBA_DEV_CB *pHbaDevCB);
/* �Ÿ�QDR������������ */
VOID hbaDevDrainFpga(HBA_DEV_CB *pHbaDevCB);
/* ���������һ�������������� */
int hbaDevRecvOneBuffer(HBA_DEV_CB *pHbaDevCB);
/* �ͷŻ�������ʹFPGA�ܹ��������øû������������� */
VOID hbaDevFreeRecvBuffer(HBA_DEV_CB *pHbaDevCB, DMA_BUFFER_NODE_HEADER *node_header);
/* ��ʼ��������� */
VOID hbaDevInitLists(HBA_DEV_CB *pHbaDevCB);
/* �ͷ�������� */
VOID hbaDevFreeLists(HBA_DEV_CB * pHbaDevCB);

/*ͨ��DMA BUFFER��ַ����ýڵ�ͷ��ַ*/
void* hbaDevGetNodeHeaderAddr(HBA_DEV_CB * pHbaDevCB, void* pDmaBuf);

/*��Ӳ���ж�*/
VOID hbaDevOpenHardInterrupt(HBA_DEV_CB *pHbaDevCB);

/*��ȡͳ��ֵ*/
FCUINT hbaDevCheckStatistics(HBA_DEV_CB *pHbaDevCB);

/*�������񣬿��Ի�ȡͳ��ֵ*/
INT32 hbaDevPeriodTask(HBA_DEV_CB *pHbaDevCB);

#ifdef __cplusplus
}
#endif  /*__cplusplus*/

#endif  /*_HBA_H*/
