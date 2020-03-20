#include "precomp.h"
#include <direct.h>
#include <io.h>

#define INDEX_FILE_LINES        300 /* �����ļ��������� */
#define INDEX_FRAME_INTERVAL    100   /* �����ļ���֡��� */
#define INDEX_FILE_LENGTH (INDEX_FILE_LINES * (sizeof(int) + sizeof(UINT64)))
#define INDEX_FN_EXT    "idx"
#define DATA_FN_EXT   "dat"
#define STATISTICS_FN    "statistics.dat"
#define DATA_DIR          "data"

static int g_fn_index; /* �ļ���������0��ʼ��������1�� ��ʼ����Ϊ-1 */
static int g_frame_num; /* ֡�������ﵽ�����ļ��������Ĺ̶�ֵ���ʹ�0��ʼ���¼��㣬�ر������ļ��������ļ����ļ�����ֵ��1�����´��������ļ��������ļ���*/
static int g_frame_num_record; /* ��ʼ��frame_num_record = 0 + INDEX_FRAME_INTERVAL��  ��frame_num��frame_num_record���ʱ��*/
static UINT64 g_data_offset; /* ֡�������ļ��е�λ�� */
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


/* ��ʼ����ؿ��������ݴ����õ���ȫ�ֱ��� */
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

/* ������Ҫ�˳�ʱ���رմ򿪵��ļ�ָ�룬 ��λ���б��� */
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

/* �����ļ������ļ�����ȫ�ֱ���g_fn_index��һ������g_fn_index���������ļ��������ļ������g_fn_index��0���ʹ���ͳ���ļ�*/
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


/*дbuf���ļ�*/
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
	����֡��
	����һ��֡��֡���ͼ�1��
	��֡���ﵽ�������ƣ���д�����ļ��������ļ����ڴ����ļ���
	�������Ҫ�л��ļ������ж��Ƿ�Ҫ��¼������
*/
int ComputeFrameNum(char **origin_buf, int *origin_len, char *cur_buf, int len_of_a_record)
{
	/*��¼֡��*/
	g_frame_num++;  /*֡����1����ʼ������һ��֡�ͼ�1*/

	/* ��¼���� */
	if (g_frame_num == g_frame_num_record)
	{
		*(int *)g_index_content_buf_pointer = htonl(g_frame_num);
		g_index_content_buf_pointer += sizeof(int);
		*(UINT64 *)g_index_content_buf_pointer = reverse_bytes_uint64(g_data_offset);
		g_index_content_buf_pointer += sizeof(UINT64);
			
		g_frame_num_record += INDEX_FRAME_INTERVAL;
	}
	
	g_data_offset += len_of_a_record;


	/* �����������ˣ��л��ļ� */
	if ((INDEX_FRAME_INTERVAL * INDEX_FILE_LINES) == g_frame_num)
	{
		/* д�ļ� */
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

/* ��64λ�����ı��ֽ����д���ļ� */
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

/* д�����ļ� */
int WriteIndexFile()
{
	WriteBufToFile(g_index_content_buf, g_index_content_buf_pointer - g_index_content_buf, g_fp_index);

	return 0;
}

/* дbuf�������ļ�g_fp_data */
void WriteBufToDataFile(char *buf, int len)
{
	WriteBufToFile(buf, len, g_fp_data);
}
