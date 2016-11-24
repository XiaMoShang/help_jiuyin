

#include"GetNetTime.h"

using namespace std;

//NTP服务器列表
struct NISTSVR{
	int     key;	//编号
	in_addr addr;	//IP地址
	LPCTSTR server;	//域名
	LPCTSTR info;	//信息
}
NISTSVRSARY[] = {
	{ 0, { 202, 112, 26, 37 }, L"s2g.time.edu.cn", L"华东南地区网络中心" },
	{ 1, { 129, 6, 15, 29 }, _T("time-b.nist.gov"), _T("NIST，盖士堡，马里兰州") },
	{ 2, { 202, 112, 7, 13 }, _T("s2m.time.edu.cn"), _T("北京大学") },	
	{ 3, { 132, 163, 4, 101 }, _T("time-a.timefreq.bldrdoc.gov"), _T("NIST，博耳德市，科罗拉多州") },
	{ 4, { 132, 163, 4, 102 }, _T("time-b.timefreq.bldrdoc.gov"), _T("NIST，博耳德市，科罗拉多州") },
	{ 5, { 132, 163, 4, 103 }, _T("time-c.timefreq.bldrdoc.gov"), _T("NIST，博耳德市，科罗拉多州") },
	{ 7, { 192, 43, 244, 18 }, _T("time.nist.gov"), _T("NCAR，博耳德市，科罗拉多州") },
	{ 8, { 131, 107, 1, 10 }, _T("time-nw.nist.gov"), _T("Microsoft，雷蒙德，华盛顿州") },
};

//所选择的NTP服务器
//static int choice = 0;

//void usage()
//{
//	printf("\n\t----------------------------------------------\n");
//	printf("\t=*= Time Getter v1.0 \t(qsilence@sina.com) =*=\n");
//	printf("\t----------------------------------------------\n\n");
//
//	int l = _countof(NISTSVRSARY);
//	for (int i = 1; i< l; i++){
//		printf("    %d. %s [%s] %s \r\n", NISTSVRSARY[i].key, NISTSVRSARY[i].server,
//			inet_ntoa(NISTSVRSARY[i].addr), NISTSVRSARY[i].info);
//	}
//}

BOOL UpdateSysTime(DWORD dwTime)
{
	UINT64 uiCurTime, uiBaseTime, uiResult;
	SYSTEMTIME systime;
	
	uiBaseTime = ((UINT64)HIGHTIME << 32) + LOWTIME;

	uiCurTime = (UINT64)dwTime * (UINT64)10000000;
	uiResult = uiBaseTime + uiCurTime;
	FileTimeToSystemTime((LPFILETIME)&uiResult, &systime);

	return SetSystemTime(&systime);
}

BOOL GetTimeFromServer(DWORD *lpdwTime)
{
	*lpdwTime = 0;
	BOOL bReturn = FALSE;
	for (size_t i = 0; i < 6; i++)
	{
		SOCKET sSock = socket(AF_INET, SOCK_STREAM, 0);
		DWORD err = GetLastError();
		if (INVALID_SOCKET != sSock)
		{
			struct sockaddr_in sin;

			memcpy(&sin.sin_addr, &NISTSVRSARY[i].addr, sizeof(in_addr));
			sin.sin_family = AF_INET;
			sin.sin_port = htons(IPPORT_TIMESERVER);

			//printf("\n    ...Waiting Connection...\n");

			if (0 == connect(sSock, (struct sockaddr *) &sin, sizeof(struct sockaddr_in)))
			{
				//printf("    ***Connected***\n");
				int iResult, iRead;

				for (iRead = 0; iRead < 4; iRead += iResult)
				{
					iResult = recv(sSock, (char*)lpdwTime + iRead, 4 - iRead, 0);
					if (iResult < 1)
						break;
				}

				if (4 == iRead)
				{
					*lpdwTime = ntohl(*lpdwTime);

					bReturn = TRUE;
					closesocket(sSock);
					break;
				}
				else
					printf("    Error getting time!\n");
			}
			else
				printf("    ***Connection Failed***\n");


			closesocket(sSock);
		}
	}
	return bReturn;
}

BOOL ServerTimeToSysTime(SYSTEMTIME *systime)
{
	WSADATA WSAData;
	DWORD dwTime;
	if (WSAStartup(MAKEWORD(1, 1), &WSAData) != 0)
	{
		//printf("WSAStartup failed.\n");
		WSACleanup();
	}
	//取服务器时间
	if (GetTimeFromServer(&dwTime))
	{
		UINT64 uiCurTime, uiBaseTime, uiResult;

		uiBaseTime = ((UINT64)HIGHTIME << 32) + LOWTIME;

		uiCurTime = ((UINT64)dwTime)*(UINT64)10000000;
		uiResult = uiBaseTime + uiCurTime;

		return FileTimeToSystemTime((LPFILETIME)&uiResult, systime);
	}
	WSACleanup();

	return 0;
}
