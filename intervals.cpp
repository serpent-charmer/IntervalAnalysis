#include "intervals.h"
#include <iostream>

#define DEBUG

int main() {

#ifdef DEBUG

	ian::Interval<double> a(1, 3);
	ian::Interval<double> b(-1, 5);

	ian::Interval<double> res;

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	res = b;
	std::cout << " = b:\t\t " << res << std::endl;

	res = a + b;
	std::cout << " a + b:\t\t " << res << std::endl;

	res = a - b;
	std::cout << " a-b:\t\t " << res << std::endl;

	res = a * b;
	std::cout << " a*b:\t\t " << res << std::endl;

	res = a / b;
	std::cout << " a/b:\t\t " << res << std::endl;

	res = a.concat(b);
	std::cout << " a concat b:\t " << res << std::endl;

	res = a.inters(b);
	std::cout << " a inters b:\t " << res << std::endl;

	std::cout << " wid(a):\t " << "(" << a.width() << ")" << std::endl;
	std::cout << " rad(a):\t " << "(" << a.radius() << ")" << std::endl;
	std::cout << " med(a):\t " << "(" << a.middle() << ")" << std::endl;
	std::cout << " abs(a):\t " << "(" << a.iabs() << ")" << std::endl;


	system("pause");


#endif //DEBUG


	return 0;
}