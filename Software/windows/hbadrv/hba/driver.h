/*++
文件名
    driver.h

描述
    驱动
--*/
#ifndef __DRIVER_H__
#define __DRIVER_H__

//
// 释放软件资源，不需要考虑硬件资源释放
//
NTSTATUS FreeSoftwareResources(
    IN PFDO_DATA fdoData
);

//
// 为读写控制请求分配队列 分配中断对象和DMA相关的资源
//
NTSTATUS AllocateSoftwareResources(
    IN PFDO_DATA fdoData
);

//
// 取得设备信息
//
NTSTATUS GetDeviceInformation(
    IN PFDO_DATA fdoData
);

//
// 例程原型
//
DRIVER_INITIALIZE              DriverEntry;             // 驱动入口例程
EVT_WDF_DRIVER_UNLOAD          EvtDriverUnload;         // 驱动卸载例程
EVT_WDF_DRIVER_DEVICE_ADD      EvtDeviceAdd;            // 添加设备回调例程
EVT_WDF_DEVICE_CONTEXT_CLEANUP EvtDeviceContextCleanup; // 清除设备上下文回调例
EVT_WDF_DEVICE_D0_ENTRY        EvtDeviceD0Entry;        // 设备已经进入D0
EVT_WDF_DEVICE_D0_EXIT         EvtDeviceD0Exit;         // 设备退出D0之前

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, EvtDriverUnload)
#pragma alloc_text(PAGE, EvtDeviceAdd)
#pragma alloc_text(PAGE, EvtDeviceContextCleanup)
#pragma alloc_text(PAGE, EvtDeviceD0Entry)
#pragma alloc_text(PAGE, EvtDeviceD0Exit)
#pragma alloc_text(PAGE, FreeSoftwareResources)
#pragma alloc_text(PAGE, AllocateSoftwareResources)
#pragma alloc_text(PAGE, GetDeviceInformation)
#endif

#endif // __DRIVER_H__