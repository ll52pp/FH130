#include <vxWorks.h>
#include <stdlib.h>
#include <stdio.h>
#include <taskLib.h>
#include <tickLib.h>
#include "fc_api.h"
#include "hw.h"
#include "hba.h"

extern BLUE_PRINT gBluePrint[];

FCHANDLE g_hDev = 0;

#if 0
#define printf logMsg
#else

#endif

#define MAX_TEST_SEND_LEN (16 * 1024 * 1024)

#define INVALID_MSG_ID -1
#define MAX_TEST_RECV_TASK_INFO 256
#define MAX_TEST_SEND_TASK_INFO 256

#define TEST_RECV_TASK_NAME "testR"
#define RECV_TASK_PRIORITY 50
#define RECV_TASK_STACK_SIZE 40960
#define RECV_TASK_OPTION 0

#define TEST_SEND_TASK_NAME "testS"
#define SEND_TASK_PRIORITY 101
#define SEND_TASK_OPTION 0
#define SEND_TASK_STACK_SIZE 40960

typedef struct tagTestSendTaskInfo
{
    int bUsed;
    int index;
    int msgId;
    int testSendEnd;
} TEST_SEND_TASK_INFO;

typedef struct tagTestRecvTaskInfo
{
    int bUsed;
    int index;
    unsigned int msgId;
    int testRecvIsEnd;
    int testRecvExit;
    int testRecvStart;
    UINT64 testRecvLen;
    UINT64 testRecvErrNum;
} TEST_RECV_TASK_INFO;

TEST_RECV_TASK_INFO testRecvTaskInfo[MAX_TEST_RECV_TASK_INFO] = {{0}};
TEST_SEND_TASK_INFO testSendTaskInfo[MAX_TEST_SEND_TASK_INFO] = {{0}};

/*--------------------------for lijun libin---------------------*/
/*测试接口预定义*/

/*第一个函数配置设备*/
int testInit(int configMode, int majorScheme, int minorScheme);

/*case 1*//*case 7*/
/*按次数发送*/
int tSendCount(int msgId, int iCiShu, int sendLen);

/*按时间发送*/
int tSendTime(int msgId, int iTimeout, int sendLen);

/*提前停止发送*/
int tStopSend(int sendMsgId);

/*case 2*//*case 7*/
/*测试接收开始，无限接收，知道调用停止接收*/
int tRecvMsgId(int recvMsgId);

/*停止接收*/
void tStopRecv(int recvMsgId);

/*打印接收信息，调用一次打印一次，不影响接收速度*/
void tPrtRecvInfo(int msgId);

/*RTC 发送测试*/
int tRtcSend();

/*RTC 接收测试*/
int tRtcRecv();

/*拆分组帧测试*/
int tChaiZu(int msgId);

/*测试接口预定义*/

/*--------------------------for lijun libin---------------------*/

/*---------------------------------------------------*/
/*打开设备*/
int tOpenDev(int devId)
{
    int ret = FC_SUCCESS;

    if(g_hDev != 0)
    {
        printf("dev had been opened!\n");
        return ret;
    }
    
    ret = FC_NP_Open(&g_hDev, devId);
    printf("FC_NP_Open devId=%d return %d\n", devId, ret);
    return ret;
}

/*关闭设备*/
int tCloseDev(int devId)
{
    int ret = FC_NP_Close(g_hDev);
    printf("FC_NP_Close devHandle=0x%x return %d\n", g_hDev, ret);
    return ret;
}

/*配置模式*/
int tConfigMode(int mode)
{
    int ret = FC_NP_ConfigMode(g_hDev, mode);
    printf("FC_NP_ConfigMode mode %d return %d!\n", mode, ret);
    return ret;
}

/*加载配置*/
int tLoadConfig(int majorScheme, int minorScheme)
{
    int ret;
    
    ret = FC_NP_LoadConfig(g_hDev, majorScheme, minorScheme);
    printf("FC_NP_LoadConfig return %d majorScheme=%d minorScheme=%d\n",
    ret, majorScheme, minorScheme);
    return ret;
}

/*获取设备链接状态*/
int tGetState(int devId)
{
    int ret;
    unsigned int state;

    ret = FC_NP_GetState(g_hDev, &state);
    printf("FC_NP_GetState devId=%d return=%d\n", devId, ret);
    printf("state=%d\n", state);

    return ret;
}

int tGetVersion(int devId)
{
    int ret;
    unsigned int version;

    ret = FC_NP_GetVersion(g_hDev, &version);
    printf("FC_NP_GetVersion devId=%d return=%d\n", devId, ret);
    printf("version=0x%x\n", version);
}


/*把当前配置存入FLASH */
int tStoreFlash()
{
    int ret;

    ret = FC_NP_FlashConfig(g_hDev);
    printf("FC_NP_LoadConfig return %d!\n",ret);

    return ret;
}


void tRecvInfoInit(int i)
{
    testRecvTaskInfo[i].bUsed = 0;
    testRecvTaskInfo[i].index = i;
    testRecvTaskInfo[i].msgId = INVALID_MSG_ID;
    testRecvTaskInfo[i].testRecvIsEnd = 0;
    testRecvTaskInfo[i].testRecvExit = 0;
    testRecvTaskInfo[i].testRecvStart = 0;
}

int tRecvInfoInitAll()
{
    int i=0;
    for(i=0;i< MAX_TEST_RECV_TASK_INFO; i++)
    {
        tRecvInfoInit(i);
    }
    
    return 0;
}

int tGetRecvInfoIndexByMsgId(int msgId)
{
    int i=0;

    if(msgId == INVALID_MSG_ID)
        return -1;

    for(i=0;i< MAX_TEST_RECV_TASK_INFO; i++)
    {
        if(testRecvTaskInfo[i].bUsed == 0)
            continue;

        testRecvTaskInfo[i].index = i;
        if(testRecvTaskInfo[i].msgId == msgId)
            return i;
    }

    return -1;
}

int tGetFreeRecvInfoIndexByMsgId(int msgId)
{
    int i=0;

    if(msgId == INVALID_MSG_ID)
        return -1;

    for(i=0;i< MAX_TEST_RECV_TASK_INFO; i++)
    {
        if(testRecvTaskInfo[i].bUsed == 1)
            continue;

        /*初始化*/
        testRecvTaskInfo[i].bUsed = 1;
        testRecvTaskInfo[i].msgId = msgId;
        testRecvTaskInfo[i].testRecvIsEnd = 0;
        testRecvTaskInfo[i].testRecvExit = 0;
        testRecvTaskInfo[i].testRecvStart = 0;
        testRecvTaskInfo[i].testRecvIsEnd = 0;
        return i;
    }

    return -1;
}

void tPrtRecvInfoByIndex(int index)
{
    printf("msgId=%d, recvTaskStart=%d, recvTaskExit=%d, recvTaskIsEnd=%d, recvLen=%llu!\n"
        ,testRecvTaskInfo[index].msgId
        ,testRecvTaskInfo[index].testRecvStart, testRecvTaskInfo[index].testRecvExit
        ,testRecvTaskInfo[index].testRecvIsEnd, testRecvTaskInfo[index].testRecvLen);
}

void tPrtRecvInfo(int msgId)
{
    int index = tGetRecvInfoIndexByMsgId(msgId);
    if(index == -1)
    {
        printf("tPrtRecvInfoByMsgId msgId=%d get msgId error!\n", msgId);
        return;
    }

    tPrtRecvInfoByIndex(index);
}

void tPrtAllRecvInfo()
{
    int i=0;
    for(i=0;i< MAX_TEST_RECV_TASK_INFO;i++)
    {
        tPrtRecvInfoByIndex(i);
    }
}

void tSendInfoInit(int i)
{
    testSendTaskInfo[i].bUsed = 0;
    testSendTaskInfo[i].index = i;
    testSendTaskInfo[i].msgId = INVALID_MSG_ID;
    testSendTaskInfo[i].testSendEnd = 0;
}

int tSendInfoInitAll()
{
    int i=0;
    for(i=0; i< MAX_TEST_SEND_TASK_INFO; i++)
    {
        tSendInfoInit(i);
    }

    return 0;
}

int tGetSendInfoIndexByMsgId(int msgId)
{
    int i=0;

    if(msgId == INVALID_MSG_ID)
        return -1;

    for(i=0;i< MAX_TEST_SEND_TASK_INFO; i++)
    {
        if(testSendTaskInfo[i].bUsed == 0)
            continue;

        testSendTaskInfo[i].index = i;
        if(testSendTaskInfo[i].msgId == msgId)
            return i;
    }

    return -1;
}


int tGetFreeSendInfoIndexByMsgId(int msgId)
{
    int i=0;

    if(msgId == INVALID_MSG_ID)
        return -1;

    for(i=0;i< MAX_TEST_SEND_TASK_INFO; i++)
    {
        if(testSendTaskInfo[i].bUsed == 1)
            continue;

        /*初始化*/
        testSendTaskInfo[i].bUsed = 1;
        testSendTaskInfo[i].msgId = msgId;
        testSendTaskInfo[i].testSendEnd = 0;
        return i;
    }

    return -1;
}


UINT32 tAsmRecvEvtInt(void *hDev, UINT32 intCode, UINT32 param0)
{
    int ret;
    UINT retLen= 0;
    
    if (IC_LINK_STATUS_SUCCESS == intCode)
    {
        printf("LINK_STATUS_SUCCESS, param0 = %d\n", param0);
    }
    if (IC_LINK_STATUS_FAILED == intCode)
    {
        printf("IC_LINK_STATUS_FAILED, param0 = %d\n", param0);
    }

    return ret;
}

/*test模块初始化*/
int testInit(int configMode, int majorScheme, int minorScheme)
{
    int ret, devId;
    
    devId = 0;
    /*configMode = CONFIG_MODE_PROJECT;*/
    
    printf("testInit start devId=%d configMode=%d majorScheme=%d minorScheme=%d\n",
        devId, configMode, majorScheme, minorScheme);

    sysClkRateSet(1000);
    
    ret = tRecvInfoInitAll();
    ret = tSendInfoInitAll();
    
    ret = tOpenDev(devId);
    if(ret != FC_SUCCESS)
        return ERROR;
    
    ret = tConfigMode(configMode);
    if(ret != FC_SUCCESS)
        return ERROR;
    
    ret = tLoadConfig(majorScheme, minorScheme);
    if(ret != FC_SUCCESS)
        return ERROR;

    ret = FC_NP_RegEvtHandler(g_hDev, (FC_INT_FUNCPTR)tAsmRecvEvtInt);
    if(ret != FC_SUCCESS)
    {
        printf("FC_NP_RegEvtHandler return error=%d!\n", ret);
        return ERROR;
    }

    return ret;
}

/*用于停止所有Demo任务*/
int testSoftResetStopFlag = 0;
int testSoftResetDev()
{
    int ret;
    
    testSoftResetStopFlag = 1;
    taskDelay(50); /*等待任务完成*/
    ret = FC_NP_SoftReset(g_hDev);
    printf("soft reset device return %d!\n", ret);
    
    testSoftResetStopFlag = 0;
    return ret;
}

int testUnloadConfigDev()
{
    int ret;
    
    testSoftResetStopFlag = 1;
    taskDelay(50); /*等待任务完成*/
    ret = FC_NP_UnLoadConfig(g_hDev);
    printf("soft reset device return %d!\n", ret);
    
    testSoftResetStopFlag = 0;
    return ret;
}


void testRecvTask(int recvMsgId)
{
    int ret = 0;
    UINT retLen= 0;
    int bufOffset = 0;
    int testRecvInfoIndex = -1;
    int recvLen = 0;
    UINT64 totalLen = 0;
    int bufLen = 3000;
    unsigned char *pBuf = NULL;

    printf("testRecvTaskId msgId=%d start!\n", recvMsgId);

    /*配置接收字符数组*/
    bufLen = MAX_IU_LEN;
    pBuf = (unsigned char*)malloc(bufLen);
    if(pBuf == NULL)
    {
        printf("testRecvTaskId msgId=%d malloc error!\n", recvMsgId);
        return;
    }
    memset(pBuf,0, bufLen);

    testRecvInfoIndex = tGetRecvInfoIndexByMsgId(recvMsgId);
    if(testRecvInfoIndex == -1)
    {
        printf("testRecvTaskId msgId=%d get msgId error!\n", recvMsgId);
        free(pBuf);
        return;
    }
    testRecvTaskInfo[testRecvInfoIndex].testRecvIsEnd = 0;
    testRecvTaskInfo[testRecvInfoIndex].testRecvStart = 1;
    testRecvTaskInfo[testRecvInfoIndex].testRecvLen = 0;
    recvLen = 0;
    bufOffset = 0;
    totalLen = 0;
    while(testRecvTaskInfo[testRecvInfoIndex].testRecvExit == 0)
    {
        if(testSoftResetStopFlag == 1)
            break;
    
        retLen = MAX_IU_LEN;
        ret = FC_NP_RecvMsg(g_hDev, recvMsgId, pBuf+bufOffset, &retLen);
        if(ret != FC_SUCCESS)
        {
            /*printf("FC_NP_RecvMsg failed return %d!\n", ret);*/
            taskDelay(1);
            continue;
        }
        else
        {
            /*printf("+");*/
        }

        totalLen += retLen;
#if 0
        bufOffset += retLen;
        if(bufOffset >= MAX_IU_LEN)
        {
            bufOffset = 0;
        }
#else
        bufOffset = 0;
#endif

        testRecvTaskInfo[testRecvInfoIndex].testRecvLen = totalLen;

    }

    free(pBuf);
    testRecvTaskInfo[testRecvInfoIndex].testRecvIsEnd = 1;
    printf("testRecvTaskId Finished msgId=%d recvLen=%llu exit!\n", recvMsgId, totalLen);
}

/*停止接收*/
void tStopRecv(int recvMsgId)
{
    int testIndex = -1;
    
    testIndex = tGetRecvInfoIndexByMsgId(recvMsgId);
    if(testIndex == -1)
    {
        printf("stopRecv msgId=%d error!\n", recvMsgId);
        return ;
    }
    
    testRecvTaskInfo[testIndex].testRecvExit = 1;
}
int tStartRecv(int recvMsgId, int testRecvTaskPriority)
{
    int testRecvTaskId = ERROR;
    int testIndex = -1;
    char testRecvTaskName[30];

    testIndex =  tGetFreeRecvInfoIndexByMsgId(recvMsgId);
    if(testIndex == -1)
    {
        printf("error: msgId is full!\n");
        return -1;
    }

    sprintf(testRecvTaskName, "%s_%d", TEST_RECV_TASK_NAME, recvMsgId);
    testRecvTaskInfo[testIndex].testRecvExit = 0;
    testRecvTaskId = taskSpawn(testRecvTaskName, testRecvTaskPriority
            ,RECV_TASK_OPTION,RECV_TASK_STACK_SIZE, (FUNCPTR)testRecvTask,
            recvMsgId,0,0,0,0,0,0,0,0,0);
    if(testRecvTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        tRecvInfoInit(testIndex);
        return -1;
    }

    return 0;
}

int waitForRecvExit(int recvMsgId)
{
    int testIndex = -1;

    testIndex =  tGetRecvInfoIndexByMsgId(recvMsgId);
    if(testIndex == -1)
    {
        printf("get msgId=%d info error!\n", recvMsgId);
        return -1;
    }

    /*等待接收结束*/
    while(1)
    {
        if(testRecvTaskInfo[testIndex].testRecvStart == 1 
                && testRecvTaskInfo[testIndex].testRecvIsEnd == 1)
            break;

        taskDelay(10);
    }

    testRecvTaskInfo[testIndex].testRecvStart = 0;
    testRecvTaskInfo[testIndex].testRecvIsEnd = 0;

    /*初始化*/
    tRecvInfoInit(testIndex);
    printf("wait testRecvTaskId msgId=%d exit Ok!\n", recvMsgId);    
    return 0;
}


int testRecvMsgIdTask(int recvMsgId)
{
    int ret;

    /*开始接收*/
    ret = tStartRecv(recvMsgId, RECV_TASK_PRIORITY);
    if(ret != OK)
    {
        printf("tRecvMsgId msgId=%d failed, return %d!\n", recvMsgId, ret);
        return -1;
    }

    printf("tRecvMsgId msgId=%d start!\n", recvMsgId);

    /*等待接收结束*/
    ret = waitForRecvExit(recvMsgId);
    printf("tRecvMsgId msgId=%d finished, ret=%d!\n", recvMsgId, ret);
    return 0;
}

/*测试接收*/
int tRecvMsgId(int recvMsgId)
{
    int testTaskId = ERROR;
    char testTaskName[30];

    sprintf(testTaskName, "%s_%d", "tRMsg", recvMsgId);
    testTaskId = taskSpawn(testTaskName, RECV_TASK_PRIORITY
            , RECV_TASK_OPTION, RECV_TASK_STACK_SIZE, testRecvMsgIdTask,
            recvMsgId, 0, 0,0,0,0,0,0,0,0);
    if(testTaskId == ERROR)
    {
        printf("tRecvMsgId msgId=%d, taskSpawn error=%d!\n", recvMsgId, errnoGet());
        return -1;
    }

    return 0;
}


/*提前停止发送*/
int tStopSend(int sendMsgId)
{
    int testIndex = -1;

    testIndex = tGetSendInfoIndexByMsgId(sendMsgId);
    if(testIndex == -1)
    {
        printf("stop Send msgId%d error!\n", sendMsgId);
        return -1;
    }

    testSendTaskInfo[testIndex].testSendEnd = 1;
    return 0;
}


/*发送一个包*/
int tSendPackage(int msgId, unsigned char *sendChar, unsigned int sendLen)
{
    int ret;
    int i;
    ret = FC_NP_SendMsg(g_hDev, msgId, sendChar, sendLen);
    /*printf("FC_NP_SendMsg msgID=%d, sendLen=%d return %d!\n", msgId, sendLen, ret);*/

    /*打印发送字符*/
    
    /*for(i=0;i < sendLen; i++)
    {
        printf("%02x ", sendChar[i]);
    }
    
    printf("\nsend end OK!\n");*/
    return ret;
}

/*按时间发，单位为秒*/
int testSendTimeTask(int iTimeout, int msgId, int sendLen, char *pUsrChar)
{
    char *sendChar = NULL;
    int ret = 0;
    int i = 0;
    UINT64 totalSendLen = 0;
    int totalTick = 0;
    int endTick = 0;
    int testInfoIndex;
    int startTick = 0;
    int *pPayload = NULL;

    testInfoIndex = tGetSendInfoIndexByMsgId(msgId);
    if(testInfoIndex == -1)
    {
        printf("testSendTime get msgId=%d info error!\n", msgId);
        return -1;
    }

    /*配置发送内容*/
    if(pUsrChar == NULL)
    {
        sendChar = (char *)malloc(sendLen);
        if(sendChar == NULL)
        {
            printf("testSendTime malloc failed!\n");
            return -1;
        }

        memset(sendChar, 0, sendLen);
        pPayload = (int*)sendChar;
        for(i=0; i < (sendLen/4); i++)
        {
            *pPayload++ = i;
        }
    }
    else
    {
        sendChar = pUsrChar;
    }

    printf("testSendTime Start time=%d, msgId=%d, sendLen=%d, pUsrChar=%p!\n", iTimeout, msgId, sendLen, pUsrChar);

    totalTick = sysClkRateGet()*iTimeout;
    startTick = tickGet();
    endTick =  totalTick + startTick;

    while(testSendTaskInfo[testInfoIndex].testSendEnd == 0)
    {
        if(testSoftResetStopFlag == 1)
            break;
    
        if(endTick <= tickGet())
            break;

        ret = tSendPackage(msgId, (unsigned char *)sendChar, (unsigned int)sendLen);
        if(ret != FC_SUCCESS)
        {
            continue;
        }

        totalSendLen += sendLen;
    }

    free(sendChar);

    tSendInfoInit(testInfoIndex);
    printf("testSendTime Finished, send msgId=%d, totalSendLen = %llu, time=%d!\n"
        , msgId, totalSendLen, (tickGet()-startTick)/sysClkRateGet());
    return 0;
}

/*单发*/
/*1可以测试Sequence; 2 SOF测试; 3 ASM帧格式测试*/
int testSendCountTask(int iCiShu, int msgId, int sendLen, unsigned char *pUsrChar)
{
    unsigned char *sendChar = NULL;
    int ret = 0;
    int i, j;
    UINT64 totalSendLen = 0;
    int testInfoIndex;
    int *pPayload = NULL;

    testInfoIndex = tGetSendInfoIndexByMsgId(msgId);
    if(testInfoIndex == -1)
    {
        printf("testSendCount get msgId=%d info error!\n", msgId);
        return -1;
    }
    if (pUsrChar == NULL)
    {    
        sendChar = (unsigned char *)malloc(sendLen*sizeof(char));
        if (sendChar == NULL)
        {
            printf("testSendCount malloc failed!\n");
            return -1;
        }
        memset(sendChar, 0, sendLen);
        
        /*pPayload = (int*)sendChar;
        for(i=0; i < (sendLen/4); i++)
        {
            *pPayload++ = i;
        }*/
        for(i=0; i < sendLen; i++)
        {    
            sendChar[i] = (UINT8)(i);
        }
    }
    else
    {
        sendChar = pUsrChar;    
    }
    
    printf("testSendCount Start ciShu=%d, msgId=%d, sendLen=%d!\n", iCiShu, msgId, sendLen);

    for (i=0;i < iCiShu; i++)
    {
        if (testSoftResetStopFlag == 1)
            break;
    
        if (testSendTaskInfo[testInfoIndex].testSendEnd == 1)
            break;

        ret = tSendPackage(msgId, sendChar, (unsigned int)sendLen);
        if (ret != FC_SUCCESS)
        {
            continue;
        }
        
        totalSendLen += sendLen;
    }

    free(sendChar);
    
#if 0
           /*计算从开始发送到释放最后一个buffer所用的时间*/
           sendBufTick = HbaDevCB[0].lastBufferTick - firstBufTick;
        printf("send buffer time is %d.\n", sendBufTick);
#endif

    tSendInfoInit(testInfoIndex);
    printf("testSendCount Finished, send msgId=%d, cishu=%d, totalLen = %llu!\n", msgId, i, totalSendLen);
    return 0;
}

/*按时间发送*/
int tSendTime(int msgId, int iTimeout, int sendLen)
{
    int testSendTaskId = ERROR;
    char testSendTaskName[30];
    int testIndex;

    if(iTimeout <= 0)
    {
        printf("send timeout param failed!\n");
        return -1;
    }

    if(sendLen <= 0 || sendLen > MAX_TEST_SEND_LEN)
    {
        printf("send length param failed, len=%d!\n", sendLen);
        return -1;
    }

    testIndex =  tGetFreeSendInfoIndexByMsgId(msgId);
    if(testIndex == -1)
    {
        printf("error: msgId is full!\n");
        return -1;
    }

    sprintf(testSendTaskName, "%s_%d", TEST_SEND_TASK_NAME, msgId);
    testSendTaskId = taskSpawn(testSendTaskName, SEND_TASK_PRIORITY
            ,0,SEND_TASK_STACK_SIZE, testSendTimeTask,
            iTimeout, (int)msgId, (int)sendLen, (int)NULL,0,0,0,0,0,0);
    if(testSendTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        tSendInfoInit(testIndex);
        return -1;
    }

    return 0;
}

/*按时间发送用户自定义的包*/
int tUsrSendTime(int msgId, int iTimeout, int sendLen, char *pUsrChar)
{
    int testSendTaskId = ERROR;
    char testSendTaskName[30];
    int testIndex;

    if(iTimeout <= 0 || pUsrChar == NULL)
    {
        printf("send timeout param failed!\n");
        return -1;
    }

    if(sendLen <= 0 || sendLen > MAX_TEST_SEND_LEN)
    {
        printf("send length param failed!\n");
        return -1;
    }

    testIndex =  tGetFreeSendInfoIndexByMsgId(msgId);
    if(testIndex == -1)
    {
        printf("error: msgId is full!\n");
        return -1;
    }

    sprintf(testSendTaskName, "%s_%d", TEST_SEND_TASK_NAME, msgId);
    testSendTaskId = taskSpawn(testSendTaskName, SEND_TASK_PRIORITY
            ,0,SEND_TASK_STACK_SIZE, testSendTimeTask,
            iTimeout, (int)msgId, (int)sendLen, (int)pUsrChar,0,0,0,0,0,0);
    if(testSendTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        tSendInfoInit(testIndex);
        return -1;
    }

    return 0;
}

/*按次数发送*/
int tSendCount(int msgId, int iCiShu, int sendLen)
{
    int testSendTaskId = ERROR;
    char testSendTaskName[30];
    int testIndex;

    if(iCiShu <= 0)
    {
        printf("send cishu param failed!\n");
        return -1;
    }

    if(sendLen <= 0 || sendLen > MAX_TEST_SEND_LEN)
    {
        printf("send length param failed!\n");
        return -1;
    }

    testIndex =  tGetFreeSendInfoIndexByMsgId(msgId);
    if(testIndex == -1)
    {
        printf("error: msgId is full!\n");
        return -1;
    }
       printf("***start task!\n");
    sprintf(testSendTaskName, "%s_%d", TEST_SEND_TASK_NAME, msgId);
    testSendTaskId = taskSpawn(testSendTaskName, SEND_TASK_PRIORITY
            , SEND_TASK_OPTION, SEND_TASK_STACK_SIZE, testSendCountTask,
            iCiShu, (int)msgId, (int)sendLen, (int)NULL, 0, 0, 0, 0, 0, 0);
    if(testSendTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        tSendInfoInit(testIndex);
        return -1;
    }

    return 0;
}

/*按次数发送用户自己定义的包*/
int tUsrSendCount(int msgId, int iCiShu, int sendLen, char *pUsrChar)
{
    int testSendTaskId = ERROR;
    char testSendTaskName[30];
    int testIndex;

    if(iCiShu <= 0 || pUsrChar == NULL)
    {
        printf("send cishu param failed!\n");
        return -1;
    }

    if(sendLen <= 0 || sendLen > MAX_TEST_SEND_LEN)
    {
        printf("send length param failed!\n");
        return -1;
    }

    testIndex =  tGetFreeSendInfoIndexByMsgId(msgId);
    if(testIndex == -1)
    {
        printf("error: msgId is full!\n");
        return -1;
    }

    sprintf(testSendTaskName, "%s_%d", TEST_SEND_TASK_NAME, msgId);
    testSendTaskId = taskSpawn(testSendTaskName, SEND_TASK_PRIORITY
            , SEND_TASK_OPTION, SEND_TASK_STACK_SIZE, testSendCountTask,
            iCiShu, (int)msgId, (int)sendLen, (int)pUsrChar,0,0,0,0,0,0);
    if(testSendTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        tSendInfoInit(testIndex);
        return -1;
    }

    return 0;
}

/*RTC 发送测试*/
int tRtcSet()
{
    int ret = 0;
    FCTime fcTime;
    fcTime.hour = 23;
    fcTime.minute = 59;
    fcTime.second = 50;
    fcTime.millisecond = 0;
    fcTime.microsecond = 0;
    fcTime.nanosecond = 0;
    ret = FC_TM_SetRtc(g_hDev, &fcTime);
    printf("rtc send finished,ret=%d!\n", ret);

    printf("rtc send finished,ret=%d, hour=%d, minute=%d, second=%d, millisecond=%d, microsecond=%d, nanosecond=%d!\n", ret,
    fcTime.hour,
    fcTime.minute,
    fcTime.second,
    fcTime.millisecond,
    fcTime.microsecond,
    fcTime.nanosecond);

    return ret;
}

/*RTC 接收测试*/
int tRtcGet()
{
    int ret = 0;
    FCTime fcTime;
    ret = FC_TM_GetRtc(g_hDev, &fcTime);

    printf("rtc recv return ret=%d, hour=%d, minute=%d, second=%d, millisecond=%d, microsecond=%d, nanosecond=%d!\n", ret,
    fcTime.hour,
    fcTime.minute,
    fcTime.second,
    fcTime.millisecond,
    fcTime.microsecond,
    fcTime.nanosecond);
    return ret;
}

/*DateTime 发送测试*/
int tDateTimeSet(int year, int month, int day)
{
    int ret = 0;
    FCDate fcDate;
    fcDate.year = year;
    fcDate.month = month;
    fcDate.day = day;

    ret = FC_TM_SetDate(g_hDev, &fcDate);
    printf("rtc send finished,ret=%d!\n", ret);

    printf("rtc send finished,ret=%d, year=%d, month=%d, day=%d!\n", ret,
    fcDate.year,
    fcDate.month,
    fcDate.day);

    return ret;
}


/*DateTime 接收测试*/
int tDateTimeGet()
{
    int ret = 0;
    FCTime fcTime;
    FCDate fcDate;
    ret = FC_TM_GetDateTime(g_hDev, &fcDate, &fcTime);

    printf("rtc recv return ret=%d, year=%d, month=%d, day=%d, hour=%d, minute=%d, second=%d,"
            "millisecond=%d, microsecond=%d, nanosecond=%d!\n", ret,
    fcDate.year,
    fcDate.month,
    fcDate.day,            
    fcTime.hour,
    fcTime.minute,
    fcTime.second,
    fcTime.millisecond,
    fcTime.microsecond,
    fcTime.nanosecond);
    return ret;
}

/*取得本地统计信息*/
int tGetLocalStat()
{

    int ret;
    NetStatistics pNetStatistics;
#if 0
    ret = FC_NM_GetLocalStatistics(g_hDev, &pNetStatistics);
    printf("FC_NM_GetLocalStatistics return=%d\n", ret);
    printf("recvFrameNum        = %lld\n", pNetStatistics.recvFrameNum);
    printf("recvIuNum           = %lld\n", pNetStatistics.recvIuNum);
    printf("recvIuErrNum        = %lld\n", pNetStatistics.recvIuErrNum);
    printf("recvFrameErrorNum   = %lld\n", pNetStatistics.recvFrameErrorNum);
    printf("recvFrameInvalidNum = %lld\n", pNetStatistics.recvFrameInvalidNum);
    printf("recvFrameDiscardNum = %lld\n", pNetStatistics.recvFrameDiscardNum);

    printf("sendFrameNum        = %lld\n", pNetStatistics.sendFrameNum);
    printf("sendIuNum           = %lld\n", pNetStatistics.sendIuNum);
#endif
    return ret;
}

int tMultiUsrSendExit = 0;

int tStopMultiSend()
{
    tMultiUsrSendExit = 1;
    return 0;
}

int testMultiUsrSendTask()
{
    int ret;
    int i,j;
    unsigned int sendLen=0;
    int iCiShu = 1;
    int msgIdNum = 256;
    UINT64 totalLen = 0;
    unsigned char * sendChar[4];

    UINT64 totalSendLen = 0;
    int totalTick = 0;
    int endTick = 0;
    int testInfoIndex;
    int startTick = 0;
    int iTimeout = 60;


    printf("testMultiUsrSendTask Start!\n");

    sendLen = 1024;
    sendChar[0] = (unsigned char *)malloc(sendLen);
    if(sendChar[0] == NULL)
    {
        printf("testMulti malloc failed!\n");
        return -1;
    }

    memset(sendChar[0], 0, sendLen);
    for(i=0; i < sendLen; i++)
    {
        sendChar[0][i] = 'A';
    }

    
    
/*
    sendChar[1] = (unsigned char *)malloc(sendLen);
    if(sendChar[1] == NULL)
    {
        printf("testMulti malloc failed!\n");
        return -1;
    }

    memset(sendChar[1], 0, sendLen);
    for(i=0; i < sendLen; i++)
    {
        sendChar[1][i] = 'B';
    }

    sendChar[2] = (unsigned char *)malloc(sendLen);
    if(sendChar[2] == NULL)
    {
        printf("testMulti malloc failed!\n");
        return -1;
    }

    memset(sendChar[2], 0, sendLen);
    for(i=0; i < sendLen; i++)
    {
        sendChar[2][i] = '1';
    }

    sendChar[3] = (unsigned char *)malloc(sendLen);
    if(sendChar[3] == NULL)
    {
        printf("testMulti malloc failed!\n");
        return -1;
    }

    memset(sendChar[3], 0, sendLen);
    for(i=0; i < sendLen; i++)
    {
        sendChar[3][i] = '2';
    }

    sendChar[4] = (unsigned char *)malloc(sendLen);
    if(sendChar[4] == NULL)
    {
        printf("testMulti malloc failed!\n");
        return -1;
    }

    memset(sendChar[4], 0, sendLen);
    for(i=0; i < sendLen; i++)
    {
        sendChar[4][i] = '3';
    }
*/
    
    totalLen = 0;
#if 1    
    for(i=0; i< iCiShu ; i++)
    {
        for(j=0; j< msgIdNum; j++)
        {

            if(testSoftResetStopFlag == 1)
                break;
        
            if(tMultiUsrSendExit == 1)
                break;
            ret = tSendPackage((j+1), sendChar[0], sendLen);
            if(ret == FC_SUCCESS)
            {
                totalLen += sendLen;
            }
        }

        if(testSoftResetStopFlag == 1)
            break;

        if(tMultiUsrSendExit == 1)
            break;
    }

    printf("testMultiUsrSendTask Finish, send ciShu=%d,totalLen=%llu!\n", i, totalLen);

    
#else

    printf("testSendTime Start time=%d, sendLen=%d!\n", iTimeout);

    totalTick = sysClkRateGet()*iTimeout;
    startTick = tickGet();
    endTick =  totalTick + startTick;

    while(tMultiUsrSendExit == 0)
    {
        if(endTick <= tickGet())
            break;

        for(j=0; j< msgIdNum; j++)
        {
            if(tMultiUsrSendExit == 1)
                break;
            ret = tSendPackage((j+1), sendChar[0], sendLen);
            if(ret == FC_SUCCESS)
            {
                totalSendLen += sendLen;
            }
        }

        if(tMultiUsrSendExit == 1)
            break;        

    }

    printf("testSendTime Finished, totalSendLen = %llu, time=%d!\n"
        ,totalSendLen, (tickGet()-startTick)/sysClkRateGet());

#endif


    for(i=0; i< 1; i++)
        free(sendChar[i]);


    return OK;
}

int tMultiUsrSend()
{
    int testMultiUsrSendId = ERROR;
    char testTaskName[30];

    tMultiUsrSendExit = 0;
    sprintf(testTaskName, "tMSendTask");
    testMultiUsrSendId = taskSpawn(testTaskName, SEND_TASK_PRIORITY
            , SEND_TASK_OPTION, SEND_TASK_STACK_SIZE, testMultiUsrSendTask,
            0,0,0,0,0,0,0,0,0,0);
    if(testMultiUsrSendId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        return -1;
    }

    return 0;
}

#if 0 /*这是多任务发送*/
int tMultiSend()
{
    int ret;

    ret = tSendTime(1, 120, 2000);
    ret = tSendTime(2, 120, 2000);
    ret = tSendTime(3, 120, 2000);
    ret = tSendTime(4, 120, 2000);

    return OK;
}
#endif

int tMultiRecvExit = 0; /*多通道接收测试退出*/
int recvMsgIdNum=256; /*多通道接收数目，必须小于或者等于配置的通道数目*/
TEST_RECV_TASK_INFO tempMultiRecvInfo[MAX_RECV_CHANNEL_NUM] = {{0}};

int tPrtMultiRecv()
{
    int i;
    for(i=0; i< recvMsgIdNum;i++)
    {
        printf("msgId=%d, totalRecvLen=%llu, totalRecvErrNum=%llu!\n", tempMultiRecvInfo[i].msgId, tempMultiRecvInfo[i].testRecvLen,
                                    tempMultiRecvInfo[i].testRecvErrNum);
    }
    return 0;

}

int testMultiRecvTask()
{
    unsigned int retLen = 0;
    int i;

    int ret = 0;
    unsigned int bufLen = 3000;
    unsigned char *pBuf = NULL;

    printf("testMultiRecvTask start!\n");

    for(i=0; i< recvMsgIdNum;i++)
    {
        tempMultiRecvInfo[i].index = i;
        tempMultiRecvInfo[i].msgId = i+1;
        tempMultiRecvInfo[i].testRecvLen = 0;
        tempMultiRecvInfo[i].testRecvErrNum = 0;
    }

    /*配置接收字符数组*/
    bufLen = MAX_IU_LEN;
    pBuf = (unsigned char*)malloc(bufLen);
    if(pBuf == NULL)
    {
        printf("testMultiRecvTask malloc error!\n");
        return ERROR;
    }
    memset(pBuf,0, bufLen);

    while(tMultiRecvExit == 0)
    {
        if(testSoftResetStopFlag == 1)
            break;
    
        for(i=0; i< recvMsgIdNum; i++)
        {
            retLen = MAX_IU_LEN;
            ret = FC_NP_RecvMsg(g_hDev, tempMultiRecvInfo[i].msgId, pBuf, &retLen);
            if(ret != FC_SUCCESS)
            {
                /*printf("FC_NP_RecvMsg failed return %d!\n", ret);*/
                tempMultiRecvInfo[i].testRecvErrNum++;                
                taskDelay(10);                
                continue;
            }
            else
            {
                /*printf("+");*/
            }

            tempMultiRecvInfo[i].testRecvLen += retLen;
        }

    }

    for(i=0; i< recvMsgIdNum;i++)
    {
        printf("msgId=%d, totalRecvLen=%llu, totalRecvErrNum=%llu!\n", tempMultiRecvInfo[i].msgId, tempMultiRecvInfo[i].testRecvLen,
                            tempMultiRecvInfo[i].testRecvErrNum);
    }

    printf("testMultiRecvTask end!\n");
    free(pBuf);
    return OK;
}


int tMultiRecv()
{
    int testMultiRecvId = ERROR;
    char testTaskName[30];

    tMultiRecvExit = 0;
    sprintf(testTaskName, "tMRecvTask");
    testMultiRecvId = taskSpawn(testTaskName, RECV_TASK_PRIORITY
            , RECV_TASK_OPTION, RECV_TASK_STACK_SIZE, testMultiRecvTask,
            0,0,0,0,0,0,0,0,0,0);
    if(testMultiRecvId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        return -1;
    }

    return 0;
}

int tStopMultiRecv()
{
    tMultiRecvExit = 1;
    
    return OK;
}

int tStopLoopBackFlag=0;
int tLoopBackStop()
{
     tStopLoopBackFlag = 1;
     return OK;
}

extern UINT32 hbaDevRecvAsmMsg(HBA_DEV_CB *dc, UINT msgID, UINT8 *pMsg, UINT *nLen, int timeout);

int printNormalLoopback = 1;

int iTest = 0;

int bCompareContent = 0;

int testLoopBackStartTask(UINT32 msgID, UINT32 msgStartLen,UINT32 msgMaxLen)
{
    unsigned char *sendBuf = NULL;
    unsigned char *recvBuf = NULL;
    unsigned int sendLen = 0;
    unsigned int retLen = 0;
    int i = 0;
    int j = 0;
    unsigned int ret;
    int thresholdRecvNum = sysClkRateGet(); /*允许接收函数失败的最大次数，这表示多长时间没收到数据*/
    int NoRecvNum=0; /*调用接收函数失败的计数*/
    int *pPayload = NULL;
    tStopLoopBackFlag = 0;
    printf("tLoopBack start msgId=%d, msgStartLen=%d, msgMaxLen=%d!\n", msgID, msgStartLen, msgMaxLen);

    
    sendBuf = (unsigned char*)malloc(msgMaxLen);
    if(sendBuf == NULL)
    {
           printf("malloc error!\n");
           return ERROR;
    }

    recvBuf = (unsigned char*)malloc( MAX_IU_LEN);
    if(recvBuf == NULL)
    {
           printf("malloc error!\n");
           return ERROR;
    }

#if 1    
    for(sendLen = msgStartLen; sendLen <= msgMaxLen; sendLen++)
#else
    for(sendLen = (msgStartLen/4)*4; sendLen <= msgMaxLen; sendLen++)
#endif        
    {
        if(testSoftResetStopFlag == 1)
            break;

        if(tStopLoopBackFlag == 1)
            break;

#if 1
        for(i=0; i < sendLen; i++)
        {    
            sendBuf[i] = (UINT8)(i);
#if 1
            if (sendBuf[i] == 0x0c || sendBuf[i] == 0xc0)
            {
                sendBuf[i] = 0x0a;
            }
            sendBuf[0] = 0xc0;
            sendBuf[1] = 0x10;
            sendBuf[sendLen-1] = 0xc0;
#endif
        }
        
        /*if ((sendLen-1)%6 == 0)
            memset(sendBuf, 0xee, sendLen);
        if ((sendLen-1)%6 == 1)
            memset(sendBuf, 0xff,sendLen);
        if ((sendLen-1)%6 == 2)
            memset(sendBuf, 0xaa,sendLen);
        if ((sendLen-1)%6 == 3)
            memset(sendBuf, 0xbb,sendLen);
        if ((sendLen-1)%6 == 4)
            memset(sendBuf, 0xaa,sendLen);
        if ((sendLen-1)%6 == 5)
            memset(sendBuf, 0xdd,sendLen);
        
           sendBuf[0] = 0xc0;
        sendBuf[1] = 0x10;
        sendBuf[sendLen-1] = 0xc0;*/
        
#else
        memset(sendBuf, 0, sendLen);
        pPayload = (int*)sendBuf;
        for(i=0; i < (sendLen/4); i++)
        {
            *pPayload++ = i;
        }

        if(sendLen % 4 == 3)
        {
            sendBuf[i] = '\x55';
            sendBuf[i+1] = '\x55';
            sendBuf[i+2] = '\x55';            
        }
        else if(sendLen %4 == 2)
        {
            sendBuf[i] = '\x66';
            sendBuf[i+1] = '\x66';
        }
        else if(sendLen %4 == 1)
        {
            sendBuf[i] = '\x77';        
        }

#endif


        if (printNormalLoopback && (sendLen % 1000) ==0)
            printf("LoopBack Len=%d start!\n", sendLen);
        ret = tSendPackage(msgID, sendBuf, sendLen);

        if (ret != FC_SUCCESS)
        {
               printf("tLoopBack Finished because FC_NP_SendMsg Error, return ret=%d last msgLen=%d!\n", ret, sendLen);
            free(recvBuf);
            free(sendBuf);
               return ERROR;
        }
        
        NoRecvNum = 0;
        while(1)
        {

            if(testSoftResetStopFlag == 1)
                break;

            retLen = MAX_IU_LEN;
            ret = hbaDevRecvAsmMsg((HBA_DEV_CB * )g_hDev, msgID, recvBuf, &retLen, WAIT_FOREVER);
            if(ret != FC_SUCCESS)
            {
                taskDelay(1);
                printf("tLoopBack failed sendLen=%d recvLen=%d return ret=%d\n", sendLen, retLen, ret);
                free(recvBuf);
                free(sendBuf);
                return ERROR;
#if 0
                NoRecvNum++;

                if(NoRecvNum > thresholdRecvNum)
                {
                    printf("tLoopBack Finished because sendLen=%d Recv Timeout!\n", sendLen);
                    free(recvBuf);
                    free(sendBuf);
                    return ERROR;
                }
#endif
                continue;
            }
#if 0
            else
            {
                NoRecvNum = 0;
            }
#endif

            if (retLen != sendLen)
            {
                printf("tLoopBack : length Error, last sendLen=%d, recvLen=%d!\n", sendLen, retLen);
                continue;
            }

        if (bCompareContent == 1)
        {
#if 1
            for(i=0; i< sendLen; i++)
            {
                if(sendBuf[i] != recvBuf[i])
                {
                    printf("tLoopBack Finished because compare Error, last sendLen=%d, index=%d, sendChar=%x, recvChar=%x!\n"
                        , sendLen,i, sendBuf[i], recvBuf[i]);
                    {
                        int j=0;
                        for(j=i+1; j< (i+20); j++)
                        {
                            printf("%02x_", recvBuf[j]);

                            if(j % 32 == 0)
                            printf("_\n");
                        }
                    }
                    free(recvBuf);
                    free(sendBuf);
                    return ERROR;
                    
                }
            }
#else
            if (memcmp(sendBuf, recvBuf, sendLen) !=0)
            {
                printf("tLoopBack Finished because compare Error, last sendLen=%d!\n", sendLen);
                return ERROR;
            }    
#endif
        }
            /*tLoopBack 停止收*/
            if(tStopLoopBackFlag == 1)
                break;

            if (printNormalLoopback && (sendLen % 1000) ==0)
                printf("LoopBack Len=%d success, tick=%u!\n", sendLen, tickGet());
            
            break;
            }
    }

    free(recvBuf);
    free(sendBuf);
    printf("testAsmMsgLoopBack Finished Success, last sendLen=%d!\n", (sendLen-1));
    return OK;
}

/*自环测试*/
int tLoopBackStart(UINT32 msgID, UINT32 msgStartLen,UINT32 msgEndLen)
{
    int testTaskId = ERROR;
    char testTaskName[30] = {'\0'};

    if(msgStartLen == 0)
        msgStartLen = 1;

    if(msgStartLen > msgEndLen)
    {
        printf("tLoopBack Error because params error msgStartLen=%d, msgEndLen=%d!\n", msgStartLen, msgEndLen);
    }

    sprintf(testTaskName, "%s_%d", "LpBk", msgID);
    testTaskId = taskSpawn(testTaskName, 100
            , 0, 40960, testLoopBackStartTask,
            msgID, msgStartLen, msgEndLen,0,0,0,0,0,0,0);
    if(testTaskId == ERROR)
    {
        printf("tLoopBackStart msgId=%d, taskSpawn error=%d!\n", msgID, errnoGet());
        return -1;
    }

    return 0;
}

/*----------双工测试--------------------------------*/
int dualStopSend = 0;
int dualStopRecv = 0;

/*发送多少次delay 一下*/
int testDelayMaxCount = 1000;
/*无限发*/
int testSendLoopTask(int msgId, int sendLen)
{
    char *sendChar = NULL;
    int ret = 0;
    int i = 0;
    UINT64 totalSendLen = 0;
    int *pPayload = NULL;
    int iCount = 0;    

    /*配置发送内容*/

    sendChar = (char *)malloc(sendLen);
    if(sendChar == NULL)
    {
        printf("testSendTime malloc failed!\n");
        return -1;
    }

    memset(sendChar, 0, sendLen);
    pPayload = (int*)sendChar;
    for(i=0; i < (sendLen/4); i++)
    {
        *pPayload++ = i;
    }

    printf("dualSend Start msgId=%d, sendLen=%d, pUsrChar=%p!\n", msgId, sendLen, sendChar);

    while(dualStopSend == 0)
    {

        if(testSoftResetStopFlag == 1)
            break;
    
        ret = tSendPackage(msgId, (unsigned char *)sendChar, (unsigned int)sendLen);
        if(ret != FC_SUCCESS)
        {
            taskDelay(1);
            continue;
        }
        else
        {
            taskDelay(1);
            printf("+");
            
            iCount ++;

            if (iCount >= testDelayMaxCount)
            {
                taskDelay(1);
                iCount = 0;
            }
        }

        totalSendLen += sendLen;
    }

    free(sendChar);

    printf("dualSend Finished, send msgId=%d, totalSendLen = %llu!\n"
        , msgId, totalSendLen);
    return 0;
}

/*双工一直收*/
int testRecvLoopTask(int recvMsgId)
{
    int ret = 0;
    UINT retLen= 0;
    int recvLen = 0;
    UINT64 totalLen = 0;
    int bufLen = 0;
    unsigned char *pBuf = NULL;

    printf("dualRecv msgId=%d start!\n", recvMsgId);

    /*配置接收字符数组*/
    bufLen = MAX_IU_LEN;
    pBuf = (unsigned char*)malloc(bufLen);
    if(pBuf == NULL)
    {
        printf("dualRecv msgId=%d malloc error!\n", recvMsgId);
        return -1;
    }
    memset(pBuf,0, bufLen);

    recvLen = 0;
    totalLen = 0;
    while(dualStopRecv == 0)
    {
        if(testSoftResetStopFlag == 1)
            break;

#if 0    
        retLen = MAX_IU_LEN;
        ret = FC_NP_RecvMsg(g_hDev, recvMsgId, pBuf, &retLen);
#else
        retLen = MAX_IU_LEN;
        ret = hbaDevRecvAsmMsg((HBA_DEV_CB * )g_hDev, recvMsgId, pBuf, &retLen, WAIT_FOREVER);
#endif
        
        if(ret != FC_SUCCESS)
        {
            printf("FC_NP_RecvMsg failed return %d!\n", ret);
            /*taskDelay(1);*/
            continue;
        }
        else
        {
            /*printf("+");*/
            printf("-");
        }

        totalLen += retLen;
    }

    free(pBuf);
    printf("dualRecv Finished msgId=%d recvLen=%llu exit!\n", recvMsgId, totalLen);

    return 0;
}

/*双工开始*/
int dualSendRecvStart(int msgId)
{/*testInit 0,1,1*/
    int testTaskId = ERROR;
    int sendLen = 10000;

    dualStopSend = 0;
    dualStopRecv = 0;

    testTaskId = taskSpawn("dualRecv", RECV_TASK_PRIORITY
            , RECV_TASK_OPTION, RECV_TASK_STACK_SIZE, testRecvLoopTask,
            msgId, 0,0,0,0,0,0,0,0,0);
    if(testTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        return -1;
    }    

    testTaskId = taskSpawn("dualSend", SEND_TASK_PRIORITY
            , SEND_TASK_OPTION, SEND_TASK_STACK_SIZE, testSendLoopTask,
            (int)msgId, (int)sendLen,0,0,0,0,0,0,0,0);
    if(testTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        return -1;
    }    

    printf("dualSendRecv Start!\n");
    return 0;
}


/*双工结束*/
int dualSendRecvStop()
{
    dualStopSend = 1;
    dualStopRecv = 1;
    
    return OK;
}

/*----优先级测试------*/

extern VOID testElsSendFrame(HBA_DEV_CB *pHbaDevCB, int length, int count);

int testPriorityStop = 0;
int tPrioritySendStop()
{
    testPriorityStop = 1;
    
    return OK;
}

/*发送高优先级*/
int testSendHighPriTask(int msgId, int sendLen)
{
    char *sendChar = NULL;
    int ret = 0;
    int i = 0;
    UINT64 totalSendLen = 0;
    int *pPayload = NULL;
    int iCount = 0;    

    /*配置发送内容*/

    sendChar = (char *)malloc(sendLen);
    if(sendChar == NULL)
    {
        printf("testSendTime malloc failed!\n");
        return -1;
    }

    memset(sendChar, 0, sendLen);
    pPayload = (int*)sendChar;
    for(i=0; i < (sendLen/4); i++)
    {
        *pPayload++ = i;
    }

    printf("testSendHighPriTask Start msgId=%d, sendLen=%d, pUsrChar=%p!\n", msgId, sendLen, sendChar);

    while(testPriorityStop == 0)
    {

        if(testSoftResetStopFlag == 1)
            break;
    
        ret = tSendPackage(msgId, (unsigned char *)sendChar, (unsigned int)sendLen);
        if(ret != FC_SUCCESS)
        {
            continue;
        }
        else
        {
            iCount ++;

            if (iCount >= 2)
            {
                taskDelay(10);
                iCount = 0;
            }
        }

        totalSendLen += sendLen;
    }

    free(sendChar);

    printf("testSendHighPriTask Finished, send msgId=%d, totalSendLen = %llu!\n"
        , msgId, totalSendLen);
    return 0;
}


/*发送低优先级*/
int testSendLowPriTask(int msgId, int sendLen)
{
    char *sendChar = NULL;
    int ret = 0;
    int i = 0;
    UINT64 totalSendLen = 0;
    int *pPayload = NULL;
    int iCount = 0;    

    /*配置发送内容*/

    sendChar = (char *)malloc(sendLen);
    if(sendChar == NULL)
    {
        printf("testSendTime malloc failed!\n");
        return -1;
    }

    memset(sendChar, 0, sendLen);
    pPayload = (int*)sendChar;
    for(i=0; i < (sendLen/4); i++)
    {
        *pPayload++ = i;
    }

    printf("testSendLowPriTask Start msgId=%d, sendLen=%d, pUsrChar=%p!\n", msgId, sendLen, sendChar);

    while(testPriorityStop == 0)
    {

        if(testSoftResetStopFlag == 1)
            break;
    
        ret = tSendPackage(msgId, (unsigned char *)sendChar, (unsigned int)sendLen);
        if(ret != FC_SUCCESS)
        {
            continue;
        }
        else
        {
            iCount ++;

            if (iCount >= 2)
            {
                taskDelay(10);
                iCount = 0;
            }
        }

        totalSendLen += sendLen;
    }

    free(sendChar);

    printf("testSendLowPriTask Finished, send msgId=%d, totalSendLen = %llu!\n"
        , msgId, totalSendLen);
    return 0;
}


/*发送ELS 帧*/
int testSendElsTask(int sendLen)
{
#if 0    
    char *sendChar = NULL;
    UINT64 totalSendLen = 0;
    int iCount = 0;    

    printf("testSendElsTask Start sendLen=%d!\n", sendLen);

    while(testPriorityStop == 0)
    {

        if(testSoftResetStopFlag == 1)
            break;
    
        testElsSendFrame((HBA_DEV_CB *)g_hDev, sendLen, 1);
        iCount ++;

        if (iCount >= 2)
        {
            taskDelay(10);
            iCount = 0;
        }

        totalSendLen += sendLen;
    }

    free(sendChar);

    printf("testSendElsTask Finished, send msgId=%d, totalSendLen = %llu!\n"
        , totalSendLen);
#endif    
    return 0;
}



int tPrioritySendStart()
{/* testInit 0,1,2*/
    int testTaskId = ERROR;
    int highMsgId = 3;
    int highMsgLen = 1000;
    int lowMsgId = 4;
    int lowMsgLen = 100000;
    int elsLen = 100;
    testTaskId = taskSpawn("HPriSend", SEND_TASK_PRIORITY
            , SEND_TASK_OPTION, SEND_TASK_STACK_SIZE, testSendHighPriTask,
            (int)highMsgId, (int)highMsgLen,0,0,0,0,0,0,0,0);
    if(testTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        return -1;
    }

    testTaskId = taskSpawn("LPriSend", SEND_TASK_PRIORITY
            , SEND_TASK_OPTION, SEND_TASK_STACK_SIZE, testSendLowPriTask,
            (int)lowMsgId, (int)lowMsgLen,0,0,0,0,0,0,0,0);
    if(testTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        return -1;
    }

    testTaskId = taskSpawn("ElsSend", SEND_TASK_PRIORITY
            , SEND_TASK_OPTION, SEND_TASK_STACK_SIZE, testSendElsTask,
            (int)elsLen, 0,0,0,0,0,0,0,0,0);
    if(testTaskId == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        return -1;
    }

    return 0;

}

/*----优先级测试------*/

/*---- Flash测试----*/
extern BLUE_PRINT gBluePrint[];
extern int gBluePrintNum;
#if 0
extern INT32 hbaDevFlashConfigWrite(HBA_DEV_CB * pHbaDevCB, CONFIG_BLOCK *cb, UINT32 majorSchemeNum, UINT32 minorSchemeNum);

int testFlashWriteBlueprint()
{
    int i,j,ret;
    CONFIG_BLOCK *pCb;
    for(i=0; i< 1; i++)
    {
        for(j=0; j < FC_MINOR_SCHEME_MAX; j++)
        {
            pCb = &(gBluePrint[i].config_block[j]);
            ret = hbaDevFlashConfigWrite((HBA_DEV_CB *)g_hDev, pCb, i, j);
            if(ret != DEV_SUCCESS)
            {
                printf("hbaDevFlashConfigWrite error return %d!\n", ret);
                return -1;
            }
        }
    }

    printf("flash write gBluePrint Success!\n");
    return 0;
}
#endif

/*测试用例*/

#define BREAK_RUN /*break*/


FCUINT IntCallBack(FCHANDLE hDev, FCUINT intCode, FCUINT param0);
FCUINT AsmRecvMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT nLen);

#if 0
VOID testOpenHba()
{
    FCUINT ret;
    
    /*打开FC节点机的N端口,为FC设备分配资源*/
    {
        FCUINT devId;
        
        devId = 0;
        ret = FC_NP_Open(&g_hDev, devId);
        if (ret)
        {
            printf("FC_NP_Open failed return %d\n", ret);
            BREAK_RUN;
        }
        printf("FC_NP_Open success hDev=%p devId=%d\n", g_hDev, devId);
    }
    
#if 0    /* IntCallBack is not defined */
    /*注册网络管理事件处理函数*/
    {
        ret = FC_NP_RegEvtHandler(g_hDev, IntCallBack);
        if (ret)
        {
             printf("FC_NP_RegEvtHandler failed return %d\n", ret);
             BREAK_RUN;
        }
        printf("FC_NP_RegEvtHandler success IntCallBack=%p\n", IntCallBack);
    }
#endif

    /*配置FC节点机的ASM通信模式*/
    {
        FCUINT configMode;
        
        configMode = CONFIG_MODE_PROJECT;
        ret = FC_NP_ConfigMode(g_hDev, configMode);
        if (ret)
        {
             printf("FC_NP_ConfigMode failed return %d\n", ret);
             BREAK_RUN;
        }
        printf("FC_NP_ConfigMode success configMode=%d\n", configMode);
    }
    
    /*加载FC节点机的ASM配置*/
    {
        FCUINT majorScheme, minorScheme;

        majorScheme = 1;
        minorScheme = 0;
        ret = FC_NP_LoadConfig(g_hDev, majorScheme, minorScheme);
        if (ret)
        {
             printf("FC_NP_LoadConfig failed return %d\n", ret);
             BREAK_RUN;
        }
        printf("FC_NP_LoadConfig success majorScheme=%d minorScheme=%d\n", majorScheme, minorScheme);
    }    
    {
        int direct, mode, index, priority, asmid, fcid, msg_recover, sid;
        HBA_DEV_CB *pHbaDevCB;

        pHbaDevCB = (HBA_DEV_CB *)g_hDev;
        direct = HOST_READ;
        mode = RAW_MODE;
        index = 0;
        priority = PRIORITY_LEVEL_RAW_MSG;
        asmid = 0;
        fcid = 0;
        msg_recover = 0;
        sid = 0;
        ret = hwCreateChannel((PREG_HW)pHbaDevCB->pMembaseCsr, direct, mode, index, priority, asmid, fcid, msg_recover);
        if (ret)
        {
            printf("hwCreateChannel return %d\n", ret);
            return ;
        }
        /* debug */
        {
            PORT_RX_ENAB en;
            en.value = ReadRegisterUlong((ULONG *)(pHbaDevCB->pMembaseCsr + 0xC));

            /* Redundant enable '0' disable '1' enable */
            en.u.redundancy_enab = 0;
            WriteRegisterUlong((ULONG *)(pHbaDevCB->pMembaseCsr + 0xC), en.value);
        }
    }
}
#endif

unsigned char *pTestIntMsg = NULL;
int testMsgIntLen = MAX_IU_LEN;
UINT     g_msgID = 0;
UINT64   g_totalLen = 0;
UINT64 g_sendLength = 0;
int bPrintRecvMsg = 0;
SEM_ID semSendMsg = NULL;
SEM_ID semMsgValid = NULL;

UINT32 tAsmRecvMsgInt(VOID *hDev, UINT32 msgID)
{
    int ret;
    UINT retLen= 0;
    int i;
    
    g_msgID = msgID;
    semGive(semMsgValid);
    
    if (pTestIntMsg == NULL)
    {
        pTestIntMsg = (unsigned char*)malloc(MAX_IU_LEN);
    }
    
    while(1)
    {
        retLen = MAX_IU_LEN;
        ret = FC_NP_RecvMsg((FCHANDLE)g_hDev, g_msgID, pTestIntMsg, &retLen);
    
        if(ret != FC_SUCCESS)
        {
            if (bPrintRecvMsg)
                printf("FC_NP_RecvMsg: return %d, msgId=%d \n", ret, g_msgID);
            break;
        }        

        if (bPrintRecvMsg)
        {
            printf("FC_NP_RecvMsg: msgId=%d recvLen=%u!\n", g_msgID, retLen);
#if 0            
                  for(i=0; i< retLen; i++)
                  {
                      printf("%02x ", pTestIntMsg[i]);       
                  
                      if((i+1) % 32 == 0)
                          printf("\n");  
                  }
                  printf("\n");
#endif
        }
        
        g_totalLen += retLen;
        g_sendLength = retLen;

        break;
    }
    /*11 20 新加*/
    semGive(semSendMsg);

    return ret;
}

void testPrintRecvTotalLen(void)
{
    printf("totalLen = %llu \n", g_totalLen);
}

int testIntRecvTask(void)
{
    int ret = 0;
    UINT retLen= 0;
    int recvLen = 0;
    UINT64 totalLen = 0;
    int bufLen = 0;
    unsigned char *pBuf = NULL;
    

    /*配置接收字符数组*/
    bufLen = MAX_IU_LEN;
    pBuf = (unsigned char*)malloc(bufLen);
    if(pBuf == NULL)
    {
        printf("malloc error!\n");
        return -1;
    }
    memset(pBuf,0, bufLen);

    recvLen = 0;
    totalLen = 0;
    while(dualStopRecv == 0)
    {
        if(testSoftResetStopFlag == 1)
            break;

        
        semTake(semMsgValid, 1000);


        while(1)
        {

            retLen = MAX_IU_LEN;
            ret = FC_NP_RecvMsg((FCHANDLE)g_hDev, g_msgID, pBuf, &retLen);
        
            if(ret != FC_SUCCESS)
            {
                if (bPrintRecvMsg)
                    printf("FC_NP_RecvMsg: return %d, msgId=%d \n", ret, g_msgID);
                break;
            }    
            
            if (bPrintRecvMsg)
                    printf("FC_NP_RecvMsg: msgId=%d recvLen=%u !\n", g_msgID, retLen);

            totalLen += retLen;
        }
    }
    
    free(pBuf);
    printf("Finished msgId=%d recvLen=%llu exit!\n", g_msgID, totalLen); 

    return 0;
}

int tRegisterMsgRecvInt()
{
    int ret;

    if(pTestIntMsg != NULL)
        free(pTestIntMsg);

    pTestIntMsg = (unsigned char*)malloc(testMsgIntLen);
    if(pTestIntMsg == NULL)
    {
        printf("tRegisterMsgRecvInt malloc error!\n");
        return -1;
    }
    
    semMsgValid = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    /*@@11 20 新加*/
    semSendMsg = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    
    ret = FC_NP_RegMsgHandler(g_hDev, (FC_ASM_RECVMSG_FUNCPTR)tAsmRecvMsgInt);
    if(ret != FC_SUCCESS)
    {
        printf("FC_NP_RegMsgHandler return error=%d!\n", ret);
        return -1;
    }
#if 0
    if(taskSpawn("tIntRecv", RECV_TASK_PRIORITY
            , RECV_TASK_OPTION, RECV_TASK_STACK_SIZE, testIntRecvTask,
            0, 0,0,0,0,0,0,0,0,0) == ERROR)
    {
        printf("taskSpawn error=%d!\n", errnoGet());
        return -1;
    }    
#endif    
    return 0;
}

int tUnRegisterMsgRecvInt()
{
    int ret;

    ret = FC_NP_UnRegMsgHandler(g_hDev);
    if(ret != FC_SUCCESS)
    {
        printf("FC_NP_RegMsgHandler return error=%d!\n", ret);
        return -1;
    }

    free(pTestIntMsg);
    pTestIntMsg = NULL;

    return 0;
}
