#ifndef _INC_HBA_TIME
#define _INC_HBA_TIME

#include "hba.h"
#include "fc_utility.h"

/* 时统管理接口 */
/* 获取FC节点机的时间 */
void hbaDevGetRtc(HBA_DEV_CB *hDev, FCTime * pFCTime);

/* 设置FC节点机的时间 */
VOID hbaDevSetRtc(HBA_DEV_CB *hDev, FCTime * pFCTime);

/* 获取FC节点机的日期 */
VOID hbaDevGetDateTime(HBA_DEV_CB *hDev, FCDate * pFCDate, FCTime *pFCTime);

/* 设置FC节点机的日期 */
VOID hbaDevSetDate(HBA_DEV_CB *hDev, FCDate * pFCDate);


#endif  /* _INC_HBA_TIME */

