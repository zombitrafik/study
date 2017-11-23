#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void firstTask() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Start the child process. 
	if (!CreateProcess(TEXT("C:\\Program Files\\Microsoft Office\\Office16\\EXCEL.EXE"),   // module name (use command line)
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	printf("pid = %d\r\n", pi.dwProcessId);
	printf("HANDLE = %d\r\n", pi.hProcess);
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void secondTask() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char bff[512];
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	LPTSTR szCmdline = _tcsdup(TEXT("C:\\Program Files\\WinRAR\\WinRAR.exe E:\\downloads\\bin.zip"));

	// Start the child process. 
	if (!CreateProcess(NULL,   // module name (use command line)
		szCmdline,        // Command line argv[1]
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	printf("pid = %d\r\n", pi.dwProcessId);
	printf("HANDLE = %d\r\n", pi.hProcess);
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void thirdTask() {
	ShellExecute(NULL,
		TEXT("open"),
		TEXT("D:\\projects\\pos_new\\Client\\app\\image\\add-picture.png"),
		NULL,
		NULL, 
		SW_SHOW);
}
void _tmain(int argc, TCHAR *argv[])
{
	thirdTask();
	system("pause");
}
