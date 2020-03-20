#include "precomp.h"

/*
 * Constants
 */
#define _MINUTE_SEC         (60)       			/* secs in a day */
#define _HOUR_SEC           (60 * 60)           /* secs in an hour */
#define _DAY_SEC            (24 * 60 * 60)      /* secs in a day */
#define _YEAR_SEC           (365 * _DAY_SEC)    /* secs in a year */
#define _FOUR_YEAR_SEC      (1461 * _DAY_SEC)   /* secs in a 4 year interval */
#define _YEAR_DAY           (365 )     			/* days in a year */
#define _BASE_YEAR          1970                /* 1970 is the base year */
#define _LEAP_YEAR_ADJUST   17                  /* Leap years 1900 - 1970 */
#define _YEARS_FROM_1900(y) (y -_BASE_YEAR + 70)

/*
 * Macro to determine if a given year, expressed as the number of years since
 * 1900, is a leap year.
 */
#define _IS_LEAP_YEAR(y)  (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))

/*
 * Number of leap years from 1970 up to, but not including, the specified year
 * (expressed as the number of years since 1900).
 */
#define _ELAPSED_LEAP_YEARS(y)  (((_YEARS_FROM_1900(y) - 1)/4) - ((_YEARS_FROM_1900(y) - 1)/100) + ((_YEARS_FROM_1900(y) + 299)/400)  - _LEAP_YEAR_ADJUST)

INT32 _lpdays[] =
{
	0, 31, 60, 91, 121, 152, 182, 213, 244, 275, 305, 335, 366
};

INT32 _days[] =
{
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};

VOID HbaDrvTimeToFCTime (const UINT64 time, FCTime *pFCTime)
{
	UINT32 tmptime;
	UINT64 second, ns;

	/* calculate seconds */
	second = time / (1000 * 1000 * 10);

	/* calculate na seconds */
	ns = (time % (1000 * 1000 * 10)) * 100;

	tmptime = second % _DAY_SEC;
	
	pFCTime->hour = (UINT32)(second / _HOUR_SEC);
	second -= (pFCTime->hour * _HOUR_SEC);
	
	pFCTime->minute = (UINT32)(second / _MINUTE_SEC);
	second -= (pFCTime->minute * _MINUTE_SEC);
	
	pFCTime->second = (UINT32)second;

	pFCTime->millisecond = (UINT32)(ns / (1000 * 1000));
	ns -= (pFCTime->millisecond) * (1000 * 1000);

	pFCTime->microsecond = (UINT32)(ns / 1000);
	ns -= (pFCTime->microsecond) * 1000;
	
	pFCTime->nanosecond = (UINT32)ns;
}

UINT64 HbaDrvFCTimeToTime (FCTime *pFCTime)
{    
    UINT64 ns;
 
	/* calculate nanoseconds */
    ns = 0;
	ns += (UINT64)pFCTime->hour * 60 * 60 * 1000 * 1000 * 1000;
	ns += (UINT64)pFCTime->minute * 60 * 1000 * 1000 * 1000;
	ns += (UINT64)pFCTime->second * 1000 * 1000 * 1000;
	ns += (UINT64)pFCTime->millisecond * 1000 * 1000;
	ns += (UINT64)pFCTime->microsecond * 1000;
	ns += (UINT64)pFCTime->nanosecond;

	ns /= 100; /* unit is 100ns */
	return ns;
}