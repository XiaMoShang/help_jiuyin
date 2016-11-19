
#include<Windows.h>
#include <tchar.h>
#include "stdio.h"
#include "tlhelp32.h"

BOOL  EnableDebugPrivilege();
void MyTerminateProcess(LPCTSTR lpProcessName);