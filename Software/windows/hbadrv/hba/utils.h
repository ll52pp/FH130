/*++
文件名
    utils.h

描述
    通用
--*/

#ifndef __UTILS_H__
#define __UTILS_H__

//
// 内核延时
//
VOID KeDelay(IN LONG time);

//
// 获取系统启动以来的毫秒数
//
LONGLONG GetSysMilliCount();
VOID print_dev_config(IN PDEV_CONFIG dc);
VOID print_buf(IN INT32 key, IN PUCHAR buf, IN INT32 length);
VOID print_statistics(IN INT key, IN PFPGA_STATISTICS_INFO fsi, IN PPORT_STATISTICS_INFO psi);

#endif  // __UTILS_H__