#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <TCHAR.H>
#include <winsock.h>
#pragma comment (lib,"Ws2_32")
//
//
//#define UNICODE
//#define _UNICODE

//#define _countof(array) (sizeof(array)/sizeof(array[0]))
#define HIGHTIME		21968699 // 21968708 // Jan 1, 1900 FILETIME.highTime
#define LOWTIME			4259332096 // 1604626432 // Jan 1, 1900 FILETIME.lowtime


BOOL UpdateSysTime(DWORD dwTime);  //更新系统时间

BOOL GetTimeFromServer(DWORD *lpdwTime); //从服务器获得时间

BOOL ServerTimeToSysTime(SYSTEMTIME *systime);