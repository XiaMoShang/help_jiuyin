#include"TerminateProcess.h"

BOOL  EnableDebugPrivilege()
{
	HANDLE hToken;
	BOOL fOk = FALSE;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) //Get Token
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))//Get Luid
			printf("Can't lookup privilege value.\n");
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;//��һ��ܹؼ����޸�������ΪSE_PRIVILEGE_ENABLED
		if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))//Adjust Token
			printf("Can't adjust privilege value.\n");
		fOk = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	return fOk;
}

void MyTerminateProcess(LPCTSTR lpProcessName)
{
	//�������̿���
	EnableDebugPrivilege();
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe32 = { 0 };
		pe32.dwSize = sizeof(pe32);

		//�õ���һ��������Ϣ
		if (!Process32First(hSnapshot, &pe32))
		{
			CloseHandle(hSnapshot);
			return;
		}
		do
		{
			int nLen = _tcslen(lpProcessName);
			int nLen2 = _tcslen(pe32.szExeFile);
			if (nLen != nLen2)
			{
				continue;
			}
			if (_tcscmp(lpProcessName, pe32.szExeFile) == 0)
			{
				//return pe32.th32ProcessID;
				HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
				TerminateProcess(hProcess, 0);//�رս���
				Sleep(100);
			}
		} while (Process32Next(hSnapshot, &pe32));
	}
	return;
}