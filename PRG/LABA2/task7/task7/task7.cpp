#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

float T1(int a, int d);

int main() {
	int a, d;
	std::cin >> a >> d;
	std::cout << T1(a, d);
	std::cin >> a;
	return 0;
}

float T1(int a, int d) {
	float d2 = sqrt((a * a) - ((d / 2.0) * (d / 2.0))) * 2;
	return (d2 * d) / 2.0;
}