/*++
文件名
    read.c

描述
    读请求
--*/

#include "precomp.h"
#include "read.tmh"

VOID EvtIoRead(
    IN WDFQUEUE Queue,
    IN WDFREQUEST Request,
    IN size_t Length
    )
/*
描述：读请求处理例程
*/
{
    NTSTATUS status;
    INT32 ret;
	size_t buf_length;
    PUCHAR buf;
	PFDO_DATA fdoData;
    PDMA_BUF_NODE_HEADER header;
    PDMA_BUF_NODE node;
    PR_CTRL r_ctrl;
    
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "%s enter", __FUNCTION__);
    fdoData = FdoGetData(WdfIoQueueGetDevice(Queue));

	// 如果监控没有开始，不能接收数据
	if (fdoData->State != ECS_MONITOR)
	{
		status = STATUS_UNSUCCESSFUL;
		TraceEvents(TRACE_LEVEL_ERROR, DBG_READ, "invalid state=%d", fdoData->State);
		WdfRequestCompleteWithInformation(Request, status, 0);
		return;
	}

	// 取得缓冲区
    status = WdfRequestRetrieveOutputBuffer(Request, Length, &buf, &buf_length);
	if (!NT_SUCCESS(status))
	{
        TraceEvents(TRACE_LEVEL_ERROR, DBG_READ, "WdfRequestRetrieveOutputBuffer failed(status=0x%08x)", status);
    	WdfRequestCompleteWithInformation(Request, status, 0);
    	return ;
    }
    header = NULL;
    ret = RecvDataFromList(fdoData, &header);
    if (ret)
    {
        buf_length = 0;
        if (ret == RECV_NO_DATA)
        {
            status = STATUS_SUCCESS;
        }
        else
        {
            status = STATUS_UNSUCCESSFUL;
        }
    }
    else
    {
        // 给R3返回地址，内存已经映射到R3，可以直接访问
        // 注意：这里用了技巧，把DMA_BUF_NODE_HEADER的地址保存在DMA_BUF_NODE->r_ctrl->r1
        //       R3释放地址时，把R3提供的地址值向前偏移sizeof(R_CTRL)个字节找到r_ctrl，从r_ctrl->r1得到header的地址(该地址FPGA保证不会写入)
        //       如果以后需要使用r1，驱动层要使用数据结构(哈希表)保存映射关系，通过查找，找到header的地址

        // 1 记录释放时用到的DMA_BUF_NODE_HEADER的地址
        node = (PDMA_BUF_NODE)header->va;
        r_ctrl = &node->r_ctrl;
        r_ctrl->r1.value = (INT32)header;

        // 2 返回应用层能访问的地址
        *(INT32 *)buf = (INT32)((PUCHAR)header->va_r3 + sizeof(R_CTRL));
        buf_length = r_ctrl->r0.u.length;
        status = STATUS_SUCCESS;
    }
    WdfRequestCompleteWithInformation(Request, status, buf_length);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "%s leave", __FUNCTION__);
}

//
// 接收数据
//
VOID RecvCallBack(
    IN PVOID context
    )
{
    INT32 ret;
    ULONG credits[3], valid_buf_num;
    PDMA_BUF_NODE_HEADER header;
    PDMA_BUF_NODE node;
    PIO_LIST_CTRL ctrl;
    PLIST_ENTRY entry;
    PFDO_DATA fdoData;
    PREG_HW reg_hw;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "%s enter", __FUNCTION__);
    fdoData = (PFDO_DATA)context;
    reg_hw = fdoData->Reg;
    ctrl = &fdoData->RecvCtrl;

    while (fdoData->RecvThreadCtrl == THREAD_CTRL_RUN)
    {
        if (fdoData->State != ECS_MONITOR)
        {
            KeDelay(MILLI_SEC);
            continue;
        }
        if (fdoData->IntRecvFlag == INT_REG_COMPLETE)
        {
            header = NULL;
            ret = RecvDataFromList(fdoData, &header);
            if (ret)
            {
                continue;
            }
            // 放入中断接收缓冲区
            ret = IntRecvListAdd(fdoData, header);
            if (ret)
            {
                // 缓冲区满了
                node = (PDMA_BUF_NODE)header->va;
                node->r_ctrl.r0.value = 0;
                node->r_ctrl.r1.value = 0;
                // 推信用
                credits[0] = header->index;
                valid_buf_num = 1;
                HwPushCreditsToFpga(reg_hw, credits, valid_buf_num);
                // 放入链表末尾
                entry = (PLIST_ENTRY)header;
                ListInsertNodeFromTail(ctrl, entry);
                TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "int recv context full");
            }
        }
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "dma read PsTerminateSystemThread will invoke");
    PsTerminateSystemThread(STATUS_SUCCESS);
}

//
// 向中断数组添加
//
INT32 IntRecvListAdd(
    IN PFDO_DATA fdoData,
    IN PDMA_BUF_NODE_HEADER header
    )
{
    INT32 t_index, r0_index;
    PR_CTRL r_ctrl;
    PDMA_BUF_NODE node;
    PCBN_INT_RECV_CONTEXT context;

    ASSERT(fdoData->IntRecvFlag == INT_REG_COMPLETE);
    context = fdoData->IntRecvContext;
    r0_index = context->r0_index;
    t_index = (context->r0_index + 1) % INT_RECV_BLOCK_MAX;
    if (context->block[t_index] != 0 || t_index == context->r3_index)
    {
        // 缓冲区满，R0写指针追上了R3读指针
        ASSERT(context->block[r0_index] == 0);
        // 通知R3接收数据
        KeSetEvent(fdoData->IntRecvEvent, IO_SOUND_INCREMENT, FALSE);
        return 1;
    }
    // 内存已经映射到R3，只要返回R3能访问的地址。
    // 注意：这里用了技巧，把DMA_BUF_NODE_HEADER的地址保存在DMA_BUF_NODE->r_ctrl->r1
    //       R3释放地址时，偏移-sizeof(R_CTRL)字节，在R3把r1的值写入缓冲区，把r0和r1清零
    //       如果以后需要使用r1，驱动层要使用数据结构(哈希表)保存映射关系，通过查找，找到header的地址
    // 记录释放时用到的DMA_BUF_NODE_HEADER的地址
    node = (PDMA_BUF_NODE)header->va;
    r_ctrl = &node->r_ctrl;
    r_ctrl->r1.value = (INT32)header;
    // 返回应用层能访问的地址
    context->block[r0_index] = (INT32)((PUCHAR)header->va_r3 + sizeof(R_CTRL));
    // 移动到下一个空闲节点
    r0_index = (r0_index + 1) % INT_RECV_BLOCK_MAX;
    // 断言不会追上，设计就是永远差一个节点
    ASSERT(r0_index != context->r3_index);
    // 必然是空闲节点
    ASSERT(context->block[r0_index] == 0);
    context->r0_index = r0_index;
    // 通知R3接收数据
    KeSetEvent(fdoData->IntRecvEvent, IO_SOUND_INCREMENT, FALSE);
    return 0;
}

//
// 从接收链表取得一个节点
//
INT32 RecvDataFromList(
    IN PFDO_DATA fdoData,
    IN PDMA_BUF_NODE_HEADER *header
    )
{
    INT32 qdr_buf_unit_size, length;
    ULONG credits[3], valid_buf_num;
    PIO_LIST_CTRL ctrl;
    PLIST_ENTRY cur_entry;
    PDMA_BUF_NODE_HEADER h;
    PDMA_BUF_NODE node;
    PREG_HW reg_hw;

    qdr_buf_unit_size = fdoData->DevConfig.qdr_buf_unit_size;
    ctrl = &fdoData->RecvCtrl;
    reg_hw = fdoData->Reg;

    h = (PDMA_BUF_NODE_HEADER)ctrl->entry;
    if (h == NULL)
    {
        // 接收链表空
        return RECV_LIST_EMPTY;
    }
    node = (PDMA_BUF_NODE)h->va;
    if (node->r_ctrl.r0.u.length == 0)
    {
        // 没有数据
        return RECV_NO_DATA;
    }
    // 把节点取下来
    cur_entry = ListRemoveNode(ctrl);
	node->r_ctrl.r0.value = RtlUlongByteSwap(node->r_ctrl.r0.value);
    length = node->r_ctrl.r0.u.length;
    ASSERT(length > 0 && length <= qdr_buf_unit_size - (INT32)sizeof(R_CTRL));
    if (length > qdr_buf_unit_size - (INT32)sizeof(R_CTRL))
    {
		node->r_ctrl.r0.value = 0;
		node->r_ctrl.r1.value = 0;
		// 推信用
		credits[0] = h->index;
		valid_buf_num = 1;
		HwPushCreditsToFpga(reg_hw, credits, valid_buf_num);
		// 放入链表末尾
		ListInsertNodeFromTail(ctrl, cur_entry);
		TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "invalid r0.u.length=%d", length);
        return RECV_LENGTH_INVALID;
    }
    // 正确的数据
    *header = h;
    ASSERT((INT32)(*header) == (INT32)cur_entry && (INT32)cur_entry == (INT32)h && h != NULL);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// 链表操作例程
///////////////////////////////////////////////////////////////////////////////
//
// 把节点从链表的头部摘下
//
PLIST_ENTRY ListRemoveNode(
    IN PIO_LIST_CTRL ctrl
    )
{
    PLIST_ENTRY entry;

    ASSERT(ctrl != NULL);
    entry = ctrl->entry;
    if (entry == NULL)
    {
        // 链表是空的
        return entry;
    }
    if (entry == entry->Flink && entry == entry->Blink)
    {
        // 如果节点的前向和后向都指向自己，那么该节点从链表中摘下以后，控制头的指针指向NULL
        ctrl->entry = NULL;
    }
    else
    {
        ctrl->entry = ctrl->entry->Flink;
    }

    // 把entry从链表上摘下来
    entry->Flink->Blink = entry->Blink;
    entry->Blink->Flink = entry->Flink;
    // 摘下的节点和链表脱离
    entry->Flink = entry->Blink = entry;

    return entry;
}

//
// 从链表的尾部插入节点(空闲节点)
//
VOID ListInsertNodeFromTail(
    IN PIO_LIST_CTRL ctrl,
    IN PLIST_ENTRY entry
    )
{
    PLIST_ENTRY cur_entry;

    cur_entry = ctrl->entry;
    if (ctrl->entry == NULL)
    {
        // 插入第一个节点，该节点的前向和后向都指向自己
        entry->Flink = entry->Blink = entry;
        ctrl->entry = entry;
    }
    else
    {
        // 不是插入第一个节点
        entry->Flink = ctrl->entry;
        entry->Blink = ctrl->entry->Blink;
        ctrl->entry->Blink->Flink = entry;
        ctrl->entry->Blink = entry;
    }
}