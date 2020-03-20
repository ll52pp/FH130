#include <vxworks.h>
#include "hba_time.h"
#include "hw.h"

/*
 * Constants
 */
#define _MINUTE_SEC        (60)                   /* secs in a minute */

#define _HOUR_SEC          (60 * 60)               /* secs in an hour */

#define _DAY_SEC           (24 * 60 * 60)       /* secs in a day */

#define _YEAR_SEC          (365 * _DAY_SEC)     /* secs in a year */

#define _FOUR_YEAR_SEC     (1461 * _DAY_SEC)    /* secs in a 4 year interval */

#define _YEAR_DAY          (365 )                 /* days in a year */


#define _BASE_YEAR         1970                   /* 1970 is the base year */


#define _LEAP_YEAR_ADJUST  17                   /* Leap years 1900 - 1970 */



#define _YEARS_FROM_1900(y)         (y -_BASE_YEAR + 70)             

/*
 * Macro to determine if a given year, expressed as the number of years since
 * 1900, is a leap year.
 */
#define _IS_LEAP_YEAR(y)        (((y % 4 == 0) && (y % 100 != 0)) || \
                                (y % 400 == 0))

/*
 * Number of leap years from 1970 up to, but not including, the specified year
 * (expressed as the number of years since 1900).
 */
#define _ELAPSED_LEAP_YEARS(y)  (((_YEARS_FROM_1900(y) - 1)/4) - ((_YEARS_FROM_1900(y) - 1)/100) + ((_YEARS_FROM_1900(y) + 299)/400)  - _LEAP_YEAR_ADJUST)





int _lpdays[] = {
    0, 31, 60, 91, 121, 152, 182, 213, 244, 275, 305, 335, 366
};

int _days[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};


STATUS hbaDrvDateToFCDate (const UINT32 days, FCDate * pFCDate)
{
        int calday;/* = *timp; */ /* calendar time to convert */
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
            if ( _IS_LEAP_YEAR(tmpYear) )
                islpyr++;

        /*
         * tmptim now holds the value for tm_year. caltim now holds the
         * number of elapsed seconds since the beginning of that year.
         */
        pFCDate->year = tmpYear;


        /*
         * Determine months since January (0 - 11) and day of month (1 - 31)
         */
        if ( islpyr )
            mdays = _lpdays;
        else
            mdays = _days;


        for ( tmpMonth = 1 ; mdays[tmpMonth] <= calday ; tmpMonth++ ) ;

        pFCDate->month = tmpMonth;

        pFCDate->day = calday - mdays[tmpMonth - 1] + 1;

        
        return OK;

}


UINT32 hbaDrvFCDateToDate (FCDate * pFCDate)
{
        
        UINT32 calday;

        /*
         * First, make sure pFCDate is reasonably close to being in range.
         */
        if ( pFCDate->year < _BASE_YEAR)
            return (UINT32)(-1);

        if ( pFCDate->month < 1 || pFCDate->month > 12)
            return (UINT32)(-1);

        if ( pFCDate->day < 1 || pFCDate->day > 31)
            return (UINT32)(-1);


 

        /*calday = (pFCDate->year - _BASE_YEAR) * 365 + _ELAPSED_LEAP_YEARS(pFCDate->year - _BASE_YEAR + 70);*/
        calday = (pFCDate->year - _BASE_YEAR) * 365;
        calday += _ELAPSED_LEAP_YEARS(pFCDate->year);
        
        calday += _days[pFCDate->month - 1];
        if ( _IS_LEAP_YEAR(pFCDate->year) && (pFCDate->month > 2) )
            calday ++;

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

int hbaDrvFCTimeToTime (FCTime * pFCTime, UINT32 *high, UINT32 *low)
{
        
    UINT64 caltime;
    UINT64 seconds;
    UINT64 ns;

	if(high == NULL || low == NULL)
		return -1;

    /*
     * First, make sure pFCTime is reasonably close to being in range.
     */
    if ( pFCTime->hour >= 24)
        return (-1);

    if ( pFCTime->minute >= 60)
        return (-1);

    if ( pFCTime->second >= 60)
        return (-1);

    /*calculate seconds */
    seconds = (pFCTime->hour) * _HOUR_SEC + 
            (pFCTime->minute) * _MINUTE_SEC + 
            (pFCTime->second);

    ns =  (pFCTime->millisecond * 1000 * 1000) + 
          (pFCTime->microsecond * 1000) + 
          (pFCTime->nanosecond);	

    /*to 100ns unit */
    caltime = (seconds * 1000 * 1000 * 10) + (ns / 100);

	*high = (UINT32)(caltime>>32);
	*low = (UINT32)(caltime & 0xFFFFFFFF);
    
	printf("sec=0x%llx, ns=0x%llx, caltime=0x%llx, high=0x%08x, low=0x%08x.\n", 
		seconds, ns, caltime, *high, *low);
    return  0;

}



/*************************************************************************************************/
#if 1    /* test code */
void _testCheckDayDiff(UINT32 year1, UINT32 month1, UINT32 day1, int diff, UINT32 year2, UINT32 month2, UINT32 day2)
{
    FCDate date1, date2;
    BOOL bCheck = TRUE;
    UINT dataValue;

    date1.year = year1;        
    date1.month = month1;     
    date1.day = day1;

    dataValue = hbaDrvFCDateToDate(&date1);

    dataValue += diff;
    hbaDrvDateToFCDate(dataValue, &date2);

    if (date2.year != year2 || date2.month != month2 || date2.day != day2)
    {
        bCheck = FALSE;
    }

    printf("%d-%d-%d + (%d) = %d-%d-%d : %s\n", year1, month1, day1, diff, date2.year, date2.month, date2.day, (bCheck==TRUE)?"OK":"FAILT");
}


void testCheckDays(void)
{
    _testCheckDayDiff(1970, 1, 1, 30,  1970, 1, 31);
    _testCheckDayDiff(1970, 1, 1, 31,  1970, 2, 1);
    _testCheckDayDiff(1970, 1, 1, 365, 1971, 1, 1);
    _testCheckDayDiff(1970, 1, 1, 365*2, 1972, 1, 1);
    _testCheckDayDiff(1970, 1, 1, 365*3, 1972, 12, 31);

    _testCheckDayDiff(1980, 2, 10, 18, 1980, 2, 28);
    _testCheckDayDiff(1980, 2, 10, 19, 1980, 2, 29);
    _testCheckDayDiff(1980, 2, 10, 20, 1980, 3, 1);

    _testCheckDayDiff(1981, 2, 10, 18, 1981, 2, 28);
    _testCheckDayDiff(1981, 2, 10, 19, 1981, 3, 1);
    _testCheckDayDiff(1981, 2, 10, 20, 1981, 3, 2);

    _testCheckDayDiff(2100, 2, 10, 18, 2100, 2, 28);
    _testCheckDayDiff(2100, 2, 10, 19, 2100, 3, 1);
    _testCheckDayDiff(2100, 2, 10, 20, 2100, 3, 2);

    _testCheckDayDiff(2104, 2, 10, 18, 2104, 2, 28);
    _testCheckDayDiff(2104, 2, 10, 19, 2104, 2, 29);
    _testCheckDayDiff(2104, 2, 10, 20, 2104, 3, 1);
}
#endif