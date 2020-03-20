/*++
文件名
    read.h

描述
    读请求
--*/

#ifndef __READ_H__
#define __READ_H__

///////////////////////////////////////////////////////////////////////////////
// 链表操作例程
///////////////////////////////////////////////////////////////////////////////
//
// 把节点从链表的头部摘下
//
PLIST_ENTRY ListRemoveNode(
    IN PIO_LIST_CTRL ctrl
    );
//
// 从链表的尾部插入节点(空闲节点)
//
VOID ListInsertNodeFromTail(
    IN PIO_LIST_CTRL ctrl,
    IN PLIST_ENTRY entry
    );
//
// 从接收链表取得一个节点
//
INT32 RecvDataFromList(
    IN PFDO_DATA fdoData,
    IN PDMA_BUF_NODE_HEADER *header
    );
//
// 向中断数组添加
//
INT32 IntRecvListAdd(
    IN PFDO_DATA fdoData,
    IN PDMA_BUF_NODE_HEADER header
    );
//
// 接收数据
//
KSTART_ROUTINE RecvCallBack;
//
// 读请求回调
//
EVT_WDF_IO_QUEUE_IO_READ EvtIoRead;

#ifdef ALLOC_PRAGMA
#endif

#endif  // __READ_H__