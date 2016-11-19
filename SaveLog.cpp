
#include"SavaLog.h"


/********************************************************************************************************************************************
���ܣ����ļ�ĩβ����һ��
pSavePathName:Ҫд���ļ���·��
pLogText : Ҫд������ݵ����ݣ�
********************************************************************************************************************************************/

DWORD SaveLog(LPTSTR pSavePathName, LPTSTR pLogText)
{
	USES_CONVERSION;
	fstream out(W2A(pSavePathName), ios::app, _SH_DENYNO);
	if (!out){
		return GetLastError();
	}
	else
	{
		
		out.write(W2A(pLogText), strlen(W2A(pLogText)));
		out.close();
		return 0;
	}
}

/********************************************************************************************************************************************
���ܣ���ȡ�ļ���һ��
pSavePathName:Ҫ��ȡ�ļ���·��
pLogText : ���ض�ȡ�������ݣ�
********************************************************************************************************************************************/

DWORD ReadLog(LPTSTR pSavePathName, LPTSTR pLogText)
{
	wifstream in(pSavePathName, ios::in, _SH_DENYNO);
	if (!in){
		return 0;
	}
	else
	{
		in.getline(pLogText, 10240, '\n');
		in.close();
		return 1;

	}
	return 0;
}


/********************************************************************************************************************************************
���ܣ���ȡ�ļ���������
pSavePathName:Ҫ��ȡ�ļ���·��
********************************************************************************************************************************************/

LPTSTR ReadAllLog(LPTSTR pSavePathName)
{
	std::wifstream t;
	streamoff length;
	TCHAR *buffer;
	t.open(pSavePathName, ios::in, _SH_DENYNO);      // open input file  
	if (!t)
	{
		return NULL;
	}
	t.seekg(0, std::ios::end);    // go to the end  
	length = t.tellg();           // report location (this is the length)  
	t.seekg(0, std::ios::beg);    // go back to the beginning  

	if (length > 0)
	{
		buffer = new TCHAR[length];    // allocate memory for a buffer of appropriate dimension  
		if (buffer == NULL)
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
	
	memset(buffer, '\0', length);
	t.read(buffer, length);       // read the whole file into the buffer 

	t.close();                    // close file handle
	return buffer;
}


/********************************************************************************************************************************************
���ܣ���ȡ�ļ���һ�в���ɾ���ļ���һ��
pSavePathName:Ҫ��ȡ�ļ���·��
********************************************************************************************************************************************/

DWORD DelFirstLine(LPTSTR pSavePathName, LPTSTR pReadText)
{
	long  length;
	TCHAR *buffer;


	EnterCriticalSection(&g_cs1);
	
	wfstream inout(pSavePathName, ios::out | ios::in, _SH_DENYNO);
	if (!inout){
		LeaveCriticalSection(&g_cs1);
		return 0;
	}
	else
	{
		inout.getline(pReadText, 10240, '\n');
		inout.seekg(0, std::ios::end);    // go to the end  
		length = inout.tellg();           // report location (this is the length)  
		inout.seekg(0, std::ios::beg);    // go back to the beginning

		if (length > 0)
		{
			buffer = new TCHAR[length];    // allocate memory for a buffer of appropriate dimension  
			if (buffer == NULL)
			{
				inout.close();
				LeaveCriticalSection(&g_cs1);
				return 0;
			}
		}
		else
		{
			inout.close();
			LeaveCriticalSection(&g_cs1);
			return 0;
		}
		
		memset(buffer, '\0', length);
		inout.read(buffer, length);       // read the whole file into the buffer 
		if ((wstring)pReadText != L"end#")
		{
			for (size_t i = 0; i < length; i++)   //�ҵ���һ�����з�
			{
				if (*buffer == '\n'){
					buffer++;
					break;
				}
				buffer++;
			}
		}
		//
		wfstream out(pSavePathName, ios::out, _SH_DENYNO);
		if (!out){
			LeaveCriticalSection(&g_cs1);
			return 0;
		}
		else
		{
			out.write(buffer, lstrlen(buffer));
			out.close();
		}
		inout.close();

	}
	LeaveCriticalSection(&g_cs1);
	return 1;
}


/********************************************************************************************************************************************
���ܣ������ļ�
pSavePathName:Ҫ��ȡ�ļ���·��
********************************************************************************************************************************************/

DWORD CopyFile(LPTSTR pFilePathName, LPTSTR pSavePathName)
{
	streamoff length;
	char *buffer;
	fstream inout(pFilePathName, ios::out | ios::in, _SH_DENYNO);
	if (!inout){
		return 0;
	}
	else
	{
		inout.seekg(0, std::ios::end);    // go to the end  
		length = inout.tellg();           // report location (this is the length)  
		inout.seekg(0, std::ios::beg);    // go back to the beginning  
		if (length >0)
		{
			buffer = new char[length];    // allocate memory for a buffer of appropriate dimension  
			if (buffer == NULL)
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
		
		memset(buffer, '\0', length);
		inout.read(buffer, length);       // read the whole file into the buffer 
		
		fstream out(pSavePathName, ios::out, _SH_DENYNO);
		if (!out){
			return 0;
		}
		else
		{
			out.write(buffer, strlen(buffer));
			out.close();
		}
		inout.close();

	}
	return 1;
}



BOOL GetLineFromFile(TCHAR* &buf, LPTSTR str)
{
	while (*buf != '\n')
	{
		if (*buf == '#')
		{
			*str = '#';
			str++;
			*str = '\0';
			buf = buf - 3;
			return FALSE;
		}
		*str = *buf;
		str++;
		buf++;
	}
	buf++;
	*str = '\0';
	return TRUE;
}
