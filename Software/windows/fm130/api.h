#pragma once

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// ���Ͷ���
///////////////////////////////////////////////////////////////////////////////
typedef int            FCINT;
typedef unsigned int   FCUINT;
typedef unsigned char  FCUCHAR;
typedef int           *FCHANDLE;

//
// ���ջص�����
//
typedef FCUINT (*FC_NP_RECV_FUNCPTR)(FCHANDLE hDev, void *buf, FCUINT length);

//
// �жϻص�����
//
typedef FCUINT (*FC_INT_FUNCPTR)(FCHANDLE hDev, FCUINT intCode, FCUINT param0);

///////////////////////////////////////////////////////////////////////////////
// ��������
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

// ֡ǩ������
#define FRAME_CFGID                     0x000000FC
#define FRAME_MONITORID                 0x000000FB

// ֡������
#define FRAME_FLAG_CRC_ERR              0x00000001
#define FRAME_FLAG_UNDERSIZE            0x00000002
#define FRAME_FLAG_OVERSIZE             0x00000004
#define FRAME_FLAG_NO_EOF_ERR           0x00000008
#define FRAME_FLAG_DISP_ERR             0x00000010
#define FRAME_FLAG_CODING_ERR           0x00000020

// �ж����붨��
#define IC_VOLTAGE_SUCCESS              0x100      // ��ѹ�Ӵ���ֵ��Ϊ����ֵ
#define IC_VOLTAGE_FAILED               0x101      // ��ѹ����
#define IC_TEMP_SUCCESS                 0x102      // �¶ȴӴ���ֵ��Ϊ����ֵ
#define IC_TEMP_FAILED                  0x103      // �¶ȴ���
#define IC_LINK_STATUS_SUCCESS          0x104      // link״̬�Ӵ���ֵ��Ϊ����ֵ
#define IC_LINK_STATUS_FAILED           0x105      // link״̬����
#define IC_IO_BUF_WRITE_FAILED          0x106      // �շ�������д����
#define IC_IO_BUF_READ_FAILED           0x107      // �շ�������������

//
// �ֶ��Լ���
//
typedef struct _FC_BIT_RESULT_MANUAL {
    FCUINT flash;       /* flash��д */
    FCUINT buffer;		/* �շ���������д */
    FCUINT temperature; /* �¶� */
    FCUINT voltage;     /* ��ѹ */
} FC_BIT_RESULT_MANUAL, *PFC_BIT_RESULT_MANUAL;

//
// ʱ��ṹ��
//
typedef struct _FCTime {
    FCUINT hour;        /*ʱ*/
    FCUINT minute;      /*��*/
    FCUINT second;      /*��*/
    FCUINT millisecond; /*����*/
    FCUINT microsecond; /*΢��*/
    FCUINT nanosecond;  /*����*/
} FCTime, *PFCTime;

//
// �˿�ͳ����Ϣ
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
// ��¼ͷ����
//
typedef struct _FCM_RECORD_HEADER
{
    UINT32 length;    /*��¼ͷ+֡����(����SOF CRC EOF)���ֽ���*/
    UINT32 flag;      /*������*/
    UINT32 cfgID;     /*�̶�ֵ0xFC000000*/
    UINT32 monitorID; /*�̶�ֵ0xFB000000*/
} FCM_RECORD_HEADER, *PFCM_RECORD_HEADER;

///////////////////////////////////////////////////////////////////////////////
// �豸����ӿ�
///////////////////////////////////////////////////////////////////////////////
//
// ���豸
//
FCUINT FCM_DevOpen(
    FCHANDLE *hDev,
    FCUINT DevId
);

//
// �ر��豸
//
FCUINT FCM_DevClose(
    FCHANDLE hDev
);

//
// ʹ���豸
//
FCUINT FCM_DevEnable(
    FCHANDLE hDev,
    FCUINT fcid,
    FCUINT credit_num
);

//
// ��λ�豸
//
FCUINT FCM_DevReset(
    FCHANDLE hDev
);

//
// ��ȡ�豸��N�˿�״̬
//
FCUINT FCM_DevGetState(
    FCHANDLE hDev,
    FCUINT *state
);

//
// ��ȡ�豸��N�˿ڰ汾��
//
FCUINT FCM_DevGetVersion(
    FCHANDLE hDev,
    FCUINT *version
);

//
// ע���жϽ��ջص�����
//
FCUINT FCM_DevRegMsgHandler(
    FCHANDLE hDev,
    FC_NP_RECV_FUNCPTR func
);

//
// ע���жϽ��ջص�����
//
FCUINT FCM_DevUnRegMsgHandler(
    FCHANDLE hDev
);

//
// ע���¼��жϻص�����
//
FCUINT FCM_DevRegEvtHandler(
    FCHANDLE hDev,
    FC_INT_FUNCPTR func
);

//
// ע���¼��жϻص�����
//
FCUINT FCM_DevUnRegEvtHandler(
    FCHANDLE hDev
);

//
// ȡ��ͳ����Ϣ
//
FCUINT FCM_GetNStatistics(
    FCHANDLE hDev,
    PORT_STATISTICS_INFO *stat
);

//
// �����豸��N�˿�BIT����
//
FCUINT FCM_IBit(
    FCHANDLE hDev,
    FC_BIT_RESULT_MANUAL *bitResult
);

//
// ��ȡ�豸�¶�
//
FCUINT FCM_GetTemp(
    FCHANDLE hDev,
    FCUINT *temperature
);

//
// ��ȡ�豸��ѹ
//
FCUINT FCM_GetVoltage(
    FCHANDLE hDev,
    FCUINT *voltage
);

//
// ��ȡ�豸����״̬
//
FCUINT FCM_GetWorkStatus(
    FCHANDLE hDev,
    FCUINT *status
);

///////////////////////////////////////////////////////////////////////////////
// ͨ�Ź���ӿ�
///////////////////////////////////////////////////////////////////////////////
//
// ���������ݵĻ�����
//
FCUINT FCM_RecvData(
    FCHANDLE hDev,
    void **ppBuffer,
    FCUINT *nLen
);

//
// �ͷŽ��ջ�����
//
FCUINT FCM_ReleaseBuf(
    FCHANDLE hDev,
    void *pBuffer
);

///////////////////////////////////////////////////////////////////////////////
// ʱͳ����ӿ�
///////////////////////////////////////////////////////////////////////////////
//
// ��ȡ�豸ʱ��
//
FCUINT FCM_TM_GetRtc(
    FCHANDLE hDev,
    FCTime *time
);

//
// �����豸ʱ��
//
FCUINT FCM_TM_SetRtc(
    FCHANDLE hDev,
    FCTime *time
);

//
// ��ʼ���
//
FCUINT FCM_DevStartMonitor(
    FCHANDLE hDev
);

//
// ֹͣ���
//
FCUINT FCM_DevStopMonitor(
    FCHANDLE hDev
);

//
// ��ӡ�����ĵ�����Ϣ
//
FCUINT FCM_DBG_DrvStastics(
    FCHANDLE hDev
);

#ifdef __cplusplus
}
#endif