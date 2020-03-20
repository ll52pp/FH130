///////////////////////////////////////////////////////////////////////////////
// 监控卡接收数据存盘模块
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/* 转换64位字节序 */
UINT64 reverse_bytes_uint64(UINT64 value);

/* 把64位变量改变字节序后写入文件 */
void WriteUint64ToFile(UINT64 value, FILE *fp);

/* 初始化监控卡接收数据存盘用到的全局变量 */
void InitWriteGlobalVariable();

/* 当程序要退出时，关闭打开的文件指针， 复位所有变量 */
void ResetWriteGlobalVariable();

/* 创建文件，把文件索引全局变量g_fn_index加一，根据g_fn_index创建索引文件和数据文件，如果g_fn_index是0，就创建统计文件*/
int CreateNewFile();

/*写buf到文件*/
int WriteBufToFile(char *buf, int length, FILE *fp);

/*
计算帧数
遇到一个帧，帧数就加1，
当帧数达到行数限制，就写索引文件和数据文件，在创建文件。
如果不需要切换文件，就判断是否要记录索引。
*/
int ComputeFrameNum(char **origin_buf, int *origin_len, char *cur_buf, int len_of_a_record);

// save statistics to file
int WriteStatisticsToFile(PFCM_DEMO_STATISTICS st);

/* 写索引文件 */
int WriteIndexFile();

/* 写buf到数据文件g_fp_data */
void WriteBufToDataFile(char *buf, int len);

#ifdef __cplusplus
}
#endif
