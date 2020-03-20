#include "precomp.h"
#include <direct.h>
#include <io.h>

#define INDEX_FILE_LINES        300 /* 索引文件索引行数 */
#define INDEX_FRAME_INTERVAL    100   /* 索引文件的帧间隔 */
#define INDEX_FILE_LENGTH (INDEX_FILE_LINES * (sizeof(int) + sizeof(UINT64)))
#define INDEX_FN_EXT    "idx"
#define DATA_FN_EXT   "dat"
#define STATISTICS_FN    "statistics.dat"
#define DATA_DIR          "data"

static int g_fn_index; /* 文件索引，从0开始，步长是1， 初始设置为-1 */
static int g_frame_num; /* 帧数，当达到索引文件的行数的固定值，就从0开始重新计算，关闭索引文件和数据文件，文件索引值加1，重新创建索引文件和数据文件。*/
static int g_frame_num_record; /* 初始是frame_num_record = 0 + INDEX_FRAME_INTERVAL，  当frame_num跟frame_num_record相等时，*/
static UINT64 g_data_offset; /* 帧在数据文件中的位置 */
static char *g_index_content_buf;
static char *g_index_content_buf_pointer;
static FILE *g_fp_index, *g_fp_data, *g_fp_statistics;

UINT64 reverse_bytes_uint64(UINT64 value)
{
	UINT64 ret;

	ret = htonl((UINT32)value);
	ret = ret << 32;

	ret += htonl((UINT32)(value >> 32));

	return ret;
}


/* 初始化监控卡接收数据存盘用到的全局变量 */
void InitWriteGlobalVariable()
{
	g_fn_index = -1;
	g_frame_num = 0;
	g_frame_num_record = 0 + INDEX_FRAME_INTERVAL;
	g_data_offset = 0;
	g_fp_index = NULL;
	g_fp_data = NULL;
	g_fp_statistics = NULL;
	g_index_content_buf = (char *)malloc(INDEX_FILE_LENGTH * 2);
	g_index_content_buf_pointer = g_index_content_buf;
}

/* 当程序要退出时，关闭打开的文件指针， 复位所有变量 */
void ResetWriteGlobalVariable()
{
	g_fn_index = -1;
	g_frame_num = 0;
	g_frame_num_record = 0 + INDEX_FRAME_INTERVAL;
	g_data_offset = 0;

	if (g_fp_index)
	{
		fclose(g_fp_index);
		g_fp_index = NULL;
	}

	if (g_fp_data)
	{
		fclose(g_fp_data);
		g_fp_data = NULL;
	}

	if (g_fp_statistics)
	{
		fclose(g_fp_statistics);
		g_fp_statistics = NULL;
	}

	free(g_index_content_buf);
	g_index_content_buf = NULL;

	g_index_content_buf_pointer = NULL;
}

/* 创建文件，把文件索引全局变量g_fn_index加一，根据g_fn_index创建索引文件和数据文件，如果g_fn_index是0，就创建统计文件*/
int CreateNewFile()
{
	int ret;
	errno_t err;
	char file_name[MAX_PATH], *mode = "wb";
	char data_path[MAX_PATH] = {0};

	ret = 0;
	g_fn_index++;

	_getcwd(data_path, MAX_PATH);
	sprintf_s(data_path, MAX_PATH, "%s\\%s", data_path, DATA_DIR);
	if( (_access(data_path, 0 )) == -1 )
	{
		 _mkdir(data_path);
	}

	do {
		if (g_fn_index > 0)
		{
			fclose(g_fp_index);
			fclose(g_fp_data);

			g_fp_index = NULL;
			g_fp_data = NULL;
		}

		/* open index file */
		memset(file_name, 0, MAX_PATH);
		sprintf_s(file_name, MAX_PATH, "%s\\%08d.%s", data_path, g_fn_index, INDEX_FN_EXT);
		err = fopen_s(&g_fp_index, file_name, mode);
		assert(err == 0);
		if (err)
		{
			ret = 1;
			break;
		}

		/* open data file */
		memset(file_name, 0, MAX_PATH);
		sprintf_s(file_name, MAX_PATH, "%s\\%08d.%s", data_path, g_fn_index, DATA_FN_EXT);
		err = fopen_s(&g_fp_data, file_name, mode);
		assert(err == 0);
		if (err)
		{
			ret = 2;
			break;
		}

		if (g_fn_index == 0)
		{
			/* open statistics file */
			memset(file_name, 0, MAX_PATH);
			sprintf_s(file_name, MAX_PATH, "%s\\%s", data_path, STATISTICS_FN);
			err = fopen_s(&g_fp_statistics, file_name, mode);
			assert(err == 0);
			if (err)
			{
				ret = 3;
				break;
			}
		}
	} while (FALSE);

	return ret;
}


/*写buf到文件*/
int WriteBufToFile(char *buf, int length, FILE *fp)
{
	assert(fp != NULL);
	if (fp)
	{
		fwrite(buf, length, 1, fp);
	}

	return 0;
}

/*
	计算帧数
	遇到一个帧，帧数就加1，
	当帧数达到行数限制，就写索引文件和数据文件，在创建文件。
	如果不需要切换文件，就判断是否要记录索引。
*/
int ComputeFrameNum(char **origin_buf, int *origin_len, char *cur_buf, int len_of_a_record)
{
	/*记录帧数*/
	g_frame_num++;  /*帧数从1，开始，遇到一个帧就加1*/

	/* 记录索引 */
	if (g_frame_num == g_frame_num_record)
	{
		*(int *)g_index_content_buf_pointer = htonl(g_frame_num);
		g_index_content_buf_pointer += sizeof(int);
		*(UINT64 *)g_index_content_buf_pointer = reverse_bytes_uint64(g_data_offset);
		g_index_content_buf_pointer += sizeof(UINT64);
			
		g_frame_num_record += INDEX_FRAME_INTERVAL;
	}
	
	g_data_offset += len_of_a_record;


	/* 索引行数满了，切换文件 */
	if ((INDEX_FRAME_INTERVAL * INDEX_FILE_LINES) == g_frame_num)
	{
		/* 写文件 */
		WriteBufToFile(*origin_buf, cur_buf - *origin_buf, g_fp_data);
		WriteBufToFile(g_index_content_buf, INDEX_FILE_LENGTH, g_fp_index);
		*origin_len -= cur_buf - *origin_buf;
		*origin_buf = cur_buf;

		g_frame_num = 0;
		g_frame_num_record = INDEX_FRAME_INTERVAL;
		g_data_offset = 0;
		g_index_content_buf_pointer = g_index_content_buf;
		CreateNewFile();
	}
	
	return 0;
}

/* 把64位变量改变字节序后写入文件 */
void WriteUint64ToFile(UINT64 value, FILE *fp)
{
	UINT64 v = reverse_bytes_uint64(value);
	WriteBufToFile((char *)&v, 8, fp);
}

int WriteStatisticsToFile(PFCM_DEMO_STATISTICS st)
{
	WriteUint64ToFile((UINT64)(g_fn_index + 1), g_fp_statistics);
	WriteUint64ToFile(st->bytes, g_fp_statistics);
	WriteUint64ToFile(st->frame_num, g_fp_statistics);
	WriteUint64ToFile(st->cfgid_err, g_fp_statistics);
	WriteUint64ToFile(st->monitorid_err, g_fp_statistics);
	WriteUint64ToFile(st->crc_err, g_fp_statistics);
	WriteUint64ToFile(st->undersize, g_fp_statistics);
	WriteUint64ToFile(st->oversize, g_fp_statistics);
	WriteUint64ToFile(st->no_eof_err, g_fp_statistics);
	WriteUint64ToFile(st->disp_err, g_fp_statistics);
	WriteUint64ToFile(st->coding_err, g_fp_statistics);

	return 0;
}

/* 写索引文件 */
int WriteIndexFile()
{
	WriteBufToFile(g_index_content_buf, g_index_content_buf_pointer - g_index_content_buf, g_fp_index);

	return 0;
}

/* 写buf到数据文件g_fp_data */
void WriteBufToDataFile(char *buf, int len)
{
	WriteBufToFile(buf, len, g_fp_data);
}
