#include<Windows.h>

#ifndef JIUYINMAIN
#define JIUYINMAIN

typedef struct
{
	DWORD pianYi_Y;
	LPTSTR pName;
}smallQu, pSmallQu;

typedef struct
{
	DWORD pianYi_Y;
	LPTSTR pName;
	smallQu mySmallQu[10];
} bigQu, pbigQu;

typedef struct {
	HWND hwnd;
	DWORD SleepTime;
	BOOL IsHook;
	BOOL ExitProcess;
	COLORREF ColorDataInfo[2000][2000];
}ShareMap, *LPShareMap;



#endif