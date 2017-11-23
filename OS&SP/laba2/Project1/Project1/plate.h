#ifndef PlateH
#define PlateH
#include <windows.h>
#include <vector>
using namespace std;

class PLATE {
private:
	int width, height; // размеры пластины
public:
	PLATE(int width, int height); // конструктор
	void Draw(HDC hDC); // нарисовать пластину с отверстиями
};
#endif