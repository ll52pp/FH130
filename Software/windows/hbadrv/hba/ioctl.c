/*++
文件名
    ioctl.c

描述
    设备控制命令
--*/

#include "precomp.h"
#include "ioctl.tmh"

VOID EvtIoDeviceControl(
    IN WDFQUEUE Queue,
    IN WDFREQUEST Request,
    IN size_t OutputBufferLength,
    IN size_t InputBufferLength,
    IN ULONG IoControlCode
)
/*++
描述：对设备的各种控制请求会回调该例程
--*/
{
    NTSTATUS status;
	size_t com_len, inbuflen, outbuflen;
    PFDO_DATA fdoData;
    PUCHAR inbuf, outbuf;
    
    PAGED_CODE();
	UNREFERENCED_PARAMETER(OutputBufferLength);
	UNREFERENCED_PARAMETER(InputBufferLength);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    
    inbuf = NULL;
    status = WdfRequestRetrieveInputBuffer(Request, 0, &inbuf, &inbuflen);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "WdfRequestRetrieveInputBuffer failed status=0x%08x", status);
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
        return ;
    }
	if (inbuf == NULL)
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "inbuf is null");
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
        return ;
    }
	if (inbuflen == 0)
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "inbuf length is zero");
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
        return;
    }
    outbuf = NULL;
	status = WdfRequestRetrieveOutputBuffer(Request, 0, &outbuf, &outbuflen);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "WdfRequestRetrieveOutputBuffer failed status=0x%08x", status);
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
        return ;
    }
	if (outbuf == NULL)
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "outbuf is null");
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
        return ;
    }
	if (outbuflen == 0)
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "outbuf length is zero");
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
        return;
    }
    
    fdoData = FdoGetData(WdfIoQueueGetDevice(Queue));
    com_len = outbuflen;
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "IoControlCode=0x%08x", IoControlCode);

	switch (IoControlCode)
	{
        case IOCTL_DEV_OPEN:
        {
            IoCtrlDevOpen(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_CLOSE:
        {
            IoCtrlDevClose(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_ENAB:
        {
            IoCtrlDevEnab(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_RESET:
        {
            IoCtrlDevReset(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_GET_STATE:
        {
            IoCtrlDevGetState(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_GET_VERSION:
        {
            IoCtrlDevGetVersion(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_REG_RECV_HANDLER:
        {
            IoCtrlDevRegRecvHandler(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_UNREG_RECV_HANDLER:
        {
            IoCtrlDevUnRegRecvHandler(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_REG_EVT_HANDLER:
        {
            IoCtrlDevRegEvtHandler(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_UNREG_EVT_HANDLER:
        {
            IoCtrlDevUnRegEvtHandler(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_GET_STATISTICS:
        {
            IoCtrlDevGetStatistics(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_IBIT:
        {
            IoCtrlDevIBit(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_GET_TEMPERATURE:
        {
            IoCtrlDevGetTemperature(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_GET_VOLTAGE:
        {
            IoCtrlDevGetVoltage(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_GET_WORK_STATUS:
        {
            IoCtrlDevGetWorkStatus(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_GET_RTC:
        {
            IoCtrlDevGetRtc(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_SET_RTC:
        {
            IoCtrlDevSetRtc(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_MONITOR_START:
        {
            IoCtrlDevMonitorStart(fdoData, inbuf, outbuf);
            break;
        }
        case IOCTL_DEV_MONITOR_STOP:
        {
            IoCtrlDevMonitorStop(fdoData, inbuf, outbuf);
            break;
        }
		default:
		{
            status = STATUS_INVALID_DEVICE_REQUEST;
			break;
		}
	}
	WdfRequestCompleteWithInformation(Request, status, com_len);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);

	return;
}

//
// 打开卡
//
VOID IoCtrlDevOpen(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    INT32 mac_off_line;
    PDEV_OPEN_REQ req;
    PDEV_OPEN_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_OPEN_REQ)inbuf;
    resp = (PDEV_OPEN_RESP)outbuf;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State != ECS_NONE)
    {
        // R3没有正常退出，需要复位设备
        mac_off_line = 1;
        IoCtrlReset(fdoData, mac_off_line);
    }
    fdoData->State = ECS_OPEN;
    resp->result = IO_CTRL_RESP_OK;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 关闭卡
//
VOID IoCtrlDevClose(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    INT32 ret, mac_off_line;
    PDEV_CLOSE_REQ req;
    PDEV_CLOSE_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_CLOSE_REQ)inbuf;
    resp = (PDEV_CLOSE_RESP)outbuf;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_CONFIG || fdoData->State == ECS_MONITOR)
    {
        // 复位设备
        mac_off_line = 1;
        ret = IoCtrlReset(fdoData, mac_off_line);
        if (ret)
        {
            TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "IoCtrlReset failed ret=%d", ret);
            return;
        }
    }
    fdoData->State = ECS_NONE;
    resp->result = IO_CTRL_RESP_OK;
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 配置设备
//
VOID IoCtrlDevEnab(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    NTSTATUS status;
    INT32 mac_off_line;
    ULONG global_sync_enab, event_period, sync_enab, rtc_base;
    PDEV_CONFIG dc;
    PREG_HW reg_hw;
    PDEV_ENAB_REQ req;
    PDEV_ENAB_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_ENAB_REQ)inbuf;
    resp = (PDEV_ENAB_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State != ECS_OPEN)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }

    // 配置端口参数
    dc = &fdoData->DevConfig;
    dc->credit_num = req->credit_num;
    dc->speed = req->speed;
    dc->did_filter_enab = req->did_filter_enab;
    dc->e_d_tov = req->e_d_tov;
    dc->redundant_enab = req->redundant_enab;
    dc->time_out = req->time_out;
    dc->qdr_buf_unit_size = AlignQdrBufSize(req->qdr_buf_unit_size);
	dc->sw_fcid = req->sw_fcid;
    print_dev_config(dc);

    HwSetPortCreditNum(reg_hw, dc->credit_num);
    HwSetPortSpeed(reg_hw, dc->speed);
    HwSetPortDidFilterEnab(reg_hw, dc->did_filter_enab);
    HwSetPortEdtovTime(reg_hw, dc->e_d_tov);
    HwSetPortRedundantEnab(reg_hw, dc->redundant_enab);
    HwSetPortTimeOut(reg_hw, dc->time_out);
	HwSetSwFcid(reg_hw, dc->sw_fcid);
    HwSetQdrBufUnitSize(reg_hw, dc->qdr_buf_unit_size);

    // RTC控制
    global_sync_enab = 1;
    event_period = 200;
    sync_enab = 0;
    rtc_base = 0;
    HwRtcControl(reg_hw, global_sync_enab, event_period, sync_enab, rtc_base);

    // 设置QDR参数
    IoCtrlConfigQdrBufParam(fdoData);
    do {
        // 分配DMA控制头
        status = IoCtrlAllocateListHeader(fdoData);
        if (!NT_SUCCESS(status))
        {
            break;
        }
        // 分配DMA缓冲区
        status = IoCtrlAllocateCommonBuffer(fdoData);
        if (!NT_SUCCESS(status))
        {
            break;
        }
        // 注册DMA缓冲区
        IoCtrlRegisterDmaBuf(fdoData);
        // 更新设备状态后才能启动线程
        fdoData->State = ECS_CONFIG;
        // 启动线程
        IoCtrlThreadStart(fdoData);
        resp->result = IO_CTRL_RESP_OK;
    } while (FALSE);
    if (!NT_SUCCESS(status))
    {
        mac_off_line = 1;
        IoCtrlReset(fdoData, mac_off_line);
    }
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 设备复位
//
VOID IoCtrlDevReset(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    INT ret, mac_off_line;
    PDEV_RESET_REQ req;
    PDEV_RESET_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_RESET_REQ)inbuf;
    resp = (PDEV_RESET_RESP)outbuf;

    resp->result = IO_CTRL_RESP_NG;
    if (!(fdoData->State == ECS_CONFIG || fdoData->State == ECS_MONITOR))
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    mac_off_line = 1;
    ret = IoCtrlReset(fdoData, mac_off_line);
    if (ret == 0)
    {
        resp->result = IO_CTRL_RESP_OK;
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 获取设备状态
//
VOID IoCtrlDevGetState(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    ULONG portStatus[2], portCount;
    PREG_HW reg_hw;
    PDEV_GET_STATE_REQ req;
    PDEV_GET_STATE_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_GET_STATE_REQ)inbuf;
    resp = (PDEV_GET_STATE_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    portCount = 2;
    HwGetPortStatus(reg_hw, portStatus, portCount);
    resp->p0_status = portStatus[0];
    resp->p1_status = portStatus[1];
    resp->result = IO_CTRL_RESP_OK;
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 获取设备版本号
//
VOID IoCtrlDevGetVersion(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    ULONG value;
    PREG_HW reg_hw;
    PDEV_GET_VERSION_REQ req;
    PDEV_GET_VERSION_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_GET_VERSION_REQ)inbuf;
    resp = (PDEV_GET_VERSION_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    value = HwGetFpgaVersion(reg_hw);
    resp->fpga_version = value;
    resp->drier_version = VERSION_MAJOR << 4 | VERSION_MINOR;
    resp->result = IO_CTRL_RESP_OK;
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 注册接收回调例程
//
VOID IoCtrlDevRegRecvHandler(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    NTSTATUS status;
    INT32 size, reference, has_err, memory_flag, event_flag, mdl_flag;
    PREG_HW reg_hw;
    PDEV_REG_RECV_HANDLER_REQ req;
    PDEV_REG_RECV_HANDLER_RESP resp;
    PCBN_INT_RECV_CONTEXT context;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_REG_RECV_HANDLER_REQ)inbuf;
    resp = (PDEV_REG_RECV_HANDLER_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE || fdoData->State == ECS_MONITOR)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    if (InterlockedCompareExchange(&fdoData->IntRecvFlag, INT_REG_DOING, INT_REG_IDLE) != 0)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "int recv flag=%d", fdoData->IntRecvFlag);
        return;
    }

    // 开始注册
    reference = 0;
    has_err = 0;
    memory_flag = 0;
    event_flag = 0;
    mdl_flag = 0;
    size = sizeof(CBN_INT_RECV_CONTEXT);

    do {
        // 分配R3/R0共享内存
        context = (PCBN_INT_RECV_CONTEXT)ExAllocatePoolWithTag(NonPagedPool, size, MEM_TAG_HBA);
        if (context == NULL)
        {
            has_err = 1;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "ExAllocatePoolWithTag failed");
            break;
        }
        memory_flag = 1;
        RtlZeroMemory(context, size);
        fdoData->IntRecvContext = context;

        // 映射事件
        status = ObReferenceObjectByHandle(
            req->handle_event,
            SYNCHRONIZE | EVENT_MODIFY_STATE,
            *ExEventObjectType,
            KernelMode,
            (PVOID *)&fdoData->IntRecvEvent,
            NULL);
        if (!NT_SUCCESS(status))
        {
            // 转换失败
            has_err = 2;
            TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "ObReferenceObjectByHandle failed status=0x%08x", status);
            break;
        }
        event_flag = 1;

        // 映射到R3
        fdoData->IntRecvMdl = IoAllocateMdl(
            context,
            size,
            FALSE,
            FALSE,
            NULL);
        if (fdoData->IntRecvMdl == NULL)
        {
            // 映射失败
            has_err = 3;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "IoAllocateMdl failed status=0x%08x", status);
            break;
        }
        MmBuildMdlForNonPagedPool(fdoData->IntRecvMdl);
        mdl_flag = 1;

        try {
            resp->context = MmMapLockedPagesSpecifyCache(
                fdoData->IntRecvMdl,
                UserMode,
                MmCached,
                NULL,
                FALSE,
                NormalPagePriority);
        }
        except(EXCEPTION_EXECUTE_HANDLER)
        {
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "MmMapLockedPagesSpecifyCache raise exception");
        }
        if (resp->context == NULL)
        {
            has_err = 4;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "MmMapLockedPagesSpecifyCache failed");
            break;
        }
        // 注意：R3的读指针和R0的写指针的初始化，后续的操作中，两个指针永远保持一个间隔，永远不会重合
        context->r3_index = 0;
        context->r0_index = 1;

        // 中断注册完成
        InterlockedCompareExchange(&fdoData->IntRecvFlag, INT_REG_COMPLETE, INT_REG_DOING);

        resp->result = IO_CTRL_RESP_OK;
    } while (FALSE);

    if (has_err)
    {
        if (mdl_flag == 1)
        {
            IoFreeMdl(fdoData->IntRecvMdl);
        }
        if (event_flag == 1)
        {
            ObDereferenceObject(fdoData->IntRecvEvent);
        }
        if (memory_flag == 1)
        {
            ExFreePoolWithTag(context, MEM_TAG_HBA);
            fdoData->IntRecvContext = NULL;
        }
        InterlockedCompareExchange(&fdoData->IntRecvFlag, INT_REG_IDLE, INT_REG_DOING);
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 注销接收回调例程
//
VOID IoCtrlDevUnRegRecvHandler(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    PDEV_UNREG_RECV_HANDLER_REQ req;
    PDEV_UNREG_RECV_HANDLER_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_UNREG_RECV_HANDLER_REQ)inbuf;
    resp = (PDEV_UNREG_RECV_HANDLER_RESP)outbuf;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_MONITOR)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "unreg recv state=%d", fdoData->State);
        return;
    }
    resp->result = IO_CTRL_RESP_OK;
    if (InterlockedCompareExchange(&fdoData->IntRecvFlag, INT_REG_DOING, INT_REG_COMPLETE) != INT_REG_COMPLETE)
    {
        // 没有注册过
        ASSERT(fdoData->IntRecvFlag == INT_REG_IDLE);
        if (fdoData->IntRecvFlag == INT_REG_IDLE)
        {
            TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "unregister recv handler");
            return;
        }
    }

    // 暂停一下，确保从FPGA接收的线程不再使用该内存
    KeDelay(10 * MILLI_SEC);

    IoFreeMdl(fdoData->IntRecvMdl);
    ObDereferenceObject(fdoData->IntRecvEvent);
    ExFreePoolWithTag(fdoData->IntRecvContext, MEM_TAG_HBA);
    fdoData->IntRecvContext = NULL;
    InterlockedCompareExchange(&fdoData->IntRecvFlag, INT_REG_IDLE, INT_REG_DOING);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 注册事件回调例程
//
VOID IoCtrlDevRegEvtHandler(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    NTSTATUS status;
    INT32 size, reference, has_err, memory_flag, event_flag, mdl_flag;
    PREG_HW reg_hw;
    PDEV_REG_EVT_HANDLER_REQ req;
    PDEV_REG_EVT_HANDLER_RESP resp;
    PCBN_INT_EVT_CONTEXT context;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_REG_EVT_HANDLER_REQ)inbuf;
    resp = (PDEV_REG_EVT_HANDLER_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE || fdoData->State == ECS_MONITOR)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    if (InterlockedCompareExchange(&fdoData->IntEvtFlag, INT_REG_DOING, INT_REG_IDLE) != INT_REG_IDLE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "InterlockedCompareExchange failed int evt flag=%d", fdoData->IntEvtFlag);
        return;
    }

    // 开始注册
    reference = 0;
    has_err = 0;
    memory_flag = 0;
    event_flag = 0;
    mdl_flag = 0;
    size = sizeof(CBN_INT_EVT_CONTEXT);

    do {
        // 分配中断接收的共享内存
        context = (PCBN_INT_EVT_CONTEXT)ExAllocatePoolWithTag(NonPagedPool, size, MEM_TAG_HBA);
        if (context == NULL)
        {
            has_err = 1;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "ExAllocatePoolWithTag failed");
            break;
        }
        memory_flag = 1;
        RtlZeroMemory(context, size);
        fdoData->IntEvtContext = context;

        // 映射事件
        status = ObReferenceObjectByHandle(
            req->handle_event,
            SYNCHRONIZE | EVENT_MODIFY_STATE,
            *ExEventObjectType,
            KernelMode,
            (PVOID *)&fdoData->IntEvtEvent,
            NULL);
        if (!NT_SUCCESS(status))
        {
            // 转换失败
            has_err = 2;
            TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "ObReferenceObjectByHandle failed status=0x%08x", status);
            break;
        }
        event_flag = 1;

        // 映射到R3
        fdoData->IntEvtMdl = IoAllocateMdl(
            context,
            size,
            FALSE,
            FALSE,
            NULL);
        if (fdoData->IntEvtMdl == NULL)
        {
            // 映射失败
            has_err = 3;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "IoAllocateMdl failed status=0x%08x", status);
            break;
        }
        MmBuildMdlForNonPagedPool(fdoData->IntEvtMdl);
        mdl_flag = 1;

        try {
            resp->context = MmMapLockedPagesSpecifyCache(
                fdoData->IntEvtMdl,
                UserMode,
                MmCached,
                NULL,
                FALSE,
                NormalPagePriority);
        }
        except(EXCEPTION_EXECUTE_HANDLER)
        {
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "MmMapLockedPagesSpecifyCache raise exception");
        }
        if (resp->context == NULL)
        {
            has_err = 4;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "MmMapLockedPagesSpecifyCache failed");
            break;
        }
        // 中断注册完成
        InterlockedCompareExchange(&fdoData->IntEvtFlag, INT_REG_COMPLETE, INT_REG_DOING);

        resp->result = IO_CTRL_RESP_OK;
    } while (FALSE);

    if (has_err)
    {
        if (mdl_flag == 1)
        {
            IoFreeMdl(fdoData->IntEvtMdl);
        }
        if (event_flag == 1)
        {
            ObDereferenceObject(fdoData->IntEvtEvent);
        }
        if (memory_flag == 1)
        {
            ExFreePoolWithTag(context, MEM_TAG_HBA);
            fdoData->IntEvtContext = NULL;
        }
        InterlockedCompareExchange(&fdoData->IntEvtFlag, INT_REG_IDLE, INT_REG_DOING);
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 注销事件回调例程
//
VOID IoCtrlDevUnRegEvtHandler(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    PDEV_UNREG_EVT_HANDLER_REQ req;
    PDEV_UNREG_EVT_HANDLER_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_UNREG_EVT_HANDLER_REQ)inbuf;
    resp = (PDEV_UNREG_EVT_HANDLER_RESP)outbuf;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_MONITOR)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "unregister evt:invalid state=%d", fdoData->State);
        return;
    }
    resp->result = IO_CTRL_RESP_OK;
    if (InterlockedCompareExchange(&fdoData->IntEvtFlag, INT_REG_DOING, INT_REG_COMPLETE) != INT_REG_COMPLETE)
    {
        // 没有注册过
        ASSERT(fdoData->IntEvtFlag == INT_REG_IDLE);
        if (fdoData->IntEvtFlag == INT_REG_IDLE)
        {
            TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "no register evt");
            return;
        }
    }

    // 暂停一下，确保FPGA不再使用该内存
    KeDelay(10 * MILLI_SEC);

    IoFreeMdl(fdoData->IntEvtMdl);
    ObDereferenceObject(fdoData->IntEvtEvent);
    ExFreePoolWithTag(fdoData->IntEvtContext, MEM_TAG_HBA);
    fdoData->IntEvtContext = NULL;
    InterlockedCompareExchange(&fdoData->IntEvtFlag, INT_REG_IDLE, INT_REG_DOING);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 获取设备统计信息
//
VOID IoCtrlDevGetStatistics(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    PREG_HW reg_hw;
    PFPGA_STATISTICS_INFO fsi;
    PPORT_STATISTICS_INFO psi;
    PDEV_GET_STATISTICS_REQ req;
    PDEV_GET_STATISTICS_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_GET_STATISTICS_REQ)inbuf;
    resp = (PDEV_GET_STATISTICS_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    resp->result = IO_CTRL_RESP_OK;
    fsi = &fdoData->FpgaStatisticsInfo;
    psi = fdoData->PortStatisticsInfo;
    HwGetStatistics(reg_hw, fsi, psi);
    print_statistics(1, fsi, psi);
    RtlCopyMemory(&resp->info, fdoData->PortStatisticsInfo, sizeof(PORT_STATISTICS_INFO) * 2);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 获取设备自检
//
VOID IoCtrlDevIBit(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    PREG_HW reg_hw;
    PDEV_IBIT_REQ req;
    PDEV_IBIT_RESP resp;
    PFC_BIT_RESULT_MANUAL bitResult;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_IBIT_REQ)inbuf;
    resp = (PDEV_IBIT_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    resp->result = IO_CTRL_RESP_OK;
    bitResult = &fdoData->BitResult;
    HwManualSelfCheck(reg_hw, bitResult);
    resp->flash = bitResult->flash;
    resp->buffer = bitResult->buffer;
    resp->temperature = bitResult->temperature;
    resp->voltage = bitResult->voltage;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 获取设备温度
//
VOID IoCtrlDevGetTemperature(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    ULONG temp;
    PREG_HW reg_hw;
    PDEV_GET_TEMPERATURE_REQ req;
    PDEV_GET_TEMPERATURE_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_GET_TEMPERATURE_REQ)inbuf;
    resp = (PDEV_GET_TEMPERATURE_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    resp->result = IO_CTRL_RESP_OK;
    temp = HwGetTemperature(reg_hw);
    resp->temperature = temp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 获取设备电压
//
VOID IoCtrlDevGetVoltage(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    ULONG voltage;
    PREG_HW reg_hw;
    PDEV_GET_VOLTAGE_REQ req;
    PDEV_GET_VOLTAGE_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_GET_VOLTAGE_REQ)inbuf;
    resp = (PDEV_GET_VOLTAGE_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    resp->result = IO_CTRL_RESP_OK;
    voltage = HwGetVoltage(reg_hw);
    resp->voltage = voltage;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 获取设备工作状态
//
VOID IoCtrlDevGetWorkStatus(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    PREG_HW reg_hw;
    PDEV_GET_WORK_STATUS_REQ req;
    PDEV_GET_WORK_STATUS_RESP resp;
    PFC_BIT_RESULT_MANUAL bitResult;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_GET_WORK_STATUS_REQ)inbuf;
    resp = (PDEV_GET_WORK_STATUS_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }

    resp->result = IO_CTRL_RESP_OK;
    resp->status = 0;
    bitResult = &fdoData->BitResult;
    HwManualSelfCheck(reg_hw, bitResult);
    do {
        if (bitResult->flash != BIT_SUCCESS)
        {
            break;
        }
        if (bitResult->buffer != BIT_SUCCESS)
        {
            break;
        }
        if (bitResult->temperature != BIT_SUCCESS)
        {
            break;
        }
        if (bitResult->voltage != BIT_SUCCESS)
        {
            break;
        }
        resp->status = 1;
    } while (FALSE);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 获取RTC
//
VOID IoCtrlDevGetRtc(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    PREG_HW reg_hw;
    UINT64 time64;
    FCTime fcTime;
    PDEV_GET_RTC_REQ req;
    PDEV_GET_RTC_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_GET_RTC_REQ)inbuf;
    resp = (PDEV_GET_RTC_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    HwReadRtcPrepare(reg_hw);
    time64 = HwGetRtc(reg_hw);
    HwReadRtcFinish(reg_hw);
    HbaDrvTimeToFCTime(time64, &fcTime);
    RtlCopyMemory(&resp->time, &fcTime, sizeof(FCTime));
    resp->result = IO_CTRL_RESP_OK;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 设置RTC
//
VOID IoCtrlDevSetRtc(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    UINT64 ns;
    PREG_HW reg_hw;
    PDEV_SET_RTC_REQ req;
    PDEV_SET_RTC_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_SET_RTC_REQ)inbuf;
    resp = (PDEV_SET_RTC_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }

    ns = HbaDrvFCTimeToTime(&req->time);
    HwSetRtc(reg_hw, ns);
    resp->result = IO_CTRL_RESP_OK;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 监控开始
//
VOID IoCtrlDevMonitorStart(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    PREG_HW reg_hw;
    PDEV_MONITOR_START_REQ req;
    PDEV_MONITOR_START_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_MONITOR_START_REQ)inbuf;
    resp = (PDEV_MONITOR_START_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE || fdoData->State == ECS_OPEN || fdoData->State == ECS_MONITOR)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    ASSERT(fdoData->State == ECS_CONFIG);
    RtlZeroMemory(&fdoData->DbgContext, sizeof(DBG_CONTEXT));
    fdoData->State = ECS_MONITOR;
    HwSetPortRxEnab(reg_hw, RX_ACTIVE);
    resp->result = IO_CTRL_RESP_OK;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 监控停止
//
VOID IoCtrlDevMonitorStop(IN PFDO_DATA fdoData, IN PUCHAR inbuf, IN PUCHAR outbuf)
{
    PREG_HW reg_hw;
    PDEV_MONITOR_STOP_REQ req;
    PDEV_MONITOR_STOP_RESP resp;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    req = (PDEV_MONITOR_STOP_REQ)inbuf;
    resp = (PDEV_MONITOR_STOP_RESP)outbuf;
    reg_hw = fdoData->Reg;

    resp->result = IO_CTRL_RESP_NG;
    if (fdoData->State == ECS_NONE || fdoData->State == ECS_OPEN || fdoData->State == ECS_CONFIG)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "invalid state=%d", fdoData->State);
        return;
    }
    ASSERT(fdoData->State == ECS_MONITOR);
    HwSetPortRxEnab(reg_hw, RX_INACTIVE);
    fdoData->State = ECS_CONFIG;
    resp->result = IO_CTRL_RESP_OK;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}
//
// 对齐QDR buf的字节数
//
INT32 AlignQdrBufSize(
    IN INT32 size
    )
{
    INT32 align;

    align = QDR_FPGA_RESERVE_SIZE;
    size = (size + align) & (~align);
    if (size < QDR_BUF_UNIT_SIZE_MIN)
    {   
        size = QDR_BUF_UNIT_SIZE_MIN;
    }
    else if (size > QDR_BUF_UNIT_SIZE_MAX)
    {
        size = QDR_BUF_UNIT_SIZE_MAX;
    }
    return size;
}

//
// 配置Qdr buffer
//
VOID IoCtrlConfigQdrBufParam(
    IN PFDO_DATA fdoData
    )
{
    INT32 i, qdr_buf_unit_size, node_count, node_size;
    PREG_HW reg_hw;

    reg_hw = fdoData->Reg;
    qdr_buf_unit_size = fdoData->DevConfig.qdr_buf_unit_size;
    node_count = QDR_BUF_SIZE / qdr_buf_unit_size;
    ASSERT(node_count > 0 && node_count <= 256);
    node_size = qdr_buf_unit_size - QDR_FPGA_RESERVE_SIZE;
    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "qdr buf unit size=0x%08x", node_size);
    HwSetQdrBufUnitSize(reg_hw, node_size);
    for (i = 0; i < node_count; ++i)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "index=0x%08x qdr buf start addr=0x%08x", i, i * qdr_buf_unit_size / 16);
        HwSetQdrBufStartAddress(reg_hw, i * qdr_buf_unit_size / 16);
    }
}

//
// 分配链表头
//
NTSTATUS IoCtrlAllocateListHeader(
    IN PFDO_DATA fdoData
    )
{
    INT32 i, qdr_buf_unit_size, dma_node_count;
    NTSTATUS status;
    PIO_LIST_CTRL ctrl;
    PDMA_BUF_NODE_HEADER dma_buf_node_header;
    PLIST_ENTRY cur_entry, first_entry, prev_entry;

    ctrl = &fdoData->RecvCtrl;
    ctrl->entry = NULL;
    cur_entry = first_entry = prev_entry = NULL;
    qdr_buf_unit_size = fdoData->DevConfig.qdr_buf_unit_size;
    // dma_node_count = QDR_BUF_SIZE / qdr_buf_unit_size;
    dma_node_count = DMA_NODE_COUNT;
    status = STATUS_SUCCESS;
    for (i = 0; i < dma_node_count; ++i)
    {
        dma_buf_node_header = (PDMA_BUF_NODE_HEADER)ExAllocatePoolWithTag(NonPagedPool, sizeof(DMA_BUF_NODE_HEADER), MEM_TAG_HBA);
        if (dma_buf_node_header == NULL)
        {
            status = STATUS_INSUFFICIENT_RESOURCES;
            break;
        }
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "index=0x%08x dma buf node header addr=0x%08x", i, (UINT32)dma_buf_node_header);
        dma_buf_node_header->index = i;
        dma_buf_node_header->dma_enabler_used = 0;
        dma_buf_node_header->va = NULL;
        dma_buf_node_header->la.QuadPart = 0;

        // 挂接到链表
        cur_entry = (PLIST_ENTRY)dma_buf_node_header;
        if (i == 0)
        {
            // 第一个节点
            first_entry = cur_entry;
            prev_entry = cur_entry;
            // 指向第一个节点
            ctrl->entry = cur_entry;
        }
        else if (i < dma_node_count - 1)
        {
            // 中间的节点
            cur_entry->Flink = NULL;
            cur_entry->Blink = prev_entry;
            prev_entry->Flink = cur_entry;
            prev_entry = cur_entry;
        }
        else
        {
            // 最后一个节点
            cur_entry->Blink = prev_entry;
            cur_entry->Flink = first_entry;
            first_entry->Blink = cur_entry;
            prev_entry->Flink = cur_entry;
        }
    }
    return status;
}

//
// 分配commonbuffer
//
NTSTATUS IoCtrlAllocateCommonBuffer(
    IN PFDO_DATA fdoData
    )
{
    NTSTATUS status;
    INT32 has_err, qdr_buf_unit_size;
    size_t dma_node_size;
    PIO_LIST_CTRL ctrl;
    PLIST_ENTRY cur_entry;
    PDMA_BUF_NODE_HEADER dma_buf_node_header;
    WDF_OBJECT_ATTRIBUTES attributes;
    WDF_DMA_ENABLER_CONFIG dmaConfig;
    WDFCOMMONBUFFER commonBuffer;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    ctrl = &fdoData->RecvCtrl;
    cur_entry = ctrl->entry;
    qdr_buf_unit_size = fdoData->DevConfig.qdr_buf_unit_size;
    dma_node_size = DMA_BUF_ALIGN_SIZE + 2 * DMA_NODE_OVERFLOW_SIZE + qdr_buf_unit_size;

    // 分配缓冲区用于和FPGA做数据交换
    WDF_DMA_ENABLER_CONFIG_INIT(&dmaConfig, WdfDmaProfilePacket, dma_node_size);
    has_err = 0;
    do
    {
        dma_buf_node_header = (PDMA_BUF_NODE_HEADER)cur_entry;
        ASSERT(dma_buf_node_header->dma_enabler_used == 0
            && dma_buf_node_header->va == NULL
            && dma_buf_node_header->la.QuadPart == 0);
        dma_buf_node_header->dma_enabler_used = 0;
        WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
        attributes.ParentObject = NULL;
        status = WdfDmaEnablerCreate(fdoData->WdfDevice, &dmaConfig, &attributes, &dma_buf_node_header->dma_enabler);
        if (!NT_SUCCESS(status))
        {
            has_err = 1;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "WdfDmaEnablerCreate failed status=0x%08x", status);
            break;
        }
        dma_buf_node_header->dma_enabler_used = 1;
        status = WdfCommonBufferCreate(dma_buf_node_header->dma_enabler, dma_node_size, WDF_NO_OBJECT_ATTRIBUTES, &commonBuffer);
        if (!NT_SUCCESS(status))
        {
            has_err = 2;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "WdfCommonBufferCreate failed status=0x%08x", status);
            break;
        }
        dma_buf_node_header->va_origin = WdfCommonBufferGetAlignedVirtualAddress(commonBuffer);
        dma_buf_node_header->la_origin = WdfCommonBufferGetAlignedLogicalAddress(commonBuffer);
        RtlZeroMemory(dma_buf_node_header->va_origin, dma_node_size);
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "index=%d va_origin=0x%08x la_origin=[l:0x%08x h:0x%08x]",
            dma_buf_node_header->index, (ULONG)dma_buf_node_header->va_origin, dma_buf_node_header->la_origin.LowPart, dma_buf_node_header->la_origin.HighPart);
        // 映射到R3
        dma_buf_node_header->mdl = IoAllocateMdl(
            dma_buf_node_header->va_origin,
            dma_node_size,
            FALSE,
            FALSE,
            NULL);
        if (dma_buf_node_header->mdl == NULL)
        {
            // 映射失败
            has_err = 3;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "IoAllocateMdl failed status=0x%08x", status);
            break;
        }
        MmBuildMdlForNonPagedPool(dma_buf_node_header->mdl);
        
        try {
            dma_buf_node_header->va_r3 = MmMapLockedPagesSpecifyCache(
                dma_buf_node_header->mdl,
                UserMode,
                MmCached,
                NULL,
                FALSE,
                NormalPagePriority);
        }
        except(EXCEPTION_EXECUTE_HANDLER)
        {
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "MmMapLockedPagesSpecifyCache raise exception");
        }
        if (dma_buf_node_header->va_r3 == NULL)
        {
            has_err = 4;
            TraceEvents(TRACE_LEVEL_ERROR, DBG_IOCTLS, "MmMapLockedPagesSpecifyCache failed");
            break;
        }
        
        cur_entry = cur_entry->Flink;
    } while (cur_entry != ctrl->entry);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave status=0x%08x", __FUNCTION__, status);
    return status;
}

//
// 向FPGA注册DMA缓冲区
//
VOID IoCtrlRegisterDmaBuf(
    IN PFDO_DATA fdoData
    )
{
    INT32 index;
    ULONG value, valid_buf_num, credits[3];
    PIO_LIST_CTRL ctrl;
    PLIST_ENTRY cur_entry;
    PDMA_BUF_NODE_HEADER dma_buf_node_header;
    PUCHAR t_va;
    PHYSICAL_ADDRESS t_la;
    PREG_HW reg_hw;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s enter", __FUNCTION__);
    ctrl = &fdoData->RecvCtrl;
    cur_entry = ctrl->entry;
    reg_hw = fdoData->Reg;

    do
    {
        dma_buf_node_header = (PDMA_BUF_NODE_HEADER)cur_entry;

        ASSERT(dma_buf_node_header->dma_enabler_used == 1
            && dma_buf_node_header->va_origin != NULL
            && dma_buf_node_header->la_origin.QuadPart != 0
            && dma_buf_node_header->va == NULL
            && dma_buf_node_header->la.QuadPart == 0);

        // 注意：一共有3个地址，R3的va地址，R0的va地址和la地址
        //       这3个地址都需要做地址对齐和跳过保护区域的处理，这样FPGA写入数据后才能被R0和R3正确读取到
        // 1 对R0的va和la做对齐和跳过保护区的处理
        t_va = dma_buf_node_header->va_origin;
        t_la.QuadPart = dma_buf_node_header->la_origin.QuadPart;
        // 对齐
        t_va = (PUCHAR)(((ULONG)t_va + DMA_BUF_ALIGN_SIZE - 1) & ~(DMA_BUF_ALIGN_SIZE - 1));
        t_la.QuadPart = (t_la.QuadPart + DMA_BUF_ALIGN_SIZE - 1) & ~(DMA_BUF_ALIGN_SIZE - 1);
        // 跳过保护区域
        t_va += DMA_NODE_OVERFLOW_SIZE;
        t_la.QuadPart += DMA_NODE_OVERFLOW_SIZE;

        // 现在得到真正和FPGA交互的DMA地址
        dma_buf_node_header->va = t_va;
        dma_buf_node_header->la.QuadPart = t_la.QuadPart;
        // 记录调试信息
        fdoData->DbgInitAddr[dma_buf_node_header->index].va = dma_buf_node_header->va;
        fdoData->DbgInitAddr[dma_buf_node_header->index].la.QuadPart = dma_buf_node_header->la.QuadPart;

        // 2 对R3的va地址做对齐和跳过缓冲区的处理
        t_va = dma_buf_node_header->va_r3;
        // 对齐
        t_va = (PUCHAR)(((ULONG)t_va + DMA_BUF_ALIGN_SIZE - 1) & ~(DMA_BUF_ALIGN_SIZE - 1));
        // 跳过保护区域
        t_va += DMA_NODE_OVERFLOW_SIZE;
        // 现在得到真正和R3交互的地址
        dma_buf_node_header->va_r3 = t_va;

        // 给FPGA注册LA地址
        index = dma_buf_node_header->index;
        value = dma_buf_node_header->la.LowPart;
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "index=%d va=0x%08x la=0x%08x", index, (UINT32)t_va, value);
        // 注册地址
        HwRegisterRxDmaBuf(reg_hw, index, value);
        // 推信用
        credits[0] = index;
        valid_buf_num = 1;
        HwPushCreditsToFpga(reg_hw, credits, valid_buf_num);

        cur_entry = cur_entry->Flink;
    } while (cur_entry != ctrl->entry);

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "%s leave", __FUNCTION__);
}

//
// 线程启动
//
NTSTATUS IoCtrlThreadStart(
    IN PFDO_DATA fdoData
    )
{
    NTSTATUS status;
    INT32 has_err;
    HANDLE h;

    status = STATUS_SUCCESS;
    has_err = 0;
    do {
        // 接收数据线程
        fdoData->RecvThreadState = THREAD_STATE_STOP;
        fdoData->RecvThreadCtrl = THREAD_CTRL_RUN;
        status = PsCreateSystemThread(&h, THREAD_ALL_ACCESS, NULL, NULL, NULL, RecvCallBack, fdoData);
        if (NT_SUCCESS(status))
        {
            ObReferenceObjectByHandle(h, THREAD_ALL_ACCESS, NULL, KernelMode, &fdoData->RecvThreadObject, NULL);
            ZwClose(h);
            fdoData->RecvThreadState = THREAD_STATE_RUN;
        }
        else
        {
            has_err = 1;
            TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "PsCreateSystemThread failed status=0x%08x", status);
            break;
        }
        // 周期自检线程
        fdoData->PeriodSelfCheckThreadState = THREAD_STATE_STOP;
        fdoData->PeriodSelfCheckThreadCtrl = THREAD_CTRL_RUN;
        status = PsCreateSystemThread(&h, THREAD_ALL_ACCESS, NULL, NULL, NULL, PeriodSelfCheckCallBack, fdoData);
        if (NT_SUCCESS(status))
        {
            ObReferenceObjectByHandle(h, THREAD_ALL_ACCESS, NULL, KernelMode, &fdoData->PeriodSelfCheckThreadObject, NULL);
            ZwClose(h);
            fdoData->PeriodSelfCheckThreadState = THREAD_STATE_RUN;
        }
        else
        {
            has_err = 2;
            TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "PsCreateSystemThread failed status=0x%08x", status);
            break;
        }
    } while (FALSE);
    if (has_err)
    {
        IoCtrlThreadStop(fdoData);
    }
    return status;
}

//
// 线程停止
//
NTSTATUS IoCtrlThreadStop(
    IN PFDO_DATA fdoData
    )
{
    NTSTATUS status;
    LARGE_INTEGER interval;

    status = STATUS_SUCCESS;
    interval.QuadPart = 2000 * MILLI_SEC;
    // 接收数据线程
    if (fdoData->RecvThreadState == THREAD_STATE_RUN)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "wait RecvCallBack thread exit");
        fdoData->RecvThreadCtrl = THREAD_CTRL_STOP;
        status = KeWaitForSingleObject(fdoData->RecvThreadObject, Executive, KernelMode, FALSE, &interval);
        ASSERT(status == STATUS_SUCCESS);
        fdoData->RecvThreadState = THREAD_STATE_STOP;
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "wait RecvCallBack complete status=0x%08x", status);
    }

    // 周期自检线程
    if (fdoData->PeriodSelfCheckThreadState == THREAD_STATE_RUN)
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "wait PeriodSelfCheckCallBack thread exit");
        fdoData->PeriodSelfCheckThreadCtrl = THREAD_CTRL_STOP;
        status = KeWaitForSingleObject(fdoData->PeriodSelfCheckThreadObject, Executive, KernelMode, FALSE, &interval);
        ASSERT(status == STATUS_SUCCESS);
        fdoData->PeriodSelfCheckThreadState = THREAD_STATE_STOP;
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "wait PeriodSelfCheckCallBack complete status=0x%08x", status);
    }
    return status;
}

//
// 复位FPGA
//
INT32 IoCtrlReset(
    IN PFDO_DATA fdoData,
    IN INT32 mac_off_line
    )
{
    NTSTATUS status;
    INT32 ret;
    PREG_HW reg_hw;

    ret = 0;
    reg_hw = fdoData->Reg;
    if (!(fdoData->State == ECS_CONFIG || fdoData->State == ECS_MONITOR))
    {
        return ret;
    }
    if (fdoData->State == ECS_MONITOR)
    {
        // 禁用端口接收使能
        HwSetPortRxEnab(reg_hw, 0);
        fdoData->State = ECS_CONFIG;
    }

    // 停止线程
    status = IoCtrlThreadStop(fdoData);
    if (!NT_SUCCESS(status))
    {
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "IoCtrlThreadStop failed status=0x%08x", status);
        ret = 1;
        return ret;
    }
    // 统计信息
    RtlZeroMemory(&fdoData->PortStatisticsInfo[0], sizeof(PORT_STATISTICS_INFO));
    RtlZeroMemory(&fdoData->PortStatisticsInfo[1], sizeof(PORT_STATISTICS_INFO));

    // 复位FPGA
    HwResetFpga(reg_hw, mac_off_line);

    // 释放资源
    IoCtrlFreeCommonBuffer(fdoData);
    IoCtrlFreeListHeader(fdoData);
    IoCtrlFreeIntRecv(fdoData);
    IoCtrlFreeIntEvt(fdoData);
    fdoData->State = ECS_OPEN;
    return ret;
}

//
// 释放dma缓冲区，解除R3映射关系
//
VOID IoCtrlFreeCommonBuffer(
    IN PFDO_DATA fdoData
    )
{
    PIO_LIST_CTRL ctrl;
    PLIST_ENTRY cur_entry;
    PDMA_BUF_NODE_HEADER dma_buf_node_header;

    ctrl = &fdoData->RecvCtrl;
    cur_entry = ctrl->entry;
    if (cur_entry == NULL)
    {
        return;
    }

    do
    {
        dma_buf_node_header = (PDMA_BUF_NODE_HEADER)cur_entry;
        cur_entry = cur_entry->Flink;
        if (dma_buf_node_header->mdl != NULL)
        {
            IoFreeMdl(dma_buf_node_header->mdl);
        }
        if (dma_buf_node_header->dma_enabler_used == 1)
        {
            WdfObjectDelete(dma_buf_node_header->dma_enabler);
        }
    } while (cur_entry != ctrl->entry);
}

//
// 释放链表控制头
//
VOID IoCtrlFreeListHeader(
    IN PFDO_DATA fdoData
    )
{
    PIO_LIST_CTRL ctrl;
    PLIST_ENTRY cur_entry;
    PDMA_BUF_NODE_HEADER dma_buf_node_header;

    ctrl = &fdoData->RecvCtrl;
    cur_entry = ctrl->entry;
    if (cur_entry == NULL)
    {
        return;
    }

    do
    {
        dma_buf_node_header = (PDMA_BUF_NODE_HEADER)cur_entry;
        cur_entry = cur_entry->Flink;
        ExFreePoolWithTag(dma_buf_node_header, MEM_TAG_HBA);
    } while (cur_entry != ctrl->entry);
}

//
// 释放中断接收响应的资源
//
VOID IoCtrlFreeIntRecv(
    IN PFDO_DATA fdoData
    )
{
    // 注销中断接收处理
    if (InterlockedCompareExchange(&fdoData->IntRecvFlag, INT_REG_DOING, INT_REG_COMPLETE) != INT_REG_COMPLETE)
    {
        ASSERT(fdoData->IntRecvFlag == INT_REG_IDLE);
        fdoData->IntRecvFlag = INT_REG_IDLE;
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "unregister handler");
        return;
    }
    IoFreeMdl(fdoData->IntRecvMdl);
    ObDereferenceObject(fdoData->IntRecvEvent);
    ExFreePoolWithTag(fdoData->IntRecvContext, MEM_TAG_HBA);
    fdoData->IntRecvContext = NULL;
    InterlockedCompareExchange(&fdoData->IntRecvFlag, 0, 1);
}

//
// 释放中断事件响应的资源
//
VOID IoCtrlFreeIntEvt(
    IN PFDO_DATA fdoData
    )
{
    // 注销中断事件处理
    if (InterlockedCompareExchange(&fdoData->IntEvtFlag, INT_REG_DOING, INT_REG_COMPLETE) != INT_REG_COMPLETE)
    {
        ASSERT(fdoData->IntEvtFlag == INT_REG_IDLE);
        fdoData->IntEvtFlag = INT_REG_IDLE;
        TraceEvents(TRACE_LEVEL_INFORMATION, DBG_IOCTLS, "unregister handler");
        return;
    }
    IoFreeMdl(fdoData->IntEvtMdl);
    ObDereferenceObject(fdoData->IntEvtEvent);
    ExFreePoolWithTag(fdoData->IntEvtContext, MEM_TAG_HBA);
    fdoData->IntEvtContext = NULL;
    InterlockedCompareExchange(&fdoData->IntEvtFlag, 0, 1);
}

//
// 周期自检的回调例程
//
VOID PeriodSelfCheckCallBack(
    IN PVOID context
    )
{
    ULONG prev_p0_status, prev_p1_status;
    PREG_HW reg_hw;
    PFDO_DATA fdoData;
    PFPGA_STATISTICS_INFO fsi;
    PPORT_STATISTICS_INFO psi;

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "%s enter", __FUNCTION__);
    fdoData = (PFDO_DATA)context;
    reg_hw = fdoData->Reg;
    prev_p0_status = prev_p1_status = 0xFFFFFFFF;
    while (fdoData->PeriodSelfCheckThreadCtrl == THREAD_CTRL_RUN)
    {
        ASSERT(fdoData->State != ECS_NONE);
        if (fdoData->State == ECS_NONE || fdoData->State == ECS_OPEN)
        {
            KeDelay(MILLI_SEC);
            continue;
        }
        // 检查端口的状态
        IoCtrlCheckPortStatus(fdoData, &prev_p0_status, &prev_p1_status);

        // 取得统计值
        fsi = &fdoData->FpgaStatisticsInfo;
        psi = fdoData->PortStatisticsInfo;
        HwGetStatistics(reg_hw, fsi, psi);
        KeDelay(10 * MILLI_SEC);
    }

    TraceEvents(TRACE_LEVEL_INFORMATION, DBG_READ, "PeriodSelfCheckCallBack PsTerminateSystemThread will invoke");
    PsTerminateSystemThread(STATUS_SUCCESS);
}

/* 检查端口的状态 */
VOID IoCtrlCheckPortStatus(
    IN PFDO_DATA fdoData,
    IN ULONG *prev_p0_status,
    IN ULONG *prev_p1_status
    )
{
    INT32 count, int_code;
    ULONG ps[2];
    PCBN_INT_EVT_CONTEXT cbn;
    PCBN_EVT_DESC desc;
    PREG_HW reg_hw;

    reg_hw = fdoData->Reg;

    // 取得端口的状态
    count = 2;
    HwGetPortStatus(reg_hw, ps, count);
    if (*prev_p0_status != ps[0] || *prev_p1_status != ps[1])
    {
        // 保存当前结果
        *prev_p0_status = ps[0];
        *prev_p1_status = ps[1];

        // 没有注册中断消息，不需要处理
        if (fdoData->IntEvtFlag != INT_REG_COMPLETE)
        {
            return;
        }

        if (ps[0] == PORT_LINK_UP || ps[1] == PORT_LINK_UP)
        {
            int_code = IC_LINK_STATUS_SUCCESS;
        }
        else
        {
            int_code = IC_LINK_STATUS_FAILED;
        }

        cbn = fdoData->IntEvtContext;
        desc = &cbn->desc[int_code - 0x100];
        if (InterlockedCompareExchange(&cbn->flag, INT_CONTEXT_USE, INT_CONTEXT_IDLE) != INT_CONTEXT_IDLE)
        {
            *prev_p0_status = *prev_p1_status = 0xFFFFFFFF;
            return;
        }
        desc->int_code = int_code;
        desc->param[0] = 0;

        // 标记复位
        InterlockedCompareExchange(&cbn->flag, INT_CONTEXT_IDLE, INT_CONTEXT_USE);

        // 设置信号通知应用层响应中断
        KeSetEvent(fdoData->IntEvtEvent, IO_NO_INCREMENT, FALSE);
    }
}