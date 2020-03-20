#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define FCM_CONFIG_FCID         0x100000
#define FCM_CONFIG_CREDIT_NUM   8
#define INT_EVT_DESC_MAX        8
#define DEV_CONFIG_SPEED        PORT_SPEED_1G

typedef struct _INT_EVT_DESC
{
    int intCode;
    int param0;
    int count;
} INT_EVT_DESC, *PINT_EVT_DESC;

typedef struct _FCM_DEMO_STATISTICS
{
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
    INT_EVT_DESC int_evt_desc[INT_EVT_DESC_MAX];
	UINT64 asm_counter[256];
} FCM_DEMO_STATISTICS, *PFCM_DEMO_STATISTICS;

// ��ʾ������ʾ
VOID Help();

// �˳�
VOID Quit();

// �����û����룬ִ������
VOID Commands();
// ���豸
VOID Test_FCM_DevOpen();
// �ر��豸
VOID Test_FCM_DevClose();
// ʹ���豸
VOID Test_FCM_DevEnable();
// ��λ�豸
VOID Test_FCM_DevReset();
// ��ȡ�豸��N�˿�״̬
VOID Test_FCM_DevGetState();
// ��ȡ�豸��N�˿ڰ汾��
VOID Test_FCM_DevGetVersion();
// ע���жϽ��ջص�����
VOID Test_FCM_DevRegMsgHandler();
// ע���жϽ��ջص�����
VOID Test_FCM_DevUnRegMsgHandler();
// ע���¼��жϻص�����
VOID Test_FCM_DevRegEvtHandler();
// ע���¼��жϻص�����
VOID Test_FCM_DevUnRegEvtHandler();
// ȡ��ͳ����Ϣ
VOID Test_FCM_GetNStatistics();
// �����豸��N�˿�BIT����
VOID Test_FCM_IBit();
// ��ȡ�豸�¶�
VOID Test_FCM_GetTemp();
// ��ȡ�豸��ѹ
VOID Test_FCM_GetVoltage();
// ��ȡ�豸����״̬
VOID Test_FCM_GetWorkStatus();
///////////////////////////////////////////////////////////////////////////////
// ͨ�Ź���ӿ�
///////////////////////////////////////////////////////////////////////////////
// ���������ݵĻ�����
VOID Test_FCM_RecvData();
///////////////////////////////////////////////////////////////////////////////
// ʱͳ����ӿ�
///////////////////////////////////////////////////////////////////////////////
// ��ȡ�豸ʱ��
VOID Test_FCM_TM_GetRtc();
// �����豸ʱ��
VOID Test_FCM_TM_SetRtc();
// ��ʼ���
VOID Test_FCM_DevStartMonitor();
// ֹͣ���
VOID Test_FCM_DevStopMonitor();
// ��������int
VOID Test_FCM_DemoStartInt();
UINT CALLBACK FCM_DemoStartInt(PVOID context);
// ֹͣ����int
VOID Test_FCM_DemoStopInt();
// ��������loop
VOID Test_FCM_DemoStartLoop();
UINT CALLBACK FCM_DemoStartLoop(PVOID context);
// ֹͣ����loop
VOID Test_FCM_DemoStopLoop();
// ��ӡͳ����Ϣ
VOID Test_PrintDemoStatistics();
// ���ͳ����Ϣ
VOID Test_ClearDemoStatistics();
// VOID Test_PrintDrvStatistics();
// ���ջص�����
FCUINT RecvCallBack(FCHANDLE hDev, void *buf, FCUINT length);
// �жϻص�����
FCUINT EvtCallBack(FCHANDLE hDev, FCUINT intCode, FCUINT param0);
VOID check_flag(UINT32 flag, PFCM_DEMO_STATISTICS v);
VOID parse_buf(char *buf, int len);
VOID parse_frame(char *buf, int length, PFCM_DEMO_STATISTICS v);
VOID print_buf(unsigned char *buf, int len);
VOID print_ibit(PFC_BIT_RESULT_MANUAL v);
VOID print_port_statistics_info(PPORT_STATISTICS_INFO v);
VOID print_fc_time(FCTime *t);
VOID print_record_header(FCM_RECORD_HEADER *r);

#ifdef __cplusplus
}
#endif