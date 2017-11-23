#include "Plate.h"
// конструктор
PLATE::PLATE(int width, int height) {
	this->width = width;
	this->height = height;
}
// нарисовать пластину и набор отверстий
void PLATE::Draw(HDC hDC) {
	// сначала рисуем пластину
	SelectObject(hDC, GetStockObject(WHITE_PEN));
	SelectObject(hDC, GetStockObject(WHITE_BRUSH));
	Rectangle(hDC, 0, 0, width, height);
}