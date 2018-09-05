#include "intervals.h"
#include <iostream>

#define DEBUG

int main() {

#ifdef DEBUG

	Interval<double> a(1, 3);
	Interval<double> b(-1, 5);

	Interval<double> res;

	cout << "a(" << a.getLeft() << " , " << a.getRight() << ")";
	cout << "\tb(" << b.getLeft() << " , " << b.getRight() << ")" << endl << endl;
	res = b;
	cout << " = b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << endl;

	res = a + b;
	cout << " a + b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << endl;

	res = a - b;
	cout << " a-b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << endl;

	res = a * b;
	cout << " a*b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << endl;

	res = a / b;
	cout << " a/b:\t\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << endl;

	res = a.concat(b);
	cout << " a concat b:\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << endl;

	res = a.inters(b);
	cout << " a inters b:\t " << "(" << res.getLeft() << " , " << res.getRight() << ")" << endl;

	cout << " wid(a):\t " << "(" << a.width() << ")" << endl;
	cout << " rad(a):\t " << "(" << a.radius() << ")" << endl;
	cout << " med(a):\t " << "(" << a.middle() << ")" << endl;
	cout << " abs(a):\t " << "(" << a.iabs() << ")" << endl;


	system("pause");


#endif //DEBUG


	return 0;
}