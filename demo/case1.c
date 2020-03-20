#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fc_api.h"
#include "..\hbaDrv\hba.h"

#define LOGTAG   "case_1"
#define ERRO     "FALSE"
#define SUCCESS  "OK"
#define FAILED    1

FCHANDLE hDev = 0;
int devsOpen(int devId)
{
    int ret;

    if (hDev)
    {
        printf("FC - device has opened ! ");
        return FAILED;
    }

    ret = FC_NP_Open(&hDev, devId);
    if (FC_SUCCESS != ret)
    {
        printf(" FC - open erro ! devId :%d, ret :0x%08x, hdev:%p", devId, ret, hDev);
    }
    else
    {
        printf(" FC device opened ! devId :%d, ret :0x%08x, hdev :%p", devId, ret, hDev);
    }
    return ret;
}

int getState(int devId)
{
    FCUINT ret, devState;

    ret = FC_NP_GetState(hDev, &devState);
    if (FC_SUCCESS != ret)
    {
        printf("FC - link status loads erro ! devId:%d state :%s", devId, ERRO);
    }
    else
    {
        printf("FC - link status loads success ! devId :%d, state :%d", devId, devState);
    }

    return ret;
}

int nBitSet(int devId)
{
    FCUINT ret;
    FC_BIT_RESULT_MANUAL bitResult;

    ret = FC_NP_IBit(hDev, &bitResult);
    if (FC_SUCCESS != ret)
    { 
        printf("FC - n terminal port configure erro devId :%d state :%s !", devId, ERRO);
    }
    else
    {
        printf("FC - n terminal port configured ! devId :%d state :%s !", devId, SUCCESS);
        printf("hDev: % 0x, flash:%d, temperature:%d, voltage:%d ",
            bitResult.flash, bitResult.temperature, bitResult.voltage);
    }
    return ret;
}

int nBitGet(int devId)
{
    FCUINT ret;
    FC_BIT_RESULT_POWER bitResult;

    ret = FC_NP_GetPuBitResult(hDev, &bitResult);
    if (FC_SUCCESS != ret)
    {
        printf("FC - self check erro ! devId :%d, state :%s", devId, ERRO);
    }
    else
    {
        printf("FC - self check success !, flash:%d, temperature:%d, voltage:%d ",
               bitResult.flash, bitResult.temperature, bitResult.voltage);
    }
    return ret;
}

int getTemp(int devId)
{
    FCUINT ret;
    FCINT temp;

    ret = FC_NP_GetTemp(hDev, &temp);
    if (FC_SUCCESS != ret)
    {
        printf("FC - temperature check erro ! devId :%d, state £º%s, temparature:%d", devId, ERRO, temp);
    }
    else
    {
        printf("FC - temperature check success !devId :%d, state £º%s, temparature:%d", devId, SUCCESS, temp);
    }
    return ret;
}

int getLinkState(int devId)
{
    FCUINT ret, linkPort = 0, linkStatus;

    ret = FC_NP_GetPortLinkStatus(hDev, linkPort, &linkStatus);
    if (FC_SUCCESS != ret)
    {
        printf("FC - get link status erro ! devId :%d, state :%s, linkPort :%d", devId, ERRO, linkPort);
    }
    else
    {
        printf("FC - get link status success !devId :%d, state : %s, linkPort : %d", devId, SUCCESS, linkPort);
    }
    return ret;
}

int setRtc(int devId)
{
    FCUINT ret;
    FCTime rtcTime;

    rtcTime.hour = 13;
    rtcTime.minute = 9;
    rtcTime.second = 10;
    rtcTime.millisecond = 10;
    rtcTime.microsecond = 10;
    rtcTime.nanosecond = 10;

    ret = FC_TM_SetRtc(hDev, &rtcTime);
    if (FC_SUCCESS != ret)
    {
        printf("FC - rtc time set erro ! devId :%d, statu :%s", devId, ERRO);
    }
    else
    {
        printf("FC - rtc time set erro ! devId :%d, statu :%s", devId, SUCCESS);
        printf("[hour:%d minute:%d second:%d millisecond:%d microsecond:%d nanosecond:%d]\n",
            rtcTime.hour, rtcTime.minute, rtcTime.second, rtcTime.millisecond, rtcTime.microsecond, rtcTime.nanosecond);
    }
    return ret;
}

int getRtc(int devId)
{
    FCUINT ret;
    FCTime rtctime;

    memset(&rtctime, 0, sizeof(FCTime));
    ret = FC_TM_GetRtc(hDev, &rtctime);
    if (FC_SUCCESS != ret)
    {
        printf("FC - time get erro ! devId :%d state :%s", devId, ERRO);
    }
    else
    {
        printf("FC - time get success ! devId :%d state :%s", devId, SUCCESS);
        printf("[hour:%d minute:%d second:%d millisecond:%d microsecond:%d nanosecond:%d]\n",
            rtctime.hour, rtctime.minute, rtctime.second, rtctime.millisecond, rtctime.microsecond, rtctime.nanosecond);
    }
    return ret;
}


int getTime(int devId)
{
    FCUINT ret;
    FCTime time;
    FCDate date;

    memset(&time, 0, sizeof(FCTime));
    memset(&date, 0, sizeof(FCDate));
    ret = FC_TM_GetDateTime(hDev, &date, &time);
    if (FC_SUCCESS != ret)
    {
        printf("FC - get time erro ! devId :%d, state :%s", devId, ERRO);
    }
    else
    {
        printf("FC - get time success ! devId :%d, state :%s", devId, SUCCESS);
        printf("[year:%d month:%d day:%d][hour:%d minute:%d second:%d millisecond:%d microsecond:%d nanosecond:%d]\n",
            date.year, date.month, date.day,
            time.hour, time.minute, time.second, time.millisecond, time.microsecond, time.nanosecond);
    }
    return ret;
}

int setTime(int devId, FCUINT year, FCUINT month, FCUINT day)
{
    FCUINT ret;
    FCDate date;

    date.year = year;
    date.month = month;
    date.day = day;

    ret = FC_TM_SetDate(hDev, &date);
    if (FC_SUCCESS != ret)
    {
        printf("FC - set DATE erro ! devId :%d, state :%s", devId, ERRO);
        printf("year :%d, month :%d, day :%d", year, month, day);
    }
    else
    {
        printf("FC - set DATE success ! devId :%d, state :%s", devId, SUCCESS);
        printf("year :%d, month :%d, day :%d", year, month, day);
    }
    return ret;
}

int softReset(int devId)
{
    FCUINT ret;

    ret = FC_NP_SoftReset(hDev);
    if (FC_SUCCESS != ret)
    {
        printf("FC - reset erro ! devId :%d, state :%s", devId, ERRO);
    }
    else
    {
        printf("FC - reset erro ! devId :%d, state :%s", devId, SUCCESS);
    }
    return ret;
}
int prePlan(int devId)
{
    FCUINT ret, majorScheme = 0, minorScheme = 0;

    ret = FC_NP_LoadConfig(hDev, majorScheme, minorScheme);
    printf("FC_NP_LoadConfig ret=0x%08x\n", ret);
    return ret;
}
int asmSend(int devId, FCUINT len)
{


    if (FC_SUCCESS != ret)
    {
        printf("FC-data send erro ! hDev :%p, ch :%d, ret =0x%08x\n",
               hDev, ch, sendChar, len, ret);
    }
    else
    {
        printf("FC-data send success ! hDev :%p, ch :%d, ret =0x%08x\n",
               hDev, ch, ret);
    }
    return ret;

}

int asmRecv(int devId)
{


    if (FC_SUCCESS != ret)
    {
        printf("FC-data send erro ! hDev :%d, id : %d, msg :%d, len : %d, ret =0x%08x\n",
            hDev, id, &msg, len, ret);
    }
    else
    {
        printf("FC-data send success ! hDev :%d, id : %d, msg :%d, len : %d, ret =0x%08x\n",
            hDev, id, &msg, len, ret);
    }
    return ret;


}

int devClose(int devId)
{
    FCUINT ret;

    ret = FC_NP_Close(hDev);
    if (FC_SUCCESS != ret) 
    {
        printf("FC - device close erro ! devId :%d, state :%s", devId, ERRO);
    }
    else
    {
        printf("FC - device closed ! devId :%d", devId);
    }
    return ret;
}
