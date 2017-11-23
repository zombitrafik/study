#include <windows.h>
#include "PlateWindow.h"
#include <gdiplus.h>

#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0600       // needed for alphablend function..

// �������� ������� �������
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	static Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	static ULONG_PTR gdiplusToken;
	// so we can load all the image formats that windows supports natively - (I'm using a transparent PNG on the main dialog)
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// �������� ������ �������� ���� ����������
	WNDCLASS wcl;
	wcl.hInstance = hThisInst;
	wcl.lpszClassName = "MainWindowClass";
	wcl.lpfnWndProc = MainWindowProc;
	wcl.style = 0;
	wcl.lpszMenuName = NULL;
	wcl.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	// ����������� ������ �������� ���� ����������
	if (!RegisterClass(&wcl)) return 0;
	// �������� �������� ���� ����������
	HWND hWnd;
	hWnd = CreateWindow("MainWindowClass", "������ ��������� ���������",
		WS_OVERLAPPEDWINDOW, 0, 0, 572, 792, HWND_DESKTOP, NULL, hThisInst, NULL);
	ShowWindow(hWnd, nWinMode);
	UpdateWindow(hWnd);
	// ����������� ������ ����������� ����
	RegisterPlateWindow();
	// �������� ����������� ����
	CreateWindow("PlateWindowClass", "��������", WS_CHILD | WS_VISIBLE,
		20, 20, 512, 712, hWnd, NULL, hThisInst, NULL);
	// ���� ��������� ���������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return msg.wParam;
}
// ������� ������� �������� ���� ����������
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}