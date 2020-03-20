#ifndef __INCLUDE_D_LIST_H__
#define __INCLUDE_D_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <semLib.h>

/***************************************************
用于把缓冲区中保存的连续帧
展开到以单个帧保存的双向链表中
***************************************************/

#define RAW_FRAME_NODE_COUNT           3072
#define RAW_FRAME_THRESHOLD_COUNT      512
#define RAW_FRAME_NUMBER_MAX           448 /* 64*7 */

/* 双向链表节点定义 */
typedef struct _LIST_ENTRY {
    struct _LIST_ENTRY *f_link; /* 下一个节点 */
    struct _LIST_ENTRY *b_link; /* 上一个节点 */
} LIST_ENTRY, *PLIST_ENTRY;

/* 原始FC帧的控制结构定义 */
typedef struct _RAW_FRAME_CTRL {
    SEM_ID      lock;            /* 操作链表的锁 */
    int         count;           /* 链表节点总数 */
    int         used_count;      /* 已经使用的节点 */
    int         threshold_count; /* 阈值，空闲节点数小于等于阈值表示链表已经满了 */
    PLIST_ENTRY read_entry;      /* 当前的读节点，该节点指向有数据的节点 */
    PLIST_ENTRY write_entry;     /* 当前的写节点，该节点指向空闲结点 */
} RAW_FRAME_CTRL, *PRAW_FRAME_CTRL;

/* 原始FC帧节点定义 */
typedef struct _RAW_FRAME_NODE {
    LIST_ENTRY entry;      /* 链表 */
    int        port;       /*来自哪个端口或要从哪个端口发送*/
    int        length;     /* 节点长度 */
    char       data[2148]; /* 保存完整的FC帧 */
} RAW_FRAME_NODE, *PRAW_FRAME_NODE;

/* 把连续保存的帧展开到单个帧链表 */
void ExpandToRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length);

/* 初始化链表 */
int InitRawFrameList(PRAW_FRAME_CTRL ctrl);

/* 释放链表 */
void UnInitRawFrameList(PRAW_FRAME_CTRL ctrl);

/* 判断链表是否已满 */
int RawFrameListIsFull(PRAW_FRAME_CTRL ctrl);

/* 向链表写入一个节点 */
void WriteRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int port);

/* 根据key从链表中读取一个节点 */
int ReadRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int *real_length, int *port);

/* 2018-3-28：从链表中读取一个节点（不根据key读取） */
int ReadFirstRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int *real_length, int *port);

#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_D_LIST_H__ */

