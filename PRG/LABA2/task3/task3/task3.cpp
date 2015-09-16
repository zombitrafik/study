#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

float T1(int l1, int l2);

int main() {
	int l1, l2;
	std::cin >> l1 >> l2;
	std::cout << T1(l1, l2);
	std::cin >> l1;
	return 0;
}

float T1(int l1, int l2) {
	float r1 = l1 / (2 * M_PI),
		  r2 = l2 / (2 * M_PI);
	return ((M_PI * r1 * r1) - (M_PI * r2 * r2));
}