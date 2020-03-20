#ifndef _HBA_ELS_H
#define _HBA_ELS_H

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus */

#include "endian.h"


/* ----------------------  ���������ȥ��ELS����󣬱�������������Ҫ�ĺ�ͽṹ�Ķ���------------ */
#if 1    
#define MAX_TIMER_NUM 4


#define E3_0105 0
#define E3_0106 0
#define E3_0103    0
#define E3_0104    0
#define E3_0102    0
#define E3_0201    0
#define E3_0202 0

#define FC_ELS_KEY_COUNT 27


struct tagHBA_DEV_CB;

typedef struct
{
    UINT port0;
    UINT port1;
    UINT length;
    char payload[0];
}FC_ELS_CONFIG;

typedef struct
{
}CYCLE_DESC;

typedef struct
{
}ELS_IO_DESC;

#endif
/* ---------------------------------- */



#define FCID_SWITCH        0xFFFFFD

/* ���ҵ��key */
void FillOperationKey(UINT *key, INT32 count);

/* ����ELS֡ΪELS_CONFIG�ṹ */
void hbaParseElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 *frame, UINT length, UINT port);

/* ����ELS֡ */
void hbaConstructElsFrame(FC_ELS_CONFIG *elsConfig, UINT8 * frame, UINT *length);
/* 
   Huilin: ����Ķ�����Ҫ��HBA_DEV_CB�ĳ� struct tagHBA_DEV_CB, �������� HBA_DEV_CB δ�������
           ��struct tagHBA_DEV_CB���������Ϊ��ǰ���й�Ԥ�ȵ�������
*/
/* ���ڷ���ELS֡ */
INT32 hbaElsCycleCheckTask(struct tagHBA_DEV_CB *pHbaDevCB);

/* WDT��������*/
UINT hbaDevNcWdtLoaderPeriodHandler(struct tagHBA_DEV_CB *pHbaDevCB);

/* ELS���ջص� */
INT32 hbaElsRecvTask(struct tagHBA_DEV_CB *pHbaDevCB);

/*������֡����Ч��*/
UINT32 HbaDevElsCheckNmFrame(struct tagHBA_DEV_CB *dc, FC_ELS_CONFIG *r_frame);

/* ELS���� */
INT32 hbaElsRecv(struct tagHBA_DEV_CB *pHbaDevCB, FC_ELS_CONFIG *elsConfig);

/* ELS���� */
UINT32 hbaElsSend(struct tagHBA_DEV_CB *pHbaDevCB, FC_ELS_CONFIG *elsConfig);

/* ���ý�ɫ */
FCUINT hbaElsRoleSet(struct tagHBA_DEV_CB *dc, FCUINT nmRole);

/* ��ȡ��ɫ */
FCUINT hbaElsRoleGet(struct tagHBA_DEV_CB *dc, FCUINT *nmRole);


void hbaConstructE1_0102(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 config);
void hbaConstructE1_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, OnNetTbl *onNetTbl);
void hbaConstructE2_0103(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did);
void hbaConstructE1_0105(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, SwConfig *pSwConfig);
void hbaConstructE1_0106(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, SwConfigData *pSwConfigData);
void hbaConstructE1_0104(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, FCINT SchemeNo);
void hbaConstructE4_0203(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 status);
VOID hbaConstructE1_0203(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 value, FCUCHAR *onNetTblStatus, FCDate * pFCDate);
void hbaConstructE1_0204(FC_ELS_CONFIG *elsConfig, UINT32 sid, FCDate *fcDate);
void hbaConstructE1_0205(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 config);
void hbaConstructE2_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did);
void hbaConstructE2_0201(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did);
void hbaConstructE3_0201(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did, UINT32 value);
void hbaConstructE3_0202(FC_ELS_CONFIG *elsConfig, UINT32 sid, UINT32 did,  NetStatistics *pStatInfo);

#ifdef __cplusplus
}
#endif  /*__cplusplus*/

#endif  /*_HBA_ELS_H*/

