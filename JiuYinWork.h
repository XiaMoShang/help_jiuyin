
#include<Windows.h>
#include<tchar.h>
#include<windowsx.h>
#include <atlbase.h>
#include<atlconv.h>
#include"JiuYinMain.h"
#include<string>
#include"SavaLog.h"
#include<time.h>
#include"resource.h"
#include"TerminateProcess.h"

class JiuYinWork
{
public:
	JiuYinWork();
	~JiuYinWork();

	HWND GetWindowHwnd(){ return hwnd; };
	void SetWindowHwnd(HWND mHwnd){ hwnd = mHwnd; };

	BOOL StartThread(){ hThread = _beginthreadex(NULL, NULL, ThreadWork, this, NULL, NULL); return true; };
	friend unsigned int __stdcall ThreadWork(void *param);


	BOOL GotoGameLoginWindow(DWORD DaquIndex, DWORD XiaoIndex);
	BOOL  LeftClick(HWND hwnd, int x, int y);

	BOOL DxBind(HWND hwnd, int type);
	void ExitProcess(){ Data->ExitProcess = TRUE; }

	BOOL GameLogin(HWND hwnd, LPTSTR pNum, LPTSTR pPasWord);
	BOOL SendStrToWindow(HWND hwnd, LPTSTR pStr, DWORD Time);

	BOOL FindPicEx(HWND hwnd, int left, int top, int right, int bottom, LPTSTR PicPath, int ColourIdex, double ColourId, int &fx, int &fy);
	BOOL comparaLeftToRightFromTopEx(HWND hwnd, int h, int w, int ColourIdex, double ColourId);
	BOOL loadBitmap(LPTSTR path);

	BOOL ExitGameWindow(HWND hwnd);
	BOOL GetMoney(HWND hwnd);
	BOOL Click(HWND hwnd, LPTSTR pbuf);
	BOOL FindColorEx(HWND hwnd, int left, int top, int right, int bottom, int ColourIdex, int, int &fx, int &fy);
	//BOOL JiuYinWork::SendKey(HWND hwnd, WPARAM s, DWORD Time);
	BOOL JiuYinWork::YanWu(HWND hwnd);

	LPShareMap Data;
	LPBYTE m_pBuffer;
	HANDLE m_hFileMap;
	COLORREF **pLoadBmpBuffer;
	DWORD loadWidth;
	DWORD loadHeight;
	TCHAR OldWindowText[MAX_PATH];
	FILETIME filetime;
	DWORD TimeIndex;
	HWND myHwnd;
private:
	HWND hwnd;
	uintptr_t hThread;
};

