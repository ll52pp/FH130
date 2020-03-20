/*++
文件名
    utils.c

描述
    通用
--*/

#include "precomp.h"
#include "utils.tmh"

//
// 延时
//
VOID KeDelay(IN LONG time)
{
    LARGE_INTEGER interval;
    interval.QuadPart = time;
	KeDelayExecutionThread(KernelMode, FALSE, &interval);
}

//
// 获取系统启动以来的毫秒数
//
LONGLONG GetSysMilliCount()
{
    LARGE_INTEGER tick;
    ULONG time;

    time = KeQueryTimeIncrement();
    KeQueryTickCount(&tick);

    tick.QuadPart *= time;
    tick.QuadPart /= (1000 * 10);

    return tick.QuadPart;
}

VOID print_dev_config(IN PDEV_CONFIG dc)
{
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INIT, "dev config[credit_num=%d speed=%d did_filter_enab=%d e_d_tov=%d redundant_enab=%d time_out=%d qdr_buf_unit_size=%d sw_fcid=%d]",
        dc->credit_num, dc->speed, dc->did_filter_enab, dc->e_d_tov, dc->redundant_enab, dc->time_out, dc->qdr_buf_unit_size, dc->sw_fcid);
}

VOID print_buf(IN INT32 key, IN PUCHAR buf, IN INT32 length)
{
    INT32 i, count;
    PUCHAR b;

    b = buf;
    count = length / 16;
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INIT, "[key=0x%08x]buf=%p length=%d", key, b, length);
    for (i = 0; i < count; ++i)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "%02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x",
            b[i * 16], b[i * 16 + 1], b[i * 16 + 2], b[i * 16 + 3], b[i * 16 + 4], b[i * 16 + 5], b[i * 16 + 6], b[i * 16 + 7], b[i * 16 + 8], b[i * 16 + 9], b[i * 16 + 10], b[i * 16 + 11], b[i * 16 + 12], b[i * 16 + 13], b[i * 16 + 14], b[i * 16 + 15]);
    }
}

VOID print_statistics(IN INT key, IN PFPGA_STATISTICS_INFO fsi, IN PPORT_STATISTICS_INFO psi)
{
    int i;
    KdPrint(("fpga statistics[recvFrameNumTotal=%I64d recvIUNumTotal=%I64d recvErrorIUNumTotal=%I64d recvDiscardFrameNumTotal=%I64d recvInvalidFrameNumTotal=%I64d sendFrameNumTotal=%I64d sendIUNumTotal=%I64d]\n",
        fsi->recvFrameNumTotal, fsi->recvIUNumTotal, fsi->recvErrorIUNumTotal, fsi->recvDiscardFrameNumTotal, fsi->recvInvalidFrameNumTotal, fsi->sendFrameNumTotal, fsi->sendIUNumTotal));
    for (i = 0; i < 2; ++i)
    {
        KdPrint(("port[%d] statistics[RxUndersizeFrameCnt=%I64d RxOversizeFrameErrCnt=%I64d RxAllFrameCnt=%I64d RxValidFrameCnt=%I64d RxWordCnt=%I64d RxRRDYCnt=%I64d RxKErrCnt=%I64d LinkChgUp2DownCnt=%I64d TxAllFrameCnt=%I64d TxValidFrameCnt=%I64d TxWordCnt=%I64d TxRRDYCnt=%I64d TxKErrCnt=%I64d]\n",
            i, psi[i].RxUndersizeFrameCnt, psi[i].RxOversizeFrameErrCnt, psi[i].RxAllFrameCnt, psi[i].RxValidFrameCnt, psi[i].RxWordCnt, psi[i].RxRRDYCnt, psi[i].RxKErrCnt, psi[i].LinkChgUp2DownCnt, psi[i].TxAllFrameCnt, psi[i].TxValidFrameCnt, psi[i].TxWordCnt, psi[i].TxRRDYCnt, psi[i].TxKErrCnt));
    }


}