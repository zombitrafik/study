#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

float T1(int n, int a);

int main() {
	int a, n;
	std::cin >> n >> a;
	std::cout << T1(n, a);
	std::cin >> a;
	return 0;
}

float T1(int n, int a) {
	return a / (2 * tan(360 / (2 * n) * M_PI / 180));
}