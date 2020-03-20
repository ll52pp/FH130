/*++
文件名
    write.h

描述
    写请求
--*/

#ifndef __WRITE_H__
#define __WRITE_H__

EVT_WDF_IO_QUEUE_IO_WRITE EvtIoWrite; // 写请求回调例程

#ifdef ALLOC_PRAGMA
#endif

#endif  // __WRITE_H__