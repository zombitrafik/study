#include "Plate.h"
// �����������
PLATE::PLATE(int width, int height) {
	this->width = width;
	this->height = height;
}
// ���������� �������� � ����� ���������
void PLATE::Draw(HDC hDC) {
	// ������� ������ ��������
	SelectObject(hDC, GetStockObject(WHITE_PEN));
	SelectObject(hDC, GetStockObject(WHITE_BRUSH));
	Rectangle(hDC, 0, 0, width, height);
}