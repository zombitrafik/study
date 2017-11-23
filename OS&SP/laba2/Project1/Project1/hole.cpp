#include "hole.h"
#include <math.h>
#include <stdlib.h>
#include <random>
// �����������
HOLE::HOLE(int x, int y, int R) {
	random_device rd;
	mt19937 gen(rd());
	this->x = x;
	this->y = y;
	this->R = R;
	this->Color = gen();
}
// ��������� ���������� �
int HOLE::GetX() {
	return x;
}
// ��������� ���������� Y
int HOLE::GetY() {
	return y;
}
// ��������, ����� �� ����� ������ ���������
int HOLE::IsPointInside(int x, int y) {
	if (pow(x - this->x, 2) + pow(y - this->y, 2) <= R*R) {
		return 1;
	}
	else {
		return 0;
	}
}
// �������� ������ ���������
void HOLE::SetSize(int size) {
	R = size;
}
// �������� ���������
void HOLE::MoveBy(int dx, int dy) {
	x += dx;
	y += dy;
}
// ���������� ���������
void HOLE::Draw(HDC hDC) {
	// �������� ����� GDI-��������,
	// �������� �� � �������� ����������,
	// ����������� �������� GDI-��������
	HPEN oldPen = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 1, Color));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, CreateSolidBrush(Color));
	Ellipse(hDC, x - R, y - R, x + R + 1, y + R + 1);
	// �������������� �������� GDI-��������,
	// �������� ����� ��������� GDI-��������
	DeleteObject(SelectObject(hDC, oldPen));
	DeleteObject(SelectObject(hDC, oldBrush));
}
// ������� ���������
void HOLE::Erase(HDC hDC) {
	// ������ ����� ������
	SelectObject(hDC, GetStockObject(WHITE_PEN));
	SelectObject(hDC, GetStockObject(WHITE_BRUSH));
	Ellipse(hDC, x - R, y - R, x + R + 1, y + R + 1);
}