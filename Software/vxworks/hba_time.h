#ifndef _INC_HBA_TIME
#define _INC_HBA_TIME

#include "hba.h"
#include "fc_utility.h"

/* ʱͳ����ӿ� */
/* ��ȡFC�ڵ����ʱ�� */
void hbaDevGetRtc(HBA_DEV_CB *hDev, FCTime * pFCTime);

/* ����FC�ڵ����ʱ�� */
VOID hbaDevSetRtc(HBA_DEV_CB *hDev, FCTime * pFCTime);

/* ��ȡFC�ڵ�������� */
VOID hbaDevGetDateTime(HBA_DEV_CB *hDev, FCDate * pFCDate, FCTime *pFCTime);

/* ����FC�ڵ�������� */
VOID hbaDevSetDate(HBA_DEV_CB *hDev, FCDate * pFCDate);


#endif  /* _INC_HBA_TIME */

