#ifndef __FC_API_H__
#define __FC_API_H__

#include <vxworks.h>

/*------------------------------�豸����ӿ�------------------------------*/
/* ��FC�ڵ㿨,������Դ */
FCUINT FC_DevOpen(FCHANDLE *hDev, FCUINT DevId);
/* �ر�FC�ڵ㿨���ͷ���Դ */
FCUINT FC_DevClose(FCHANDLE hDev);

/*��λFC�ڵ㿨*/
FCUINT FC_DevReset(FCHANDLE hDev);

/* ��ȡFC�ڵ����N�˿�״̬ */
FCUINT FC_DevGetState(FCHANDLE hDev, FCUINT *state);
/* ��ȡFC�ڵ����N�˿ڰ汾�� */
FCUINT FC_DevGetVersion(FCHANDLE hDev, FCUINT *version);
/* ����FC�ڵ㿨 */
FCUINT FC_DevConfig(FCHANDLE hDev, PDEV_CONFIG dev_config);
/* ע���жϽ��ջص����� */
FCUINT FC_DevRegMsgHandler(FCHANDLE hDev, FC_NP_RECV_FUNCPTR func);
/* ע���жϽ��ջص����� */
FCUINT FC_DevUnRegMsgHandler(FCHANDLE hDev);
/*------------------------------ͨ�Ź���ӿ�------------------------------*/
/* ���������ݵĻ����� */
FCUINT FC_RecvData(FCHANDLE hDev, void **ppBuffer, FCUINT *nLen);
/* �ͷŽ��ջ����� */
FCUINT FC_ReleaseBuf(FCHANDLE hDev, void *pBuffer);
/*------------------------------ʱͳ����ӿ�------------------------------*/
/* ��ȡFC�ڵ����ʱ�� */
FCUINT FC_TM_GetRtc(FCHANDLE hDev, FCTime *time);
/* ����FC�ڵ����ʱ�� */
FCUINT FC_TM_SetRtc(FCHANDLE hDev, FCTime *time);

/*��ʼ���*/
FCUINT FC_DevStartMonitor(FCHANDLE hDev);

/*ֹͣ���*/
FCUINT FC_DevStopMonitor(FCHANDLE hDev);



#endif /* __FC_API_H__ */