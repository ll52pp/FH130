#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <taskLib.h>
#include  <vxWorks.h>
#include  "fc_api.h"
#include  "..\hbaDrv\hba.h"
#include  "case3.h"

#define  ERRO                    "FALSE"
#define  SUCCESS                 "OK"
#define  FAILED                   1


SEM_ID sysSem;
FCHANDLE hDev = 0;
unsigned int sendLen = 500;
unsigned int msgId   = 10;

/*测试用例*/
unsigned int test(int devId)
{
    int mode = 0;
    int times = 2;

    devsOpen(devId);
    setConfig(mode);
    prePlan(devId);
    startSend(devId, msgId, times, sendLen);/*两次收发*/
    devClose(devId);

    printf("Test case has finished! ");
}

/*打开设备*/
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
        prePlan(devId);/*防错*/
    }
    else
    {
        printf(" FC - device opened ! devId :%d, ret :0x%08x, hdev :%p", devId, ret, hDev);
    }
    return ret;
}

/*配置模式*/
int setConfig(int mode)
{
    unsigned int ret = FC_NP_ConfigMode(hDev, mode);

    printf("FC_NP_ConfigMode mode %d return %d!\n", mode, ret);

    return ret;
}

/*加载配置*/
int prePlan(int devId)
{
    FCUINT ret, majorScheme = 0, minorScheme = 0;

    ret = FC_NP_LoadConfig(hDev, majorScheme, minorScheme);

    printf("FC_NP_LoadConfig ret=0x%08x\n", ret);
    return ret;
}

/*发送进程*/
int beginSend(int times, int msgId, int sendLen, unsigned char *pUsrChar)
{
    unsigned char *sendChar = NULL;
    int ret = 0;
    int i, j;
    unsigned int totalSendLen = 0;
    int testInfoIndex;
    int *pPayload = NULL;

    testInfoIndex = tGetSendInfoIndexByMsgId(msgId);
    if (testInfoIndex == -1)
    {
        printf("beginSend get msgId=%d info error!\n", msgId);
        return FAILED;
    }
    if (pUsrChar == NULL)
    {
        sendChar = (unsigned char *)malloc(sendLen*sizeof(char));
        if (sendChar == NULL)
        {
            printf("beginSend malloc failed!\n");
            return FAILED;
        }
        memset(sendChar, 0, sendLen);

        for (i = 0; i < sendLen; i++)
        {
            sendChar[i] = (unsigned int)(i);
        }
    }
    else
    {
        sendChar = pUsrChar;
    }

    printf("beginSend Start times=%d, msgId=%d, sendLen=%d!\n", times, msgId, sendLen);

    for (i = 0; i < times; i++)
    {
        ret = FC_NP_SendMsg(hDev, msgId, sendChar, (unsigned int)sendLen);
        if (ret != FC_SUCCESS)
        {
            continue;
        }

        totalSendLen += sendLen;
    }

    free(sendChar);
    tSendInfoInit(testInfoIndex);

    printf("beginSend Finished, send msgId=%d, times=%d, totalLen = %llu!\n", msgId, i, totalSendLen);
    return 0;
    semGive(sysSem);/*释放信号量*/
}


/*启动发送*/
int startSend(int devId, int msgId, int times, int sendLen)
{
    int taskId = ERROR;
    int index = 0;

    if (times <= 0)
    {
        printf("FC - send times param failed!\n");
        return FAILED;
    }

    if (sendLen <= 0 || sendLen > MAX_TEST_SEND_LEN)
    {
        printf("send length param failed ! devId:%d\n", devId);
        return FAILED;
    }

    index = tGetFreeSendInfoIndexByMsgId(msgId);
    if (index == -1)
    {
        printf("error: msgId is full!\n");
        return FAILED;
    }
    /*创建发送进程并返回发送进程ID*/
    taskId = taskSpawn(TEST_SEND_TASK_NAME, SEND_TASK_PRIORITY
        , SEND_TASK_OPTION, SEND_TASK_STACK_SIZE, beginSend,
        times, (int)msgId, (int)sendLen, (int)NULL, 0, 0, 0, 0, 0, 0);

    if (taskId == ERROR)
    {
        printf("taskSpawn error !\n");
        tSendInfoInit(index);
        return FAILED;
    }
    return 0;

    startRecv(devId); /*调用接收接口*/
}

/*接收*/
int startRecv(int msgId)
{
    int ret;
    ret = tStartRecv(msgId, RECV_TASK_PRIORITY); /*开始接收*/
    if (ret != 0)
    {
        printf("tmsgId msgId=%d failed, return %d!\n", msgId, ret);
        return FAILED;
    }

    printf("FC - tmsgId msgId=%d start!\n", msgId);

    ret = recvQuit(msgId); /*等待接收结束*/

    printf("tmsgId msgId=%d finished, ret=%d!\n", msgId, ret);
    return 0;
}
/*关闭设备*/
int devClose(int devId)
{
    FCUINT ret;

    ret = FC_NP_Close(hDev);
    if (FC_SUCCESS != ret)
    {
        printf("device close erro ! devId :%d, state :%s", devId, ERRO);
    }
    else
    {
        printf("device closed ! devId :%d", devId);
    }
    return ret;
}

int tGetSendInfoIndexByMsgId(int msgId)
{
    int i = 0;

    if (msgId == INVALID_MSG_ID)
        return FAILED;

    for (i = 0; i < MAX_TEST_SEND_TASK_INFO; i++)
    {
        if (testSendTaskInfo[i].bUsed == 0)
            continue;

        testSendTaskInfo[i].index = i;
        if (testSendTaskInfo[i].msgId == msgId)
            return i;
    }

    return FAILED;
}


int tGetFreeSendInfoIndexByMsgId(int msgId)
{
    int i = 0;

    if (msgId == INVALID_MSG_ID)
        return FAILED;

    for (i = 0; i < MAX_TEST_SEND_TASK_INFO; i++)
    {
        if (testSendTaskInfo[i].bUsed == 1)
            continue;

        testSendTaskInfo[i].bUsed = 1;
        testSendTaskInfo[i].msgId = msgId;
        testSendTaskInfo[i].testSendEnd = 0;
        return i;
    }

    return FAILED;
}

unsigned int beginRecv(void *hDev, unsigned int msgId)
{
    int ret;
    int i;
    unsigned int retLen;
    unsigned int g_totalLen;
    unsigned int g_sendLength;
    unsigned int g_msgID = msgId;

    unsigned char *pTestIntMsg = NULL;
    UINT64 testMsgIntLen = MAX_IU_LEN;

    semTake(sysSem, 800);/*取得信号量*/

    if (pTestIntMsg == NULL)
    {
        pTestIntMsg = (unsigned char*)malloc(MAX_IU_LEN);
    }

    for (;;)
    {
        int bPrintRecvMsg = 0;
        retLen = MAX_IU_LEN;
        ret = FC_NP_RecvMsg((FCHANDLE)hDev, g_msgID, pTestIntMsg, &retLen);

        if (ret != FC_SUCCESS)
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
    semGive(sysSem); /*释放信号量*/

    return ret;
}


int tStartRecv(int msgId, int testRecvTaskPriority)
{
    int taskId = ERROR;
    int index = -1;
    index = tGetFreeRecvInfoIndexByMsgId(msgId);
    if (index == -1)
    {
        printf("error: msgId is erro !\n");
        return FAILED;
    }

    testRecvTaskInfo[index].testRecvExit = 0;

    sysSem = semBCreate(SEM_Q_FIFO, SEM_EMPTY); /*任务互斥*/

    /*创建接收进程并返回进程ID*/
    taskId = taskSpawn(TEST_RECV_TASK_NAME, testRecvTaskPriority
        , RECV_TASK_OPTION, RECV_TASK_STACK_SIZE, beginRecv, msgId, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    if (taskId == ERROR)
    {
        printf("taskSpawn error!");
        tRecvInfoInit(index);
        return FAILED;
    }

    return 0;
}

int recvQuit(int msgId)
{
    int index = -1;

    index = tGetRecvInfoIndexByMsgId(msgId);
    if (index == -1)
    {
        printf("get msgId=%d info error!\n", msgId);
    }
    for (;;)
    {
        if (testRecvTaskInfo[index].testRecvStart == 1
            && testRecvTaskInfo[index].testRecvIsEnd == 1)
            break;

    }

    testRecvTaskInfo[index].testRecvStart = 0;
    testRecvTaskInfo[index].testRecvIsEnd = 0;

    tRecvInfoInit(index);
    printf("wait taskId msgId=%d exit Ok!\n", msgId);
}


int tRecvInfoInitAll()
{
    int i = 0;
    for (i = 0; i < MAX_TEST_RECV_TASK_INFO; i++)
    {
        tRecvInfoInit(i);
    }

    return 0;
}

int tGetRecvInfoIndexByMsgId(int msgId)
{
    int i = 0;

    if (-1 == msgId)
        return FAILED;

    for (i = 0; i < MAX_TEST_RECV_TASK_INFO; i++)
    {
        if (testRecvTaskInfo[i].bUsed == 0)
            continue;

        testRecvTaskInfo[i].index = i;
        if (testRecvTaskInfo[i].msgId == msgId)
            return i;
    }

    return FAILED;
}
int tGetFreeRecvInfoIndexByMsgId(int msgId)
{
    int i = 0;

    if (msgId == INVALID_MSG_ID)
        return FAILED;

    for (i = 0; i < MAX_TEST_RECV_TASK_INFO; i++)
    {
        if (testRecvTaskInfo[i].bUsed == 1)
            continue;

        testRecvTaskInfo[i].bUsed = 1;
        testRecvTaskInfo[i].msgId = msgId;
        testRecvTaskInfo[i].testRecvIsEnd = 0;
        testRecvTaskInfo[i].testRecvExit = 0;
        testRecvTaskInfo[i].testRecvStart = 0;
        testRecvTaskInfo[i].testRecvIsEnd = 0;
        return i;
    }

    return FAILED;
}
