#ifndef __INCLUDE_D_LIST_H__
#define __INCLUDE_D_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <semLib.h>

/***************************************************
���ڰѻ������б��������֡
չ�����Ե���֡�����˫��������
***************************************************/

#define RAW_FRAME_NODE_COUNT           3072
#define RAW_FRAME_THRESHOLD_COUNT      512
#define RAW_FRAME_NUMBER_MAX           448 /* 64*7 */

/* ˫������ڵ㶨�� */
typedef struct _LIST_ENTRY {
    struct _LIST_ENTRY *f_link; /* ��һ���ڵ� */
    struct _LIST_ENTRY *b_link; /* ��һ���ڵ� */
} LIST_ENTRY, *PLIST_ENTRY;

/* ԭʼFC֡�Ŀ��ƽṹ���� */
typedef struct _RAW_FRAME_CTRL {
    SEM_ID      lock;            /* ����������� */
    int         count;           /* ����ڵ����� */
    int         used_count;      /* �Ѿ�ʹ�õĽڵ� */
    int         threshold_count; /* ��ֵ�����нڵ���С�ڵ�����ֵ��ʾ�����Ѿ����� */
    PLIST_ENTRY read_entry;      /* ��ǰ�Ķ��ڵ㣬�ýڵ�ָ�������ݵĽڵ� */
    PLIST_ENTRY write_entry;     /* ��ǰ��д�ڵ㣬�ýڵ�ָ����н�� */
} RAW_FRAME_CTRL, *PRAW_FRAME_CTRL;

/* ԭʼFC֡�ڵ㶨�� */
typedef struct _RAW_FRAME_NODE {
    LIST_ENTRY entry;      /* ���� */
    int        port;       /*�����ĸ��˿ڻ�Ҫ���ĸ��˿ڷ���*/
    int        length;     /* �ڵ㳤�� */
    char       data[2148]; /* ����������FC֡ */
} RAW_FRAME_NODE, *PRAW_FRAME_NODE;

/* �����������֡չ��������֡���� */
void ExpandToRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length);

/* ��ʼ������ */
int InitRawFrameList(PRAW_FRAME_CTRL ctrl);

/* �ͷ����� */
void UnInitRawFrameList(PRAW_FRAME_CTRL ctrl);

/* �ж������Ƿ����� */
int RawFrameListIsFull(PRAW_FRAME_CTRL ctrl);

/* ������д��һ���ڵ� */
void WriteRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int port);

/* ����key�������ж�ȡһ���ڵ� */
int ReadRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int *real_length, int *port);

/* 2018-3-28���������ж�ȡһ���ڵ㣨������key��ȡ�� */
int ReadFirstRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int *real_length, int *port);

#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_D_LIST_H__ */

