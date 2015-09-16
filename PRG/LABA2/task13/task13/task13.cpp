#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <array>

int T1(int a1, int a2, int a3, int b1, int b2, int b3);

int main() {
	int a1, a2, a3, b1, b2, b3;
	std::cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
	std::cout << T1(a1, a2, a3, b1, b2, b3);
	std::cin >> a1;
	return 0;
}

int T1(int a1, int a2, int a3, int b1, int b2, int b3) {
	if (a1 != b1) {
		return ((a1 - b1) * (a1 - b1)) * 6;
	}
	if (a2 != b2) {
		return((a2 - b2) * (a2 - b2)) * 6;
	}
	if (a3 != b3) {
		return ((a3 - b3) * (a3 - b3)) * 6;
	}
	return 0;
}