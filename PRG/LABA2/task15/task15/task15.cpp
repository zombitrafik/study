#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <array>

float T1(int a1, int a2, int a3, int b1, int b2, int b3);

int main() {
	int a1, a2, a3, b1, b2, b3;
	std::cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
	std::cout << acos(T1(a1, a2, a3, b1, b2, b3)) * 180.0 / M_PI;
	std::cin >> a1;
	return 0;
}

float T1(int a1, int a2, int a3, int b1, int b2, int b3) {
	return ((a1 * b1 + a2 * b2 + a3 * b3) / ((sqrt(a1 * a1 + a2 * a2 + a3 * a3) * sqrt(b1 * b1 + b2 * b2 + b3 * b3)) * 1.0));
}