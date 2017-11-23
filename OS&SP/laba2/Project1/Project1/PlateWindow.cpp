#include "PlateWindow.h"
#include "Plate.h"
#include <math.h>
#include <gdiplus.h>
#include <algorithm>

#ifdef UNICODE
typedef std::wostringstream tstringstream;
#else
typedef std::ostringstream tstringstream;
#endif


HBITMAP blackKingBmp = NULL;
HBITMAP blackBishopBmp = NULL;
HBITMAP blackHorseBmp = NULL;
HBITMAP blackPawnBmp = NULL;
HBITMAP blackQueenBmp = NULL;
HBITMAP blackRookBmp = NULL;

HBITMAP whiteKingBmp = NULL;
HBITMAP whiteBishopBmp = NULL;
HBITMAP whiteHorseBmp = NULL;
HBITMAP whitePawnBmp = NULL;
HBITMAP whiteQueenBmp = NULL;
HBITMAP whiteRookBmp = NULL;

HBITMAP bgBmp = NULL;

HBITMAP boardBmp = NULL;

static PLATE Plate(512, 712); // объект-пластина

HBITMAP mLoadImg(WCHAR *szFilename)
{
	HBITMAP result = NULL;

	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(szFilename, false);
	bitmap->GetHBITMAP(NULL, &result);
	delete bitmap;
	return result;
}

void displayImage(HBITMAP mBmp, HWND mHwnd, RECT rect, int alpha)
{
	RECT myRect;
	BITMAP bm;
	HDC screenDC, memDC;
	HBITMAP oldBmp;
	BLENDFUNCTION bf;

	GetObject(mBmp, sizeof(bm), &bm);

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = alpha; // 0xff;

	bf.AlphaFormat = AC_SRC_ALPHA;

	screenDC = GetDC(mHwnd);
	GetClientRect(mHwnd, &myRect);

	if (mBmp == NULL) {
		//FillRect(screenDC, &myRect, WHITE_BRUSH);
	}
	else
	{
		memDC = CreateCompatibleDC(screenDC);
		oldBmp = (HBITMAP)SelectObject(memDC, mBmp);
		int w = rect.right > bm.bmWidth ? rect.right : bm.bmWidth;
		int h = rect.bottom > bm.bmHeight ? rect.bottom : bm.bmHeight;
		//int w = bm.bmWidth;
		//int h = bm.bmHeight;
		AlphaBlend(screenDC, rect.left, rect.top, w, h, memDC, 0, 0, bm.bmWidth, bm.bmHeight, bf);
		SelectObject(memDC, oldBmp);
		DeleteDC(memDC);
		ReleaseDC(mHwnd, screenDC);
	}
}

void displayText(HWND hwnd, LPCSTR text, RECT position) {
	HDC wdc = GetWindowDC(hwnd);
	SetTextColor(wdc, 0x00000000);
	SetBkMode(wdc, TRANSPARENT);
	DrawText(wdc, text, -1, &position, DT_SINGLELINE | DT_NOCLIP);
	DeleteDC(wdc);
}

enum FIGURE_TYPE
{
	KING,
	BISHOP,
	HORSE,
	PAWN,
	QUEEN,
	ROOK
};

enum FIGURE_COLOR
{
	WHITE,
	BLACK
};

HBITMAP getImageLinkByFigure(FIGURE_TYPE figureType, FIGURE_COLOR figureColor) {
	switch (figureType) {
	case KING: {
		return figureColor == WHITE ? whiteKingBmp : blackKingBmp;
	}
	case BISHOP: {
		return figureColor == WHITE ? whiteBishopBmp : blackBishopBmp;
	}
	case HORSE: {
		return figureColor == WHITE ? whiteHorseBmp : blackHorseBmp;
	}
	case PAWN: {
		return figureColor == WHITE ? whitePawnBmp : blackPawnBmp;
	}
	case QUEEN: {
		return figureColor == WHITE ? whiteQueenBmp : blackQueenBmp;
	}
	case ROOK: {
		return figureColor == WHITE ? whiteRookBmp : blackRookBmp;
	}
	default: {
		return whitePawnBmp;
	}
	}
}

RECT getPositionByFigure(FIGURE_TYPE figureType, FIGURE_COLOR figureColor) {
	RECT rect;
	int topPadding = 20;
	int leftPadding = 64;
	int multiplier = 0;
	if (figureColor == BLACK) {
		topPadding = 630;
	}
	switch (figureType) {
	case KING: {
		multiplier = 0;
		break;
	}
	case BISHOP: {
		multiplier = 1;
		break;
	}
	case HORSE: {
		multiplier = 2;
		break;
	}
	case PAWN: {
		multiplier = 3;
		break;
	}
	case QUEEN: {
		multiplier = 4;
		break;
	}
	case ROOK: {
		multiplier = 5;
		break;
	}
	}
	rect.left = leftPadding + 64 * multiplier;
	rect.top = topPadding;
	return rect;
}

class Figure {
private:
	int x, y;
	FIGURE_TYPE figureType;
	FIGURE_COLOR figureColor;
	HBITMAP image;
	bool changed;
	bool inDrag;
public:
	Figure() {
		x = 0;
		y = 0;
		figureType = PAWN;
		figureColor = WHITE;
		changed = true;
		image = getImageLinkByFigure(figureType, figureColor);
		inDrag = false;
	}
	Figure(int _x, int _y, FIGURE_TYPE _figureType, FIGURE_COLOR _figureColor) {
		x = _x;
		y = _y;
		figureType = _figureType;
		figureColor = _figureColor;
		changed = true;
		image = getImageLinkByFigure(figureType, figureColor);
		inDrag = false;
	}
	bool isPointInside(int mx, int my) {
		return x * 64 < mx && x * 64 + 64 > mx && y * 64 < my && y * 64 + 64 > my;
	}
	void draw(HWND hwnd) {
		RECT rect;
		if (!inDrag) {
			rect.top = 100 + y * 64;
			rect.left = x * 64;
		}
		else {
			rect.top = y;
			rect.left = x;
		}
		displayImage(image, hwnd, rect, inDrag ? 100 : 255);
		changed = false;
	}
	int getX() const{
		return x;
	}
	int getY() const {
		return y;
	}
	FIGURE_TYPE getType() const {
		return figureType;
	}
	FIGURE_COLOR getColor() const {
		return figureColor;
	}
	bool isChanged() {
		return changed;
	}
	void setPosition(int _x, int _y) {
		x = _x;
		y = _y;
		changed = true;
	}
	void setInDrag(bool value) {
		inDrag = value;
	}
	friend bool operator==(const Figure& left, const Figure& right);
};
inline bool operator==(const Figure& lhs, const Figure& rhs) {
	return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getType() == rhs.getType() && lhs.getColor() == rhs.getColor();
}

std::vector<Figure> figures;

Figure * getFigureUnderMouse(int x, int y) {
	for (std::vector<Figure>::iterator it = figures.begin(); it != figures.end(); ++it) {
		if (it->isPointInside(x, y)) {
			return &(*it);
		}
	}
	return NULL;
}

class Slot {
private:
	FIGURE_TYPE slotType;
	FIGURE_COLOR slotColor;
	int restCount, total;
	RECT position;
	bool changed;
	HBITMAP image;
	bool inDrag;
public:
	Slot() {
		slotType = PAWN;
		slotColor = WHITE;
		total = 8;
		restCount = 8;
		changed = true;
		image = getImageLinkByFigure(slotType, slotColor);
		inDrag = false;
	}
	Slot(FIGURE_TYPE figureType, FIGURE_COLOR figureColor, int _count) {
		slotType = figureType;
		slotColor = figureColor;
		total = _count;
		restCount = _count;
		image = getImageLinkByFigure(slotType, slotColor);
		position = getPositionByFigure(figureType, figureColor);
		changed = true;
		inDrag = false;
	}
	FIGURE_TYPE getType() {
		return slotType;
	}
	FIGURE_COLOR getColor() {
		return slotColor;
	}
	int getTotal() {
		return total;
	}
	int getRestCount() {
		return restCount;
	}
	bool isPointInside(int x, int y) {
		return position.left < x && position.left + 64 > x && position.top < y && position.top + 64 > y;
	}
	void setPosition(RECT rect) {
		position = rect;
		changed = true;
	}
	RECT getPosition() {
		return position;
	}
	void draw(HWND hwnd) {
		displayImage(image, hwnd, position, 255);
		
		if (!inDrag) {
			char buffer[20];
			_itoa_s(restCount, buffer, 20, 10);
			LPCSTR p = buffer;
			RECT textPos;
			textPos.left = position.left + 28;
			textPos.top = position.top + 60;
			displayText(hwnd, p, textPos);
		}

		changed = false;
	}
	bool isChanged() {
		return changed;
	}
	void decrease() {
		restCount--;
	}
	void increase() {
		restCount++;
	}
	void setInDrag(bool value) {
		inDrag = value;
	}
};

Slot slots[12] = {};

Slot * getSlotUnderMouse(int x, int y) {
	for (int i = 0; i < 12; i++) {
		if (slots[i].isPointInside(x, y) && slots[i].getRestCount() > 0) {
			return &slots[i];
		}
	}
	return NULL;
}

Slot * draggedSlot = NULL;

Figure * draggedFigure = NULL;

void decreaseQuantityOf(FIGURE_TYPE ft, FIGURE_COLOR fc) {
	for (int i = 0; i < 12; i++) {
		if (slots[i].getType() == ft && slots[i].getColor() == fc) {
			slots[i].decrease();
		}
	}
}

void increaseQuantityOf(FIGURE_TYPE ft, FIGURE_COLOR fc) {
	for (int i = 0; i < 12; i++) {
		if (slots[i].getType() == ft && slots[i].getColor() == fc) {
			slots[i].increase();
		}
	}
}

bool hasChangedSlots() {
	for (int i = 0; i < 12; i++) {
		if (slots[i].isChanged()) {
			return true;
		}
	}
	for (std::vector<Figure>::iterator it = figures.begin(); it != figures.end(); ++it) {
		if (it->isChanged()) {
			return true;
		}
	}

	if (draggedSlot != NULL && draggedSlot->isChanged()) {
		return true;
	}

	if (draggedFigure != NULL && draggedFigure->isChanged()) {
		return true;
	}
	return false;
}

void drawSlots(HWND hwnd) {

	for (int i = 0; i < 12; i++) {
		if (slots[i].getRestCount() > 0) {
			slots[i].draw(hwnd);
		}
	}
}

void drawBoard(HWND hwnd) {
	RECT top;
	top.top = 0;
	top.left = 0;
	top.right = 512;
	top.bottom = 100;

	displayImage(bgBmp, hwnd, top, 255);

	RECT rect;
	rect.top = 100;
	rect.left = 0;

	displayImage(boardBmp, hwnd, rect, 255);

	RECT bottom;
	bottom.top = 612;
	bottom.left = 0;
	bottom.right = 512;
	bottom.bottom = 712;

	displayImage(bgBmp, hwnd, bottom, 255);
}

void drawFigures(HWND hwnd) {
	for (std::vector<Figure>::iterator it = figures.begin(); it != figures.end(); ++it) {
		it->draw(hwnd);
	}
}

void drawDragged(HWND hwnd) {
	if (draggedSlot != NULL && draggedSlot->isChanged()) {
		draggedSlot->draw(hwnd);
	}
	if (draggedFigure != NULL && draggedFigure->isChanged()) {
		draggedFigure->draw(hwnd);
	}
}

void draw(HWND hWnd, bool force) {
	if (hasChangedSlots() || force) {
		drawBoard(hWnd);
		drawSlots(hWnd);
		drawFigures(hWnd);
		drawDragged(hWnd);
	}
}

bool isMouseOverBoard(int x, int y) {
	return y > 100 && y < 612;
}

int RegisterPlateWindow()
{
	WNDCLASS wcl;
	wcl.hInstance = GetModuleHandle(NULL);
	wcl.lpszClassName = "PlateWindowClass";
	wcl.lpfnWndProc = PlateWindowProc;
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpszMenuName = NULL;
	wcl.hIcon = NULL;
	wcl.hCursor = LoadCursor(NULL, IDC_CROSS);
	wcl.hbrBackground = (HBRUSH)(1 + COLOR_WINDOW);
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	return RegisterClass(&wcl);
}
// Оконная функция внутреннего окна
LRESULT CALLBACK PlateWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Статические локальные переменные, необходимые для работы оконной функции
	static int LastX, LastY; // последние координаты мыши
	static enum { NO_OPERATION, CHANGE_SIZE, CHANGE_POS } Mode; // режим работы с объектами
																// извлечь параметры сообщений манипулятора "мышь"	
	MouseState ms;
	ExtractMouseParams(wParam, lParam, &ms);
	switch (uMsg)
	{
	case WM_ERASEBKGND:
		return 1;
	case WM_CREATE: {
		blackKingBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\black_king.png");
		blackBishopBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\black_bishop.png");
		blackHorseBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\black_horse.png");
		blackPawnBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\black_pawn.png");
		blackQueenBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\black_queen.png");
		blackRookBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\black_rook.png");

		whiteKingBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\white_king.png");
		whiteBishopBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\white_bishop.png");
		whiteHorseBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\white_horse.png");
		whitePawnBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\white_pawn.png");
		whiteQueenBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\white_queen.png");
		whiteRookBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\white_rook.png");

		boardBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\board.bmp");
		bgBmp = mLoadImg(L"e:\\study\\OS&SP\\laba2\\bg.png");

		slots[0] = Slot(KING, BLACK, 1);
		slots[1] = Slot(BISHOP, BLACK, 2);
		slots[2] = Slot(HORSE, BLACK, 2);
		slots[3] = Slot(PAWN, BLACK, 8);
		slots[4] = Slot(QUEEN, BLACK, 1);
		slots[5] = Slot(ROOK, BLACK, 2);
		slots[6] = Slot(KING, WHITE, 1);
		slots[7] = Slot(BISHOP, WHITE, 2);
		slots[8] = Slot(HORSE, WHITE, 2);
		slots[9] = Slot(PAWN, WHITE, 8);
		slots[10] = Slot(QUEEN, WHITE, 1);
		slots[11] = Slot(ROOK, WHITE, 2);

		break;
	}
	case WM_PAINT:
	{
		draw(hWnd, false);
		break;
	}
	case WM_LBUTTONDOWN: // нажатие левой кнопки манипулятора "мышь"
						 // создаем объект и начинаем менять его размер
	{
		Slot * slot = getSlotUnderMouse(ms.xPos, ms.yPos);
		if (slot != NULL) {
			draggedSlot = new Slot(slot->getType(), slot->getColor(), slot->getTotal());
			draggedSlot->setInDrag(true);
			break;
		}
		Figure * figure = getFigureUnderMouse(ms.xPos, ms.yPos - 100);
		if (figure != NULL) {
			draggedFigure = new Figure(ms.xPos / 64, (ms.yPos - 100) / 64, figure->getType(), figure->getColor());
			draggedFigure->setInDrag(true);
			std::vector<Figure>::iterator newEnd = std::remove(figures.begin(), figures.end(), *figure);
			figures.erase(newEnd, figures.end());
		}
		break;
	}
	case WM_MOUSEMOVE: // перемещение манипулятора "мышь"
	{
		if (draggedSlot != NULL) {
			RECT rect;
			rect.top = ms.yPos - 32;
			rect.left = ms.xPos - 32;
			draggedSlot->setPosition(rect);
			draw(hWnd, false);
			break;
		}
		if (draggedFigure != NULL) {
			draggedFigure->setPosition(ms.xPos - 32, ms.yPos - 32);
			draw(hWnd, false);
		}
		break;
	}
	case WM_LBUTTONUP: {
		if (isMouseOverBoard(ms.xPos, ms.yPos)) {
			if (draggedSlot != NULL) {
				Figure * figure = getFigureUnderMouse(ms.xPos, (ms.yPos - 100));
				if (figure == NULL) {
					figures.push_back(Figure(ms.xPos / 64, (ms.yPos - 100) / 64, draggedSlot->getType(), draggedSlot->getColor()));
					decreaseQuantityOf(draggedSlot->getType(), draggedSlot->getColor());
				}
			}
			if (draggedFigure != NULL) {
				Figure * figure = getFigureUnderMouse(ms.xPos, (ms.yPos - 100));
				if (figure == NULL) {
					figures.push_back(Figure(ms.xPos / 64, (ms.yPos - 100) / 64, draggedFigure->getType(), draggedFigure->getColor()));
				}
				else {
					increaseQuantityOf(draggedFigure->getType(), draggedFigure->getColor());
				}
			}
		}
		else {
			if (draggedFigure != NULL) {
				increaseQuantityOf(draggedFigure->getType(), draggedFigure->getColor());
			}
		}
		draggedFigure = NULL;
		draggedSlot = NULL;
		draw(hWnd, true);
		break;
	}
	case WM_MBUTTONUP: 
	{
		break;
	}
	case WM_RBUTTONUP: // отпустили правую кнопку
	{
		if (isMouseOverBoard(ms.xPos, ms.yPos)) {
			Figure * figure = getFigureUnderMouse(ms.xPos, (ms.yPos - 100));
			if (figure != NULL) {
				increaseQuantityOf(figure->getType(), figure->getColor());		

				std::vector<Figure>::iterator newEnd = std::remove(figures.begin(), figures.end(), *figure);
				figures.erase(newEnd, figures.end());
			}
		}
		draw(hWnd, true);
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
// функция для анализа параметров сообщений манипулятора "мышь"
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