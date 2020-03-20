#include <sockLib.h>
#include <inetLib.h>
#include <selectLib.h>
#include <msgQLib.h>
#include "fc_demo.h"
#include "list.h"


int g_dev;
DEMO_STATISTICS g_statistics;
SEM_ID semStartTest;
/* 配置参数 */
DEV_CONFIG g_dev_config;
/* 打印接收到的数据 */
int g_print_data=0;

int curClientSd = ERROR;
int bStartSockSend = 0;

int sockSendBufLen = 512*1024;

LIST_STR g_list_test_sock_idle;
LIST_STR g_list_test_sock_ready;
SEM_ID   g_semTestSockBufferValid = NULL;

typedef struct tagTEST_SOCK_BUFFER
{
	LIST_NODE node;   /* must be the first field */     

	UINT32 bufLen;
	UINT32 dataLen;
	
	UINT8   data[0];  
	
} TEST_SOCK_BUFFER;


int Send(int socket, char *buf, unsigned int buflen, unsigned int *sendlen);
int testSocket();
int testStopSocket();



void print_config();

void dev_set_config(INT32 fcid, INT32 credit_num ,INT32 speed ,INT32 did_filter_enab ,INT32 e_d_tov ,INT32 redundant_enab ,INT32 time_out, UINT32 qdrBufUnitSize);



/* 使用方法 */
void usage()
{
    printf("--------------------------------------------------------\n");
    printf("start_test\n");                        /* 启动测试 */
    printf("stop_test\n");                         /* 停止测试 */
    printf("--------------------------------------------------------\n");
    printf("dev_open\n");                          /* 打开设备 */
    printf("dev_close\n");                         /* 关闭设备 */
    printf("dev_get_state\n");                     /* 获取FC节点机的N端口状态 */
    printf("dev_get_version\n");                   /* 获取FC节点机的N端口版本号 */
    printf("dev_config\n");                        /* 配置FC节点卡 */
	printf("dev_start_monitor\n");                 /*开始监控*/
	printf("dev_stop_monitor\n");                  /*停止监控*/
	printf("dev_reset\n");                         /*软复位卡*/
    printf("dev_config_speed(speed) 1-1G 2-2G\n"); /* 配置速率 */
    printf("dev_reg_msg_handler\n");               /* 注册中断接收回调函数 */
    printf("dev_unreg_msg_handler\n");            /* 注销中断接收回调函数 */
    /*------------------------------通信管理接口------------------------------*/
    printf("\n");/* 请求有数据的缓冲区 */
    printf("\n");/* 释放接收缓冲区 */
    /*------------------------------时统管理接口------------------------------*/
    printf("get_rtc\n");                           /* 获取FC节点机的时间 */
    printf("set_rtc(hour, minute, second, millisecond, microsecond, nanosecond)\n"); /* 设置FC节点机的时间 */
    printf("get_date_time\n");                     /* 获取FC节点机的日期 */
    printf("set_date(year, month, day)\n");        /* 设置FC节点机的日期 */
    printf("print_stat\n");                  /* 打印统计数据 */
    printf("clear_statistics\n");                  /* 清除统计数据 */
    printf("g_print_data=1\n");                    /* 打印接收到的数据内容 */
    printf("--------------------------------------------------------\n");
}

UINT32 tQdrBufUnitSize = 512*1024;
void dev_set_qdr()
{
	g_dev_config.qdrBufUnitSize = tQdrBufUnitSize;
}

/* 启动测试 */
void start_test()
{
    int task_id;
	

    semStartTest = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    /* 启动接收线程 */
    task_id = taskSpawn("test_task", 50, 0, 40960, test_callback, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (task_id == ERROR)
    {
        printf("start test task failed\n");
    }
    else
    {
        printf("start test success\n");
    }



	testSocket();

}

/* 停止测试 */
void stop_test()
{
    /* 设置信号量，使测试停止 */
    semGive(semStartTest);
	taskDelay(60);
	testStopSocket();
	semDelete(semStartTest);
	semStartTest = NULL;
}


void test_sock_init(void)
{
	int sendBufLen = g_dev_config.qdrBufUnitSize;
	char * pBuffer = NULL;
	TEST_SOCK_BUFFER * pTestSockBuffer = NULL;
	int i;
	
	#define MAX_SOCK_BUFFER 5
	
	listInit(&g_list_test_sock_idle, 1);	
	listInit(&g_list_test_sock_ready, 1);	
	g_semTestSockBufferValid = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

	printf("g_dev_config.qdrBufUnitSize = %d\n", g_dev_config.qdrBufUnitSize);

	pBuffer = (char * )malloc((sizeof(TEST_SOCK_BUFFER) + g_dev_config.qdrBufUnitSize) * MAX_SOCK_BUFFER);
	if (pBuffer != NULL)
	{
		for (i=0; i<MAX_SOCK_BUFFER; i++)
		{
			pTestSockBuffer =  (TEST_SOCK_BUFFER * )(pBuffer + i*((sizeof(TEST_SOCK_BUFFER) + g_dev_config.qdrBufUnitSize)));
			pTestSockBuffer->bufLen = g_dev_config.qdrBufUnitSize;
			pTestSockBuffer->dataLen = 0;
			
			listAddNodeToListTail(pTestSockBuffer, &g_list_test_sock_idle);
		}
	}
	
}
/* 测试的回调例程 */
int test_callback(void *context)
{
    INT32 ret, dev_open_flag, dev_reg_msg_handler_flag;

    dev_open_flag = 0;
    dev_reg_msg_handler_flag = 0;
    do {
        ret = dev_open();
        if (ret)
        {
            break;
        }
        dev_open_flag = 1;
		
		/* 初始化配置参数 */
		dev_init_config();
		dev_set_qdr();
        ret = dev_config();
        if (ret)
        {
            break;
        }

        ret = dev_reg_msg_handler();
        if (ret)
        {
            break;
        }
        dev_reg_msg_handler_flag = 1;

		clear_statistics();
        ret = dev_start_monitor();
        if (ret)
        {
            break;
        }

        printf("test task is running\n");
        /* 阻塞，等待结束测试 */
        semTake(semStartTest, WAIT_FOREVER);        

        ret = dev_close();
        if (ret)
        {
            break;
        }
        dev_open_flag = 0;
    } while (FALSE);
    
    if (dev_reg_msg_handler_flag == 1)
    {
        dev_unreg_msg_handler();
    }
    if (dev_open_flag == 1)
    {
        dev_close();
    }


	
    printf("test task complete\n");
    return 0;
}

/*------------------------------设备管理接口------------------------------*/

/* 打开FC节点卡,分配资源 */
unsigned int dev_open()
{
    FCUINT ret, DevId=0;
    ret = FC_DevOpen(&g_dev, DevId);
    if (ret)
    {
        printf("FC_DevOpen failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevOpen success g_dev=%d\n", g_dev);
    }

    return ret;
}

/* 关闭FC节点卡，释放资源 */
unsigned int dev_close()
{
    FCUINT ret;

    ret = FC_DevClose(g_dev);
    if (ret)
    {
        printf("FC_DevClose failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevClose success\n");
    }
    return ret;
}

VOID dev_getData()
{
	FCUINT ret;
	char *pBuffer = NULL;
	FCUINT nLen=0;
	ret = FC_RecvData(g_dev,&pBuffer,&nLen);
	if (ret)
	{
		printf("FC_RecvData failed ret=%d\n", ret);
		return;
	}

	printf("data BufferAddr=0x%08x,len=%d.\n", pBuffer, nLen);
	ret = parse_dmaBuf(pBuffer,nLen);
	ret = FC_ReleaseBuf(g_dev, pBuffer);
    if (ret)
    {
        printf("FC_ReleaseBuf failed ret=%d\n", ret);
    }
}

/* 获取FC节点机的N端口状态 */
unsigned int dev_get_state()
{
    FCUINT ret, state;

    ret = FC_DevGetState(g_dev, &state);
    if (ret)
    {
        printf("FC_DevGetState failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevGetState success state=%d\n", state);
    }
    return ret;
}

/* 获取FC节点机的N端口版本号 */
unsigned int dev_get_version()
{
    FCUINT ret, version;

    ret = FC_DevGetVersion(g_dev, &version);
    if (ret)
    {
        printf("FC_DevGetVersion failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevGetVersion success versoin=0x%08x\n", version);
    }
    return ret;
}

unsigned int dev_reset()
{
    FCUINT ret;

    ret = FC_DevReset(g_dev);
    if (ret)
    {
        printf("FC_DevReset failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevReset success\n");
    }

    print_config();

    return ret;
}

/* 配置FC节点卡 */
unsigned int dev_config()
{
    FCUINT ret;

    ret = FC_DevConfig(g_dev, &g_dev_config);
    if (ret)
    {
        printf("FC_DevConfg failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevConfig success\n");
    }

    print_config();

    return ret;
}

/*开始监控*/
unsigned int dev_start_monitor()
{
    FCUINT ret;
	
    ret = FC_DevStartMonitor(g_dev);
    if (ret)
    {
        printf("FC_DevStartMonitor failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevStartMonitor success\n");
    }

    return ret;
}

/*停止监控*/
unsigned int dev_stop_monitor()
{
    FCUINT ret;
	
    ret = FC_DevStopMonitor(g_dev);
    if (ret)
    {
        printf("FC_DevStopMonitor failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevStopMonitor success\n");
    }

    return ret;
}


/* 注册中断接收回调函数 */
unsigned int dev_reg_msg_handler()
{
    FCUINT ret;

    ret = FC_DevRegMsgHandler(g_dev, fc_np_recv_func);
    if (ret)
    {
        printf("FC_DevRegMsgHandler failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevRegMsgHandler success\n");
    }
    return ret;
}

/* 注销中断接收回调函数 */
unsigned int dev_unreg_msg_handler()
{
    FCUINT ret;

    ret = FC_DevUnRegMsgHandler(g_dev);
    if (ret)
    {
        printf("FC_DevUnRegMsgHandler failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_DevUnRegMsgHandler success\n");
    }
    return ret;
}

/*------------------------------时统管理接口------------------------------*/
/* 获取FC节点机的时间 */
unsigned int get_rtc()
{
    FCUINT ret;
    FCTime time;

    ret = FC_TM_GetRtc(g_dev, &time);
    if (ret)
    {
        printf("FC_TM_GetRtc failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_TM_GetRtc success\n");
        print_time(&time);
    }
    return ret;
}

unsigned int set_rtc(unsigned int hour, unsigned int minute, unsigned int second)
{
    FCUINT ret;
    FCTime time;
	UINT64 tmpTime;

    time.hour = hour;
    time.minute = minute;
    time.second = second;
    time.millisecond = 0;
    time.microsecond = 0;
    time.nanosecond = 0;

    ret = FC_TM_SetRtc(g_dev, &time);
    if (ret)
    {
        printf("FC_TM_SetRtc failed ret=%d\n", ret);
    }
    else
    {
        printf("FC_TM_SetRtc success\n");
    }
    return ret;
}

/* 接收回调定义 */
int g_recvCnt = 0;
UINT64 g_recvLen = 0;
int g_prtDemo = 0;
ULONG tickLast = 0;
ULONG tickFirst = 0;
int g_prtParse = 1;
UINT64 lastTimeStamp = 0;
int timeStampErrCnt=0;

unsigned int fc_np_recv_func(INT32 *hDev, void *pBuffer, UINT nLen)
{
    int result;
    unsigned int length;
    FCUINT ret;
    char *buf;

	if(g_prtDemo)
	{
		printf("recv_buf, pBuffer=0x%08x, len=%d!\n", pBuffer, nLen);
	}
	ASSERT(hDev != NULL);
    ASSERT((int)hDev == g_dev);
    ASSERT(pBuffer != NULL);
    ASSERT(nLen != 0);
    /* 长度必定是4的整数倍 */
    ASSERT((nLen & 0x3) == 0);

	g_recvCnt++;
	if(g_recvCnt == 1)
	{
		tickFirst = tickGet();
	}
	else
	{
		tickLast = tickGet();
	}

    /* 解析帧，记录统计数据 */
	if(g_prtParse)
	{
	    buf = pBuffer;
	    length = nLen;
		result = parse_dmaBuf(buf, length);
	}	

	if(bStartSockSend != 0)
	{
		TEST_SOCK_BUFFER * pTestSockBuffer = (TEST_SOCK_BUFFER *)listRemoveNodeFromListHead(&g_list_test_sock_idle);
		if (pTestSockBuffer != NULL) 
		{
			if (length > pTestSockBuffer->bufLen)
			{
				printf("fc_np_recv_func: invalid len, length=%u,  bufLen=%u\n", length, pTestSockBuffer->bufLen);

				pTestSockBuffer->dataLen = 0;
				listAddNodeToListTail(pTestSockBuffer, &g_list_test_sock_idle);
			}
			else
			{
				memcpy(pTestSockBuffer->data, buf, length);
				pTestSockBuffer->dataLen = length;

				listAddNodeToListTail(pTestSockBuffer, &g_list_test_sock_ready);
				
			}
			
				
		}
	}

    /* 释放缓冲区 */
    ret = FC_ReleaseBuf(hDev, pBuffer);
    if (ret)
    {
        printf("FC_ReleaseBuf failed ret=%d\n", ret);
    }


	g_recvLen += length;
    return ret;
}

/* 打印时间结构体 */
void print_time(FCTime *time)
{
    printf("hour=%d minute=%d second=%d millisecond=%d microsecond=%d nanosecond=%d\n",
        time->hour, time->minute, time->second, time->millisecond, time->microsecond, time->nanosecond);
}

/* 打印日期结构体 */
void print_date(FCDate *date)
{
    printf("year=%d month=%d day=%d\n", date->year, date->month, date->day);
}

/* 打印统计数据 */
void print_stat()
{
    PDEMO_STATISTICS d;
    
    d = &g_statistics;
    printf("frameNum=%lld frameTotalbytes=%lld, bufTotalBytes=%lld, bufTotalNum=%lld\n", 
		d->frameNum, d->frameTotalByte, d->bufferTotalByte, d->bufferTotalNum);

}

/* 统计数据清零 */
void clear_statistics()
{
    memset(&g_statistics, 0, sizeof(DEMO_STATISTICS));
}


#if 1
#define CFG_ID 0xFC000000
#define MONITOR_ID 0xFB000000

typedef struct
{
	UINT32 frameLen; /*frameLen-16*/
	UINT32 errorFlag;
	UINT32 cfgID;
	UINT32 monitorID;
}__attribute__((packed)) RECORD_HEADER, *PRECORD_HEADER;

#else
#define RECORD_SIGNATURE 0xFC691352
typedef struct
{
	UINT32 signature; /*0xFC691352*/
	UINT64 timeStamp;
	UINT32 errorFlag;
	UINT32 frameLen;
}__attribute__((packed)) RECORD_HEADER, *PRECORD_HEADER;

#endif

/* 解析帧，记录统计数据 */

int parse_frame(char *buf, int length)
{
#if 0
    if (g_print_data>0)
    {
    	g_print_data--;
        print_buf(buf, length);
    }
#endif
	return 0;
}




int g_print_offset = 0;

int testDelay = 0;
int parse_dmaBuf(char *buf, int length)
{
    /* length(4byte)+data+length(4byte)+data+... */
    int offset;
    PDEMO_STATISTICS st;
	RECORD_HEADER *pRecordHeader;
	UINT32 eof;

    st = &g_statistics;
    offset = 0;

    if (g_print_data > 0)
    {
    	g_print_data--;
        print_buf(buf, length);
    }

    while (offset < length)
    {
    	pRecordHeader = (RECORD_HEADER*)(buf + offset);


#if 0
		if(g_print_offset==1 && offset==0)
		{
			printf("Header Addr=0x%08x, offset=%d, signature=0x%08x, errFlag=%08x, timeStamp=%llu, frameLen=%d.\n", pRecordHeader
				, offset, pRecordHeader->signature, pRecordHeader->errorFlag, pRecordHeader->timeStamp
				, pRecordHeader->frameLen);
		}

		if(pRecordHeader->timeStamp < lastTimeStamp)
		{
			printf("bufLen=%d,offset=%d,timeStamp error,cur=%lld, last=%lld!\n", length, offset
				,pRecordHeader->timeStamp
				, lastTimeStamp);

			timeStampErrCnt++;
		}

		lastTimeStamp = pRecordHeader->timeStamp;
		
#endif


#if 0
		if(!((pRecordHeader->signature == RECORD_SIGNATURE) || (pRecordHeader->signature == 0xfc000000)))
		{
			printf("bufLen=%d,offset=%d,frame error,real signature 0x%08x not be hoped signature 0x%08x\n",
				length, offset, pRecordHeader->signature, RECORD_SIGNATURE);

			timeStampErrCnt++;

			print_buf((char *)pRecordHeader, sizeof(RECORD_HEADER));
		}
#else
		if(!((pRecordHeader->cfgID == CFG_ID) || (pRecordHeader->monitorID == MONITOR_ID)))
		{
			printf("bufLen=%d,offset=%d,frame error,real cfgID 0x%08x monitorID 0x%08x\n",
				length, offset, pRecordHeader->cfgID, pRecordHeader->monitorID);

			timeStampErrCnt++;

			print_buf((char *)pRecordHeader, sizeof(RECORD_HEADER));
		}

#endif

		parse_frame(buf + offset + sizeof(RECORD_HEADER), pRecordHeader->frameLen-16);
        offset += (sizeof(RECORD_HEADER) + pRecordHeader->frameLen-16);
		eof = *(UINT32*)(buf + offset-4);
		if(eof != 0xbc957575  && eof != 0xbcb57575 && eof !=  0xbc95d5d5 && eof != 0xbcb5d5d5)
		{
			printf("bufAddr=0x%08x, offset=%d,eof error,value=0x%08x.\n", buf, offset,eof);
		}

		if(testDelay)
		taskDelay(60);

        st->frameNum++;
        st->frameTotalByte += pRecordHeader->frameLen-16;
    }

	st->bufferTotalByte += length;
	st->bufferTotalNum++;
    return 0;
}

/* 打印缓冲区 */
void print_buf(char *buf, int length)
{
    int i;

    for (i = 0; i < length; ++i)
    {
        printf("%02x", buf[i]);
        if ((i + 1) % 4 == 0)
        {
            printf(" ");
        }
        if ((i + 1) % 20 == 0)
        {
            printf("\n");
        }
    }

	printf("\n");
}

void print_config()
{
	printf("config fcid = 0x%08x, credit_num = %d ,speed =%d, did_filter_enab =%d,e_d_tov = %d,redundant_enab =%d ,time_out =%d, qdrBufUnitSize=0x%x.\n", g_dev_config.fcid
		,g_dev_config.credit_num
		,g_dev_config.speed 		 
		,g_dev_config.did_filter_enab 
		,g_dev_config.e_d_tov		  
		,g_dev_config.redundant_enab  
		,g_dev_config.time_out
		,g_dev_config.qdrBufUnitSize);
}

void print_speed()
{
	ULONG tickUsed = tickLast - tickFirst;
	int tickRate = sysClkRateGet();
	ULONG time = tickUsed/((ULONG)(tickRate));
	printf("start tick=%d, stop tick=%d, seconds=%d, recvLen=%lld, speed=%lld B/S.\n", tickFirst, tickLast, time, g_recvLen, g_recvLen/(UINT64)(time));
}

void clear_speed()
{
	tickFirst = 0;
	tickLast = 0;
	g_recvCnt = 0;
	g_recvLen = 0;
}

/* 配置参数初始化 */
int bInitConfig = 0;
void dev_init_config()
{
	if(bInitConfig == 0)
	{
		g_dev_config.fcid            = 0x100001;
		g_dev_config.credit_num      = 8;             /* 信用 1-16 */
		g_dev_config.speed           = PORT_SPEED_2G; /* 速率 0 自适应 1-1Gbps 2-2Gbps */
		g_dev_config.did_filter_enab = 0;             /* 接收方向DID过滤使能 */
		g_dev_config.e_d_tov         = 100;           /* e_d_tov时间，单位是毫秒 */
		g_dev_config.redundant_enab  = 1;             /* 冗余使能 0-禁止 1-使能 */
		g_dev_config.time_out        = 1000;          /* 超时覆盖的时间，单位是毫秒 */
		g_dev_config.qdrBufUnitSize = 512*1024;
	}
	
	bInitConfig = 1;
}

/* 配置参数设置 */
void dev_set_config(INT32 fcid, INT32 credit_num ,INT32 speed ,INT32 did_filter_enab ,INT32 e_d_tov ,INT32 redundant_enab ,INT32 time_out, UINT32 qdrBufUnitSize)
{
	bInitConfig = 1;
    g_dev_config.fcid            = fcid;
    g_dev_config.credit_num      = credit_num;             /* 信用 1-16 */
    g_dev_config.speed           = speed; /* 速率 0 自适应 1-1Gbps 2-2Gbps */
    g_dev_config.did_filter_enab = did_filter_enab;             /* 接收方向DID过滤使能 */
    g_dev_config.e_d_tov         = e_d_tov;           /* e_d_tov时间，单位是毫秒 */
    g_dev_config.redundant_enab  = redundant_enab;             /* 冗余使能 0-禁止 1-使能 */
    g_dev_config.time_out        = time_out;          /* 超时覆盖的时间，单位是毫秒 */
	g_dev_config.qdrBufUnitSize = qdrBufUnitSize;
}

/* 配置速率 */
unsigned int dev_set_speed(int speed)
{
    INT32 ret;
    HBA_DEV_CB *pHbaDevCB;

    pHbaDevCB = (HBA_DEV_CB *)g_dev;
    ret = hbaDevConfigSpeed(pHbaDevCB, speed);
    if (ret)
    {
        printf("hbaDevConfigSpeed failed ret=%d\n", ret);
    }
    else
    {
        printf("hbaDevConfigSpeed success speed=%d\n", speed);
    }
    return ret;
}

/*--------socket-------*/
#if 1






int testSockPrint = 0;
int testSockPayloadIncrease = 0;
int sock_parse_frame(char *buf, int length)
{
	int i;

	if(testSockPayloadIncrease)
	{		
		for(i=0; i< length;)
		{
		}
	}
	return 0;
}


int sock_parse_dmaBuf(char *buf, int length)
{
#if 0
    /* length(4byte)+data+length(4byte)+data+... */
    int offset;
    PDEMO_STATISTICS st;
	RECORD_HEADER *pRecordHeader;
	UINT32 eof;

	UINT64 tmpTimeStamp = 0;

    if (testSockPrint > 0)
    {
    	testSockPrint--;
        print_buf(buf, length);
    }

    offset = 0;
    while (offset < length)
    {
    	pRecordHeader = (RECORD_HEADER*)(buf + offset);

		if(testSockPrint)
		{
			printf("socket Header Addr=0x%08x, offset=%d, signature=0x%08x, errFlag=%08x, timeStamp=%llu, frameLen=%d.\n", pRecordHeader
				, offset, pRecordHeader->signature, pRecordHeader->errorFlag, pRecordHeader->timeStamp
				, pRecordHeader->frameLen);
		}
		if(pRecordHeader->timeStamp < tmpTimeStamp)
		{
			printf("socket bufLen=%d,offset=%d,timeStamp error,cur=%lld, last=%lld!\n", length, offset
				,pRecordHeader->timeStamp
				, lastTimeStamp);
		}
		tmpTimeStamp = pRecordHeader->timeStamp;

		if(!((pRecordHeader->signature == RECORD_SIGNATURE) || (pRecordHeader->signature == 0xfc000000)))
		{
			printf("socket bufLen=%d,offset=%d,frame error,real signature 0x%08x not be hoped signature 0x%08x\n",
				length, offset, pRecordHeader->signature, RECORD_SIGNATURE);
		}

		sock_parse_frame(buf + offset + sizeof(RECORD_HEADER), pRecordHeader->frameLen);
        offset += (sizeof(RECORD_HEADER) + pRecordHeader->frameLen);
		eof = *(UINT32*)(buf + offset-4);
		if(eof != 0xbc957575  && eof != 0xbcb57575	&& eof !=  0xbc95d5d5 && eof != 0xbcb5d5d5)
		{
			printf("socket bufAddr=0x%08x, offset=%d,eof error,value=0x%08x.\n", buf, offset,eof);
		}

    }
#endif
    return 0;
}


int testSockSendTotalLen = 0;
int testSockSendBufNum = 0;
int testSockSendPartTotalLen = 0;
int Send(int socket, char *buf, unsigned int buflen, unsigned int *sendlen)
{
	int ret;
	if (!socket || socket == ERROR || !buf || !sendlen)
	{
		printf("invalid socket parameter\n");
		return -1;
	}

	*sendlen = 0;
	do {
		if ((ret = send(socket, buf, buflen, 0)) > 0) {
			*sendlen += ret;
			buf += ret;
			buflen -= ret;
		}
	} while (ret > 0 && buflen > 0);
	return ret;
}

STATUS testSockTask(void);

#define TEST_SOCKET_PORT 6010
/*----*/
int stopSockClient = 0;
STATUS testSockClientTask()
{
	int *sendBuf= NULL;
	int sendBufLen = g_dev_config.qdrBufUnitSize;
	int ret,actLen, actSendBufValue;

	while(1)
	{
		TEST_SOCK_BUFFER * pTestSockBuffer = NULL;
		
		if(stopSockClient == 1)
			break;
		
		pTestSockBuffer = (TEST_SOCK_BUFFER *)listRemoveNodeFromListHead(&g_list_test_sock_ready);
		if (pTestSockBuffer == NULL)
		{
			semTake(g_semTestSockBufferValid, 1); 
			continue;
		}
		
		if(bStartSockSend != 0)
		{
			ret = Send(curClientSd, (char*)pTestSockBuffer->data, pTestSockBuffer->dataLen, &actLen);
			if(ret < 0 || pTestSockBuffer->dataLen != actLen)
			{
				if(ret < 0)
				{
					bStartSockSend = 0;
				}

				testSockSendTotalLen += actLen;
				testSockSendPartTotalLen += actLen;
				#if 0
				printf("Sock Send error ret=%d!", ret);
				#endif
			}
			else
			{
				if (testSockPrint > 0)
				{
					testSockPrint--;
					printf("socket bufAddr=0x%08x, length=%d.\n", (char*)pTestSockBuffer->data, actLen);
					sock_parse_dmaBuf((char*)pTestSockBuffer->data, pTestSockBuffer->dataLen);
				}

				testSockSendTotalLen += actLen;
				testSockSendBufNum++;
				
				if((testSockSendBufNum % 50) == 0)
					taskDelay(1);
				
			}
		}

		pTestSockBuffer->dataLen = 0;
		listAddNodeToListTail(pTestSockBuffer, &g_list_test_sock_idle);

	}

	free(sendBuf);
		
}

int	serverSd = -1;
STATUS testSockTask(void) 					  
{
	struct timeval	to;
	int	clientSd;
	struct sockaddr_in	cliAddr, servAddr;
	UINT32 cliLen=0;
	static fd_set rdSet, wrSet, exSet; 
	INT32 nready, maxfdp;
	unsigned long	retCode;
    int i, ret;
	ULONG tempTick;

	serverSd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverSd<0)
	{
		printf("cannot open socket.\n");
		return ERROR;
	}

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(TEST_SOCKET_PORT);

	if((ret = bind(serverSd, (struct sockaddr *) &servAddr, sizeof(servAddr)))<0) 
	{
		printf("Socket failed to bind port, ret=%d, err=0x%08x.\n", ret, errnoGet());
		close(serverSd);
		return ERROR;																							
	}

	if(listen(serverSd,10) < 0)
	{
		printf("Socket listen failed\n");
		close(serverSd);
		return ERROR;
	}

	while(1)
	{
		/* prepare to block on 'select' */
		maxfdp = serverSd;
		FD_ZERO( &rdSet );
		FD_ZERO( &wrSet );
		FD_ZERO( &exSet );
		FD_SET( serverSd, &rdSet );

		to.tv_sec = 2;
		to.tv_usec = 0;
		nready = select((maxfdp+1), &rdSet, NULL, NULL, &to);

		/* if error, the select returns '-1' */
		if( nready < 0 )
		{	
      		printf("'select' returns ERROR. rtn=%08x, err=0x%08x.\n", nready, errnoGet());
			if(stopSockClient == 1)
				return OK;
		}
		else if( nready == 0 )
		{
			/* periodic time out */
		}
		else 
		{
			if (FD_ISSET(serverSd, &rdSet))
			{
				cliLen = sizeof(cliAddr);
				clientSd = accept(serverSd, (struct sockaddr *) &cliAddr, &cliLen);
				
				if(clientSd < 0) 
				{
					printf("testSockTask: Socket failed to accept connection : ErrNo: %d", clientSd);				
					continue;
				}

				if(curClientSd != clientSd)
				{
					bStartSockSend = 0;
					taskDelay(1);
					ret = close(curClientSd);
					curClientSd = clientSd;
					bStartSockSend = 1;
				}
			}
		}
	}
	
	return OK;
}

int testSocket()
{
	int task_id;

	taskDelay(100);
	
	test_sock_init();
	
	stopSockClient = 0;

    task_id = taskSpawn("testSock", 53, 0, 40960, testSockTask, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (task_id == ERROR)
    {
        printf("start testSock task failed\n");
    }
    else
    {
        printf("start testSock success\n");
    }		

    task_id = taskSpawn("testSendSock", 54, 0, 40960, testSockClientTask, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (task_id == ERROR)
    {
        printf("start testSendSock task failed\n");
    }
    else
    {
        printf("start testSendSock success\n");
    }	
}

int testStopSocket()
{
	int oldTick = sysClkRateGet();
	stopSockClient=1;
	sysClkRateSet(1000);	
	taskDelay(3000);
	bStartSockSend = 0;
	sysClkRateSet(oldTick);
	close(serverSd);	
	close(curClientSd);
	taskDelay(1);
	serverSd = ERROR;	
	curClientSd = ERROR;

	return 0;
}

#endif
/*----*/
	
