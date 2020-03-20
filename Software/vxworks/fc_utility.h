#ifndef __FC_UTILITY_H__
#define __FC_UTILITY_H__

#include <vxworks.h>

/*���Ͷ���*/
typedef unsigned char   FCUCHAR;
typedef unsigned short  FCUSHORT;
typedef unsigned int      FCUINT;
typedef unsigned long   FCULONG;
typedef int                     FCINT;
typedef short                 FCSHORT;
typedef int                    *FCHANDLE;

/* ���֧��4���豸 */
#define MAX_DEVICE_NUM              4
/* ÿ���豸���֧��2���˿� */
#define MAX_PORT_NUM                  2

#define FC_SUCCESS                        0x00000000 /* �ɹ�*/
#define FC_FAILURE                          0x00000001 /* ���� */
#define FC_PARAMS_INVALID          0x00000002 /* ��Ч�Ĳ���  */
#define FC_LINK_DOWN                  0x00000003 /*�˿�linkdown*/
#define FC_INITIALISE_FAIL              0x00000004 /* ��ʼ��ʧ�� */
#define FC_SELF_CHECK_FAIL          0x00000005 /* �Լ�ʧ��*/
#define FC_INVALID_OP                  0x00000006 /* ��Ч�Ĳ�����ͨ��������ִ������  */
#define FC_DEV_CLOSED                 0x00000007 /* �豸�Ѿ��ر� */
#define FC_RECV_NO_DATA            0x00000008 /* û���յ����� */

/*�Լ췵��ֵ*/
#define BIT_SUCCESS                      0
#define BIT_FAILURE                        1

/*�ж����붨��*/
/*��ѹ�Ӵ���ֵ��Ϊ����ֵ*/
#define IC_VOLTAGE_SUCCESS    0x100
/*��ѹ����*/
#define IC_VOLTAGE_FAILED          0x101
/*�¶ȴӴ���ֵ��Ϊ����ֵ*/
#define IC_TEMP_SUCCESS            0x102
/*�¶ȴ���*/
#define IC_TEMP_FAILED                  0x103
/*link״̬�Ӵ���ֵ��Ϊ����ֵ*/
#define IC_LINK_STATUS_SUCCESS 0x104
/*link״̬����*/
#define IC_LINK_STATUS_FAILED  0x105

/*����1000������ʹ�ø���*/
/*��ѹ����ֵ*/
#define SC_VOLTAGE_VALUE            1000
/*��ѹ��ֵ*/
#define SC_VOLTAGE_THRESHOLD   200
/*�¶�����ֵ*/
#define SC_TEMP_VALUE                  30000
/*�¶���ֵ*/
#define SC_TEMP_THRESHOLD         70000

#define PORT_SPEED_1G                  1
#define PORT_SPEED_2G                  2

/* ���ջص����� */
typedef unsigned int (* FC_NP_RECV_FUNCPTR)(INT32 *hDev, void *pBuffer, UINT nLen);

/* �豸���ò��� */
typedef struct _DEV_CONFIG
{
    INT32 fcid;
    INT32 credit_num;         /* ���� 1-16 */
    INT32 speed;                  /* ���� 0 ����Ӧ 1-1Gbps 2-2Gbps */
    INT32 did_filter_enab;    /* ���շ���DID����ʹ�� */
    INT32 e_d_tov;      /* e_d_tovʱ�䣬��λ�Ǻ��� */
    INT32 redundant_enab; /* ����ʹ�� 0-��ֹ 1-ʹ�� */
    INT32 time_out;             /* ��ʱ���ǵ�ʱ�䣬��λ�Ǻ��� */
	FCUINT qdrBufUnitSize;     /*QDRÿһС��BUF�Ĵ�С*/
} DEV_CONFIG, *PDEV_CONFIG;

/* ʱ��ṹ�� */
typedef struct _FCTime {
    FCUINT hour;               /* ʱ  */
    FCUINT minute;           /* ��   */
    FCUINT second;          /* ��   */
    FCUINT millisecond;     /* ���� */
    FCUINT microsecond;  /* ΢�� */
    FCUINT nanosecond;   /* ���� */
} FCTime, *PFCTime;

/* ���ڽṹ�� */
typedef struct _FCDate {
    FCUINT year;         /*��*/
    FCUINT month;     /*��*/
    FCUINT day;          /*��*/
} FCDate, *PFCDate;

#endif /* __FC_UTILITY_H__ */
