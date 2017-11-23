#ifndef holeH
#define holeH
#include <windows.h>
#include <vector>
using namespace std;
class HOLE {
private:
	int x, y; // ���������� ������ ���������
	int R; // ������ ���������
	unsigned Color; // ���� ���������
public:
	HOLE(int x, int y, int R); // �����������
	int GetX(); // ��������� ���������� �
	int GetY(); // ��������� ���������� Y
	int IsPointInside(int x, int y); // ��������, ����� �� ����� ������
	void SetSize(int size); // �������� ������ ���������
	void MoveBy(int dx, int dy); // �������� ���������
	void Draw(HDC hDC); // ���������� ���������
	void Erase(HDC hDC); // ������� ���������
};
#endif