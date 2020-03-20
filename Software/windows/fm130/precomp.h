/*--

文件名
precomp.h
说  明
预编译头文件

--*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <tchar.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <locale.h>
#include <process.h>
#include <initguid.h>
#include <WinIoCtl.h>
#include <Windows.h>
#include <WinDef.h>
#include <Setupapi.h>

#include "api.h"
#include "utility.h"

#pragma comment(lib, "SetupAPI.Lib")
#pragma comment(lib, "WS2_32.Lib")