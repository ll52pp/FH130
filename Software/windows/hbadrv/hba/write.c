/*++
文件名
    write.c

描述
    写请求
--*/

#include "precomp.h"
#include "write.tmh"

VOID EvtIoWrite(
    IN WDFQUEUE Queue,
    IN WDFREQUEST Request,
    IN size_t Length
)
/*++
描述：写请求处理例程
--*/
{
    NTSTATUS status;
	size_t buf_len;
	PUCHAR buf;
    ULONG credits[3], valid_buf_num;
    PFDO_DATA fdoData;
    PDMA_BUF_NODE_HEADER header;
    PIO_LIST_CTRL ctrl;
    PR_CTRL r_ctrl;
    PLIST_ENTRY entry;
    PREG_HW reg_hw;
    
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_WRITE, "%s enter", __FUNCTION__);
    fdoData = FdoGetData(WdfIoQueueGetDevice(Queue));
    reg_hw = fdoData->Reg;

	// 取得缓冲区
    status = WdfRequestRetrieveInputBuffer(Request, Length, &buf, &buf_len);
	if (!NT_SUCCESS(status))
	{
        TraceEvents(TRACE_LEVEL_ERROR, DBG_WRITE, "WdfRequestRetrieveInputBuffer failed status=0x%08x", status);
    	WdfRequestCompleteWithInformation(Request, status, 0);
    	return ;
    }
    // 注意：header地址是在R3层取得的
    header = (PDMA_BUF_NODE_HEADER)*(int *)buf;
    ASSERT(header != NULL);
    r_ctrl = (PR_CTRL)header->va;
    r_ctrl->r0.value = 0;
    r_ctrl->r1.value = 0;
    entry = (PLIST_ENTRY)header;
    ctrl = &fdoData->RecvCtrl;
    // 推信用
    credits[0] = header->index;
    valid_buf_num = 1;
    HwPushCreditsToFpga(reg_hw, credits, valid_buf_num);
    // 放入链表末尾
    ListInsertNodeFromTail(ctrl, entry);
    buf_len = sizeof(INT32);
	WdfRequestCompleteWithInformation(Request, status, buf_len);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_WRITE, "%s leave", __FUNCTION__);
}