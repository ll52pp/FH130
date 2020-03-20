/******************************************************************************
* FH130ͷ�ļ�����                                                             *
* �汾                                                                        *
* ˵��                                                                        *
******************************************************************************/

#ifndef __FH_130_API_H__
#define __FH_130_API_H__

/*���Ͷ���*/
typedef short                                    FCSHORT;
typedef int                                      FCINT;
typedef unsigned char                            FCUCHAR;
typedef unsigned short                           FCUSHORT;
typedef unsigned int                             FCUINT;
typedef unsigned long long                       FCUINT64;
typedef int                                     *FCHANDLE;

/*ASM���ջص�����*/
typedef FCUINT (* FC_ASM_RECVMSG_FUNCPTR)(FCHANDLE hDev, FCUINT msgID);

/*�жϻص�����*/
typedef FCUINT (* FC_INT_FUNCPTR)(FCHANDLE hDev, FCUINT intCode, FCUINT param0);
typedef void (* FC_MEMCPY_FUNCPTR)(void *dest, void *src, unsigned int size);


/*�Լ췵��ֵ*/
#define BIT_SUCCESS                              0
#define BIT_FAILURE                              1


#define NC_OFF_NET                               0
#define NC_ON_NET                                1

#define NT_OFF_NET                               0
#define NT_ON_NET                                1

#define NT_OFF_LINE                              0
#define NT_ON_LINE                               1


#define CONFIG_MODE_PROJECT                      0
#define CONFIG_MODE_FLASH                        1

/*�����ͼ���� */
#define FC_MAJOR_SCHEME_MAX                      128
/*ÿ����ͼ�����ÿ���� */
#define FC_MINOR_SCHEME_MAX                      4

/*��ɫ*/
#define ROLE_NC                                  1
#define ROLE_BNC                                 2 
#define ROLE_NRT                                 3

/*����ʱ�ӷ�������ģ��ʱ�ӿͻ���*/
#define CLK_SYNC_ROLE_SERVER_MASTER              1
/*����ʱ�ӿͻ���*/
#define CLK_SYNC_ROLE_CLIENT                     2

/* RTCͬ����ɫ����*/
/*1 ������- ���͹㲥��Ϣ*/
#define SYNC_MODE_SERVER                         1
/*2 �ͻ���- ���չ㲥��Ϣ*/
#define SYNC_MODE_CLIENT                         2

/*WDT���ڽ�ֹ*/
#define WDT_LOADER_PERIOD_DISABLE                0
/*WDT����ʹ��*/
#define WDT_LOADER_PERIOD_ENAB                   1
/*û���յ�ELS֡*/
#define RECV_ELS_INIT                            0
/*�Ѿ��յ�ELS֡*/
#define RECV_ELS_COMPLETE                        1

/* �����ɫ���� */
#define FC_NET_ROLE_NC                           1 /*���������*/
#define FC_NET_ROLE_BNC                          2 /*�������������*/
#define FC_NET_ROLE_NRT                          3 /*����Զ���ն�*/

#define FC_NET_CLK_SYNC_ROLE_SERVER_MASTER       1 /*����ʱ�ӷ�������ģ��ʱ�ӿͻ���*/
#define FC_NET_CLK_SYNC_ROLE_CLIENT              2 /*����ʱ�ӿͻ���*/

#define FC_SYNC_MODE_SERVER                      1 /*����RTCʱ��*/
#define FC_SYNC_MODE_CLIENT                      2 /*����RTCʱ��*/

#define FC_WDT_LOADER_PERIOD_DISABLE             0 /*WDT�������ڽ�ֹ*/
#define FC_WDT_LOADER_PERIOD_ENAB                1 /*WDT��������ʹ��*/

#define FC_WDT_LOCAL_MODE                        1 /*����ģʽ*/
#define FC_WDT_NET_MODE                          2 /*����ģʽ*/

#define FC_NODE_STATE_OFF_LINE                   0 /*�ڵ㲻����*/
#define FC_NODE_STATE_ON_LINE                    1 /*�ڵ�����*/

#define FC_PORT_STATUS_LINK_DOWN                 0 /* �˿���·DOWN */
#define FC_PORT_STATUS_LINK_UP                   1 /* �˿���·UP */

#define FC_CHANNEL_NUM_MAX                       256 /*���ͺͽ���ͨ���ĸ��������256*/

#define FC_SW_NUM_MAX                            2   /*����������Ŀ*/
#define FC_SW_PORT_NUM_MAX                       36  /*�������Ķ˿���Ŀ*/

#define FC_CONFIG_MODE_PROJECT                   0   /*����ģʽ*/
#define FC_CONFIG_MODE_FLASH                     1   /*FLASHģʽ*/

#define FC_MAJOR_SCHEME_MAX                      128 /*�����ͼ���� */
#define FC_MINOR_SCHEME_MAX                      4   /*ÿ����ͼ�����ÿ����*/

#define FC_ASM_RUN_DISABLE                       0   /*��ֹASM���ͽ���*/
#define FC_ASM_RUN_ENAB                          1   /*����ASM���ͽ���*/

#define FC_NC_BNC_MULTICAST_ADDR                 0x00FFFBFE  /*�����鲥�ţ�������NC��BNC�ڵ㷢���鲥��Ϣ*/

/* ����/������Ϣ���� */
#define MSG_TYPE_URGENCY_MSG				1
#define MSG_TYPE_EVENT_MSG					2
#define MSG_TYPE_ELS_MSG					3	/* ��������Ҫʹ�� */
#define MSG_TYPE_STREAM_MSG					4


/* �������ȼ� */
#define MAX_PRIORITY_LEVEL_NUM              4
#define PRIORITY_LEVEL_0 	                0 /* LOW , for ELS*/
#define PRIORITY_LEVEL_1  	                1	
#define PRIORITY_LEVEL_2 	                2
#define PRIORITY_LEVEL_3 	                3 /* HIGH*/

/* ��Ϣ���Ǳ�� */
#define MSG_NO_RECOVER		0	/* ��������Ϣ������󻺴���ʱ��������������Ϣ */
#define MSG_RECOVER			1	/* ��������Ϣ������󻺴���ʱ���������ϵ�һ����Ϣ��������������Ϣ */


/******************************************************************************
* �ж����붨��                                                                *
******************************************************************************/

#define IC_VOLTAGE_SUCCESS                       0x100      /*��ѹ�Ӵ���ֵ��Ϊ����ֵ*/
#define IC_VOLTAGE_FAILED                        0x101      /*��ѹ����*/
#define IC_TEMP_SUCCESS                          0x102      /*�¶ȴӴ���ֵ��Ϊ����ֵ*/
#define IC_TEMP_FAILED                           0x103      /*�¶ȴ���*/
#define IC_LINK_STATUS_SUCCESS                   0x104      /*link״̬�Ӵ���ֵ��Ϊ����ֵ*/
#define IC_LINK_STATUS_FAILED                    0x105      /*link״̬����*/
#define IC_IO_BUF_WRITE_FAILED                   0x106      /*�շ�������д����*/
#define IC_IO_BUF_READ_FAILED                    0x107      /*�շ�������������*/
#define IC_DISCARD_MSG           		         0x108      /*��Ϣ����*/
#define IC_COVER_MSG             		         0x109      /*��Ϣ����*/
#define IC_IU_TIMEOUT             		         0x10A      /*IU��ʱ*/
#define IC_IU_SEQ_ERR             		         0x10B      /*IU��ʱ*/
#define IC_IU_LENGTH_INVALID         	         0x10C      /*IU������Ч*/
#define IC_ELS_RECV_RECONSTRUCT                  0x200      /*�ع�*/
#define IC_ELS_RECV_NC_ON_NET                    0x201      /*NC����*/
#define IC_ELS_RECV_NC_TIMEOUT                   0x202      /*WDT��ʱ*/
#define IC_ELS_RECV_RECONSTRUCT_SUCCESS          0x203      /*�ع����*/
#define IC_ELS_RECV_RECONSTRUCT_FAIL             0x204      /*�ع�ʧ��*/
#define IC_NC_CONFLICT                           0x208      /*NC��ͻ*/
#define IC_NC_CHANGED                            0x209      /*NC�л�*/

/******************************************************************************
* ������
******************************************************************************/

/* ͨ�ô����� */
#define FC_SUCCESS                               0          /* �ɹ� */
#define FC_FAILURE                               0xE000FFFF /* ʧ�� */

#define FC_INVALID_HANDLE						 0xE0000001 /* ��Ч��� */
#define FC_PARAMS_INVALID   			         0xE0000002 /* ��Ч�Ĳ���  */
#define FC_INVALID_PORT_NUMBER					 0xE0000003 /* ��Ч�Ķ˿ں�*/	

/* ���ù�������� */
#define FC_DEVICE_ID_INVALID                     0xE1000001 /* ��Ч���豸ID */
#define FC_DEVICE_STATE_INVALID                  0xE1000002 /* ��Ч���豸״̬ */
#define FC_DEVICE_NOT_FOUNT                      0xE1000003 /* �豸û���ҵ� */

/* ���ù�������� */
#define FC_GET_CONFIG_FAIL   			         0xE2000001 /* ��ȡ��������ʧ�� */
#define FC_INITIALISE_FAIL   			         0xE2000002 /* ��ʼ��ʧ�� */  
#define FC_SELF_CHECK_FAIL   			         0xE2000003 /* �Լ�ʧ�� */
#define FC_HASH_CONFLICT                         0xE2000004 /* ��ϣ��ͻ */
#define FC_DEV_GET_CONFIG_FAILED                 0xE2000005 /* �豸��ȡ����ʧ�� */
#define FC_DEV_CB_INIT_FAILED                    0xE2000006 /* �豸�����ĳ�ʼ��ʧ�� */
#define FC_DEV_START_FAILED                      0xE2000007 /* �豸����ʧ�� */
#define FC_INVALID_MAJOR_SCHEME					 0xE2000008 /* ��Ч�Ĵ�汾�� */
#define FC_INVALID_MINOR_SCHEME					 0xE2000009 /* ��Ч��С�汾�� */

#define FC_INVALID_FCID					 		 0xE2000011 /* FCID��Ч */
#define FC_INVALID_NM_ROLE					 	 0xE2000012 /* ��������ɫ��Ч */
#define FC_INVALID_TM_ROLE					 	 0xE2000013 /* ʱ��ͬ����ɫ��Ч */
#define FC_INVALID_WDT_PERIOD				     0xE2000014 /* WDT��ʱ����Ч */
#define FC_INVALID_CLK_SYNC_PERIOD				 0xE2000015 /* ʱ��ͬ��������Ч */
#define FC_SEND_CHANNEL_BEYOND					 0xE2000016 /* ����ͨ����������Χ */	
#define FC_RECV_CHANNEL_BEYOND					 0xE2000017 /* ����ͨ����������Χ */
#define FC_TX_MSG_MAX_LEN_BEYOND				 0xE2000021 /* ��Ч�ķ�����Ϣ��󳤶� */
#define FC_INVALID_TX_MSG_SRC_ID				 0xE2000022 /* ��Ч�ķ�����ϢԴID */
#define FC_INVALID_TX_MSG_DST_ID				 0xE2000023 /* ��Ч�ķ�����ϢĿ��ID */
#define FC_INVALID_TX_MSG_TYPE					 0xE2000024 /* ��Ч�ķ�����Ϣ���� */
#define FC_INVALID_TX_MSG_PRIORITY               0xEC000025 /*��Ч�ķ�����Ϣ���ȼ�*/
#define FC_RX_MSG_MAX_LEN_BEYOND				 0xE2000031 /* ��Ч�Ľ�����Ϣ��󳤶� */
#define FC_INVALID_RX_MSG_TYPE					 0xE2000032 /* ��Ч�Ľ�����Ϣ���� */
#define FC_INVALID_RX_MSG_SRC_ID				 0xE2000033 /* ��Ч�Ľ�����ϢԴID */
#define FC_INVALID_RX_MSG_RECOVER				 0xE2000034 /* ��Ч�Ľ�����Ϣ���Ǳ�� */

/* ����ͨѶ����ԭ��ֵ */
#define FC_MSG_ID_INVALID   			         0xE3000001 /* ��Ч��msgID  */
#define FC_ASM_RUN_INVALID                       0xE3000002 /* ASM���п����ǽ�ֹ */
#define FC_DEV_CLOSED 					         0xE3000003 /* �豸�Ѿ��ر� */
#define FC_INVALID_RUN_CONTROL					 0xE3000004 /* ��Ч�����п���ֵ */
#define FC_PORT_LINK_DOWN                        0xE3000005 /* �˿�linkdown */

#define FC_SEND_INVALID_LENGTH                   0xE3000011 /* ��Ч�ķ��ͳ��� */
#define FC_SEND_INVALID_BUFFER                   0xE3000012 /* ��Ч�ķ��ͻ��� */
#define FC_SEND_MSG_BUFFER_EMPTY 		         0xE3000013 /* ���ͻ������� */

#define FC_RECV_INVALID_BUFFER                   0xE3000021 /* ��Ч�ķ��ͻ��� */
#define FC_RECV_LENGTH_IS_ZERO                   0xE3000022 /* �����ֽڳ������� */
#define FC_RECV_LENGTH_TOO_BIG                   0xE3000023 /* �����ֽڳ��ȳ���ASM IU������ֽڳ��� */
#define FC_RECV_LENGTH_TOO_SMALL                 0xE3000024 /* �����ֽڳ��ȳ���ASM IU������ֽڳ��� */
#define FC_RECV_NO_DATA             	         0xE3000025 /* û���յ����� */
#define FC_RECV_ASM_TIMEOUT						 0xE3000026 /* ���ճ�ʱ */

/* ʱ�ӹ������ԭ��ֵ */
#define FC_TM_INVALID_YEAR_VALUE				 0xE4000001 /* ��Ч�����ֵ */
#define FC_TM_INVALID_MONTH_VALUE				 0xE4000002 /* ��Ч���·�ֵ */
#define FC_TM_INVALID_DAY_VALUE					 0xE4000003 /* ��Ч������ֵ */
#define FC_TM_INVALID_HOUR_VALUE				 0xE4000004 /* ��Ч��ʱ��ֵ */
#define FC_TM_INVALID_MINUTE_VALUE				 0xE4000005 /* ��Ч�ķ���ֵ */
#define FC_TM_INVALID_SECOND_VALUE				 0xE4000006 /* ��Ч������ֵ */
#define FC_TM_SET_DATE_FAIL					 	 0xE4000007 /* �������ڴ��� */
#define FC_TM_SET_RTC_FAIL					 	 0xE4000008 /* ����RTCʱ����� */
#define FC_TM_ROLE_ILLE_OPERATION                0xE4000009 /* ʱ�ӽ�ɫ�ķǷ����� */
#define FC_TM_INVALID_CARRIER_RTC_SYN_MODE		 0xE400000A /* ��Ч���ذ�RTCͬ��ģʽ */	
#define FC_TM_INVALID_PLUSE_DUTY		 		 0xE400000B /* ��Ч���ذ�RTCͬ��PLUSE_DUTY */	

/* ����������ԭ��ֵ */
#define FC_NM_ROLE_SAMED                         0xE5000001 /* ��������ͬ����������ɫ */
#define FC_NM_ROLE_ILLE_OPERATION                0xE5000002 /* ��������ɫ�ķǷ����� */
#define FC_NM_NC_IS_OFF_LINE                     0xE5000003 /* NC�ڵ�û������ */
#define FC_NM_SYNC_IO_WAIT_FAILED                0xE5000004	/* ����ELS֡�Ժ�ȴ�����ELS֡��ʱ */
#define FC_NM_FRAME_SEND_FAILED                  0xE5000005 /* �����������֡ʧ�� */
#define FC_NM_INVALID_PORT_ID		 			 0xE5000006 /* ��Ч��port ID */
#define FC_NM_INVALID_PORT_COUNT				 0xE5000007 /* ��Ч�Ķ˿���Ŀ */	
#define FC_NM_INVALID_NET_TBL_INDEX				 0xE5000008 /*��Ч����������λ*/


/*�ֶ��Լ���*/
typedef struct
{
	FCUINT flash;        /*flash��д*/
	FCUINT temperature;  /*�¶�*/
	FCUINT voltage;      /*��ѹ*/	
} FC_BIT_RESULT_MANUAL;

/*�ϵ��Լ���*/
typedef struct
{
	FCUINT memory;       /*�ڴ����*/
	FCUINT reg;          /*�Ĵ�����д*/
	FCUINT temperature;  /*�¶�*/
	FCUINT voltage;      /*��ѹ*/
	FCUINT flash;        /*flash��д*/
} FC_BIT_RESULT_POWER;

/*�Լ���*/
typedef struct
{
	FCUINT memory;       /*�ڴ����*/
	FCUINT reg;          /*�Ĵ�����д*/
	FCUINT temperature;  /*�¶�*/
	FCUINT voltage;      /*��ѹ*/
	FCUINT flash;        /*flash��д*/
} FC_BIT_RESULT;

/*ʱ��ṹ��*/
typedef struct
{
	FCUINT hour;         /*ʱ*/
	FCUINT minute;       /*��*/
	FCUINT second;       /*��*/
	FCUINT millisecond;  /*����*/
	FCUINT microsecond;  /*΢��*/
	FCUINT nanosecond;   /*����*/
} FCTime;

/*FTP����*/
typedef struct
{
	FCUCHAR hostIp[16]; /*������IP��ַ�����15���ַ���\0��β*/
	FCUCHAR user[16];   /*�û��������15���ַ���\0��β*/
	FCUCHAR pwd[16];    /*���룬���15���ַ���\0��β*/
} FC_FTP_PARAM;

/*���ڽṹ��*/
typedef struct
{
	FCUINT year;         /*��*/
	FCUINT month;        /*��*/
	FCUINT day;          /*��*/
} FCDate;

/*����״̬��*/
typedef struct
{
	FCUCHAR Status[FC_SW_PORT_NUM_MAX]; /*0: off net, 1: on net*/
} OnNetTbl;

/*�ڵ�ͳ����Ϣ*/
typedef struct
{
    FCUINT RxMinFrameErrCnt[2]; /*Indicates the number of frames received that did not meet the minimum frame length requirement since this register was last read*/
    FCUINT RxMaxFrameErrCnt[2]; /*Indicates the number of frames received that exceeded the maximum frame length requirement since this register was last read*/
    FCUINT RxFrameCnt[2];       /*Indicates the number of frames received since this register was last read*/
    FCUINT RxWordCnt[2];        /*number of 32-bit data words received within FC frame(s) since this register was last read*/
    FCUINT RxPSMErrCnt[2];      /*Indicates the number of illegal PSM transactions that occurred since this register was last read*/
    FCUINT RxRRDYCnt[2];        /*Indicates the number of R_RDYs received since this register was last read*/
    FCUINT TxFrameCnt[2];       /*Indicates the number of frames transmitted since this register was last read*/
    FCUINT TxWordCnt[2];        /*Indicates the number of 32-bit data words transmitted within FC frame(s) since this register was last read*/
    FCUINT TxKErrCnt[2];        /*Indicates the number of 32-bit data words transmitted with an invalid K character since this register was last read*/
    FCUINT TxRRDYCnt[2];        /*Indicates the number of R_RDYs transmitted since this register was last read*/
} NetStatistics;

/*������link״̬��*/
typedef struct
{
	FCUCHAR Status[FC_SW_NUM_MAX][FC_SW_PORT_NUM_MAX]; /*0: off line, 1: on line*/
} SwLinkStatusTbl;

/*�������汾��*/
/*Ӧ�ô��������ڴ��ǰ���1�ֽڶ���ģ���������뷽ʽ��
����ᵼ����sizeofȡ�ṹ��Сȡ����,memcpy��ʱ�����ڴ�!!!*/
typedef struct 
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
	
	/*����汾��*/
	FCUSHORT VersionA   : 4;  /*A(0~9)(LSB=1)*/
	FCUSHORT VersionB   : 7;  /*B(00~99)(LSB=1)*/
	FCUSHORT VersionC   : 5;  /*C(00~25)�������״̬��ʶ(A~Z)*/

	/*����汾��������*/
	FCUINT BuildYear    : 12; /*��(LSB=1)*/
	FCUINT BuildMonth   : 4;  /*��(LSB=1)*/
	FCUINT BuildDay     : 5;  /*��(LSB=1)*/
    FCUINT              : 2;  /**/
	FCUINT SoftwareCode : 9;  /*�������*/
	/*����汾����ʱ��*/
	FCUINT BuildHour    : 5;  /*ʱ(LSB=1)*/
	FCUINT BuildMinute  : 6;  /*��(LSB=1)*/
	FCUINT BuildSecond  : 6;  /*��(LSB=1)*/
    FCUINT              : 15; /**/
    
#else
    
	/*����汾��*/
	FCUSHORT VersionC   : 5;  /*C(00~25)�������״̬��ʶ(A~Z)*/
	FCUSHORT VersionB   : 7;  /*B(00~99)(LSB=1)*/
	FCUSHORT VersionA   : 4;  /*A(0~9)(LSB=1)*/

	/*����汾��������*/
	FCUINT SoftwareCode : 9;  /*�������*/
	FCUINT              : 2;  /**/
	FCUINT BuildDay     : 5;  /*��(LSB=1)*/
	FCUINT BuildMonth   : 4;  /*��(LSB=1)*/
	FCUINT BuildYear    : 12; /*��(LSB=1)*/
	
	/*����汾����ʱ��*/
	FCUINT              : 15; /**/
	FCUINT BuildSecond  : 6;  /*��(LSB=1)*/
	FCUINT BuildMinute  : 6;  /*��(LSB=1)*/
	FCUINT BuildHour    : 5;  /*ʱ(LSB=1)*/
	
#endif
}__attribute__((packed,aligned(1))) SW_IMPSoftWareVersion;

/*����汾��*/
typedef struct 
{
#if _HBA_ENDIAN == _HBA_BIG_ENDIAN
	
	/*����汾��*/
	FCUSHORT VersionA   : 4;  /*A(0~9)(LSB=1)*/
	FCUSHORT VersionB   : 7;  /*B(00~99)(LSB=1)*/
	FCUSHORT VersionC   : 5;  /*C(00~25)�������״̬��ʶ(A~Z)*/

	/*����汾��������*/
	FCUINT BuildYear    : 12; /*��(LSB=1)*/
	FCUINT BuildMonth   : 4;  /*��(LSB=1)*/
	FCUINT BuildDay     : 5;  /*��(LSB=1)*/
    FCUINT              : 11;  /**/

	/*����汾����ʱ��*/
	FCUINT BuildHour    : 5;  /*ʱ(LSB=1)*/
	FCUINT BuildMinute  : 6;  /*��(LSB=1)*/
	FCUINT BuildSecond  : 6;  /*��(LSB=1)*/
	FCUINT              : 15; /**/
	
#else
	
	/*����汾��*/
	FCUSHORT VersionC   : 5;  /*C(00~25)�������״̬��ʶ(A~Z)*/
	FCUSHORT VersionB   : 7;  /*B(00~99)(LSB=1)*/
	FCUSHORT VersionA   : 4;  /*A(0~9)(LSB=1)*/

	/*����汾��������*/
    FCUINT              : 11;  /**/
    FCUINT BuildDay     : 5;  /*��(LSB=1)*/
   	FCUINT BuildMonth   : 4;  /*��(LSB=1)*/
	FCUINT BuildYear    : 12; /*��(LSB=1)*/

	/*����汾����ʱ��*/
	FCUINT              : 15; /**/
	FCUINT BuildSecond  : 6;  /*��(LSB=1)*/
	FCUINT BuildMinute  : 6;  /*��(LSB=1)*/
	FCUINT BuildHour    : 5;  /*ʱ(LSB=1)*/
	
#endif	
} FC_SoftwareVersion;


/*��������������*/
typedef struct
{
	FCUINT configMode;
	FCUINT configLength;
	FCUINT checksum;
} SwConfig;

/*������������������*/
typedef struct
{
	FCUINT endFlag;
	FCUINT length;
	FCUINT order;
	FCUCHAR configData[0];
} SwConfigData;

/*�˿���Ϣ*/
typedef struct
{
	FCUCHAR port_name[16];      /*���ض˿ڵ�����*/
    FCUINT  port_id;            /*����port_id*/
    FCUINT  port_type;          /*�˿����� 1-ASM*/
    FCUINT  credit_num;         /*����*/
    FCUINT  role;               /*�˿ڵ���������ɫ 1-��������� 2-������������� 3-�����ն�*/
	FCUINT  clk_sync_role;      /*ʱ��ͬ����ɫ 1-����ʱ�ӷ�������ģ��ʱ�ӿͻ��� 2-����ʱ�ӿͻ���*/
    FCUINT  nc_wdt_period;      /*�����������WDT��ʱ����*/
	FCUINT  wdt_loader_period;  /*WDT��������send els frame, ���ֵ�����nc_wdt_periodС */
    FCUINT  clk_sync_period;    /*ʱ��ͬ������ set to fpga*/
    FCUINT  nonblock_txmsg_num; /*�����ݿ鷢����Ϣ������*/
    FCUINT  nonblock_rxmsg_num; /*�����ݿ������Ϣ������*/
    FCUINT  block_txmsg_num;    /*���ݿ鷢����Ϣ������*/
    FCUINT  block_rxmsg_num;    /*���ݿ������Ϣ������*/
} FC_PORT_CONFIG;

/*����ͨ��*/
typedef struct 
{
	FCUCHAR msg_name[16];/*��Ϣ������*/
	FCUINT  msg_id;      /*������ϢID*/
	FCUINT  msg_type;    /*��Ϣ���� 1-���� 2-�¼� 3-����(��Ҫʹ��) 4-����Ϣ*/
	FCUINT  msg_priority;/*��Ϣ���ȼ� 0-3��0�����ȼ���ͣ�3�����ȼ���� */
	FCUINT  msg_src_id;  /*��Ϣ��ԴASM�˿�port_id*/
	FCUINT  msg_dst_id;  /*��Ϣ��Ŀ��ASM�˿�port_id*/
} FC_MSG_SEND_ITEM;

/*����ͨ��*/
typedef struct
{
	FCUCHAR msg_name[16];/*��Ϣ������*/
	FCUINT  msg_id;      /*������ϢID*/
	FCUINT  msg_max_len; /*�����Ϣ����*/
	FCUINT  msg_type;    /*��Ϣ���� 1-���� 2-�¼� 3-����(��Ҫʹ��) 4-����Ϣ*/
	FCUINT  msg_src_id;  /*��Ϣ��ԴASM�˿�port_id*/
	FCUINT  msg_recover; /*��Ϣ���ǿ��Ʊ�־0-������1-����*/
} FC_MSG_RECV_ITEM;

/*���ÿ�*/
typedef struct
{
    FC_PORT_CONFIG port_config;
	FC_MSG_SEND_ITEM send_item[FC_CHANNEL_NUM_MAX];
	FC_MSG_RECV_ITEM recv_item[FC_CHANNEL_NUM_MAX];
} CONFIG_BLOCK;

/*��ͼ*/
typedef struct
{
    CONFIG_BLOCK config_block[FC_MINOR_SCHEME_MAX];
} BLUE_PRINT;

/******************************************************************************
* �豸����ӿ�                                                                *
******************************************************************************/

/*��FC�ڵ����N�˿�,ΪFC�豸������Դ*/
FCUINT FC_NP_Open(FCHANDLE *hDev, FCUINT devId);

/*�ر�FC�ڵ����N�˿�*/
FCUINT FC_NP_Close(FCHANDLE hDev);

/*��ȡFC�ڵ����N�˿�״̬*/
FCUINT FC_NP_GetState(FCHANDLE hDev, FCUINT* fcState);

/*��ȡFC�ڵ����N�˿ڰ汾��*/
FCUINT FC_NP_GetVersion(FCHANDLE hDev, FCUINT* version);

/*��λFC�ڵ����N�˿�*/
FCUINT FC_NP_SoftReset(FCHANDLE hDev);

/*����FC�ڵ����N�˿�BIT����*/
FCUINT FC_NP_IBit(FCHANDLE hDev, FC_BIT_RESULT_MANUAL *bitResult);

/*ȡ���Լ���*/
FCUINT FC_NP_GetPuBitResult(FCHANDLE hDev, FC_BIT_RESULT_POWER *bitResult);

/*ע����������¼�������*/
FCUINT FC_NP_RegEvtHandler(FCHANDLE hDev, FC_INT_FUNCPTR func);

/*ע����������¼�������*/
FCUINT FC_NP_UnRegEvtHandler(FCHANDLE hDev);

/******************************************************************************
* ͨ�Ź���ӿ�                                                                *
******************************************************************************/

/*����FC�ڵ����ASMͨ��ģʽ*/
FCUINT FC_NP_ConfigMode(FCHANDLE hDev, FCUINT configMode);

/*����FC�ڵ����ASM����*/
FCUINT FC_NP_LoadConfig(FCHANDLE hDev, FCUINT majorScheme, FCUINT minorScheme);

/*ж��FC�ڵ����ASM����*/
FCUINT FC_NP_UnLoadConfig(FCHANDLE hDev);
    
/*��flash��������*/
FCUINT FC_NP_FlashConfig(FCHANDLE hDev);

/*����ָ����ASM��Ϣ*/
FCUINT FC_NP_SendMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT nLen);

/*����ָ����ASM��Ϣ*/
FCUINT FC_NP_RecvMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT *nLen);

/*ע��ASM��Ϣ������*/
FCUINT FC_NP_RegMsgHandler(FCHANDLE hDev, FC_ASM_RECVMSG_FUNCPTR func);

/*ע��ASM��Ϣ������*/
FCUINT FC_NP_UnRegMsgHandler(FCHANDLE hDev);

/*��ȡ��������״̬�Ƿ�����*/
FCUINT FC_NP_GetWorkStatus(FCHANDLE hDev, FCUINT *status);

/*��ȡ�¶�*/
FCUINT FC_NP_GetTemp(FCHANDLE hDev, FCINT *temperature);

/*��ȡ�˿ڵ�link״̬*/
FCUINT FC_NP_GetPortLinkStatus(FCHANDLE hDev, FCUINT port, FCUINT *status);

/*����ASM���ͺͽ���
control 0-��ֹASM���ͺͽ���
        1-����ASM���ͺͽ���
*/
FCUINT FC_NP_AsmRunControl(FCHANDLE hDev, FCUINT control);

/******************************************************************************
* ʱͳ����ӿ�                                                                *
******************************************************************************/
/*��ȡFC�ڵ����ʱ��*/
FCUINT FC_TM_GetRtc(FCHANDLE hDev, FCTime * pFCTime);

/*����FC�ڵ����ʱ��*/
FCUINT FC_TM_SetRtc(FCHANDLE hDev, FCTime * pFCTime);

/******************************************************************************
�ذ�ʱ��ͬ������
����˵����
  hDev : �豸���
  carrier_rtc_enb : 0 ��ֹ 1 - ����
  mode : 0 - �ͻ��� 1 - ������
  pluse_duty :
*******************************************************************************/
FCUINT FC_TM_SetCarrierRTCSyn(FCHANDLE hDev, FCUINT carrier_rtc_enb, FCUINT mode, FCUINT pluse_duty);

/*��ȡFC�ڵ��������*/
FCUINT FC_TM_GetDateTime(FCHANDLE hDev, FCDate *pFCDate, FCTime *pFCTime);

/*����FC�ڵ��������*/
FCUINT FC_TM_SetDate(FCHANDLE hDev, FCDate * pFCDate);

/*���ýڵ��ͬ����ɫ*/
FCUINT FC_TM_SyncModeSet(FCHANDLE hDev, FCUINT mode);

/*ȡ�ýڵ��ͬ����ɫ*/
FCUINT FC_TM_SyncModeGet(FCHANDLE hDev, FCUINT *mode);

/*ʹ��ͬ������*/
FCUINT FC_TM_SyncEnable(FCHANDLE hDev);

/*��ֹͬ������*/
FCUINT FC_TM_SyncDisable(FCHANDLE hDev);

/******************************************************************************
* �������ӿ�                                                                *
******************************************************************************/

/*���ö˿ڵ���������ɫ*/
FCUINT FC_NM_RoleSet(FCHANDLE hDev,	FCUINT value);

/*ȡ�ö˿ڵ���������ɫ*/
FCUINT FC_NM_RoleGet(FCHANDLE hDev,	FCUINT *value);

/*ȡ������״̬��*/
FCUINT FC_NM_GetOnNetTable(FCHANDLE hDev, OnNetTbl *pOnNetTbl);

/*ȡ�ñ�������״̬*/
FCUINT FC_NM_GetOnNetState(FCHANDLE hDev, FCUINT *pState);

/*ȡ�ñ���ͳ����Ϣ*/
FCUINT FC_NM_GetLocalStatistics(FCHANDLE hDev, NetStatistics * pNetStatistics);

/*���ؽ���������*/
FCUINT FC_NM_NC_LoadSwConfig(FCHANDLE hDev, FCUINT portId, SwConfig *pSwConfig);

/*���ؽ�������������*/
FCUINT FC_NM_NC_LoadSwConfigData(FCHANDLE hDev, FCUINT portId, SwConfigData *pSwConfigData);

/*ȡ�ý�����link״̬*/
FCUINT FC_NM_GetSwLinkStatus(FCHANDLE hDev, SwLinkStatusTbl *pSwLinkStatusTbl);

/*ȡ�ý������㲥��Ӧ�������Ϣ��BSP*/
FCUINT FC_NM_GetSwVersion(FCHANDLE hDev, FCUINT port, SW_IMPSoftWareVersion *pSwAppVersion, SW_IMPSoftWareVersion *pSwBspVersion);

/*�ϱ�����汾*/
FCUINT FC_NM_GetFcSoftwareVersion(FC_SoftwareVersion *pFcSoftwareVersion);

/*ȡ�ý������Լ���*/
FCUINT FC_NM_NC_GetSwBitResult(FCHANDLE hDev, FCINT port, FCUINT64 *pSwBitResult);

/*���ý�����������*/
FCUINT FC_NM_NC_SetMonitorScheme(FCHANDLE hDev, FCINT port, FCINT SchemeNo);

/*��Ȩ��������*/
FCUINT FC_NM_NC_GrantNrtOnNet(FCHANDLE hDev, FCUINT portId);

/*��Ȩ��������*/
FCUINT FC_NM_NC_GrantNrtOffNet(FCHANDLE hDev, FCUINT portId);

/*�����ع�����*/
FCUINT FC_NM_NC_NetRestruct(FCHANDLE hDev, FCUINT configNum);

/*ȡ������ڵ��Լ���*/
FCUINT FC_NM_NC_GetNrtBitResult(FCHANDLE hDev, FCUINT portId, FCUINT *pNrtBitResult);

/*ȡ������ڵ�ͳ����Ϣ*/
FCUINT FC_NM_NC_GetNetStatistics(FCHANDLE hDev, FCUINT portId, NetStatistics *pNetStatistics);

/*�ж�����ڵ��Ƿ�����*/
FCUINT FC_NM_NRT_NcIsOnNet(FCHANDLE hDev, FCUINT *pNcIsOnNet);

/*������������*/
FCUINT FC_NM_NRT_OnNetReq(FCHANDLE hDev);

/*������������*/
FCUINT FC_NM_NRT_OffNetReq(FCHANDLE hDev);

/*ʹ��WDT*/
FCUINT FC_NM_WDTEnable(FCHANDLE hDev, FCUINT mode);

/*��ֹWDT*/
FCUINT FC_NM_WDTDisable(FCHANDLE hDev, FCUINT mode);

/*ȡ��WDT��Ϣ*/
FCUINT FC_NM_GetWDTValue(FCHANDLE hDev, FCUINT *pWdt, FCUINT *pWdtLoader);

FCUINT FC_TM_BoardSyncRoleSet(FCHANDLE hDev, FCUINT role);

/*615���Ժ��� ��ȡ2��FC�˿ڵ�link״̬*/
FCUINT FC_DBG_GetAllPortStatus(FCHANDLE hDev, FCUINT *ports, FCUINT count);

/*ע���ڴ濽������*/
FCUINT FC_NP_RegMemCopyHandler(FC_MEMCPY_FUNCPTR func);


#endif /*__FH_130_API_H__*/

