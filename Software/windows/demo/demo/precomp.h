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

#include "..\\..\\fm130\\api.h"
#include "fc_demo.h"

#pragma comment(lib, "SetupAPI.Lib")
#pragma comment(lib, "WS2_32.Lib")
#pragma comment(lib, "..\\Debug\\fm130.lib")