/*++
文件名
    precomp.h

描述
    预编译头文件
--*/

#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4214)

#include <ntddk.h> 
#include <wdf.h>
#include <initguid.h>
#include <wdmguid.h>
#include <ntintsafe.h>
#include <ntstrsafe.h>
#include <evntrace.h>

#include "trace.h"
#include "public.h"
#include "hba_time.h"
#include "driver.h"
#include "hw.h"
#include "utils.h"
#include "read.h"
#include "write.h"
#include "ioctl.h"