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
		return abs((a1 - b1) * (a1 - b1) * (a1 - b1));
	}
	if (a2 != b2) {
		return abs((a2 - b2) * (a2 - b2) * (a2 - b2));
	}
	if (a3 != b3) {
		return abs((a3 - b3) * (a3 - b3) * (a3 - b3));
	}
	return 0;
}