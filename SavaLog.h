///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<Windows.h>
#include<fstream>
#include<string>
#include<atlconv.h>

extern CRITICAL_SECTION g_cs1;
//#define READ_MODE_GETLINE     1
//#define READ_MODE_ALLFILE     2

#define SAVELOG_H

using namespace std;
DWORD SaveLog(LPTSTR pSavePathName, LPTSTR pLogText);

DWORD ReadLog(LPTSTR pSavePathName, LPTSTR pLogText);
LPTSTR ReadAllLog(LPTSTR pSavePathName);


BOOL GetLineFromFile(TCHAR* &buf, LPTSTR str);
DWORD DelFirstLine(LPTSTR pSavePathName, LPTSTR pReadText);
DWORD CopyFile(LPTSTR pFilePathName, LPTSTR pSavePathName);

