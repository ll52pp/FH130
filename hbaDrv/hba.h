#ifndef _HBA_H
#define _HBA_H

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus */

#define HBA_INCLUDE_ELS                          /*����ELSģ��*/
#define HBA_INCLUDE_FLASH                        /*����FLASHģ��*/

#define USE_MSG_COVER                            /*֧����Ϣ����*/
#define USE_MSG_DISCARD                          /*֧����Ϣ����*/
#define USE_IU_TIMEOUT                           /*֧��IU���չ����г�ʱ����*/

#define USE_SEND_SHARE_BUFFER                    /*����ʹ��share buffer*/

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
typedef long long      INT64;        /*�з���64bit*/
typedef unsigned long long UINT64;   /*�޷���64bit*/
typedef signed int     INT32;        /*�з���32bit*/
typedef unsigned int   UINT32;       /*�޷���32bit*/
typedef signed short   INT16;        /*�з���16bit*/
typedef unsigned short UINT16;        /*�޷���16bit*/
typedef signed char    INT8;          /*�з���8bit*/
typedef unsigned char  UINT8;         /*�޷���8bit*/
typedef    int            BOOL;          /* BOOL���� */

typedef void           VOID;         /* VOID���� */

#endif    /* __INCvxTypesOldh */
#endif    /* VXWORKS */


typedef float          FLOAT;         /* ��������*/
typedef unsigned       UBIT;          /*λ����*/
typedef INT32 *        PINT32;        /*�з���32bitָ������*/
typedef UINT32 *       PUINT32;       /*�޷���32bitָ������*/
typedef INT16 *        PINT16;        /*�з���16bitָ������*/
typedef UINT16 *       PUINT16;       /*�޷���16bitָ������*/
typedef INT8 *         PINT8;         /*�з���8bitָ������*/
typedef UINT8 *        PUINT8;        /*�޷���8bitָ������*/
typedef BOOL           BOOLEAN;       /* �������� */
typedef void  *        PVOID;         /* PVOID���� */

/* �汾�Ŷ��� */
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

/* ���ڷ���ELS֡ */
#define  HBA_ELS_CYCLE_CHECK_TASK_NAME       "tHbaElsCycleCheck"
#define  HBA_ELS_CYCLE_CHECK_TASK_PRIORITY   60
#define  HBA_ELS_CYCLE_CHECK_TASK_STACKSIZE  40960

/* ELS���ջص� */
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

#define IO_STATE_MODE_RAW                   1 /*���ͽ���RAW����֡*/
#define IO_STATE_MODE_ASM                   2 /*���ͽ���ASM����*/

/* ���ȼ� */
#define PRIORITY_LEVEL_HIGH_ASM_MSG            PRIORITY_LEVEL_3
#define PRIORITY_LEVEL_LOW_ASM_MSG            PRIORITY_LEVEL_0

#define PRIORITY_LEVEL_STREAM_MSG            PRIORITY_LEVEL_0
#define PRIORITY_LEVEL_RAW_MSG                PRIORITY_LEVEL_1
#define PRIORITY_LEVEL_EVENT_MSG            PRIORITY_LEVEL_2
#define PRIORITY_LEVEL_URGENCY_MSG            PRIORITY_LEVEL_3



/* DMA ���ͺͽ��� buffer�йض��� */

/* ���� Buffer ͳһ��һ������ */
#define MAX_SEND_BUFER_LEN                    (63 * 1024)    /*��� 511*128 �ֽ�, Լ63K*/

/* ���� Buffer�Ĵ�С�������������ȼ���ͬ���ֱ��� */
/* ���� Buffer��С�������õķ�Χ��4K - 128K, ������ó�4K�ı��� */
#define MAX_RECV_BUFER_LEN_P0                 (64*1024)    /* ASM���� ��K���� */
#define MAX_RECV_BUFER_LEN_P1                 (8*1024)    /* ELS, ��С4K, ��K���� */
#define MAX_RECV_BUFER_LEN_P2                 (4*1024)    /* ����飬��С4K, ��K���� */
#define MAX_RECV_BUFER_LEN_P3                 (4*1024)    /* �����飬��С4K, ��K���� */

#define MAX_RECV_BUFER_LEN_ELS            MAX_RECV_BUFER_LEN_P1

#ifdef AE653_BUILD

#define MAX_RECV_BUFFER_NUM_P0                32 /*156*/        /* ���1024 */
#define MAX_RECV_BUFFER_NUM_P1              32
#define MAX_RECV_BUFFER_NUM_P2              32
#define MAX_RECV_BUFFER_NUM_P3                32

#define MAX_RECV_BUFFER_NUM                 (MAX_RECV_BUFFER_NUM_P0 + MAX_RECV_BUFFER_NUM_P1 + MAX_RECV_BUFFER_NUM_P2 + MAX_RECV_BUFFER_NUM_P3)
#define MAX_SEND_BUFFER_NUM                 256

#else

#define MAX_RECV_BUFFER_NUM_P0                512        /* ���1024 */
#define MAX_RECV_BUFFER_NUM_P1              128
#define MAX_RECV_BUFFER_NUM_P2              128
#define MAX_RECV_BUFFER_NUM_P3                128

#define MAX_RECV_BUFFER_NUM                 (MAX_RECV_BUFFER_NUM_P0 + MAX_RECV_BUFFER_NUM_P1 + MAX_RECV_BUFFER_NUM_P2 + MAX_RECV_BUFFER_NUM_P3)
#define MAX_SEND_BUFFER_NUM                 512

#endif


/* ϵͳ�ṩ�����DMA����������Ҫ�޸�! */
#define MAX_TX_DMA_BUF_NUM            4096
#define MAX_RX_DMA_BUF_NUM_PER_PRIO    1024

#define MAX_BYTES_PER_DMA            128


#define SEND_BUFFER_ALLOCATEE_ASM             0
#define SEND_BUFFER_ALLOCATEE_RAW             256
#define SEND_BUFFER_ALLOCATEE_SHARE         0xFFFFFFFF

#define SEND_BUFFER_SIGNATURE                0xFECAFECA
#define RECV_BUFFER_SIGNATURE                0xFECDFECD

#define FC_MINOR_SCHEME_SIZE               (32 * 1024) /*ÿ�����ÿ���ֽ���*/
#define FC_MAJOR_SCHEME_SIZE               (FC_MINOR_SCHEME_MAX * FC_MINOR_SCHEME_SIZE) /*ÿ����ͼ���ֽ���*/

/* ͨ�������� */
#define MAX_RECV_CHANNEL_NUM                256
#define MAX_SEND_CHANNEL_NUM                256

#define INVALID_CHANNEL_NO                    (-1)
#define RAW_CHANNNEL_NO                        256

#define MAX_PRESERVE_MSG_COUNT                     4    /* ÿ��(����)ͨ���������������Ϣ��, ������ᵼ����Ϣ���ǻ��߶��� */
#define MAX_PRESERVE_STRM_IU_COUNT                 2    /* ÿ����ͨ�������������IU��, ������ᵼ����Ϣ���ǻ��߶��� */
#define MAX_PRIVATE_SEND_BUFFER_NUM_PER_MSG        4    /* ÿ��ͨ����˽�еķ���buffer���� Ŀǰ���� */

#define INVALID_ASM_MSG_ID                  0


#define FCID_TYPE_INVALID               0           /* ��Ч��ַ */
#define FCID_TYPE_SINGLE                1           /* �������� */
#define FCID_TYPE_MULTICAST             2           /* �ಥ���� */
#define FCID_TYPE_BROADCAST             3           /* �㲥���� */

#define FCID_BROADCAST                  0xFFFFFF  /*�㲥��*/
#define FCID_MULTICAST_MIN              0xFFFB00  /*�鲥�ſ�ʼ*/
#define FCID_MULTICAST_MAX              0xFFFBFF  /*�鲥�Ž���*/
#define FCID_SINGLECASE_MAX                0xFF0000  /*��󵥲���ַ*/

/* IU buffer �շ���Buffer�йض��� */
#define MAX_IU_LEN                            0x1000000

#ifdef USE_IU_TIMEOUT
#define RECV_IU_TIMEOUT                     2000    /* IU���ճ�ʱ���壬��λ: ms */
#endif

/* BIT ���Խ�� */
#define BIT_SUCCESS                              0
#define BIT_FAILURE                              1

/* ���� */
#define PORT_SPEED_1G                            1
#define PORT_SPEED_2G                            2

/* bufferʹ�ú�FPGA�Ƿ���������*/
#define MSG_DISCARD_DISABLE                        0     /* ������ */    
#define MSG_DISCARD_ENABLE                        1     /* ���� */    

/*����1000������ʹ�ø���*/
#define SC_VOLTAGE_VALUE                         1000       /*��ѹ����ֵ*/
#define SC_VOLTAGE_THRESHOLD                     200        /*��ѹ��ֵ*/
#define SC_TEMP_VALUE                            30000      /*�¶�����ֵ*/
#define SC_TEMP_THRESHOLD                        90000      /*�¶���ֵ*/

#define BIT_TYPE_MANULA                          0          /*�ֶ��Լ�*/
#define BIT_TYPE_POWER                           1          /*�ϵ��Լ�*/

#define FC_SELF_CHECK_PERIOD                     200        /*�������������ֵ������*/


/*��ͼ��FLASH ��ŵĻ���ַ*/
#define FC_SCHEME_ADDRESS                        0


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
#define DEV_FLASH_WR_FAIL               -18  /* FLASH WR ʧ�� */
#define DEV_NOT_SUPPORT                      -19  /* ���ܲ�֧�� */
#define DEV_PORT_LINK_DOWN               -20  /* �˿���·״̬down */
#define DEV_WDT_PERIOD_ERR             -21    /* WDT �������ô���*/
#define DEV_OTHER_FAILURE              -99  /* �豸������������  */

#define ASM_MSG_ID_INVALID             -101 /* ͨ����ϢID��Ч  */
#define RAW_MSG_LEN_INVALID            -102 /* ͨ����Ϣ������Ч */
#define ASM_PARAMS_UNMATCH             -103 /* ͨ�Ų���ƥ�����  */
#define ASM_STMSG_NUM_OVER             -104 /* ���ݿ���Ϣ�������ñ���Ŀ����  */
#define ASM_LTMSG_NUM_OVER             -105 /* �����ݿ���Ϣ�������ñ���Ŀ����  */
#define ASM_SRMSG_NUM_OVER             -106 /* ���ݿ���Ϣ�������ñ���Ŀ����  */
#define ASM_LRMSG_NUM_OVER             -107 /* �����ݿ���Ϣ�������ñ���Ŀ����  */
#define ASM_MSG_BUFER_FULL             -108 /* ��Ϣ���ͻ�������  */
#define RAW_MSG_BUFFER_EMPTY           -109 /* ��Ϣ���ͻ�������  */
#define ASM_BUFER_FREE_FAIL            -110 /* ��Ϣ�շ��������ͷ�ʧ��  */
#define ASM_BUFER_ALLOC_FAIL           -111 /* ��Ϣ�շ�����������ʧ��  */
#define ASM_OP_INVALID                 -112 /* �����ݿ���Ϣ���տ��Ʋ�����Ч */
#define RAW_PARAMS_INVALID             -113 /* ͨ�Ų�����Ч  */
#define ASM_MSG_UNACK                  -114 /* ���� */
#define ASM_ACKMSG_ERROR               -115 /* Ӧ����Ϣ���ô���  */
#define ASM_BLK_MSG_LOGIC_ERR          -116 /* ����  */
#define ASM_STREAM_RXBUF_REG_ERR       -117 /* �����ݿ���Ϣ���ջ�����ע�����  */
#define ASM_STREAM_RXBUF_UPDATE_ERR    -118 /* �����ݿ���Ϣ���ջ�����ˢ�´���  */
#define ASM_STREAM_RXBUF_COMPLETE_ERR  -119 /* �����ݿ���Ϣ���ջ������л�����  */
#define ASM_TXBUFF_ID_ERROR            -120  /* �����ݿ���Ϣ���ͻ�����ID����  */
#define RAW_RECV_TIMEOUT               -121  /* �������ݳ�ʱ  */
#define RAW_RECV_NO_DATA               -122  /* û�����ݱ����յ�  */
#define RAW_OTHER_FAILURE              -199 /* ͨ����Ϣ������������  */

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

#if 1/*liujin added for rtc*/
#define CLK_SYNC_ROLE_SERVER_MASTER       1 /*����ʱ�ӷ�������ģ��ʱ�ӿͻ���*/
#define CLK_SYNC_ROLE_CLIENT              2 /*����ʱ�ӿͻ���*/
#endif

/* ��FPGA�����Ķ�д������Ķ��� */
/* TX ���� */
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

/* RX ���� */
typedef union
{
    struct
    {
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
        ULONG sop         : 1; /* [    31] : RW sop */
        ULONG eop         : 1; /* [    30] : RW eop */
        ULONG seq_err     : 1; /* [    29] : RW block sequence error, fpga set */
        ULONG ox_id_err   : 1; /* [    28] : RW block oxid error, û��ʹ�� */        
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
        
    /* ���Ϳ��ж��У�ÿ��ͨ��������һ��������Ϊר�ã�
    ��֤�����еĻ��汻����ͨ������ʱ����ͨ��Ҳ�����뵽����*/
    LIST_STR list_send_idle_private;

    /* ����buffer����ȴ����ź��� */
    SEM_ID semSendBufferValid;
        
    /* Ҫ���͵������ȹҵ�������� */
    /* LIST_STR  list_toSend; */

    BOOL bIsStream;

    /* ͳ������ */
    UINT64 sendBuffers;
    UINT64 sendBytes;
} ASM_SEND_CHANNEL;

typedef struct
{
    /* ���Ϳ��ж��У�ÿ��ͨ��������һ��������Ϊר�ã�
    ��֤�����еĻ��汻����ͨ������ʱ����ͨ��Ҳ�����뵽����*/
    LIST_STR list_send_idle_private;

    /*����buffer����ȴ����ź���*/
    SEM_ID  semSendBufferValid;
    
    /*�Ѿ��յ��������ȷŵ�����*/
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
    UINT32     Index;    /*type=IU_BUFFER_TYPE_PRIVATE, ָʾʹ�ø�IU buffer��ͨ����
                      type=IU_BUFFER_TYPE_DYNAMIC�����ֶ�����*/
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
    BOOL bMsgCover;                /* ��Ϣ���� */
#endif

    LIST_STR  list_recved;        /* �Ѿ��յ��������ȷŵ�����, ���Recv Buffer  */
    SEM_ID    semListRecvedLock;/* ����Ҫ��list_recved�е�IU����(���buffer)����ʱ����list_recved���б������ڼ䲻������������Ը��б���в��� */
    

    LIST_STR  list_currentIU;    /* ��ǰ���ڽ��յ�IU */
    UINT32    tickSOP;            /* ��ǰIU ���յ�һ��֡��tickֵ */
    UINT32    nIULen;
    UINT32    nIUCount;            /* list_recved �д�ŵ�IU ���� */    

    SEM_ID  semRecvBufferValid;    /* ����buffer��Ч���ź��� */

    /* ͳ��ֵ */
    UINT64 totalIuCount;      /* ���յ���IU ���� */
    UINT64 discardIuCount;  /* ������IU ���� */
    UINT64 coverIuCount;      /* ���ǵ�IU ���� */
    UINT64 IuLenException;    /* IU�����쳣�ĸ���ͳ�� */
    UINT64 IuSeqException;    /* IU Sequence�ĸ���ͳ�� */
    UINT64 IuTmroutException;/* IU�����쳣�ĸ���ͳ�� */
    UINT64 recvBuffers;
    UINT64 recvBytes;
    UINT32 msg_recv_type;    /*1-�ж�0-��ѯ*/
    
} ASM_RECV_CHANNEL;

typedef struct
{
    LIST_STR list_recved;        /* �Ѿ��յ��������ȷŵ����� */
    SEM_ID   semRecvBufferValid;/* ����buffer��Ч���ź��� */
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
    UINT32 allocatee; /* ָ��buffer���ĸ����������Դ��0~255 for ASM private, 256 for RAW private,  0xFFFFFFFF for share,  used for buffer recycle */    
    int    ch;          /* ʹ�ø÷���buffer��ͨ����,�������buffer��ͨ���ţ� 0~255 for ASM private, 256 for RAW private,  -1 û�б�ʹ�� */
    BOOL bStream;      /* �Ƿ�Ϊ�����ͣ� ���������Ϳ���ȷ������� */
    UINT32 seqNo;     /* ���͵���ţ����������ͣ� ���ڿ鷢�ͣ����ֶ���Ч����Ϊ0 */
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

/*����ͳ����Ϣ*/
typedef struct
{
    FCUINT64 recvFrameNum;     /*1 ����֡��*/
    FCUINT64 recvIuNum;        /*2 ����IU����*/
    FCUINT64 recvIuErrNum;     /*3 ���մ���֡�� IU��ǲ�ƥ��/CRC����/��������֡ͷ�����*/
    FCUINT64 recvIuDiscardNum; /*4 ���ն�����IU���� ���ն������˶�����Ǻ󣬷����Ķ�����IU����*/
    FCUINT64 recvIuInvalidNum; /*5 ������Ч��֡�� ASMIDû�����ù��������յ���*/
    FCUINT64 sendFrameNum;     /*6 ����֡��*/
    FCUINT64 sendIuNum;        /*7 ����IU����*/
} LocalStatisticsInfo;

typedef struct
{
    UINT64 recvFrameNumTotal;
    UINT64 recvIUNumTotal;
    UINT64 recvErrorIUNumTotal;
    UINT64 recvDiscardFrameNumTotal;    /* ����Iu������֡�� */
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

    FCUINT                       asmRunControl; /*ASM���ͽ��տ��� 0-��ֹASM���ͽ��� 1-����ASM���ͽ���*/

    UINT8                        *pMembaseCsr; /* the membase for FPGA config */
    
    UINT8                         irq;         /* Interrupt Request Level */
    UINT8                         reserved[3]; /* ʹ���� */
    
    UINT8                        *pSendDmaBufBaseAddr; /* send DMA buffer base address, should be uncachable */
    UINT8                        *pRecvDmaBufBaseAddr; /* send DMA buffer base address, should be uncachable */

    UINT8                        *pSendBufBaseAddr;    /* send buffer base address, be cachable */
    UINT8                        *pRecvBufBaseAddr;    /* recv buffer base address, be cachable */
    
    FC_ASM_RECVMSG_FUNCPTR        pRecvCallBackFunc;    /*ASM���ջص�*/
    FC_INT_FUNCPTR                pIntCallbackFunc;             /*�жϻص�*/
    
    /* ���Ϳ��ж��У����� */
    LIST_STR                      list_send_idle_share;
    SEM_ID                        semSendShareBufferValid;

    /* ���տ��ж��У� �ö���û�б�Ҫ*/
    LIST_STR                      list_recv_idle_share;
    SEM_ID                        semRecvShareBufferValid;

    /* �Ѿ����ͣ��ȴ�FPGA������ϵĶ��У���FPGA�й� */
    LIST_STR                      list_SentWaitAck[MAX_PRIORITY_LEVEL_NUM];   

    /* �����ն���, �ȵ�FPGA���գ���FPGA�й� */
    LIST_STR                      list_toRecv[MAX_PRIORITY_LEVEL_NUM];    
    SEM_ID                        semRecvListLock;

    /* ͨ������: 256������ͨ��, 256������ͨ��, 1��raw����ͨ��, 1��raw ����ͨ�� */
    RAW_SEND_CHANNEL              rawSendChannel;
    ASM_SEND_CHANNEL              asmSendChannels[MAX_SEND_CHANNEL_NUM];
    UINT                          asmSendChannelCount;
    RAW_RECV_CHANNEL              rawRecvChannel;
    ASM_RECV_CHANNEL              asmRecvChannels[MAX_RECV_CHANNEL_NUM];
    UINT                          asmRecvChannelCount;
    
#ifdef USE_IU_TIMEOUT    
    /* IU ����timeoutʱ�� */
    UINT32                        recvIUTimeoutTick;
#endif

    /* ��·״̬ */
    UINT32                        linkStatus;
    UINT32                        linkStatusChgCount;
    BOOL                          bLinkStatusChecking;

    int                           RawDataBufOffset;
    UINT8                        *pRawDataBuf;
    
    /* �Լ� */
    BOOL                          bBuildInTesting;
    FC_BIT_RESULT                 bitResult;
    
    /*ֹͣ�豸���*/
    BOOL bToStop;

    /*����ID*/
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
    
    /* ELS֡���� */
    RAW_FRAME_CTRL                rawFrameCtrl;
    UINT8                        *pRawDataBlock;
    UINT32                        wdtLoaderPeriodEnab; /*��������ʹ�ܿ���*/
    
    UINT32                        wdtTimeoutFlag;      /*WDT��ʱ�ϱ��ж��Ѿ��ϱ��ı�ǣ�WDT��ʱ�ж�ֻ�ϱ�һ��*/
    
#if 0 /* Huilin */    
    
    UINT32                        recvE1_0203Flag;     /*�յ�NC���͵�����֡�ı��*/
#endif    
    UINT32                        ncFcid;              /*NC�ڵ��FCID*/
    UINT32                        elsKeyRecvList[FC_ELS_KEY_COUNT];
    CYCLE_DESC                    cycleDesc[MAX_TIMER_NUM];
    FC_ELS_CONFIG                 elsConfig[FC_ELS_KEY_COUNT];
    FC_ELS_CONFIG                 elsRecvConfig; /* huilin */
    
    OnNetTbl                      onNetTbl;           /*��������*/
    SwLinkStatusTbl               swLinkStatusTbl; /*�������㲥�Ķ˿���·״̬��*/
    SW_IMPSoftWareVersion         swAppVersion[FC_PORT_NUM_MAX]; /*��������Ӧ�������Ϣ*/
    SW_IMPSoftWareVersion         swBspVersion[FC_PORT_NUM_MAX]; /*��������BSP*/

    INT32                         wdtInitCounter;  /*NC�ڵ�ȴ������б��NC�ڵ㷢������֡��������*/
    UINT32                        NcLinkdownTimes;
    LocalStatisticsInfo           localStatisticsInfo;/*����ͳ����Ϣ*/

    /*ͳ������*/
    UINT64                        sentBytes;
    UINT64                        recvBytes;
    UINT64                           moveBytes;
    UINT64                        sentIUs;
    UINT64                        recvIUs;
    UINT64                        dicardIUs;       /* ������IU��  */
    UINT64                        coverIUs;         /* ���ǵ�IU ���� */
    UINT64                        exceptionIUs;   /* ���ǵ�IU ���� */
    UINT64                        sentRawBuffers;
    UINT64                        recvRawBuffers;
    UINT64                        sendBuffers;
    UINT64                        recvBuffers;
    UINT64                        sendCmptBuffers;    /* ȷ�Ϸ��ͳɹ���buffer�� */
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

/*�����豸*/
UINT32 hbaDevCreate(HBA_DEV_CB **pdc, UINT32 Device_Id);

/*���豸*/
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

/*����ʱ��ͬ������*/
void hbaDevSetClkSyncPeriod(HBA_DEV_CB *dc, int clkSyncPeriod);

/*�ϵ��Լ�*/
STATUS hbaDevPuSelfCheck(HBA_DEV_CB *dc);

/*�ֶ��Լ�*/
void hbaDevManualSelfCheck(HBA_DEV_CB *dc);

/*���緢����Լ�*/
void hbaDevNetSelfCheck(HBA_DEV_CB *dc);

/*�ڴ��Լ�*/
STATUS hbaDevCheckMemory(HBA_DEV_CB *dc);

/*�����Լ�˿ڵ�link״̬*/
int hbaDevPeriodSelfCheckTask(HBA_DEV_CB *dc);

/*�շ�����(���ݽ�����)*/
FCUINT hbaDevCheckIoBufWrite(HBA_DEV_CB *dc);
FCUINT hbaDevCheckIoBufRead(HBA_DEV_CB *dc);

/*ELS����֡�Ի�*/
STATUS hbaDevCheckElsRing(HBA_DEV_CB *dc);

/*�ӿڼĴ���(PCIEͨѶ) */
STATUS hbaDevCheckRegisterIo(HBA_DEV_CB *dc);

/*Flash��д*/
STATUS hbaDevCheckFlashRW(HBA_DEV_CB *dc);

/*ȡ��2���˿ڵ���·״ֵ̬*/
FCUINT hbaDevCheckLinkStatus(HBA_DEV_CB *dc);

/*ASM֡�Ի�*/
STATUS hbaDevCheckAsmRing(HBA_DEV_CB *dc);

/* ʱͳ����ӿ� */
/*���ýڵ��ͬ����ɫ*/
void hbaDevSyncModeSet(HBA_DEV_CB *hDev, FCUINT enab);

/*ʹ��ͬ������*/
void hbaDevSyncEnable(HBA_DEV_CB *hDev);

/*��ֹͬ������*/
void hbaDevSyncDisable(HBA_DEV_CB *hDev);

void hbaDevSetRTCRxTx(HBA_DEV_CB *hDev, FCUINT rx_enab, FCUINT tx_enab);

INT32 hbaDevIsOnNet(HBA_DEV_CB *dc);

/*�ж��豸��IO״̬*/
UINT32 HbaDevIoState(HBA_DEV_CB *dc, UINT32 mode);

/*����ʱ��ͬ������*/
void hbaDevSetClkSyncPeriod(HBA_DEV_CB *dc, int clkSyncPeriod);

/* ���ڷ���ELS֡ */
INT32 hbaElsCycleCheckTask(HBA_DEV_CB *dc);

/* ��NC�ڵ��WDT��ʱ�������*/
FCUINT hbaDevWdtCheckPeriodHandler(HBA_DEV_CB *dc);

/* NC�ڵ��WDT��������*/
UINT hbaDevNcWdtLoaderPeriodHandler(HBA_DEV_CB *dc);

/* ����ͬ������send els frame clk_sync_role=2 period send =1 user send by api 3-not send*/
UINT hbaDevDateSyncPeriodHandler(HBA_DEV_CB *dc);

/* ELS���ջص� */
INT32 hbaElsRecvTask(HBA_DEV_CB *dc);

/* ���ҵ��key */
void FillOperationKey(UINT *key, INT32 count);

/* ELS���� */
INT32 hbaElsRecv(HBA_DEV_CB *dc, FC_ELS_CONFIG *elsConfig);

/* ����ELS֡ΪELS_CONFIG�ṹ */
void hbaParseElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 *frame, UINT length, UINT port);

/* ����ELS֡ */
void hbaConstructElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 * frame, UINT *length);

/********************************************************************************/
/*������յ���ELS֡*/
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

/*���Ժ���*/
void hba_print_w_ctrl(W_CTRL *t);
void hba_print_r_ctrl(R_CTRL *t);

#ifdef __cplusplus
}
#endif  /*__cplusplus*/

#endif  /*_HBA_H*/

