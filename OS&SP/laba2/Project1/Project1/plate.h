#ifndef PlateH
#define PlateH
#include <windows.h>
#include <vector>
using namespace std;

class PLATE {
private:
	int width, height; // ������� ��������
public:
	PLATE(int width, int height); // �����������
	void Draw(HDC hDC); // ���������� �������� � �����������
};
#endif