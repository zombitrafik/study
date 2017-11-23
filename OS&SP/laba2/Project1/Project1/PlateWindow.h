#include <windows.h>
#pragma hdrstop
#ifndef PlateWindowH
#define PlateWindowH
// �������� � ����������� ������ ���� "��������"
int RegisterPlateWindow();
// ������� ������� ����� ����
LRESULT CALLBACK PlateWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// ��������� ��� ������� ���������� ��������� ������������ "����"
typedef struct {
	int xPos, // ���������� ��������� ����
		yPos;
	int lButtonPressed, // ��������� ������ ����
		rButtonPressed,
		mButtonPressed;
	int shiftPressed, // ��������� ������ ��������
		controlPressed;
} MouseState;
// ������� ��� ������� ���������� ��������� ������������ "����"
void ExtractMouseParams(WPARAM wParam, LPARAM lParam, MouseState * ms);
#endif