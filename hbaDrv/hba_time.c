#include <vxworks.h>
#include "hba_time.h"
#include "hw.h"




int _lpdays[13] = {    0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
int _days[13] =   { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

STATUS hbaDrvDateToFCDate (const UINT32 days, FCDate * pFCDate)
{
        int calday;/* = *timp; *//* calendar time to convert */
        int islpyr = 0;                 /* is-current-year-a-leap-year flag */
        int tmpYear;
        int tmpMonth;
        int *mdays;                     /* pointer to days or lpdays */


        calday = (int)days;

        /*
         * Determine the years since 1900. Start by ignoring leap years.
         */
        tmpYear = (int)(calday / _YEAR_DAY) + _BASE_YEAR;
        calday -= ((tmpYear - _BASE_YEAR) * _YEAR_DAY);

        /*
         * Correct for elapsed leap years
         */
        calday -= _ELAPSED_LEAP_YEARS(tmpYear);

        /*
         * If we have underflowed the __time64_t range (i.e., if caltim < 0),
         * back up one year, adjusting the correction if necessary.
         */
        if ( calday < 0 ) {
            calday += _YEAR_DAY;
            tmpYear --;
            if ( _IS_LEAP_YEAR(tmpYear) ) {
                calday += 1;
                islpyr++;
            }
        }
        else
            {
            if (_IS_LEAP_YEAR(tmpYear))
               {
                    islpyr++;
               }
          }

        /*
         * tmptim now holds the value for tm_year. caltim now holds the
         * number of elapsed seconds since the beginning of that year.
         */
        pFCDate->year = tmpYear;


        /*
         * Determine months since January (0 - 11) and day of month (1 - 31)
         */
        if ( islpyr > 0 )
           {
                mdays = _lpdays;
           }
        else
        {
            mdays = _days;
        }

        for ( tmpMonth = 1 ; mdays[tmpMonth] <= calday ; tmpMonth++ ) 
        {
            ;
        }

        pFCDate->month = tmpMonth;

        pFCDate->day = (calday - mdays[tmpMonth - 1]) + 1;

        
        return OK;

}


UINT32 hbaDrvFCDateToDate (FCDate * pFCDate)
{
        
        UINT32 calday;

        /*
         * First, make sure pFCDate is reasonably close to being in range.
         */
        if ( pFCDate->year < _BASE_YEAR)
        {
            return INVALID_DATE_VALUE;
        }

        if ( (pFCDate->month < MONTH_MIN) || (pFCDate->month > MONTH_MAX))
        {
            return INVALID_DATE_VALUE;
        }

        if ( (pFCDate->day < DAY_MIN) || (pFCDate->day > DAY_MAX))
        {
            return INVALID_DATE_VALUE;
        }


 

        /*calday = (pFCDate->year - _BASE_YEAR) * 365 + _ELAPSED_LEAP_YEARS(pFCDate->year - _BASE_YEAR + 70);*/
        calday = (pFCDate->year - _BASE_YEAR) * _YEAR_DAY;
        calday += _ELAPSED_LEAP_YEARS(pFCDate->year);
        
        calday += _days[pFCDate->month - 1];
        if ((_IS_LEAP_YEAR(pFCDate->year)) && (pFCDate->month > 2))
        {
                calday ++;
        }

        calday += (pFCDate->day - 1);


        
        return calday;

}

STATUS hbaDrvTimeToFCTime (const UINT64 time, FCTime * pFCTime)
{
    UINT32 tmptime;
    UINT64 seonds;
    UINT64 ns;

    /* calculate seconds */
    seonds = time / (1000 * 1000 * 10);    

    /* calculate na seconds */
    ns = (time % (1000 * 1000 * 10)) * 100;


        
    tmptime = seonds % _DAY_SEC;
    
    pFCTime->hour = (seonds / _HOUR_SEC);
    seonds -= (pFCTime->hour * _HOUR_SEC);
    
    pFCTime->minute = (seonds / _MINUTE_SEC);
    seonds -= (pFCTime->minute * _MINUTE_SEC);
    
    pFCTime->second = seonds;



    pFCTime->millisecond = ns / (1000 * 1000);
    ns -= (pFCTime->millisecond) * (1000 * 1000);

    pFCTime->microsecond = ns / 1000;
    ns -= (pFCTime->microsecond) * 1000;
    
    pFCTime->nanosecond = ns;

    return OK;
}


/* 返回-1表示无效*/
UINT64 hbaDrvFCTimeToTime (FCTime * pFCTime)
{
        
    UINT64 caltime;
    UINT64 seonds;
    UINT64 ns;

    /*
     * First, make sure pFCTime is reasonably close to being in range.
     */
    if ( pFCTime->hour >= HOUR_MAX)
    {
        return INVALID_TIME_VALUE;
    }

    if ( pFCTime->minute >= MINUTE_MAX)
    {
        return INVALID_TIME_VALUE;
    }
    if ( pFCTime->second >= SECOND_MAX)
    {
        return INVALID_TIME_VALUE;
    }
 
    /*calculate seconds */
    seonds = ((pFCTime->hour) * _HOUR_SEC) + 
            ((pFCTime->minute) * _MINUTE_SEC)+ 
            (pFCTime->second);

    ns =  (pFCTime->millisecond * 1000 * 1000) + 
          (pFCTime->microsecond * 1000) + 
          (pFCTime->nanosecond);

    /*to 100ns unit */
    caltime = (seonds * 1000 * 1000 * 10) + (ns / 100);    
    
    return caltime;

}



/*************************************************************************************************/
/* 时统管理接口 */
/* 载板时钟同步配置 */ /* 20171108 */
void hbaSetCarrierRTCSyn(
    HBA_DEV_CB *dc, 
    UINT32 carrier_rtc_enb, 
    UINT32 mode, 
    UINT32 pluse_duty)
{
    REG_HW *reg_hw;
    
    if(dc == NULL);
    {
        printf("hbaSetCarrierRTCSyn pHbaDevCB point Fault\n");
        return;
    }
    if( pluse_duty <= 0 )
    {
        printf("hbaSetCarrierRTCSyn pluse_duty value Fault\n");
        return;
    }
    if( (mode == 0 ||  mode == 1) && (carrier_rtc_enb == 0 || carrier_rtc_enb == 1) )
    {
        reg_hw = (REG_HW *)dc->pMembaseCsr;
        hwSetCarrierRTCSyn(reg_hw, carrier_rtc_enb, mode, pluse_duty);
    }
#if 0
    ASSERT((pHbaDevCB != NULL);
    ASSERT(pluse_duty > 0);
    ASSERT(mode == 0 || mode == 1);
    ASSERT(carrier_rtc_enb == 0 || carrier_rtc_enb == 1);
    
    reg_hw = (REG_HW *)pHbaDevCB->pMembaseCsr;
    hwSetCarrierRTCSyn(reg_hw, carrier_rtc_enb, mode, pluse_duty);
#endif
}

/* 获取FC节点机的时间 */
void hbaDevGetRtc(HBA_DEV_CB *dc, FCTime * pFCTime)
{
    UINT64 time = 0;
    REG_HW *reg_hw;

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    
    hwReadRtcPrepare(reg_hw);

    hw_delay(1000);
    
    time = hwGetRtc(reg_hw);
    
    hwReadRtcFinish(reg_hw);
        
    hbaDrvTimeToFCTime(time, pFCTime);
}

/* 设置FC节点机的时间 */
INT32 hbaDevSetRtc(HBA_DEV_CB *dc, FCTime * pFCTime)
{
    UINT64 time = 0;

    time = hbaDrvFCTimeToTime (pFCTime);
    if (time == INVALID_TIME_VALUE)
    {
        /* 参数无效 */
        return ERROR;
    }
    
    hwSetRtc((REG_HW *)dc->pMembaseCsr, time);
    return OK;
}

/* 获取FC节点机的日期 */
void hbaDevGetDateTime(HBA_DEV_CB *dc, FCDate *pFCDate, FCTime *pFCTime)
{
    UINT64 time = 0;
    UINT32 date = 0;
    REG_HW *reg_hw;

    reg_hw = (REG_HW *)dc->pMembaseCsr;
    
    hwReadRtcPrepare(reg_hw);

    hw_delay(1000);

    date = hwGetDate(reg_hw);
    time = hwGetRtc(reg_hw);
    
    hwReadRtcFinish(reg_hw);

    hbaDrvDateToFCDate(date, pFCDate);
    hbaDrvTimeToFCTime(time, pFCTime);
    
}

/* 设置FC节点机的日期 */
INT32 hbaDevSetDate(HBA_DEV_CB *dc, FCDate * pFCDate)
{
    REG_HW *reg_hw;
    UINT32 date = 0;
    
    reg_hw = (REG_HW *)dc->pMembaseCsr;
    date =  hbaDrvFCDateToDate(pFCDate);
    if (date == INVALID_DATE_VALUE)
        return ERROR;
    
    hwSetDate(reg_hw, date);
    return OK;
}


