///////////////////////////////////////////////////////////////////////////////
// ��ؿ��������ݴ���ģ��
///////////////////////////////////////////////////////////////////////////////

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/* ת��64λ�ֽ��� */
UINT64 reverse_bytes_uint64(UINT64 value);

/* ��64λ�����ı��ֽ����д���ļ� */
void WriteUint64ToFile(UINT64 value, FILE *fp);

/* ��ʼ����ؿ��������ݴ����õ���ȫ�ֱ��� */
void InitWriteGlobalVariable();

/* ������Ҫ�˳�ʱ���رմ򿪵��ļ�ָ�룬 ��λ���б��� */
void ResetWriteGlobalVariable();

/* �����ļ������ļ�����ȫ�ֱ���g_fn_index��һ������g_fn_index���������ļ��������ļ������g_fn_index��0���ʹ���ͳ���ļ�*/
int CreateNewFile();

/*дbuf���ļ�*/
int WriteBufToFile(char *buf, int length, FILE *fp);

/*
����֡��
����һ��֡��֡���ͼ�1��
��֡���ﵽ�������ƣ���д�����ļ��������ļ����ڴ����ļ���
�������Ҫ�л��ļ������ж��Ƿ�Ҫ��¼������
*/
int ComputeFrameNum(char **origin_buf, int *origin_len, char *cur_buf, int len_of_a_record);

// save statistics to file
int WriteStatisticsToFile(PFCM_DEMO_STATISTICS st);

/* д�����ļ� */
int WriteIndexFile();

/* дbuf�������ļ�g_fp_data */
void WriteBufToDataFile(char *buf, int len);

#ifdef __cplusplus
}
#endif
