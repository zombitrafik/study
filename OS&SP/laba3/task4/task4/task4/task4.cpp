// lab34.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "task4.h"
#include <vector>
#include "Object.h"
using namespace std;
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HBITMAP hBitmap = NULL;
Object *calc;
Object * chrome;
Object *fireFox;
static vector<Object*> listObj;
void ExtractMouseParams(WPARAM wParam, LPARAM lParam, MouseState * ms);

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL LoadAndBlitBitmap(LPCWSTR fileName, HDC hWinDc, int x, int y);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TASK4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	calc = new Object(0, 0,
		L"E:\\study\\OS&SP\\laba3\\task4\\ws.bmp",
		L"C:\\Program Files\\JetBrains\\WebStorm 2017.1.4\\bin\\webstorm.exe");
	chrome = new Object(128, 0, L"E:\\study\\OS&SP\\laba3\\task4\\ch.bmp",
		L"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe");
	fireFox = new Object(256, 0, L"E:\\study\\OS&SP\\laba3\\task4\\tc.bmp",
		L"C:\\Program Files (x86)\\Total Commander\\totalcmd.exe");

	listObj.push_back(calc);
	listObj.push_back(chrome);
	listObj.push_back(fireFox);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASK4));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASK4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_LAB34);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 400, 160, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	MouseState ms;
	ExtractMouseParams(wParam, lParam, &ms);

	switch (message)
	{
	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		//LoadAndBlitBitmap(L"C:\\Users\\KOMMANDE01\\Documents\\Visual Studio 2017\\Projects\\lab3_4\\resources\\calcul.bmp", hdc,100,100);
		for (int i = 0; i < listObj.size(); i++) {
			listObj.at(i)->Draw(hdc);
		}
		//listObj.at(0)->Draw(hdc);

		//calc->Draw(hdc);
		//chrome->Draw(hdc);
		//fireFox->Draw(hdc);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONUP: {
		for (int i = 0; i < listObj.size(); i++) {
			if (listObj.at(i)->isPointInside(ms.xPos, ms.yPos)) {
				listObj.at(i)->StartApplication();
			}
		}
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
BOOL LoadAndBlitBitmap(LPCWSTR fileName, HDC hWinDc, int x, int y) {
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL) {
		MessageBox(NULL, L"Load failed", L"Error", MB_OK);
		return false;
	}
	HDC hLocalDC;
	hLocalDC = CreateCompatibleDC(hWinDc);
	if (hLocalDC == NULL) {
		MessageBox(NULL, L"CreateCompatableDc failed", L"Error", MB_OK);
		return false;
	}
	BITMAP qBitmap;
	int res = GetObject(hBitmap, sizeof(BITMAP), &qBitmap);

	if (!res) {
		MessageBox(NULL, L"GetObject failed", L"Error", MB_OK);
		return false;
	}

	HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
	if (hOldBmp = NULL) {
		MessageBox(NULL, L"Select object failed", L"Error", MB_OK);
		return false;
	}

	BitBlt(hWinDc, x, y, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
	SelectObject(hLocalDC, hOldBmp);
	DeleteDC(hLocalDC);
	DeleteObject(hBitmap);
}
// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
void ExtractMouseParams(WPARAM wParam, LPARAM lParam, MouseState * ms) {
	// извлечение координат указателя
	ms->xPos = LOWORD(lParam);
	ms->yPos = HIWORD(lParam);
	// анализ состояния кнопок и клавиш
	ms->lButtonPressed = (wParam & MK_LBUTTON) != 0;
	ms->rButtonPressed = (wParam & MK_RBUTTON) != 0;
	ms->mButtonPressed = (wParam & MK_MBUTTON) != 0;
	ms->shiftPressed = (wParam & MK_SHIFT) != 0;
	ms->controlPressed = (wParam & MK_CONTROL) != 0;
}