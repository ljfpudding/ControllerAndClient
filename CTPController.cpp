// CTPController.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <time.h>


int main(int argc, char *argv[])
{
	printf("main start.\n");

	HANDLE hendEvent = NULL;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	hendEvent = CreateEvent(&sa, FALSE, FALSE, NULL);

	TCHAR        lpHandle[20];
	memset(lpHandle, 0, sizeof(lpHandle));
	wsprintf(lpHandle, _T("%X"), hendEvent);


	HANDLE hTimeHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	SECURITY_ATTRIBUTES saProcess, saThread;

	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = TRUE;

	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = TRUE;

	while (TRUE)
	{
		time_t nowtime;
		nowtime = time(NULL); //��ȡ����ʱ��  		
		struct tm local;
		localtime_s(&local, &nowtime);  //��ȡ��ǰϵͳʱ�� 

		switch (local.tm_hour)
		{
		case 21:
			if (local.tm_min == 20)
			{
				BOOL bResult = ::CreateProcess(_T("�����ڻ�����ϵͳ.exe"), lpHandle, &saProcess, &saThread, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
				if (!bResult)
				{
					printf("20 CreateProcess Failed.\n");
					WaitForSingleObject(hTimeHandle, 1000 * 60 * 5);
				}
				printf("20 CreateProcess Successful.\n");
				WaitForSingleObject(hTimeHandle, 1000 * 60 * 5);
			}

			if (local.tm_min == 30)
			{
				SetEvent(hendEvent);//��ֹ�ӽ���
				printf("300 SetEvent\n");
				WaitForSingleObject(hTimeHandle, 1000 * 60 * 5);
			}

			if (local.tm_min == 40)
			{
				BOOL bResult = ::CreateProcess(_T("�����ڻ�����ϵͳ.exe"), lpHandle, &saProcess, &saThread, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
				if (!bResult)
				{
					printf("40 CreateProcess Failed.\n");
					WaitForSingleObject(hTimeHandle, 1000 * 60 * 5);
				}
				printf("40 CreateProcess Successful.\n");
				WaitForSingleObject(hTimeHandle, 1000 * 60 * 5);
			}

			if (local.tm_min == 50)
			{
				SetEvent(hendEvent);//��ֹ�ӽ���
				printf("300 SetEvent\n");
				WaitForSingleObject(hTimeHandle, 1000 * 60 * 5);
			}

			break;

		default:
			break;
		}		
	}
	
	printf("CTP Controller END \n");
	return 0;


}

