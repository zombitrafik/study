#pragma once
#include "stdafx.h"
class Object {
private:
	int x, y;
	int size = 128;
	LPWSTR imageSource;
	LPWSTR applicationSource;
public:
	Object(int x, int y, LPWSTR imageSource, LPWSTR applicationSource) {
		this->x = x;
		this->y = y;
		this->imageSource = imageSource;
		this->applicationSource = applicationSource;
	}

	void setApplicationSource(LPWSTR path) {
		this->applicationSource = path;
	}
	BOOL Draw(HDC hWinDc) {
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, imageSource, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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

		BitBlt(hWinDc, this->x, this->y, qBitmap.bmWidth, qBitmap.bmHeight, hLocalDC, 0, 0, SRCCOPY);
		SelectObject(hLocalDC, hOldBmp);
		DeleteDC(hLocalDC);
		DeleteObject(hBitmap);
	}
	BOOL isPointInside(int posX, int posY) {
		if ((this->x<posX && (this->x + size)>posX) && (this->y<posY && (this->y + size)>posY)) {

			return true;

		}
		else {
			return false;
		}
	}
	void StartApplication() {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		ZeroMemory(&pi, sizeof(pi));
		si.cb = sizeof(si);
		CreateProcess(this->applicationSource, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	}
};
typedef struct {
	int xPos,
		yPos;
	int lButtonPressed,
		rButtonPressed,
		mButtonPressed;
	int shiftPressed,
		controlPressed;
} MouseState;