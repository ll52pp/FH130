#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <tchar.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <locale.h>
#include <process.h>
#include <initguid.h>
#include <WinIoCtl.h>
#include <Windows.h>
#include <WinDef.h>
#include <Setupapi.h>

#include "..\\lib\\api.h"

#pragma comment(lib, "SetupAPI.Lib")
#pragma comment(lib, "WS2_32.Lib")
#pragma comment(lib, "..\\lib\\fm130.lib")

/*ͳ�����ݽṹ*/
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

/*����*/
#define FCM_CONFIG_CREDIT_NUM   8
/*����*/
#define FCM_SPEED               PORT_SPEED_2G
/*�����ļ���*/
#define DATA_FILE_NAME          "data"

/*���̿��أ�0-������ 1-����*/
int g_save_file = 0;
FILE *g_fp = NULL;
FCHANDLE g_dev = NULL;
HANDLE g_recv_handle = INVALID_HANDLE_VALUE;
HANDLE g_stop_int_recv_handle = INVALID_HANDLE_VALUE;
FCM_DEMO_STATISTICS g_demo_stat = { 0 };

/*��������*/
void start_recv();
/*ֹͣ����*/
void stop_recv();
/*�������ݵĻص�*/
UINT CALLBACK recv_callback(PVOID context);
/*�˳�*/
void quit();
/*�¼��жϻص�*/
FCUINT event_callback(FCHANDLE hDev, FCUINT intCode, FCUINT param0);
/*�������ݵĻص�*/
FCUINT int_recv_callback(FCHANDLE hDev, void *buf, FCUINT length);
/*��������*/
void parse_buf(unsigned char *buf, int length);
/*����¼ͷ�Ĵ�����*/
int check_flag(UINT32 flag, PFCM_DEMO_STATISTICS v);
/*��ӡͳ��ֵ*/
void print_statistics();
/*��ʾ������ʾ*/
void usage();
/*�����û����룬ִ������*/
void command_handler();

int main(const int argc, const char *argv[])
{
	command_handler();
	printf("press any key exit\n");
	getchar();
	return 0;
}
/*��������*/
void start_recv()
{
	UINT t_id;

	if (g_recv_handle == INVALID_HANDLE_VALUE)
	{
		g_recv_handle = (HANDLE)_beginthreadex(NULL, 0, recv_callback, NULL, 0, &t_id);
		if (g_recv_handle == INVALID_HANDLE_VALUE)
		{
			printf("start recv thread failed err=%d\n", GetLastError());
		}
		else
		{
			printf("start recv thread success\n");
		}
	}
}
/*ֹͣ����*/
void stop_recv()
{
	DWORD reason;

	if (g_recv_handle != INVALID_HANDLE_VALUE)
	{
		SetEvent(g_stop_int_recv_handle);
		reason = WaitForSingleObject(g_recv_handle, INFINITE);
		if (reason != WAIT_OBJECT_0)
		{
			printf("stop recv thread failed err=%d\n", GetLastError());
		}
		else
		{
			printf("stop recv thread success\n");
		}
	}
}
/*�������ݵĻص�*/
unsigned int CALLBACK recv_callback(PVOID context)
{
	FCUINT ret, dev_id;
	FCUINT va_addr, nLen;
	FCUCHAR *buf;
	FC_INT_FUNCPTR func_event;
	FC_NP_RECV_FUNCPTR func_int_recv;
	errno_t err;
	char data_fn[MAX_PATH];
	int save_file_flag, dev_open_flag, reg_event_flag, reg_int_recv_flag, dev_enab_flag, monitor_flag;
	DWORD reason;

	printf("recv thread start\n");
	dev_open_flag = reg_event_flag = reg_int_recv_flag = dev_enab_flag = monitor_flag = 0;
	func_event = event_callback;
	func_int_recv = int_recv_callback;
	buf = (FCUCHAR *)&va_addr;
	nLen = sizeof(int);
	sprintf_s(data_fn, MAX_PATH, "%s_%d.bin", DATA_FILE_NAME, GetTickCount());
	do {
		/*����ʹ�жϽ���ֹͣ���ź���*/
		g_stop_int_recv_handle = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (g_stop_int_recv_handle == INVALID_HANDLE_VALUE)
		{
			printf("create stop int recv single failed err=%d\n", GetLastError());
			break;
		}
		/*���ļ�*/
		if (g_save_file == 1)
		{
			err = fopen_s(&g_fp, data_fn, "ab+");
			if (err)
			{
				g_fp = NULL;
				printf("open %s failed err=%d\n", data_fn, GetLastError());
				break;
			}
			save_file_flag = 1;
			printf("save data to %s\n", data_fn);
		}
		/*���豸*/
		dev_id = 0;
		ret = FCM_DevOpen(&g_dev, dev_id);
		if (ret)
		{
			printf("open dev failed ret=%d err=%d\n", ret, GetLastError());
			break;
		}
		dev_open_flag = 1;
		printf("open dev success g_dev=%p dev_id=%d\n", g_dev, dev_id);
		/*ע���ж��¼�����*/
		ret = FCM_DevRegEvtHandler(g_dev, func_event);
		if (ret)
		{
			printf("register event handler failed ret=%d err=%d\n", ret, GetLastError());
			break;
		}
		reg_event_flag = 1;
		printf("register event handler success\n");
		/*ע���жϽ��ս������ݵĻص�*/
		ret = FCM_DevRegMsgHandler(g_dev, func_int_recv);
		if (ret)
		{
			printf("register msg int handler failed ret=%d err=%d\n", ret, GetLastError());
			break;
		}
		reg_int_recv_flag = 1;
		printf("register msg int handler success\n");
		/*ʹ���豸 FCID�̶�Ϊ0x100000*/
		ret = FCM_DevEnable(g_dev, 0x100000, FCM_CONFIG_CREDIT_NUM, FCM_SPEED);
		if (ret)
		{
			printf("dev enab failed ret=%d err=%d\n", ret, GetLastError());
			break;
		}
		dev_enab_flag = 1;
		printf("dev enab success\n");
		/*��ʼ���*/
		ret = FCM_DevStartMonitor(g_dev);
		if (ret)
		{
			printf("start monitor failed ret=%d err=%d\n", ret, GetLastError());
			break;
		}
		monitor_flag = 1;
		printf("start monitor success recv data...\n");
		/*�ȴ�ֹͣ���յ��ź�*/
		reason = WaitForSingleObject(g_stop_int_recv_handle, INFINITE);
		if (reason != WAIT_OBJECT_0)
		{
			printf("wait stop int recv single failed err=%d\n", GetLastError());
		}
	} while (FALSE);
	/*�˳��߳�*/
	if (g_stop_int_recv_handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(g_stop_int_recv_handle);
		g_stop_int_recv_handle = INVALID_HANDLE_VALUE;
	}
	if (save_file_flag == 1)
	{
		fclose(g_fp);
		printf("close file success\n");
	}
	if (monitor_flag == 1)
	{
		ret = FCM_DevStopMonitor(g_dev);
		if (ret)
		{
			printf("stop monitor failed ret=%d err=%d\n", ret, GetLastError());
			return 0;
		}
		printf("stop monitor success\n");
	}
	if (reg_event_flag == 1)
	{
		ret = FCM_DevUnRegEvtHandler(g_dev);
		if (ret)
		{
			printf("unregister event handler failed ret=%d err=%d\n", ret, GetLastError());
			return 0;
		}
		printf("unregister event handler success\n");
	}
	if (reg_int_recv_flag == 1)
	{
		ret = FCM_DevUnRegMsgHandler(g_dev);
		if (ret)
		{
			printf("unregister msg int handler failed ret=%d err=%d\n", ret, GetLastError());
			return 0;
		}
		printf("unregister msg int handler success\n");
	}
	if (dev_open_flag == 1)
	{
		ret = FCM_DevClose(g_dev);
		if (ret)
		{
			printf("dev close failed ret=%d err=%d\n", ret, GetLastError());
			return 0;
		}
		printf("dev close success\n");
	}
	g_recv_handle = INVALID_HANDLE_VALUE;
	printf("recv thread stop\n");
	return 0;
}
/*�˳�*/
void quit()
{
	if (g_recv_handle != INVALID_HANDLE_VALUE)
	{
		stop_recv();
	}
}
/*�¼��жϻص�*/
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
/*�������ݵĻص�*/
FCUINT int_recv_callback(FCHANDLE hDev, void *buf, FCUINT length)
{
	size_t w_len;
	FCUINT ret;

	if (g_save_file == 1)
	{
		w_len = fwrite(buf, length, 1, g_fp);
		if (w_len != 1)
		{
			printf("write data failed expect len is %d real len is %d\n", length, w_len);
		}
	}
	parse_buf((unsigned char *)buf, length);
	/*�ͷŻ�����*/
	ret = FCM_ReleaseBuf(hDev, buf);
	if (ret)
	{
		printf("[%s]FCM_ReleaseBuf failed ret=0x%08x err=0x%08x\n", __FUNCTION__, ret, GetLastError());
	}
	return 0;
}
/*��������*/
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
/*����¼ͷ�Ĵ�����*/
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
/*��ӡͳ��ֵ*/
void print_statistics()
{
	int i;
	PFCM_DEMO_STATISTICS s;

	s = &g_demo_stat;
	printf("bytes=%I64d frame_num=%I64d cfgid_err=%I64d monitorid_err=%I64d crc_err=%I64d undersize=%I64d oversize=%I64d no_eof_err=%I64d disp_err=%I64d coding_err=%I64d\n",
		s->bytes, s->frame_num, s->cfgid_err, s->monitorid_err, s->crc_err, s->undersize, s->oversize, s->no_eof_err, s->disp_err, s->coding_err);
	for (i = 0; i < INT_EVT_DESC_MAX; ++i)
	{
		PINT_EVT_DESC d = &s->int_evt_desc[i];
		if (d->count == 0) continue;
		printf("event int[int code=0x%08x param0=%d count=%d]", d->intCode, d->param0, d->count);
	}
}
/*��ʾ������ʾ*/
void usage()
{
	printf("++++++++++++++++++++FM130 TEST COMMAND++++++++++++++++++++\n");
	printf("| s - start monitor         | t - stop monitor           |\n");
	printf("| y - clear screen          | x - exit                   |\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
/*�����û����룬ִ������*/
void command_handler()
{
	int cmd, stop, refresh;

	refresh = 1;
	stop = 0;
	fflush(stdin);
	while (stop == 0)
	{
		if (refresh == 1)
		{
			refresh = 0;
			usage();
		}
		cmd = getchar();
		fflush(stdin);
		cmd = tolower(cmd);

		switch (cmd)
		{
		case 's': { start_recv(); break; }
		case 't': { stop_recv(); break; }
		case 'y': { system("cls"); refresh = 1; break; }
		case 'x': { quit(); stop = 1; break; }
		default: { refresh = 1; break; }
		}
	}
}