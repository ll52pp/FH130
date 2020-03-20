#ifndef _INC_HBA_TIME
#define _INC_HBA_TIME

#define OK     0
#define ERROR  -1

VOID HbaDrvTimeToFCTime(const UINT64 time, FCTime *pFCTime);
UINT64 HbaDrvFCTimeToTime(FCTime *pFCTime);

#endif  /* _INC_HBA_TIME */

