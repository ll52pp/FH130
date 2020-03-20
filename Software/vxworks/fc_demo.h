#ifndef __FC_API_H__
#define __FC_API_H__

#include "hba.h"
#include "fc_utility.h"

/* demo程序的统计数据结构 */
typedef struct _DEMO_STATISTICS
{
    UINT64 frameNum;
    UINT64 frameTotalByte;
	UINT64 bufferTotalByte; /*R0 length*/
	UINT64 bufferTotalNum; /*DMA BUFFER NUM*/	
} DEMO_STATISTICS, *PDEMO_STATISTICS;

/* 使用方法 */
void usage();
/* 启动测试 */
void start_test();
/* 停止测试 */
void stop_test();
/* 测试的回调例程 */
int test_callback(void *context);

/*------------------------------设备管理接口------------------------------*/
/* 打开FC节点卡,分配资源 */
unsigned int dev_open();
/* 关闭FC节点卡，释放资源 */
unsigned int dev_close();
/* 获取FC节点机的N端口状态 */
unsigned int dev_get_state();
/* 获取FC节点机的N端口版本号 */
unsigned int dev_get_version();
/* 配置FC节点卡 */
unsigned int dev_config();
/* 注册中断接收回调函数 */
unsigned int dev_reg_msg_handler();
/* 注销中断接收回调函数 */
unsigned int dev_unreg_msg_handler();

/*------------------------------时统管理接口------------------------------*/
/* 获取FC节点机的时间 */
unsigned int get_rtc();
/* 设置FC节点机的时间 */
unsigned int set_rtc(unsigned int hour, unsigned int minute, unsigned int second);
/* 获取FC节点机的日期 */
unsigned int get_date_time();
/* 设置FC节点机的日期 */
unsigned int set_date(unsigned int year, unsigned int month, unsigned int day);
/* 接收回调定义 */
unsigned int fc_np_recv_func(INT32 *hDev, void *pBuffer, UINT nLen);
/* 打印日期结构体 */
void print_date(FCDate *date);
/* 打印时间结构体 */
void print_time(FCTime *time);
/* 打印统计数据 */
void print_statistics();
/* 统计数据清零 */
void clear_statistics();
/* 解析帧，记录统计数据 */
int parse_frame(char *buf, int length);

int parse_dmaBuf(char *buf, int length);
/* 打印缓冲区 */
void print_buf(char *buf, int length);
/* 配置参数初始化 */
void dev_init_config();
/* 配置速率 */
unsigned int dev_config_speed(int speed);

/*开始监控*/
unsigned int dev_start_monitor();

/*停止监控*/
unsigned int dev_stop_monitor();


#endif /* __FC_DEMO_H__ */