#include <vxWorks.h>
#include <stdlib.h>
#include <stdio.h>
#include <taskLib.h>
#include <tickLib.h>
#include "fc_api.h"
#include "..\hbaDrv\hba.h"


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
    return ret

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

    return ret;
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

/*测试用例*/

#define BREAK_RUN /*break*/


FCUINT IntCallBack(FCHANDLE hDev, FCUINT intCode, FCUINT param0);
FCUINT AsmRecvMsg(FCHANDLE hDev, FCUINT msgID, FCUCHAR *pMsg, FCUINT nLen);


unsigned char *pTestIntMsg = NULL;
int testMsgIntLen = MAX_IU_LEN;
UINT     g_msgID = 0;
UINT64   g_totalLen = 0;
UINT64 g_sendLength = 0;
int bPrintRecvMsg = 0;
SEM_ID semSendMsg = NULL;
semMsgValid = NULL;

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
        }
        
        g_totalLen += retLen;
        g_sendLength = retLen;

        break;
    }
    /*11 20 新加*/
    semGive(semSendMsg);

    return ret;
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