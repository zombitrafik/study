#include <iostream>
#include "stdafx.h"
#include <windows.h>
#include <cstring>
#include <clocale>
using namespace std;

#define THREADS_NUMBER 10
#define ITERATIONS_NUMBER 100
#define PAUSE 10 /* ms */

DWORD dwCounter = 0;
CONST HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
TCHAR szMessage[256];
DWORD dwTemp, i;
char alfha[] = "aouiey";


struct threadproc {
	HANDLE hMutex;
	DWORD start;
	DWORD finish;
	char *str;
};

DWORD WINAPI ThreadProc(CONST LPVOID lpParam) {
	threadproc *args = (threadproc*)lpParam;
	CONST HANDLE hMutex = args->hMutex;
	DWORD start = args->start;
	DWORD finish = args->finish;
	char *str = args->str;
	DWORD i;
	for (i = start; i < finish; i++) {
		if (strchr(alfha, str[i])) {
			WaitForSingleObject(hMutex, INFINITE);
			dwCounter++;
			wsprintf(szMessage, TEXT("Character = %c\r\n"), str[i]);
			WriteConsole(hStdOut, szMessage, lstrlen(szMessage), &dwTemp, NULL);
			ReleaseMutex(hMutex);
			Sleep(PAUSE);
		}

	}
	ExitThread(0);
}

VOID Error(CONST HANDLE hStdOut, CONST LPCWSTR szMessage) {
	DWORD dwTemp;
	TCHAR szError[256];
	WriteConsole(hStdOut, szMessage, lstrlen(szMessage), &dwTemp, NULL);
	wsprintf(szError, TEXT("LastError = %d\r\n"), GetLastError());
	WriteConsole(hStdOut, szError, lstrlen(szError), &dwTemp, NULL);
	ExitProcess(0);
}

INT main() {
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);
	char str[] = "ssedfwefwefwaayy edfwdcfedf";
	HANDLE hThreads[THREADS_NUMBER];

	CONST HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);
	if (NULL == hMutex) {
		Error(hStdOut, TEXT("Failed to create mutex.\r\n"));
	}
	DWORD count = strlen(str) / THREADS_NUMBER;
	threadproc arg[THREADS_NUMBER];
	for (i = 0; i < THREADS_NUMBER; i++) {
		arg[i].hMutex = hMutex;
		arg[i].start = i * count;
		arg[i].str = str;
		if (i == THREADS_NUMBER - 1)
			arg[i].finish = strlen(str);
		else
			arg[i].finish = i * count + count;

		hThreads[i] = CreateThread(NULL, 0, ThreadProc, &arg[i], 0, NULL);
		if (NULL == hThreads[i]) {
			Error(hStdOut, TEXT("Failed to create thread.\r\n"));
		}
	}

	WaitForMultipleObjects(THREADS_NUMBER, hThreads, TRUE, INFINITE);
	wsprintf(szMessage, TEXT("Counter = %d\r\n"), dwCounter);
	WriteConsole(hStdOut, szMessage, lstrlen(szMessage), &dwTemp, NULL);

	for (i = 0; i < THREADS_NUMBER; i++) {
		CloseHandle(hThreads[i]);
	}
	CloseHandle(hMutex);
	system("pause");
}