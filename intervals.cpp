#include "intervals.h"
#include <iostream>

#define DEBUG

int main() {

#ifdef DEBUG

	Interval<double> a(1, 3);
	Interval<double> b(-1, 5);

	Interval<double> res;

	std::cout << "a(" << a.getLeft() << " , " << a.getRight() << ")" << std::endl;
	std::cout << "b(" << b.getLeft() << " , " << b.getRight() << ")" << std::endl;
	res = b;
	std::cout << " = b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << std::endl;

	res = a + b;
	std::cout << " a + b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << std::endl;

	res = a - b;
	std::cout << " a-b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << std::endl;

	res = a * b;
	std::cout << " a*b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << std::endl;

	res = a / b;
	std::cout << " a/b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << std::endl;

	res = a.concat(b);
	std::cout << " a concat b:\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << std::endl;

	res = a.inters(b);
	std::cout << " a inters b:\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << std::endl;

	std::cout << " wid(a):\t " << "(" << a.width() << ")" << std::endl;
	std::cout << " rad(a):\t " << "(" << a.radius() << ")" << std::endl;
	std::cout << " med(a):\t " << "(" << a.middle() << ")" << std::endl;
	std::cout << " abs(a):\t " << "(" << a.iabs() << ")" << std::endl;


	system("pause");


#endif //DEBUG


	return 0;
}