#ifndef _INC_HBA_TIME
#define _INC_HBA_TIME

#include "hba.h"
#include "utils.h"


/*
 * Constants
 */
#define _MINUTE_SEC        (60)                   /* secs in a minute */

#define _HOUR_SEC          (60 * 60)               /* secs in an hour */

#define _DAY_SEC           (24 * 60 * 60)       /* secs in a day */

#define _YEAR_SEC          (365 * _DAY_SEC)     /* secs in a year */

#define _FOUR_YEAR_SEC     (1461 * _DAY_SEC)    /* secs in a 4 year interval */

#define _YEAR_DAY          (365 )                 /* days in a year */




#define _LEAP_YEAR_ADJUST  17                   /* Leap years 1900 - 1970 */


#define _BASE_YEAR         1970                   /* 1970 is the base year */


#define _YEARS_FROM_1900(y)         ((y) -_BASE_YEAR + 70)             

/*
 * Macro to determine if a given year, expressed as the number of years since
 * 1900, is a leap year.
 */
#define _IS_LEAP_YEAR(y)        ((((y) % 4 == 0) && ((y) % 100 != 0)) || \
                                ((y) % 400 == 0))

/*
 * Number of leap years from 1970 up to, but not including, the specified year
 * (expressed as the number of years since 1900).
 */
#define _ELAPSED_LEAP_YEARS(y)  (((_YEARS_FROM_1900(y) - 1)/4) - ((_YEARS_FROM_1900(y) - 1)/100) + ((_YEARS_FROM_1900(y) + 299)/400)  - _LEAP_YEAR_ADJUST)



#define HOUR_MAX    24
#define MINUTE_MAX    60
#define SECOND_MAX    60

#define MONTH_MIN    1
#define MONTH_MAX    12

#define DAY_MIN        1
#define DAY_MAX        31

#define INVALID_TIME_VALUE         ((UINT64)(-1))
#define INVALID_DATE_VALUE         ((UINT32)(-1))


/* 时统管理接口 */
/* 获取FC节点机的时间 */
void hbaDevGetRtc(HBA_DEV_CB *dc, FCTime *pFCTime);

/* 设置FC节点机的时间 */
INT32 hbaDevSetRtc(HBA_DEV_CB *dc, FCTime *pFCTime);

/* 载板时钟同步配置 */ /* 20171108 */
void hbaSetCarrierRTCSyn(HBA_DEV_CB *dc, UINT32 carrier_rtc_enb, UINT32 mode, UINT32 pluse_duty);

/* 获取FC节点机的日期 */
void hbaDevGetDateTime(HBA_DEV_CB *dc, FCDate *pFCDate, FCTime *pFCTime);

/* 设置FC节点机的日期 */
INT32 hbaDevSetDate(HBA_DEV_CB *dc, FCDate *pFCDate);


#endif  /* _INC_HBA_TIME */

