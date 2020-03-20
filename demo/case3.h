#ifndef CASE_3_H
#define CESE_3_H
#endif // !CASE_3_H

#define  MAX_TEST_RECV_TASK_INFO  256
#define  MAX_TEST_SEND_TASK_INFO  256
#define  MAX_TEST_SEND_LEN       (16 * 1024 * 1024)
#define  INVALID_MSG_ID           -1
#define  MAX_TEST_RECV_TASK_INFO  256
#define  MAX_TEST_SEND_TASK_INFO  256
#define  TEST_RECV_TASK_NAME     "beginRecv"
#define  RECV_TASK_PRIORITY       50
#define  RECV_TASK_STACK_SIZE     40960
#define  RECV_TASK_OPTION         0
#define  TEST_SEND_TASK_NAME     "beginSend"
#define  SEND_TASK_PRIORITY       101
#define  SEND_TASK_OPTION         0
#define  SEND_TASK_STACK_SIZE     40960

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
    unsigned int testRecvLen;
    unsigned int testRecvErrNum;
} TEST_RECV_TASK_INFO;

TEST_RECV_TASK_INFO testRecvTaskInfo[MAX_TEST_RECV_TASK_INFO] = { { 0 } };
TEST_SEND_TASK_INFO testSendTaskInfo[MAX_TEST_SEND_TASK_INFO] = { { 0 } };
