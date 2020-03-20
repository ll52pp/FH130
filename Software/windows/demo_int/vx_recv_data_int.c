#include <stdio.h>
#include <stdlib.h>
#include <vxworks.h>
#include <semlib.h>

#include "../lib/api.h"

#define assert(BOOL) \
{ \
    if (!(BOOL))  printf("ASSERT: %s(%d)\n", __FILE__, __LINE__); \
}

#define RECV_TASK_NAME          "tRecvInt"
#define RECV_TASK_PRIORITY      50
#define RECV_TASK_OPTION        0
#define RECV_TASK_STACK_SIZE    40960
/*统计数据结构*/
#define INT_EVT_DESC_MAX        8
typedef struct _INT_EVT_DESC
{
	int intCode;
	int param0;
	int count;
} INT_EVT_DESC, *PINT_EVT_DESC;
typedef struct _FCM_DEMO_STATISTICS
{
	UINT64 bytes;
	UINT64 frame_num;
	UINT64 cfgid_err;
	UINT64 monitorid_err;
	UINT64 crc_err;
	UINT64 undersize;
	UINT64 oversize;
	UINT64 no_eof_err;
	UINT64 disp_err;
	UINT64 coding_err;
	INT_EVT_DESC int_evt_desc[INT_EVT_DESC_MAX];
} FCM_DEMO_STATISTICS, *PFCM_DEMO_STATISTICS;

/*信用*/
#define FCM_CONFIG_CREDIT_NUM   8
/*速率*/
#define FCM_SPEED               PORT_SPEED_2G

FCHANDLE g_dev = NULL;
int g_recv_handle = ERROR;
SEM_ID g_stop_int_recv_handle = NULL;
FCM_DEMO_STATISTICS g_demo_stat = { 0 };

/*启动接收*/
void start_recv();
/*停止接收*/
void stop_recv();
/*接收数据的回调*/
UINT recv_callback(PVOID context);
/*事件中断回调*/
FCUINT event_callback(FCHANDLE hDev, FCUINT intCode, FCUINT param0);
/*接收数据的回调*/
FCUINT int_recv_callback(FCHANDLE hDev, void *buf, FCUINT length);
/*解析数据*/
void parse_buf(unsigned char *buf, int length);
/*检查记录头的错误标记*/
int check_flag(UINT32 flag, PFCM_DEMO_STATISTICS v);
/*打印统计值*/
void print_statistics();
/*显示命令提示*/
void usage();

/*启动接收*/
void start_recv()
{
	UINT t_id;

	if (g_recv_handle == ERROR)
	{
		g_recv_handle = taskSpawn(RECV_TASK_NAME, RECV_TASK_PRIORITY,
				RECV_TASK_OPTION, RECV_TASK_STACK_SIZE, recv_callback,
				0,0,0,0,0,0,0,0,0,0);
		if (g_recv_handle == ERROR)
		{
			printf("start recv thread failed err=%d\n", errnoGet());
		}
		else
		{
			printf("start recv thread success\n");
		}
	}
}
/*停止接收*/
void stop_recv()
{
	if (g_recv_handle != ERROR)
	{
		semGive(g_stop_int_recv_handle);
		while(g_recv_handle != ERROR)
		{
			taskDelay(1);
		}
		printf("stop recv thread success\n");
	}
}
/*接收数据的回调*/
unsigned int recv_callback(PVOID context)
{
	FCUINT ret, dev_id;
	FCUINT va_addr, nLen;
	FCUCHAR *buf;
	FC_INT_FUNCPTR func_event;
	FC_NP_RECV_FUNCPTR func_int_recv;
	int dev_open_flag, reg_event_flag, reg_int_recv_flag, dev_enab_flag, monitor_flag;
	STATUS reason;

	printf("recv thread start\n");
	dev_open_flag = reg_event_flag = reg_int_recv_flag = dev_enab_flag = monitor_flag = 0;
	func_event = event_callback;
	func_int_recv = int_recv_callback;
	buf = (FCUCHAR *)&va_addr;
	nLen = sizeof(int);
	do {
		/*创建使中断接收停止的信号量*/
		g_stop_int_recv_handle = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
		if (g_stop_int_recv_handle == NULL)
		{
			printf("create stop int recv single failed err=%d\n", errnoGet());
			break;
		}
		/*打开设备*/
		dev_id = 0;
		ret = FCM_DevOpen(&g_dev, dev_id);
		if (ret)
		{
			printf("open dev failed ret=%d err=%d\n", ret, errnoGet());
			break;
		}
		dev_open_flag = 1;
		printf("open dev success g_dev=%p dev_id=%d\n", g_dev, dev_id);
		/*注册中断事件处理*/
		ret = FCM_DevRegEvtHandler(g_dev, func_event);
		if (ret)
		{
			printf("register event handler failed ret=%d err=%d\n", ret, errnoGet());
			break;
		}
		reg_event_flag = 1;
		printf("register event handler success\n");
		/*注册中断接收接收数据的回调*/
		ret = FCM_DevRegMsgHandler(g_dev, func_int_recv);
		if (ret)
		{
			printf("register msg int handler failed ret=%d err=%d\n", ret, errnoGet());
			break;
		}
		reg_int_recv_flag = 1;
		printf("register msg int handler success\n");
		/*使能设备 FCID固定为0x100000*/
		ret = FCM_DevEnable(g_dev, 0x100000, FCM_CONFIG_CREDIT_NUM, FCM_SPEED);
		if (ret)
		{
			printf("dev enab failed ret=%d err=%d\n", ret, errnoGet());
			break;
		}
		dev_enab_flag = 1;
		printf("dev enab success\n");
		/*开始监控*/
		ret = FCM_DevStartMonitor(g_dev);
		if (ret)
		{
			printf("start monitor failed ret=%d err=%d\n", ret, errnoGet());
			break;
		}
		monitor_flag = 1;
		printf("start monitor success recv data...\n");
		/*等待停止接收的信号*/
		reason = semTake(g_stop_int_recv_handle, WAIT_FOREVER);
		if (reason != OK)
		{
			printf("wait stop int recv single failed err=%d\n", errnoGet());
		}
	} while (FALSE);
	/*退出线程*/
	if (g_stop_int_recv_handle != NULL)
	{
		semDelete(g_stop_int_recv_handle);
		g_stop_int_recv_handle = NULL;
	}
	if (monitor_flag == 1)
	{
		ret = FCM_DevStopMonitor(g_dev);
		if (ret)
		{
			printf("stop monitor failed ret=%d err=%d\n", ret, errnoGet());
			return 0;
		}
		printf("stop monitor success\n");
	}
	if (reg_event_flag == 1)
	{
		ret = FCM_DevUnRegEvtHandler(g_dev);
		if (ret)
		{
			printf("unregister event handler failed ret=%d err=%d\n", ret, errnoGet());
			return 0;
		}
		printf("unregister event handler success\n");
	}
	if (reg_int_recv_flag == 1)
	{
		ret = FCM_DevUnRegMsgHandler(g_dev);
		if (ret)
		{
			printf("unregister msg int handler failed ret=%d err=%d\n", ret, errnoGet());
			return 0;
		}
		printf("unregister msg int handler success\n");
	}
	if (dev_open_flag == 1)
	{
		ret = FCM_DevClose(g_dev);
		if (ret)
		{
			printf("dev close failed ret=%d err=%d\n", ret, errnoGet());
			return 0;
		}
		printf("dev close success\n");
	}
	g_recv_handle = ERROR;
	printf("recv thread stop\n");
	return 0;
}
/*事件中断回调*/
FCUINT event_callback(FCHANDLE hDev, FCUINT intCode, FCUINT param0)
{
	int idx, count;
	PINT_EVT_DESC d;

	assert(hDev != NULL);
	count = INT_EVT_DESC_MAX;
	idx = intCode - 0x100;
	if (!(idx >= 0 && idx < count))
	{
		printf("g_dev=%p int code=0x%08x param0=0x%08x\n", hDev, intCode, param0);
		return 0 ;
	}
	d = &g_demo_stat.int_evt_desc[idx];
	if (d->intCode == 0)
	{
		d->intCode = intCode;
	}
	else
	{
		assert(d->intCode == intCode && d->count > 0);
	}
	d->count++;
	return 0;
}
/*接收数据的回调*/
FCUINT int_recv_callback(FCHANDLE hDev, void *buf, FCUINT length)
{
	size_t w_len;
	FCUINT ret;

	parse_buf((unsigned char *)buf, length);
	/*释放缓冲区*/
	ret = FCM_ReleaseBuf(hDev, buf);
	if (ret)
	{
		printf("[%s]FCM_ReleaseBuf failed ret=0x%08x err=0x%08x\n", __FUNCTION__, ret, errnoGet());
	}
	return 0;
}
/*解析数据*/
void parse_buf(unsigned char *buf, int length)
{
	int ret, frame_length;
	PFCM_DEMO_STATISTICS stat;
	PFCM_RECORD_HEADER rec_header;

	stat = &g_demo_stat;
	while (length > 0)
	{
		rec_header = (PFCM_RECORD_HEADER)buf;
		if (rec_header->cfgID != FRAME_CFGID)
		{
			stat->cfgid_err++;
			return;
		}
		if (rec_header->monitorID != FRAME_MONITORID)
		{
			stat->monitorid_err++;
			return;
		}
		ret = check_flag(rec_header->flag, stat);
		if (ret) return;
		frame_length = rec_header->length - sizeof(FCM_RECORD_HEADER);
		stat->bytes += frame_length;
		stat->frame_num++;

		buf += rec_header->length;
		length -= rec_header->length;
	}
	assert(length == 0);
}
/*检查记录头的错误标记*/
int check_flag(UINT32 flag, PFCM_DEMO_STATISTICS v)
{
	if (flag & FRAME_FLAG_CRC_ERR) { v->crc_err++; return 1; }
	if (flag & FRAME_FLAG_UNDERSIZE) { v->undersize++; return 2; }
	if (flag & FRAME_FLAG_OVERSIZE) { v->oversize++; return 3; }
	if (flag & FRAME_FLAG_NO_EOF_ERR) { v->no_eof_err++; return 4; }
	if (flag & FRAME_FLAG_DISP_ERR) { v->disp_err++; return 5; }
	if (flag & FRAME_FLAG_CODING_ERR) { v->coding_err++; return 6; }
	return 0;
}
/*打印统计值*/
void print_statistics()
{
	int i;
	PFCM_DEMO_STATISTICS s;

	s = &g_demo_stat;
	printf("statistics[bytes=%lld frame_num=%lld cfgid_err=%lld monitorid_err=%lld crc_err=%lld undersize=%lld oversize=%lld no_eof_err=%lld disp_err=%lld coding_err=%lld]\n",
		s->bytes, s->frame_num, s->cfgid_err, s->monitorid_err, s->crc_err, s->undersize, s->oversize, s->no_eof_err, s->disp_err, s->coding_err);
	for (i = 0; i < INT_EVT_DESC_MAX; ++i)
	{
		PINT_EVT_DESC d = &s->int_evt_desc[i];
		if (d->count == 0) continue;
		printf("event int[int code=0x%08x param0=%d count=%d]", d->intCode, d->param0, d->count);
	}
}
/*显示命令提示*/
void usage()
{
	printf("============= FM130 TEST COMMAND ============\n");
	printf("| start_recv()      -- start monitor        |\n");
	printf("| stop_recv()       -- stop monitor         |\n");
	printf("| print_statistics()-- print demo statistics|\n");
	printf("=============================================\n");
}
