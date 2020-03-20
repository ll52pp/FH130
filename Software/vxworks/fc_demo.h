#ifndef __FC_API_H__
#define __FC_API_H__

#include "hba.h"
#include "fc_utility.h"

/* demo�����ͳ�����ݽṹ */
typedef struct _DEMO_STATISTICS
{
    UINT64 frameNum;
    UINT64 frameTotalByte;
	UINT64 bufferTotalByte; /*R0 length*/
	UINT64 bufferTotalNum; /*DMA BUFFER NUM*/	
} DEMO_STATISTICS, *PDEMO_STATISTICS;

/* ʹ�÷��� */
void usage();
/* �������� */
void start_test();
/* ֹͣ���� */
void stop_test();
/* ���ԵĻص����� */
int test_callback(void *context);

/*------------------------------�豸����ӿ�------------------------------*/
/* ��FC�ڵ㿨,������Դ */
unsigned int dev_open();
/* �ر�FC�ڵ㿨���ͷ���Դ */
unsigned int dev_close();
/* ��ȡFC�ڵ����N�˿�״̬ */
unsigned int dev_get_state();
/* ��ȡFC�ڵ����N�˿ڰ汾�� */
unsigned int dev_get_version();
/* ����FC�ڵ㿨 */
unsigned int dev_config();
/* ע���жϽ��ջص����� */
unsigned int dev_reg_msg_handler();
/* ע���жϽ��ջص����� */
unsigned int dev_unreg_msg_handler();

/*------------------------------ʱͳ����ӿ�------------------------------*/
/* ��ȡFC�ڵ����ʱ�� */
unsigned int get_rtc();
/* ����FC�ڵ����ʱ�� */
unsigned int set_rtc(unsigned int hour, unsigned int minute, unsigned int second);
/* ��ȡFC�ڵ�������� */
unsigned int get_date_time();
/* ����FC�ڵ�������� */
unsigned int set_date(unsigned int year, unsigned int month, unsigned int day);
/* ���ջص����� */
unsigned int fc_np_recv_func(INT32 *hDev, void *pBuffer, UINT nLen);
/* ��ӡ���ڽṹ�� */
void print_date(FCDate *date);
/* ��ӡʱ��ṹ�� */
void print_time(FCTime *time);
/* ��ӡͳ������ */
void print_statistics();
/* ͳ���������� */
void clear_statistics();
/* ����֡����¼ͳ������ */
int parse_frame(char *buf, int length);

int parse_dmaBuf(char *buf, int length);
/* ��ӡ������ */
void print_buf(char *buf, int length);
/* ���ò�����ʼ�� */
void dev_init_config();
/* �������� */
unsigned int dev_config_speed(int speed);

/*��ʼ���*/
unsigned int dev_start_monitor();

/*ֹͣ���*/
unsigned int dev_stop_monitor();


#endif /* __FC_DEMO_H__ */