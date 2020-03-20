/*++
文件名
    driver.c

描述
    驱动
--*/

#include "precomp.h"
#include "driver.tmh"

NTSTATUS DriverEntry(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
)
/*++
描述：驱动入口例程
--*/
{
    NTSTATUS status;
    WDF_DRIVER_CONFIG config;
    
    WPP_INIT_TRACING(DriverObject, RegistryPath);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INIT, "%s enter", __FUNCTION__);
   
    WDF_DRIVER_CONFIG_INIT(&config, EvtDeviceAdd);
    config.EvtDriverUnload = EvtDriverUnload;
    status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_INIT, "WdfDriverCreate failed status=0x%08x", status);
        WPP_CLEANUP(DriverObject);
        return status;
    }

	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_INIT, "%s leave", __FUNCTION__);
    return status;
}

NTSTATUS EvtDeviceAdd(
    IN WDFDRIVER Driver,
    IN PWDFDEVICE_INIT DeviceInit
)
/*++
描述：安装设备对象的回调例程
--*/
{
    NTSTATUS status;
    WDF_PNPPOWER_EVENT_CALLBACKS pnpPowerCallbacks;
    WDF_OBJECT_ATTRIBUTES attributes;
    WDFDEVICE device;
    PFDO_DATA fdoData;
    
    PAGED_CODE();
	UNREFERENCED_PARAMETER(Driver);
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s entry", __FUNCTION__);
    
    // 直接访问方式
    WdfDeviceInitSetIoType(DeviceInit, WdfDeviceIoDirect);

    // 即插即用和电源管理
    WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&pnpPowerCallbacks);
    pnpPowerCallbacks.EvtDevicePrepareHardware = EvtDevicePrepareHardware;
    pnpPowerCallbacks.EvtDeviceReleaseHardware = EvtDeviceReleaseHardware;
    pnpPowerCallbacks.EvtDeviceD0Entry = EvtDeviceD0Entry;
    pnpPowerCallbacks.EvtDeviceD0Exit = EvtDeviceD0Exit;
    pnpPowerCallbacks.EvtDeviceD0EntryPostInterruptsEnabled = EvtDeviceD0EntryPostInterruptsEnabled;
    pnpPowerCallbacks.EvtDeviceD0ExitPreInterruptsDisabled = EvtDeviceD0ExitPreInterruptsDisabled;
    WdfDeviceInitSetPnpPowerEventCallbacks(DeviceInit, &pnpPowerCallbacks);
    
    // 允许同时打开多个句柄
    WdfDeviceInitSetExclusive (DeviceInit, FALSE);
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attributes, FDO_DATA);
    attributes.EvtCleanupCallback = EvtDeviceContextCleanup;
    status = WdfDeviceCreate(&DeviceInit, &attributes, &device);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfDeviceCreate failed status=0x%08x", status);
        return status;
    }
    fdoData = FdoGetData(device);
    fdoData->WdfDevice = device;
    
    // 初始化设备对象需要的资源
    status = AllocateSoftwareResources(fdoData);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "AllocateSoftwareResources failed status=0x%08x", status);
        return status;
    }
    
    // 创建设备对象的接口
    status = WdfDeviceCreateDeviceInterface(device, (LPGUID)&GUID_DEVINTERFACE_FM130, NULL);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfDeviceCreateDeviceInterface failed status=0x%08x", status);
        return status;
    }
    
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
    return status;
}

VOID EvtDriverUnload(
    IN WDFDRIVER DriverObject
)
/*++
描述：驱动卸载时回调该例程
--*/
{
    PAGED_CODE();
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s entry", __FUNCTION__);
    WPP_CLEANUP(WdfDriverWdmGetDriverObject(DriverObject));
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
}

VOID EvtDeviceContextCleanup(
    IN WDFDEVICE Device
)
/*++
描述：设备对象被删除时会回调该例程
--*/
{
    NTSTATUS status;
    PFDO_DATA fdoData;
    
    PAGED_CODE();
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s entry", __FUNCTION__);
    fdoData = FdoGetData(Device);
    status = FreeSoftwareResources(fdoData);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "FreeSoftwareResources failed status=0x%08x", status);
    }
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
}

NTSTATUS EvtDeviceD0Entry(
    IN WDFDEVICE Device,
    IN WDF_POWER_DEVICE_STATE PreviousState
)
/*++
描述：设备进入工作状态以后调用该例程
--*/
{
    NTSTATUS status;
    PFDO_DATA fdoData;
	PREG_HW reg_hw;
    
    PAGED_CODE();
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s entry", __FUNCTION__);
    status = STATUS_SUCCESS;
    fdoData = FdoGetData(Device);
	reg_hw = fdoData->Reg;
    ASSERT(PowerDeviceD0 != PreviousState);

	// 禁用端口接收使能
	HwSetPortRxEnab(reg_hw, 0);

	// 复位FPGA，复位MAC
	HwResetFpga(reg_hw, 1);

	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
    return status;
}

NTSTATUS EvtDeviceD0Exit(
    IN WDFDEVICE Device,
    IN WDF_POWER_DEVICE_STATE TargetState
)
/*++
描述：设备退出工作状态之前调用该例程
--*/
{
	INT32 mac_off_line;
	NTSTATUS status;
	PFDO_DATA fdoData;
	PREG_HW reg_hw;

    PAGED_CODE();
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s entry", __FUNCTION__);
    status = STATUS_SUCCESS;
    fdoData = FdoGetData(Device);
	reg_hw = fdoData->Reg;

	switch (TargetState)
	{
        case WdfPowerDeviceD1:
        case WdfPowerDeviceD2:
        case WdfPowerDeviceD3:
		case WdfPowerDeviceD3Final:
			{
                if (fdoData->State == ECS_CONFIG || fdoData->State == ECS_MONITOR)
                {
                    mac_off_line = 1;
                    IoCtrlReset(fdoData, mac_off_line);
                }
				// 向框架返回成功
				status = STATUS_SUCCESS;
			}
            break;
        case WdfPowerDevicePrepareForHibernation:
            ASSERT(FALSE);
            break;
        default:
            break;
    }

	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
    return status;
}

NTSTATUS AllocateSoftwareResources(
    IN OUT PFDO_DATA fdoData
)
/*++
描述：为读写控制请求分配队列
      分配中断对象和DMA相关的资源
--*/
{
    NTSTATUS status;
    WDF_IO_QUEUE_CONFIG ioQueueConfig;
	WDF_OBJECT_ATTRIBUTES attributes;
    WDF_INTERRUPT_CONFIG interruptConfig;
    
    PAGED_CODE();
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s enter", __FUNCTION__);
    
    // 取得设备的BUS_INTERFACE_STANDARD以便读写配置空间
    status = WdfFdoQueryForInterface(
		fdoData->WdfDevice,
		&GUID_BUS_INTERFACE_STANDARD,
		(PINTERFACE)&fdoData->BusInterface,
		sizeof(BUS_INTERFACE_STANDARD),
		1,
		NULL);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfFdoQueryForInterface failed status=0x%08x", status);
        return status;
    }
    
    // 取得设备信息
    status = GetDeviceInformation(fdoData);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "GetDeviceInformation failed status=0x%08x", status);
        return status;
    }
   	
	// 初始化设备状态
    fdoData->State = ECS_NONE;
    
    // 写请求
	WDF_IO_QUEUE_CONFIG_INIT(&ioQueueConfig, WdfIoQueueDispatchSequential);
    ioQueueConfig.EvtIoWrite = EvtIoWrite;

	WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
	attributes.SynchronizationScope = WdfSynchronizationScopeNone;
	attributes.ExecutionLevel = WdfExecutionLevelPassive;
    status = WdfIoQueueCreate(fdoData->WdfDevice, &ioQueueConfig, &attributes, &fdoData->WriteQueue);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfIoQueueCreate failed status=0x%08x", status);
        return status;
    }
    status = WdfDeviceConfigureRequestDispatching(fdoData->WdfDevice, fdoData->WriteQueue, WdfRequestTypeWrite);
    if(!NT_SUCCESS(status)){
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfDeviceConfigureRequestDispatching failed status=0x%08x", status);
        return status;
    }
    
    // 读请求
    WDF_IO_QUEUE_CONFIG_INIT(&ioQueueConfig, WdfIoQueueDispatchSequential);
    ioQueueConfig.EvtIoRead = EvtIoRead;

	WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
	attributes.SynchronizationScope = WdfSynchronizationScopeNone;
	attributes.ExecutionLevel = WdfExecutionLevelPassive;
    status = WdfIoQueueCreate(fdoData->WdfDevice, &ioQueueConfig, &attributes, &fdoData->ReadQueue);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfIoQueueCreate failed status=0x%08x", status);
        return status;
    }
    status = WdfDeviceConfigureRequestDispatching(fdoData->WdfDevice, fdoData->ReadQueue, WdfRequestTypeRead);
    if(!NT_SUCCESS(status)){
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfDeviceConfigureRequestDispatching failed status=0x%08x", status);
        return status;
    }
    
    // 控制请求
    WDF_IO_QUEUE_CONFIG_INIT(&ioQueueConfig, WdfIoQueueDispatchSequential);
    ioQueueConfig.EvtIoDeviceControl = EvtIoDeviceControl;

	WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
	attributes.SynchronizationScope = WdfSynchronizationScopeNone;
	attributes.ExecutionLevel = WdfExecutionLevelPassive;
    status = WdfIoQueueCreate(fdoData->WdfDevice, &ioQueueConfig, &attributes, &fdoData->IoctlQueue);
	if (!NT_SUCCESS(status))
	{
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfIoQueueCreate failed status=0x%08x", status);
        return status;
    }
    status = WdfDeviceConfigureRequestDispatching(fdoData->WdfDevice, fdoData->IoctlQueue, WdfRequestTypeDeviceControl);
    if(!NT_SUCCESS(status)){
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfDeviceConfigureRequestDispatching failed status=0x%08x", status);
        return status;
    }
    
    // 初始化中断对象
    WDF_INTERRUPT_CONFIG_INIT(&interruptConfig, EvtInterruptIsr, EvtInterruptDpc);
    interruptConfig.EvtInterruptEnable = EvtInterruptEnable;
    interruptConfig.EvtInterruptDisable = EvtInterruptDisable;
    status = WdfInterruptCreate(fdoData->WdfDevice, &interruptConfig, WDF_NO_OBJECT_ATTRIBUTES, &fdoData->Interrupt);
    if(!NT_SUCCESS(status)){
		TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfInterruptCreate failed status=0x%08x", status);
        return status;
    }

	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);

    return status;
}

//
// 释放软件资源，不需要考虑硬件资源的释放
//
NTSTATUS FreeSoftwareResources(
    IN PFDO_DATA fdoData
)
{
	NTSTATUS status;

    PAGED_CODE();
	UNREFERENCED_PARAMETER(fdoData);

	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s enter", __FUNCTION__);
    status = STATUS_SUCCESS;
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
    return status;
}

//
// 取得设备信息
//
NTSTATUS GetDeviceInformation(
    IN PFDO_DATA fdoData
)
{
	ULONG bus_num, ret_len;
	NTSTATUS status;
	
    PAGED_CODE();
	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s enter", __FUNCTION__);
	do {
	    // 获取bus
	    status = WdfDeviceQueryProperty(fdoData->WdfDevice, DevicePropertyBusNumber, sizeof(ULONG), &bus_num, &ret_len);
		if (!NT_SUCCESS(status))
		{
			TraceEvents(TRACE_LEVEL_ERROR, DBG_PNP, "WdfDeviceQueryProperty(DevicePropertyBusNumber) failed status=0x%08x", status);
	    	break;
	    }
	    fdoData->Location.u.function = 0;
	    fdoData->Location.u.device = 0;
	    fdoData->Location.u.bus = (USHORT)bus_num;
		TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "bus_num=%d", bus_num);
	    // check vendor id & device id
	    // query pci config space & ext space
    } while (FALSE);

	TraceEvents(TRACE_LEVEL_INFORMATION, DBG_PNP, "%s leave", __FUNCTION__);
	return status;
}