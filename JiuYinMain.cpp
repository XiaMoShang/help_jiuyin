///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#include<time.h>
#include "Shlobj.h"
#include"SavaLog.h"
#include"JiuYinMain.h"
#include"JiuYinWork.h"
#include"resource.h"
#include<windowsx.h>
#include<atlbase.h>


#define GETMONEY 0


TCHAR lpszBuffer[256];
CRITICAL_SECTION g_cs;	
CRITICAL_SECTION g_cs1;//关键段代码
SYSTEMTIME cSysTime;                                            //系统时间
TCHAR pzAccountPath[MAX_PATH], pzNouseAccountPath[MAX_PATH], pzGamePath[MAX_PATH], szAccountPath[MAX_PATH], szNouseAccountPath[MAX_PATH];                       //账号存放路径
DWORD iDaquIndex, iXiaoIndex;
JiuYinWork JiuWork[100];
LPTSTR pzNouseAccount, pzAccount;


bigQu MYJIUYINXUANQU[] = {
	{ 0, L"江湖三区", { { 0, L"九阴真经  江湖三区-世外桃源" }, { 1, L"九阴真经  江湖三区-世家风云" }, { 2, L"九阴真经  江湖三区-雄霸天下" }, { 3, L"" }, { 4, L"" }, { 5, L"" }, { 6, L"" }, { 7, L"" }, { 8, L"" }, { 9, L"" } } },
	{ 0, L"江湖二区", { { 0, L"九阴真经  江湖二区-荡剑山" }, { 1, L"九阴真经  江湖二区-通天谷" }, { 2, L"九阴真经  江湖二区-风云阁" }, { 3, L"九阴真经  江湖二区-恶人谷" }, { 4, L"九阴真经  江湖二区-无忧谷" }, { 5, L"九阴真经  江湖二区-侠隐峰" }, { 6, L"" }, { 7, L"" }, { 8, L"" }, { 9, L"" } } },
	{ 0, L"江湖一区", { { 0, L"九阴真经  江湖一区-藏剑峰" }, { 1, L"九阴真经  江湖一区-梵音寺" }, { 2, L"九阴真经  江湖一区-侠客岛" }, { 3, L"九阴真经  江湖一区-明月峰" }, { 4, L"九阴真经  江湖一区-侠客" }, { 5, L"" }, { 6, L"" }, { 7, L"" }, { 8, L"" }, { 9, L"" } } }
};

//ThreadBaiTanParam My_BaiTan[] = {
//	{ 1, 0, "荡剑山", "kuangzuoquan2", "1064671193k", "1064671193" },
//	{ 1, 0, "荡剑山", "kuangzuoquan1", "1064671193k", "1064671193" },
//	/*{ 0, 1, "世家风云", "15620693983", "1210910110k", "1064671193" },*/
//	{ 0, 1, "世家风云", "huanfengwu1", "1064671193k", "1064671193" },
//	{ 0, 2, "雄霸天下", "kuangzuoquan1", "1064671193k", "1064671193" },
//	{ 0, 2, "雄霸天下", "kuangzuoquan2", "1064671193k", "1064671193" },
//	//{ 0, 0, "世外桃源", "kuangzuoquan1", "1064671193k", "1064671193" },
//	//{ 0, 0, "世外桃源", "kuangzuoquan2", "1064671193k", "1064671193" },
//};





/////////////////////////// chHANDLE_DLGMSG Macro /////////////////////////////


// The normal HANDLE_MSG macro in WindowsX.h does not work properly for dialog
// boxes because DlgProc returns a BOOL instead of an LRESULT (like
// WndProcs). This chHANDLE_DLGMSG macro corrects the problem:
#define chHANDLE_DLGMSG(hWnd, message, fn)                 \
   case (message) : return (SetDlgMsgResult(hWnd, message, \
   HANDLE_##message((hWnd), (wParam), (lParam), (fn))))





//////////////////////// Dialog Box Icon Setting Macro ////////////////////////


// Sets the dialog box icons
inline void chSETDLGICONS(HWND hWnd, int idi) {
	SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)
		LoadIcon((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		MAKEINTRESOURCE(idi)));
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)
		LoadIcon((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		MAKEINTRESOURCE(idi)));
}



///////////////////////////////////////////////////////////////////////////////////////////////
//关闭窗口
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int WINAPI CloseWindows(void * param){
	HWND hwnd;
	while (true)
	{
		/*hwnd = FindWindowA("#32770", NULL);
		if (hwnd)
		{
		SendMessage(hwnd, WM_CLOSE, 0, 0);
		CloseWindow(hwnd);
		}*/
		hwnd = FindWindowA(NULL, "lua script");
		if (hwnd)
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		hwnd = FindWindowA(NULL, "run error");
		if (hwnd)
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		hwnd = FindWindowA(NULL, "lua error");
		if (hwnd)
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		hwnd = FindWindowA("#32770", "TS");
		if (hwnd)
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		Sleep(20);

	}
}



BOOL InitConfigFormFile(HWND hwnd, LPTSTR ConfigFilePath)
{
	Button_SetCheck(GetDlgItem(hwnd, IDC_MONEY_AOTO), GetPrivateProfileInt(L"RADIO", L"IDC_MONEY_AOTO", 0, ConfigFilePath));
	Button_SetCheck(GetDlgItem(hwnd, IDC_MONEY_DAN), GetPrivateProfileInt(L"RADIO", L"IDC_MONEY_NAOTO", 0, ConfigFilePath));
	Button_SetCheck(GetDlgItem(hwnd, IDC_RADIO_USE), GetPrivateProfileInt(L"RADIO", L"IDC_MONEY_DAN", 0, ConfigFilePath));
	Button_SetCheck(GetDlgItem(hwnd, IDC_RADIO_USE), GetPrivateProfileInt(L"RADIO", L"IDC_RADIO_USE", 0, ConfigFilePath));
	Button_SetCheck(GetDlgItem(hwnd, IDC_RADIO_BAITAN), GetPrivateProfileInt(L"RADIO", L"IDC_RADIO_BAITAN", 0, ConfigFilePath));
	Button_SetCheck(GetDlgItem(hwnd, IDC_CHECK_YANSHI), GetPrivateProfileInt(L"RADIO", L"IDC_CHECK_YANSHI", 0, ConfigFilePath));
	Button_SetCheck(GetDlgItem(hwnd, IDC_CHECK_HUANHAO), GetPrivateProfileInt(L"RADIO", L"IDC_CHECK_HUANHAO", 0, ConfigFilePath));


	SetDlgItemInt(hwnd, IDC_TIME_S, GetPrivateProfileInt(L"EDIT", L"IDC_TIME_S", 0, ConfigFilePath), 0);
	SetDlgItemInt(hwnd, IDC_TIME_F, GetPrivateProfileInt(L"EDIT", L"IDC_TIME_F", 2, ConfigFilePath), 0);
	SetDlgItemInt(hwnd, IDC_TIME_M, GetPrivateProfileInt(L"EDIT", L"IDC_TIME_M", 40, ConfigFilePath), 0);
	SetDlgItemInt(hwnd, IDC_THREADNUM, GetPrivateProfileInt(L"EDIT", L"IDC_THREADNUM", 15, ConfigFilePath), 0);
	SetDlgItemInt(hwnd, IDC_EDIT_YANSHI, GetPrivateProfileInt(L"EDIT", L"IDC_EDIT_YANSHI", 6, ConfigFilePath), 0);


	HWND hwndList_M = GetDlgItem(hwnd, IDC_MY_DAQU);
	HWND hwndList_S = GetDlgItem(hwnd, IDC_MY_XIAOQU);
	iDaquIndex = GetPrivateProfileInt(L"COMBOX", L"IDC_MY_DAQU", 0, ConfigFilePath);
	iXiaoIndex = GetPrivateProfileInt(L"COMBOX", L"IDC_MY_XIAOQU", 0, ConfigFilePath);

	ComboBox_SetCurSel(hwndList_M, iDaquIndex);  // Select the first entry
	ComboBox_ResetContent(hwndList_S);
	for (size_t j = 0; j < 10; j++)
	{
		if (MYJIUYINXUANQU[iDaquIndex].mySmallQu[j].pName != L"")
		{
			ComboBox_InsertString(hwndList_S, j, MYJIUYINXUANQU[iDaquIndex].mySmallQu[j].pName);
		}
	}
	ComboBox_SetCurSel(hwndList_S, iXiaoIndex);  // Select the first entry


	//TCHAR Buffer[MAX_PATH]; 
	GetPrivateProfileString(L"EDIT", L"IDC_EDIT_GAMEPATH", L"", pzGamePath, MAX_PATH, ConfigFilePath);
	SetDlgItemText(hwnd, IDC_EDIT_GAMEPATH, pzGamePath);
	GetPrivateProfileString(L"EDIT", L"IDC_EDIT_ACCOUNT", L"", pzAccountPath, MAX_PATH, ConfigFilePath);
	SetDlgItemText(hwnd, IDC_EDIT_ACCOUNT, pzAccountPath);
	GetPrivateProfileString(L"EDIT", L"IDC_EDIT_NOUSE_ACCOUNT", L"", pzNouseAccountPath, MAX_PATH, ConfigFilePath);
	SetDlgItemText(hwnd, IDC_EDIT_NOUSE_ACCOUNT, pzNouseAccountPath);

	pzAccount = ReadAllLog(pzAccountPath);
	pzNouseAccount = ReadAllLog(pzNouseAccountPath);

	//wsprintf(szAccountPath, L"%s临时.txt", pzAccountPath);
	////sprintf_s(szNouseAccountPath, "%s临时.txt", pzNouseAccountPath);
	//CopyFile(pzAccountPath, szAccountPath, 0);

	//wsprintf(szNouseAccountPath, L"%s临时.txt", pzNouseAccountPath);
	////CopyFile(pzAccountPath, szAccountPath, 0);
	//CopyFile(pzNouseAccountPath, szNouseAccountPath, 0);

	return TRUE;
}

LPTSTR GetState(HWND hwnd, DWORD ID){
	if (Button_GetState(GetDlgItem(hwnd, ID)))
	{
		return L"1";
	}
	else
	{
		return L"0";
	}
}

BOOL SaveConfigFormFile(HWND hwnd, LPTSTR ConfigFilePath)
{
	WritePrivateProfileString(L"RADIO", L"IDC_MONEY_AOTO", GetState(hwnd, IDC_MONEY_AOTO), ConfigFilePath);
	WritePrivateProfileString(L"RADIO", L"IDC_MONEY_NAOTO", GetState(hwnd, IDC_MONEY_NAOTO), ConfigFilePath);
	WritePrivateProfileString(L"RADIO", L"IDC_MONEY_DAN", GetState(hwnd, IDC_MONEY_DAN), ConfigFilePath);
	WritePrivateProfileString(L"RADIO", L"IDC_RADIO_USE", GetState(hwnd, IDC_RADIO_USE), ConfigFilePath);
	WritePrivateProfileString(L"RADIO", L"IDC_RADIO_BAITAN", GetState(hwnd, IDC_RADIO_BAITAN), ConfigFilePath);
	WritePrivateProfileString(L"RADIO", L"IDC_CHECK_YANSHI", GetState(hwnd, IDC_CHECK_YANSHI), ConfigFilePath);
	WritePrivateProfileString(L"RADIO", L"IDC_CHECK_HUANHAO", GetState(hwnd, IDC_CHECK_HUANHAO), ConfigFilePath);

	WCHAR Buffer[MAX_PATH];
	wsprintf(Buffer, L"%d", GetDlgItemInt(hwnd, IDC_TIME_S, 0, 0));
	WritePrivateProfileString(L"EDIT", L"IDC_TIME_S", Buffer, ConfigFilePath);
	wsprintf(Buffer, L"%d", GetDlgItemInt(hwnd, IDC_TIME_F, 0, 0));
	WritePrivateProfileString(L"EDIT", L"IDC_TIME_F", Buffer, ConfigFilePath);
	wsprintf(Buffer, L"%d", GetDlgItemInt(hwnd, IDC_TIME_M, 0, 0));
	WritePrivateProfileString(L"EDIT", L"IDC_TIME_M", Buffer, ConfigFilePath);
	wsprintf(Buffer, L"%d", GetDlgItemInt(hwnd, IDC_THREADNUM, 0, 0));
	WritePrivateProfileString(L"EDIT", L"IDC_THREADNUM", Buffer, ConfigFilePath);
	wsprintf(Buffer, L"%d", GetDlgItemInt(hwnd, IDC_EDIT_YANSHI, 0, 0));
	WritePrivateProfileString(L"EDIT", L"IDC_EDIT_YANSHI", Buffer, ConfigFilePath);


	GetDlgItemText(hwnd, IDC_EDIT_GAMEPATH, Buffer, MAX_PATH);
	WritePrivateProfileString(L"EDIT", L"IDC_EDIT_GAMEPATH",Buffer, ConfigFilePath);

	GetDlgItemText(hwnd, IDC_EDIT_ACCOUNT, Buffer, MAX_PATH);
	WritePrivateProfileString(L"EDIT", L"IDC_EDIT_ACCOUNT", Buffer, ConfigFilePath);

	GetDlgItemText(hwnd, IDC_EDIT_NOUSE_ACCOUNT, Buffer, MAX_PATH);
	WritePrivateProfileString(L"EDIT", L"IDC_EDIT_NOUSE_ACCOUNT", Buffer, ConfigFilePath);

	
	wsprintf(Buffer, L"%d", ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_MY_DAQU)));
	WritePrivateProfileString(L"COMBOX", L"IDC_MY_DAQU", Buffer, ConfigFilePath);

	wsprintf(Buffer, L"%d", ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_MY_XIAOQU)));
	WritePrivateProfileString(L"COMBOX", L"IDC_MY_XIAOQU", Buffer, ConfigFilePath);

	return 1;
}


/////////////////////////////////////////////////////////////////////////////////////


BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {

	chSETDLGICONS(hwnd, IDI_JIUYIN);

	//SetDlgItemInt(hwnd, IDC_TIME_F, 2, 0);
	//SetDlgItemInt(hwnd, IDC_TIME_S, 0, 0);
	//SetDlgItemInt(hwnd, IDC_TIME_M, 0, 0);
	//SetDlgItemInt(hwnd, IDC_THREADNUM, 10, 0);
	//SetDlgItemInt(hwnd, IDC_EDIT_YANSHI, 5, 0);




	//GetLocalTime(&cSysTime);									//获得本地时间
	//cSysTime.wSecond = cSysTime.wSecond + 5;

	HWND hwndList_M = GetDlgItem(hwnd, IDC_MY_DAQU);
	HWND hwndList_S = GetDlgItem(hwnd, IDC_MY_XIAOQU);

	for (size_t i = 0; i < 3; i++)
	{
		//ComboBox_AddString(hwndList_M, MYJIUYINXUANQU[i].pName);
		ComboBox_InsertString(hwndList_M, i, MYJIUYINXUANQU[i].pName);
	}
	for (size_t j = 0; j < 10; j++)
	{
		if (MYJIUYINXUANQU[0].mySmallQu[j].pName != L"")
		{
			ComboBox_InsertString(hwndList_S, j, MYJIUYINXUANQU[0].mySmallQu[j].pName);
			//ComboBox_AddString(hwndList_S, MYJIUYINXUANQU[0].mySmallQu[j].pName);
		}
	}
	ComboBox_SetCurSel(hwndList_S, 0);  // Select the first entry
	ComboBox_SetCurSel(hwndList_M, 0);  // Select the first entry

	InitializeCriticalSection(&g_cs);
	InitializeCriticalSection(&g_cs1);


	TCHAR ConfigPath[MAX_PATH];
	GetModuleFileName(NULL, ConfigPath, _countof(ConfigPath));
	PTSTR pDllname = _tcsrchr(ConfigPath, TEXT('\\')) + 1;
	_tcscpy_s(pDllname, _countof(ConfigPath) - (pDllname - ConfigPath),
		TEXT("config.ini"));
	InitConfigFormFile(hwnd, ConfigPath);
	//InitializeCriticalSection(&g_cs_fic);

	return(TRUE);
}


/////////////////////////////////////////////////////////////////////////////////////


BOOL Dlg_OnHotKey(HWND hwnd, int idHotKey, UINT fuMode, UINT vk) {
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////

BOOL  ChoiseWork(HWND hwnd, DWORD WorkCode)
{
	HWND hwndRadioNaoto = GetDlgItem(hwnd, IDC_MONEY_NAOTO);
	HWND hwndRadioAoto = GetDlgItem(hwnd, IDC_MONEY_AOTO);
	HWND hwndRadioDan = GetDlgItem(hwnd, IDC_MONEY_DAN);
	HWND hwndRadioUse = GetDlgItem(hwnd, IDC_RADIO_USE);

	switch (WorkCode)
	{
	case GETMONEY:
		if (Button_GetState(hwndRadioAoto))
		{
			for (size_t i = 0; i < GetDlgItemInt(hwnd, IDC_THREADNUM, 0, 0); i++)
			{

				SYSTEMTIME myLocalTime;
				WORD	myHour = GetDlgItemInt(hwnd, IDC_TIME_S, 0, 0);
				WORD	myMinute = GetDlgItemInt(hwnd, IDC_TIME_F, 0, 0);
				WORD	mySecond = GetDlgItemInt(hwnd, IDC_TIME_M, 0, 0);
				GetLocalTime(&myLocalTime);
				FILETIME filetime;
				if (myHour == 0)
				{
					if ((myLocalTime.wHour != 0)){
						SystemTimeToFileTime(&myLocalTime, &filetime);
						UINT64  uiBaseTime, uiResult;
						uiBaseTime = ((UINT64)filetime.dwHighDateTime << 32) + filetime.dwLowDateTime;
						uiResult = uiBaseTime + 24*60*60*(UINT64)10000000;
						FileTimeToSystemTime((LPFILETIME)&uiResult, &myLocalTime);
					}
				}
				myLocalTime.wHour = myHour;
				myLocalTime.wMinute = myMinute;
				myLocalTime.wSecond = mySecond;
				
				SystemTimeToFileTime(&myLocalTime, &(filetime));
				JiuWork[i].filetime = filetime;
				JiuWork[i].TimeIndex = i;
				JiuWork[i].myHwnd = hwnd;
				JiuWork[i].StartThread();
				//hThread[i] = _beginthreadex(NULL, 3 * 1024 * 1024, StartWork, &param, CREATE_SUSPENDED, dStartWorkId + i);
				//SetThreadPriority((HANDLE)hThread[i], THREAD_PRIORITY_HIGHEST);
				//ResumeThread((HANDLE)hThread[i]);
			}
		}
		break;
	default:
		break;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////


BOOL chooseFile(LPTSTR szBuffer){
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = _T("从下面选择文件或文件夹:");
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
	{
		return 0;
	}
	else
	{
		SHGetPathFromIDList(idl, szBuffer);
		return 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////


void EnableDebugPriv() {
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, NULL);
	CloseHandle(hToken);
}




void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
	WPARAM wParam = 0;
	LPARAM IParam = 0;
	switch (id) {

	case IDCANCEL:{
					  for (size_t i = 0; i < 100; i++)
					  {
						  if (JiuWork[i].Data != NULL)
						  {
							  JiuWork[i].ExitProcess();
						  }  
					  }
					  
					  TCHAR ConfigPath[MAX_PATH];
					  GetModuleFileName(NULL, ConfigPath, _countof(ConfigPath));
					  PTSTR pDllname = _tcsrchr(ConfigPath, TEXT('\\')) + 1;
					  _tcscpy_s(pDllname, _countof(ConfigPath) - (pDllname - ConfigPath),
						  TEXT("config.ini"));
					  SaveConfigFormFile(hwnd, ConfigPath);

					  DeleteFile(szAccountPath);
					  DeleteFile(szNouseAccountPath);
					  EndDialog(hwnd, id);
					  break;
	}
	case IDC_START:
	{
			 _beginthreadex(NULL, 0, CloseWindows, 0, 0, 0);
			 //MyTerminateProcess(L"fxgame.exe");
			 ChoiseWork(hwnd, GETMONEY);
			break;
	}
	case IDC_BUT_ACCOUNT:{
							 chooseFile(pzAccountPath);
							 SetDlgItemText(hwnd, IDC_EDIT_ACCOUNT, pzAccountPath);

							 pzAccount = ReadAllLog(pzAccountPath);
							 pzNouseAccount = ReadAllLog(pzNouseAccountPath);
							 //wsprintf(szAccountPath, L"%s临时.txt", pzAccountPath);
							 //sprintf_s(szNouseAccountPath, "%s临时.txt", pzNouseAccountPath);
							 //CopyFile(pzAccountPath, szAccountPath, 0);
							 //CopyFile(pzNouseAccountPath, szNouseAccountPath, 0);
							 break;
	}
	case IDC_BUT_NOUSE_ACCOUNT:{
								   chooseFile(pzNouseAccountPath);
								   SetDlgItemText(hwnd, IDC_EDIT_NOUSE_ACCOUNT, pzNouseAccountPath);
								   pzAccount = ReadAllLog(pzAccountPath);
								   pzNouseAccount = ReadAllLog(pzNouseAccountPath);

								   //sprintf_s(szAccountPath, "%s临时.txt", pzAccountPath);
								   //wsprintf(szNouseAccountPath, L"%s临时.txt", pzNouseAccountPath);
								   //CopyFile(pzAccountPath, szAccountPath, 0);
								   //CopyFile(pzNouseAccountPath, szNouseAccountPath, 0);
								   break;
	}
	case IDC_BUT_GAMEPATH:{
							  chooseFile(pzGamePath);
							  SetDlgItemText(hwnd, IDC_EDIT_GAMEPATH, pzGamePath);
							  break;
	}


	case IDC_MY_DAQU:{
						 HWND hwndList_M = GetDlgItem(hwnd, IDC_MY_DAQU);
						 HWND hwndList_S = GetDlgItem(hwnd, IDC_MY_XIAOQU);
						 iDaquIndex = ComboBox_GetCurSel(hwndList_M);
						 ComboBox_ResetContent(hwndList_S);
						 for (size_t j = 0; j < 10; j++)
						 {
							 if (MYJIUYINXUANQU[iDaquIndex].mySmallQu[j].pName != L"")
							 {
								 //ComboBox_AddString(hwndList_S, MYJIUYINXUANQU[num].mySmallQu[j].pName);
								 ComboBox_InsertString(hwndList_S, j, MYJIUYINXUANQU[iDaquIndex].mySmallQu[j].pName);
							 }
						 }
						 ComboBox_SetCurSel(hwndList_S, 0);  // Select the first entry
						 break;
	}
	case IDC_MY_XIAOQU:{
						   HWND hwndList_S = GetDlgItem(hwnd, IDC_MY_XIAOQU);
						   iXiaoIndex = ComboBox_GetCurSel(hwndList_S);
						   break;
	}
		
	case IDC_EXIT:
			break;
	}
}


////////////////////////////////////////////////////////////////////////////////////////


INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
		chHANDLE_DLGMSG(hwnd, WM_COMMAND, Dlg_OnCommand);
		//chHANDLE_DLGMSG(hwnd, WM_HOTKEY, Dlg_OnHotKey);
	}

	return(FALSE);
}


int WINAPI _tWinMain(HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int) {


	// MessageBox(NULL, "1111", "111", MB_OK);
	
	DialogBoxParam(hinstExe, MAKEINTRESOURCE(IDD_JIUYIN),
		NULL, Dlg_Proc, 0);
	//TCHAR  str[1024];
//	LPTSTR pzAccount = ReadAllLog(pzAccountPath);

	//while (true)
	//{
	//	GetLineFromFile(pzAccount, str);
	//}
	//
	return(0);
}