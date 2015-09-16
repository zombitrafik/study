#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <array>

std::array<float, 2> T1(int a1, int a2, int b1, int b2, int c1, int c2);

int main() {
	int a1, a2, b1, b2, c1, c2;
	std::cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;
	std::array<float, 2> a;
	a = T1(a1, a2, b1, b2, c1, c2);
	std::cout << a[0] << ";" << a[1];
	std::cin >> a1;
	return 0;
}

std::array<float, 2> T1(int a1, int a2, int b1, int b2, int c1, int c2) {
	float x = (a1 + c1) / 2.0,
		  y = (a2 + c2) / 2.0;
	float d1 = x * 2 - b1,
		  d2 = y * 2 - b2;

	std::array<float, 2> arr;
	arr[0] = d1;
	arr[1] = d2;
	return arr;
}