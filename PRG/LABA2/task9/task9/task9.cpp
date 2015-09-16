#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

float T1(int s, int d1, int d2);

int main() {
	int s, d1, d2;
	std::cin >> s >> d1 >> d2;
	std::cout << T1(s, d1, d2);
	std::cin >> s;
	return 0;
}

float T1(int s, int d1, int d2) {
	float a1 = (2 * s) / ((d1 * d2) * 1.0);
	a1 = asin(a1) * 180 / M_PI;
	float a2 = 180 - a1;
	float c1 = sqrt((d1 / 2.0)*(d1 / 2.0) + (d2 / 2.0)*(d2 / 2.0) - 2 * (d1 / 2.0)*(d2 / 2.0)*cos(a1));
	float c2 = sqrt((d1 / 2.0)*(d1 / 2.0) + (d2 / 2.0)*(d2 / 2.0) - 2 * (d1 / 2.0)*(d2 / 2.0)*cos(a2));
	return (c1 + c2) * 2;
	// return (d1*d1 + d2*d2) / 2.0;
}