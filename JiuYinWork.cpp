
#include"JiuYinWork.h"

//#include <afx.h>

using namespace std;



#define WINDOWS_X 150
#define WINDOWS_Y 108

extern TCHAR szAccountPath[MAX_PATH], szNouseAccountPath[MAX_PATH], pzGamePath[MAX_PATH];
//CString szAccountPath, szNouseAccountPath, pzGamePath;
extern CRITICAL_SECTION g_cs,g_cs1;

DWORD flag;

extern DWORD iDaquIndex, iXiaoIndex;
extern bigQu MYJIUYINXUANQU[];
extern LPTSTR pzNouseAccount, pzAccount;

extern LPTSTR logbuf,accoutbuf;

JiuYinWork::JiuYinWork()
{
}

JiuYinWork::~JiuYinWork()
{
	
}



/**************************************************************************
*  Hwnd ���ھ��
*	x ����ĻX����
*   y ����ĻY����
**************************************************************************/
BOOL  JiuYinWork::LeftClick(HWND hwnd, int x, int y)
{

	LPARAM lparam = MAKELPARAM(x, y);    //����ת��
	LRESULT result = ::SendMessage(hwnd, WM_LBUTTONDOWN, VK_LBUTTON, lparam);
	LRESULT result1 = ::SendMessage(hwnd, WM_LBUTTONUP, VK_LBUTTON, lparam);
	return (result&result1)>0;

}



/******************************************************************************
*  ���ܣ���¼����¼����
*	DaquIndex :����ƫ��
*	XiaoIndex ��������ƫ��
*****************************************************************************/

BOOL JiuYinWork::GotoGameLoginWindow(DWORD DaquIndex, DWORD XiaoIndex)
{
	HWND hwnd;

	MyTerminateProcess(L"fxupdate.exe");
	//LPCSTR sz = W2A(pzGamePath);
	USES_CONVERSION;
	WinExec(W2A(pzGamePath), SW_SHOWMAXIMIZED);
	for (size_t i = 0; i < 15; i++){
		if (!(hwnd = FindWindow(L"FxMain", L"�����澭������")))          //Ѱ�Ҹ�����
			Sleep(100);
	}

	if (hwnd)
		SetWindowText(hwnd, L"������");
	else
		return 0;
	Sleep(2000);

	//CutHwndPic(hwnd);

	LeftClick(hwnd, 1244 - WINDOWS_X, 764 - WINDOWS_Y);
	Sleep(2000);

	LeftClick(hwnd, 873 - WINDOWS_X, 662 - WINDOWS_Y);
	Sleep(2000);

	LeftClick(hwnd, 1054 - WINDOWS_X, 814 - WINDOWS_Y);
	Sleep(2000);

	LeftClick(hwnd, 622 - WINDOWS_X, 266 + 60 * DaquIndex - WINDOWS_Y);
	Sleep(2000);

	LeftClick(hwnd, 1042 - WINDOWS_X, 547 + XiaoIndex * 45 - WINDOWS_Y);
	Sleep(2000);

	LeftClick(hwnd, 1009 - WINDOWS_X, 836 - WINDOWS_Y);
	Sleep(2000);

	LeftClick(hwnd, 876 - WINDOWS_X, 657 - WINDOWS_Y);
	Sleep(2000);

	LeftClick(hwnd, 1400 - WINDOWS_X, 818 - WINDOWS_Y);
	Sleep(5000);

	return 1;
}



/***************************************************************************
*	��¼����Ϸ
*	Hwnd : ���ھ��
*	pNum ���˺�
*	pPasword : ����
**************************************************************************/

BOOL JiuYinWork::GameLogin(HWND hwnd, LPTSTR pNum, LPTSTR pPasWord)
{
	int fx, fy;
	while (!FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\����.bmp", 0x151515, 0.8, fx, fy))
		
		Sleep(2000);

	Sleep(5000);
	LeftClick(hwnd, 554, 324);
	Sleep(1000);

	SendStrToWindow(hwnd, pNum, 1);

	Sleep(500);
	LeftClick(hwnd, 546, 364);
	Sleep(500);

	SendStrToWindow(hwnd, pPasWord, 1);

	//Sleep(2000);
	//SendKey(hwnd, '/n', 100);
	//Sleep(2000);
	//SendKey(hwnd, '/n', 100);

	Sleep(2000);
	LeftClick(hwnd, 636, 339);

	Sleep(2000);
	LeftClick(hwnd, 508, 445);


	while (!(FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\��ƽ.bmp", 0x101010, 0.9, fx, fy)
		|| FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\������Ϸ.bmp", 0x101010, 0.9, fx, fy)
		|| FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\��.bmp", 0x101010, 0.9, fx, fy)))
		Sleep(2000);


	Sleep(2000);
	LeftClick(hwnd, 495, 674);

	while (!(FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\��ƽ.bmp", 0x101010, 0.9, fx, fy)
		|| FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\��.bmp", 0x101010, 0.9, fx, fy)))
		Sleep(1000);

	Sleep(2000);

	while (!(FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\��ƽ.bmp", 0x101010, 0.9, fx, fy)
		|| FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\��.bmp", 0x101010, 0.9, fx, fy)))
		Sleep(1000);
	return 1;
}



/***************************************************************************
*	�����ַ�����Ϣ������
*	Hwnd : ���ھ��
*	pStr ����Ϣ�ַ���
*	Time : �ȴ�ʱ�䣨�Ժ���Ϊ��λ��
**************************************************************************/

BOOL JiuYinWork::SendStrToWindow(HWND hwnd, LPTSTR pStr, DWORD Time)
{
	TCHAR* s;
	DWORD length = lstrlen(pStr);
	for (size_t i = 0; i < length; i++, pStr++)
	{
		s = pStr;
		SendMessage(hwnd, WM_CHAR, *s, 0);
		Sleep(Time);
	}
	return 1;
}


/***************************************************************************
*	�����ַ�����Ϣ������
*	Hwnd : ���ھ��
*	pStr ����Ϣ�ַ���
*	Time : �ȴ�ʱ�䣨�Ժ���Ϊ��λ��
**************************************************************************/

//BOOL JiuYinWork::SendKey(HWND hwnd, TCHAR s, DWORD Time)
//{
//	SendMessage(hwnd, WM_KEYFIRST, s, 0);
//	Sleep(Time);
//	SendMessage(hwnd, WM_KEYUP, s, 0);
//
//}


BOOL JiuYinWork::loadBitmap(LPTSTR path)
{
	//std::string rstr;
	BYTE *rstr = NULL;
	int rstrlen = 0;
	BITMAPFILEHEADER fileheader = { 0 };

	HANDLE file_Handle = CreateFile(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file_Handle == INVALID_HANDLE_VALUE)
	{
		int err = ::GetLastError();
		TCHAR erro[MAX_PATH] = { 0 };
		wsprintf(erro, L"����:%s,λͼʧ��", path);
		::MessageBox(NULL, erro, L"TS", 0);
		CloseHandle(file_Handle);
		return false;
	}
	DWORD dword = 0, ReadFileSize = 0;
	DWORD fileszie = GetFileSize(file_Handle, NULL);
	if (fileszie > 0)
	{
		rstr = new BYTE[fileszie + 1];
		if (rstr == NULL)
		{
			return false;
		}
	}
	else
	{
		return false;
	}


	memset(rstr, 0, sizeof(BYTE)*fileszie);
	{
		::ReadFile(file_Handle, rstr, fileszie, &ReadFileSize, NULL);
	}
	CloseHandle(file_Handle);

	BITMAPINFOHEADER head;
	DWORD headSize = sizeof(BITMAPINFOHEADER);
	memcpy(&head, &rstr[sizeof(BITMAPFILEHEADER)], sizeof(BITMAPINFOHEADER));
	loadWidth = head.biWidth;
	loadHeight = head.biHeight;
	WORD biBitCount = head.biBitCount;
	if (biBitCount != 24)
	{
		::MessageBoxA(NULL, "��ѡ��24λλͼ��", "TS", 0);
		return false;
	}

	int totalSize = (loadWidth *biBitCount / 8 + 3) / 4 * 4 * loadHeight;
	//BYTE *pBmpBuf = new BYTE[totalSize];
	//memset(pBmpBuf,0,sizeof(BYTE)*totalSize);
	size_t size = 0;
	size = rstrlen - headSize - sizeof(BITMAPFILEHEADER);
	BYTE *pBmpBuf = &rstr[headSize + sizeof(BITMAPFILEHEADER)];
	//memcpy(pBmpBuf,&rstr[headSize+sizeof(BITMAPFILEHEADER)],size);

	if (loadHeight > 0)
	{
		pLoadBmpBuffer = new COLORREF*[loadHeight];     ///// ��ά���� �����洢ͼ�����ɫֵ
		if (pLoadBmpBuffer == NULL)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
	for (int i = 0; i<loadHeight; i++)
	{
		if (loadWidth > 0)
		{
			pLoadBmpBuffer[i] = new COLORREF[loadWidth];
			if (pLoadBmpBuffer[i] == NULL)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	COLORREF helpcolor = 0;
	int pitch = loadWidth % 4;
	//HDC hDC = ::GetWindowDC(::GetDesktopWindow());
	for (int i = 0; i<loadHeight; i++)
	{
		int realPitch = i*pitch;
		for (int j = 0; j<loadWidth; j++)
		{
			UCHAR b = pBmpBuf[(i*loadWidth + j) * 3 + realPitch];
			UCHAR g = pBmpBuf[(i*loadWidth + j) * 3 + 1 + realPitch];
			UCHAR r = pBmpBuf[(i*loadWidth + j) * 3 + 2 + realPitch];
			helpcolor = RGB(r, g, b);
			pLoadBmpBuffer[loadHeight - i - 1][j] = helpcolor;
		}
	}
	delete[] rstr;
	return true;
}


////////////////// ���� ��ʽ //////////////////
////////////////////////////////////////////////0��������,���ϵ���//////////////////////////
////////������ɫΪ��͸����ͼƬ////////////////
BOOL JiuYinWork::comparaLeftToRightFromTopEx(HWND hwnd, int h, int w, int ColourIdex, double ColourId)
{

	BYTE loadR = 0, loadG = 0, loadB = 0;
	BYTE wndR = 0, wndG = 0, wndB = 0;
	int absResult = 0;
	COLORREF pLoadColor = 0, pWndColor = 0;

	//DWORD pid;
	//GetWindowThreadProcessId(hwnd, &pid);
	//TCHAR ShareMemoryName[MAX_PATH];
	//wsprintf(ShareMemoryName, L"ShareMemory_%d", pid);
	//CShareMemory *ShareMemory = new CShareMemory(ShareMemoryName);
	//HANDLE m_hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ShareMemoryName);
	//// ӳ�������ڴ棬ȡ�ù����ڴ���׵�ַ
	//if (m_hFileMap == NULL)
	//{
	//	return false;
	//}

	//if (m_pBuffer == NULL)
	//{
	//	DWORD err = GetLastError();
	//	return false;
	//}

	//Data = (LPShareMap)m_pBuffer;
	if (Data == NULL)
	{
		return 0;
	}

	BYTE m_colorOffsR = GetRValue(ColourIdex);
	BYTE m_colorOffsG = GetGValue(ColourIdex);
	BYTE m_colorOffsB = GetBValue(ColourIdex);
	for (int i = 0; i<loadHeight; i++)
	{
		for (int j = 0; j<loadWidth; j++)
		{

			pLoadColor = pLoadBmpBuffer[i][j];
			loadR = GetRValue(pLoadColor);
			loadG = GetGValue(pLoadColor);
			loadB = GetBValue(pLoadColor);

			pWndColor = Data->ColorDataInfo[h + i][w + j];
			wndR = GetRValue(pWndColor);
			wndG = GetGValue(pWndColor);
			wndB = GetBValue(pWndColor);

			absResult = (loadR - wndR) + abs(loadG - wndG) + abs(loadB - wndB);   ///�������ƶȱȽ�
			BYTE m_simColor = 0;
			m_simColor = (BYTE)((1 - ColourId)*absResult / 3);
			//if(pLoadBmpBuffer[i][j] == pWndBmpBuffer[h+i][w+j])
			if (pLoadColor == 0)
			{
				continue;
			}
			if (abs(loadR - wndR) <= (m_colorOffsR + m_simColor) && abs(loadG - wndG) <= (m_colorOffsG + m_simColor) && abs(loadB - wndB) <= (m_colorOffsB + m_simColor))
			{
				continue;
			}
			else
			{
				return false;
			}

		}
	}
	//if (m_hFileMap != NULL)
	//{
	//	CloseHandle(m_hFileMap);
	//}
	return true;
}

/***************************************************************************
*	��̨��ͼ
*	Hwnd : ���ھ��
*	
**************************************************************************/
BOOL JiuYinWork::FindPicEx(HWND hwnd, int left, int top, int right, int bottom, LPTSTR PicPath, int ColourIdex, double ColourId, int &fx, int &fy)
{
	BOOL isFind = false;

	WCHAR wcPicPath[MAX_PATH];
	WCHAR wcPicPath1[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, wcPicPath1);

	wsprintf(wcPicPath, L"%s%s%s", wcPicPath1, "\\", PicPath);

	if (loadBitmap(wcPicPath) == 0)
		return false;
	if (left < 0)
	{
		left = 0;
	}
	if (left > 1920)
		return 0;

	if (top < 0)
	{
		top = 0;
	}
	if (top > 1920)
	{
		return 0;
	}if (right < 0)
	{
		right = 0;
	}
	if (right > 1920)
	{
		return 0;
	}if (bottom < 0)
	{
		bottom = 0;
	}
	if (bottom > 1920)
	{
		return 0;
	}
	if (bottom - top < 0)
	{
		return 0;
	}
	if (right - left < 0)
	{
		return 0;
	}

	for (size_t i = left; i < right - 1; i++)
	{
		for (size_t j = top; j < bottom - 1; j++)
		{
			isFind = comparaLeftToRightFromTopEx(hwnd, i, j, ColourIdex, ColourId); //0:������,���ϵ���
			if (isFind)
			{
				fx = i;
				fy = j;
				return isFind;
			}
		}

	}

	//switch (type)
	//{
	//case 0:
	//{
	//break;
	//}
	//case 1:
	//	isFind = leftToRightFromBottom(xpos, ypos);//1:���ҵ���,���ϵ���
	//	break;

	//case 2:
	//	isFind = rightToLeftFromTop(xpos, ypos);//2:������,���µ���
	//	break;

	//case 3:
	//	isFind = rightToLeftFromBottom(xpos, ypos);//3:���ҵ���,���µ���
	//	break;
	//}
	//TSRuntime::add_log( "findImage-xpos:%d,ypos:%d,xpos_offset:%d,ypos_offset:%d,m_Dir:%d",xpos,ypos,xpos_offset,ypos_offset,m_Dir);
	for (int i = 0; i<loadHeight; i++)
	{
		delete[] pLoadBmpBuffer[i];
		pLoadBmpBuffer[i] = NULL;
	}
	delete[] pLoadBmpBuffer;
	pLoadBmpBuffer = NULL;


	//TSRuntime::add_log( "findImage-end");
	return isFind;

}



/***************************************************************************
*	��̨��ͼ
*	Hwnd : ���ھ��
*
**************************************************************************/
BOOL JiuYinWork::FindColorEx(HWND hwnd, int left, int top, int right, int bottom, int Colour, int ColourIdex, int &fx, int &fy)
{
	bool isFind = false;

	BYTE cdR = 0, cdG = 0, cdB = 0;
	BYTE idR = 0, idG = 0, idB = 0;
	BYTE wndR = 0, wndG = 0, wndB = 0;
	COLORREF pWndColor = 0;
	if (left < 0)
	{
		left = 0;
	}
	if (left > 1920)
		return 0;

	if (top < 0)
	{
		top = 0;
	}
	if (top > 1920)
	{
		return 0;
	}if (right < 0)
	{
		right = 0;
	}
	if (right > 1920)
	{
		return 0;
	}if (bottom < 0)
	{
		bottom = 0;
	}
	if (bottom > 1920)
	{
		return 0;
	}
	if (bottom - top < 0)
	{
		return 0;
	}
	if (right - left < 0)
	{
		return 0;
	}

	cdR = GetRValue(Colour);
	cdG = GetGValue(Colour);
	cdB = GetBValue(Colour);

	idR = GetRValue(ColourIdex);
	idG = GetGValue(ColourIdex);
	idB = GetBValue(ColourIdex);

	for (size_t i = left; i < right - 1; i++)
	{
		for (size_t j = top; j < bottom - 1; j++)
		{
			pWndColor = Data->ColorDataInfo[i][j];
			wndR = GetRValue(pWndColor);
			wndG = GetGValue(pWndColor);
			wndB = GetBValue(pWndColor);

			if (abs(cdR - wndR) <= (idR) && abs(cdG - wndG) <= (idG) && abs(cdB - wndB) <= (idB))
			{
				isFind = TRUE;
				return isFind;
			}
		}

	}

	//switch (type)
	//{
	//case 0:
	//{
	//break;
	//}
	//case 1:
	//	isFind = leftToRightFromBottom(xpos, ypos);//1:���ҵ���,���ϵ���
	//	break;

	//case 2:
	//	isFind = rightToLeftFromTop(xpos, ypos);//2:������,���µ���
	//	break;

	//case 3:
	//	isFind = rightToLeftFromBottom(xpos, ypos);//3:���ҵ���,���µ���
	//	break;
	//}
	//TSRuntime::add_log( "findImage-xpos:%d,ypos:%d,xpos_offset:%d,ypos_offset:%d,m_Dir:%d",xpos,ypos,xpos_offset,ypos_offset,m_Dir);

	//TSRuntime::add_log( "findImage-end");
	return isFind;

}

/***************************************************************************
*	�˳�����Ϸ��¼����
*	Hwnd : ���ھ��
*
**************************************************************************/

BOOL JiuYinWork::ExitGameWindow(HWND hwnd)
{
	int fx, fy;
	LeftClick(hwnd, 961, 694);
	Sleep(1000);
	LeftClick(hwnd, 485, 431);
	Sleep(1000);
	LeftClick(hwnd, 518, 442);
	Sleep(1000);

	while (!FindPicEx(hwnd, 0, 0, 1024, 768, L"ts\\����.bmp", 0x151515, 0.8, fx, fy))
		Sleep(2000);

	return 0;

}

/***************************************************************************
*	�����Ǯ
*	Hwnd : ���ھ��
*
**************************************************************************/

BOOL JiuYinWork::GetMoney(HWND hwnd)
{
	TCHAR buf[128], windowTitle[256];
	SetWindowText(hwnd, L"------>��ʼ�칤��<------");
	EnterCriticalSection(&g_cs1);
	while (GetLineFromFile(pzAccount, buf))
	{
		LeaveCriticalSection(&g_cs1);//DelFirstLine
		if ((wstring)buf == L"end#")
		{
			break;
		}
		else
		{
			ExitGameWindow(hwnd);
			wsprintf(windowTitle, L"------>��ʼ�칤��----%s<------", buf);
			//MessageBox(NULL,buf,"buf",MB_OK);
			SetWindowText(hwnd, windowTitle);
			GameLogin(hwnd, buf, L"1064671193k");
			Click(hwnd, buf);
		}
	}
	return TRUE;
}


/***************************************************************************
*	�����Ǯ
*	Hwnd : ���ھ��
*
**************************************************************************/

BOOL JiuYinWork::YanWu(HWND hwnd)
{
	TCHAR buf[128], windowTitle[256];
	SetWindowText(hwnd, L"------>��ʼ����<------");
	EnterCriticalSection(&g_cs1);
	while (GetLineFromFile(pzAccount, buf))
	{
		LeaveCriticalSection(&g_cs1);//DelFirstLine
		if ((wstring)buf == L"end#")
		{
			break;
		}
		else
		{
			ExitGameWindow(hwnd);
			wsprintf(windowTitle, L"------>����----%s<------", buf);
			//MessageBox(NULL,buf,"buf",MB_OK);
			SetWindowText(hwnd, windowTitle);
			GameLogin(hwnd, buf, L"1064671193k");
			LeftClick(hwnd, 623, 696);
			Sleep(2000);
			LeftClick(hwnd, 142,169);
			Sleep(2000);
			LeftClick(hwnd, 827, 213);
			Sleep(2000);
			LeftClick(hwnd, 510, 378);
			Sleep(2000);
			//int fx, fy;
			for (size_t i = 0; i < 20; i++)
			{
				/*LeftClick(hwnd, 202, 272);
				if (FindPicEx(hwnd, 0, 0, 666, 768, L"ts\\������ʾ.bmp", 0x101010, 0.8, fx, fy))
				{
					LeftClick(hwnd, 400, 573);
					Sleep(2000);
					LeftClick(hwnd, 300, 240);
					Sleep(2000);

					SendStrToWindow(hwnd, L"1064671193", 1);

					LeftClick(hwnd, 300, 291);
					Sleep(2000);

					SendStrToWindow(hwnd, L"1064671193", 1);

					LeftClick(hwnd, 283, 395);
					Sleep(2000);
					LeftClick(hwnd, 520, 443);
					Sleep(2000);
					LeftClick(hwnd, 551, 506);
					Sleep(2000);

				}
				if (FindPicEx(hwnd, 0, 0, 666, 768, L"ts\\������֤.bmp", 0x101010, 0.8, fx, fy))
				{
					LeftClick(hwnd, 285, 483);
					Sleep(2000);

					SendStrToWindow(hwnd, L"1064671193", 1);

					LeftClick(hwnd, 414, 594);
					Sleep(2000);
				}*/
				LeftClick(hwnd, 798, 514);
				Sleep(2000);
			}
		}
	}
	return TRUE;
}

/***************************************************************************
*	�����Ǯ
*	Hwnd : ���ھ��
*
**************************************************************************/

BOOL JiuYinWork::Click(HWND hwnd, LPTSTR pbuf)
{
	SYSTEMTIME serverTime;
	LeftClick(hwnd, 904 - 400, 137 - 30);
	Sleep(100);

	GetLocalTime(&serverTime);
	LeftClick(hwnd, 1130 - 400, 366 - 30);
	LeftClick(hwnd, 1130 - 400, 294 - 30);
	LeftClick(hwnd, 1130 - 400, 220 - 30);

	LeftClick(hwnd, 904 - 400, 137 - 30);
	Sleep(100);

	LeftClick(hwnd, 1130 - 400, 366 - 30);
	LeftClick(hwnd, 1130 - 400, 294 - 30);
	LeftClick(hwnd, 1130 - 400, 220 - 30);

	LeftClick(hwnd, 904 - 400, 137 - 30);
	Sleep(100);

	LeftClick(hwnd, 1130 - 400, 366 - 30);
	LeftClick(hwnd, 1130 - 400, 294 - 30);
	LeftClick(hwnd, 1130 - 400, 220 - 30);

	Data->SleepTime = 288;
	TCHAR  windowTitle[256];
	LPTSTR str2, str1, str3, str4;
	int fx, fy;
	//Sleep(100);
	//flag = 1;
	if (FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����1.bmp", 0x111111, 0.9, fx, fy)
		|| FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����2.bmp", 0x111111, 0.9, fx, fy)
		|| FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����.bmp", 0x111111, 0.9, fx, fy)){
		//MessageBox(NULL, L"11", L"11", 0);
		flag = 1;
		str2 = L"    ��ȡ������֮��";

	}
	else{
		str2 = L"û����ȡ������֮��";
		wsprintf(windowTitle, L"%s\n", pbuf);
		StrCat(accoutbuf, windowTitle);
	}

	if (FindPicEx(hwnd, 0, 0, 500, 500, L"ts\\����֮��.bmp", 0x101010, 0.8, fx, fy)){
		str1 = L"    ����֮��";
	}
	else{
		str1 = L"û������֮��";
	}


	//if (FindPicEx(hwnd, 500, 300, 1024, 768, L"ts\\�ر�.bmp", 0x101010, 0.9, fx, fy))
	//{
	//}

	LeftClick(hwnd, 740, 617);
	LeftClick(hwnd, 740, 617);
	Sleep(1000);

	if (FindPicEx(hwnd, 300, 300, 950,600, L"ts\\����.bmp", 0x101010, 0.9, fx, fy)){
		str3 = L"����";
	}
	else{
		str3 = L"����";
	}

	LeftClick(hwnd, 833, 45);
	Sleep(2500);
	//for (size_t i = 0; i < 11; i++)
	//{
	//	LeftClick(hwnd,149, 403);
	//	Sleep(20);
	//}
	//DWORD ret = TS->FindPic(0, 0, 200, 200, "��ü.bmp|����.bmp|����.bmp", "303030", 0.8, 0, &X, &Y) + 1;
	if (FindPicEx(hwnd, 30, 50, 100, 150, L"ts\\��ü.bmp", 0x050505, 1, fx, fy))
	{
		str4 = L"��ü";
	}
	else if (FindPicEx(hwnd, 30, 50, 100, 150, L"ts\\����.bmp", 0x050505, 1, fx, fy))
	{
		str4 = L"����";
	}
	else if (FindPicEx(hwnd, 30, 50, 100, 150, L"ts\\����.bmp", 0x050505, 1, fx, fy))
	{
		str4 = L"����";
	}
	else {
		str4 = L"����";
	}

	LeftClick(hwnd, 927, 46);
	Sleep(1000);


	wsprintf(windowTitle, L"%18s ʱ�䣺%4d/%02d/%02d  %02d:%02d:%02d.%03d  ����%1d %15s  %s  %s  %s  %s  \n",OldWindowText,
		serverTime.wYear, serverTime.wMonth, serverTime.wDay, serverTime.wHour, serverTime.wMinute,
		serverTime.wSecond, serverTime.wMilliseconds, serverTime.wDayOfWeek, pbuf, str1, str2, str3, str4);

	StrCat(logbuf, windowTitle);
	return true;
}




DWORD TimeIndex=0;
unsigned int __stdcall ThreadWork(void *param){

	JiuYinWork *work = (JiuYinWork *)param;

	//Sleep(5000);
	//POINT x;
	//GetCursorPos(&x);
	//HWND hwnd = WindowFromPoint(x);
	//work->DxBind(hwnd, 1);
	//int fx, fy;
	//BOOL ret1;
	//while (true)
	//{
	//	if (work->FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����1.bmp", 0x151515, 0.9, fx, fy)
	//		|| work->FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����2.bmp", 0x151515, 0.9, fx, fy)
	//		|| work->FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����.bmp", 0x151515, 0.9, fx, fy)){
	//		MessageBox(NULL, L"11", L"11", 0);
	//	}
	//	//ret1 = work->FindColorEx(hwnd,700, 400, 1024, 768, 0x00FF00, 0X101010,fx,fy);
	//	ret1 = work->FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����.bmp", 0x101010, 0.9, fx, fy);
	//	ret1 = work->FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����1.bmp", 0x101010,0.9, fx, fy);
	//	ret1 = work->FindPicEx(hwnd, 400, 400, 1024, 1024, L"ts\\����2.bmp", 0x101010,0.9, fx, fy);
	//	Sleep(10);
	//}

	if (pzAccount == NULL || pzNouseAccount == NULL)
	{
		MessageBox(NULL, L"�ļ���ʧ��", L"err", NULL);
	}

	SYSTEMTIME MySystemTime_y, MySystemTime_exit, MySystemTime_login;

	UINT64 myBaseTime;
	myBaseTime = ((UINT64)work->filetime.dwHighDateTime << 32) + work->filetime.dwLowDateTime;
	if (Button_GetState(GetDlgItem(work->myHwnd, IDC_CHECK_YANSHI)))
	{
		myBaseTime = myBaseTime + TimeIndex * GetDlgItemInt(work->myHwnd, IDC_EDIT_YANSHI, 0, 0) * (UINT64)10000000;
		TimeIndex++;
	}
	FILETIME getMoneyFileTime = *(LPFILETIME)&myBaseTime;
	FileTimeToSystemTime(&getMoneyFileTime, &MySystemTime_y);

	EnterCriticalSection(&g_cs);
	srand((int)time(0));
	DWORD randm_exit = (rand() % 100) + 150;
	DWORD randm_login = (rand() % 60) + 90;

	UINT64  uiBaseTime, MyFileTime_exit, MyFileTime_login;
	uiBaseTime = ((UINT64)work->filetime.dwHighDateTime << 32) + work->filetime.dwLowDateTime;
	MyFileTime_exit = uiBaseTime - randm_exit*(UINT64)10000000;
	FileTimeToSystemTime((LPFILETIME)&MyFileTime_exit, &MySystemTime_exit);
	MyFileTime_login = uiBaseTime - randm_login*(UINT64)10000000;
	FileTimeToSystemTime((LPFILETIME)&MyFileTime_login, &MySystemTime_login);

	
login:
	if (!work->GotoGameLoginWindow(iDaquIndex, iXiaoIndex))
	{
		goto login;
	}
	for (size_t i = 0; i < 20; i++)
	{
		work->SetWindowHwnd(FindWindow(L"FxMain", MYJIUYINXUANQU[iDaquIndex].mySmallQu[iXiaoIndex].pName));
		if (!work->GetWindowHwnd())
			Sleep(3 * 1000);
		else
		{
			Sleep(3 * 1000);
			break;
		}
	}
	int ret = GetWindowText(work->GetWindowHwnd(), work->OldWindowText, MAX_PATH);                    //����ԭ�����ڱ���
	if (!work->GetWindowHwnd())
		goto login;

	if (work->GetWindowHwnd())
	{
		Sleep(10000);
		work->DxBind(work->GetWindowHwnd(), 1);
		//POINT x;
		//GetCursorPos(&x);
		//WindowFromPoint(x);
		//while (true)
		//{

		//}
		TCHAR lpszBuffer[MAX_PATH];
		wsprintf(lpszBuffer, L"�˳� = %02d:%02d:%02d  ��¼ = %02d:%02d:%02d �� = %02d:%02d:%02d ", MySystemTime_exit.wHour, MySystemTime_exit.wMinute, MySystemTime_exit.wSecond,
			MySystemTime_login.wHour, MySystemTime_login.wMinute, MySystemTime_login.wSecond, MySystemTime_y.wHour, MySystemTime_y.wMinute, MySystemTime_y.wSecond);
		SetWindowText(work->hwnd, lpszBuffer);
	}
	LeaveCriticalSection(&g_cs);
	TCHAR buf[MAX_PATH];

	EnterCriticalSection(&g_cs1);
	GetLineFromFile(pzNouseAccount, buf);
	LeaveCriticalSection(&g_cs1);
	//int fx, fy;
	//int ret = FindPic(hwnd, "ts\\����.bmp", 0x020202, 0.9, fx, fy);
	work->GameLogin(work->hwnd, buf, L"1064671193k");

	//SYSTEMTIME cSysTime;
	//GetLocalTime(&cSysTime);


	FILETIME filetime;
	GetSystemTimeAsFileTime(&filetime);
	//if (1)
	//{
	//	work->YanWu(work->hwnd);
	//	work->ExitGameWindow(work->hwnd);										//���ص�¼����
	//}
	while ((((UINT64)filetime.dwHighDateTime << 32) + filetime.dwLowDateTime) + (UINT64)8 * 60 * 60 * 10000000 <= MyFileTime_exit)
	{
		GetSystemTimeAsFileTime(&filetime);

		//SYSTEMTIME test;
		//FileTimeToSystemTime((LPFILETIME)&MyFileTime_exit, &test);

		//FileTimeToSystemTime(&filetime, &test);
		//SetSystemTime(&cSysTime);
		if (flag == 1)
		{
			break;
		}
		Sleep(100);
	}

	work->ExitGameWindow(work->hwnd);										//���ص�¼����

	while ((((UINT64)filetime.dwHighDateTime << 32) + filetime.dwLowDateTime) + (UINT64)8 * 60 * 60*10000000 <= MyFileTime_login)
	{
		GetSystemTimeAsFileTime(&filetime);
		if (flag == 1)
		{
			break;
		}
		Sleep(100);
	}

	EnterCriticalSection(&g_cs1);
	GetLineFromFile(pzAccount, buf);
	LeaveCriticalSection(&g_cs1);

	work->GameLogin(work->hwnd, buf, L"1064671193k");



	while ((((UINT64)filetime.dwHighDateTime << 32) + filetime.dwLowDateTime) + (UINT64)8 * 60 * 60 * 10000000 <= myBaseTime)
	{
		GetSystemTimeAsFileTime(&filetime);
		if (flag == 1)
			break;
		Sleep(10);
	}

	work->Data->SleepTime = 60;
	work->Click(work->hwnd, buf);

	work->GetMoney(work->hwnd);

	return 0;
}


BOOL JiuYinWork::DxBind(HWND hwnd, int type)
{
	TCHAR Dll[MAX_PATH];
	TCHAR InjectDll[MAX_PATH];
	GetModuleFileName(NULL, Dll, _countof(Dll));
	PTSTR pDllname = _tcsrchr(Dll, TEXT('\\')) + 1;
	_tcscpy_s(pDllname, _countof(Dll) - (pDllname - Dll),
		TEXT("MemoryLoadDll.dll"));

	GetModuleFileName(NULL, InjectDll, _countof(InjectDll));
	PTSTR pInjectDllname = _tcsrchr(InjectDll, TEXT('\\')) + 1;
	_tcscpy_s(pInjectDllname, _countof(InjectDll) - (pInjectDllname - InjectDll),
		TEXT("InjectionDll.dll"));
	HMODULE hdll = LoadLibrary(InjectDll);
	if (type == 1)
	{
		typedef BOOL(*Fun)(DWORD, LPTSTR);
		Fun InjectLibW = NULL;
		InjectLibW = (Fun)GetProcAddress(hdll, "InjectLibW");
		printf("��������̴��ھ����\n");

		//HWND hwnd;
		//scanf_s("%d", &hwnd);
		DWORD pid;

		GetWindowThreadProcessId(hwnd, &pid);


		//pid = GetCurrentProcessId();

		//SIZE_T cchSize = lstrlenA(Dll) + 1;
		//PWSTR pszLibFileW = (PWSTR)
		//	_alloca(cchSize * sizeof(wchar_t));

		//// Convert the ANSI pathname to its Unicode equivalent
		//StringCchPrintfW(pszLibFileW, cchSize, L"%S", Dll);

		if (InjectLibW(pid, Dll)){
			printf("dllע��ɹ�");
		}
		else
		{
			printf("dllע��ʧ��");
			return 0;
		}
		Sleep(500);

		TCHAR ShareMemoryName[MAX_PATH];
		wsprintf(ShareMemoryName, L"ShareMemory_%d", pid);


		m_hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, ShareMemoryName);
		// ӳ�������ڴ棬ȡ�ù����ڴ���׵�ַ
		if (m_hFileMap == NULL)
		{
			return false;
		}
		m_pBuffer = (LPBYTE)MapViewOfFile(
			m_hFileMap,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			0
			);
		if (m_pBuffer == NULL)
		{
			return false;
		}
		//sm = new CShareMemory(ShareMemoryName, sizeof(ShareMap), FALSE);

		Data = (LPShareMap)m_pBuffer;
		if (Data == NULL)
		{
			printf("��ù����ڴ��ַʧ��\n");
			return 0;
		}
		else
		{
			Data->hwnd = hwnd;
			Data->SleepTime = 298;
		}
	}
	if (m_hFileMap != NULL)
	{
		CloseHandle(m_hFileMap);
	}
	return 1;

}





