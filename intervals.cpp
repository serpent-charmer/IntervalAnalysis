
#include <iostream>
#include <algorithm>
#include <typeinfo>
#define  DEBUG

using namespace std;

template<typename T>
class Interval {
public:
	Interval();
	Interval(const T &left, const T &right);
	Interval& operator+=(const Interval &interval);
	Interval& operator-=(const Interval &interval);
	Interval& operator*=(const Interval &interval);
	Interval& operator/=(const Interval &interval);
	Interval& operator+(const Interval &interval);
	Interval& operator-(const Interval &interval);
	Interval operator*(const Interval &interval);
	Interval operator/(const Interval &interval);
	Interval& operator=(const Interval &interval);
	void setLeft(const T &left);
	void setRight(const T &right);
	T getLeft(void);
	T getRight(void);
	Interval concat(const Interval &interval);
	Interval inters(const Interval &interval);
	void isGenericTypeReal(); //throws an exception
	T width();
	T radius();
	T middle();
	T iabs();

private:
	T left, right;
};

template<typename T>
Interval<T>::Interval()
{
	isGenericTypeReal();
	left = 0;
	right = 0;
}

template<typename T>
Interval<T>::Interval(const T &left, const T &right) {
	isGenericTypeReal();
	this->left = left;
	this->right = right;
}

template<typename T>
Interval<T>& Interval<T>::operator+=(const Interval &interval) {
	left += interval.left;
	right += interval.right;
	return *this;
}

template<typename T>
Interval<T>& Interval<T>::operator-=(const Interval &interval) {
	left -= interval.left;
	right = interval.right - right;
	return *this;
}

template<typename T>
Interval<T>& Interval<T>::operator*=(const Interval &interval) {

	T arr[] = {
		left * interval.left,
		left * interval.right,
		right * interval.left,
		right * interval.right };
	left = *min_element(begin(arr), end(arr));
	right = *max_element(begin(arr), end(arr));
	return *this;
}

template<typename T>
Interval<T>& Interval<T>::operator/=(const Interval &interval) {
	if (right == 0 || interval.right == 0)
		throw std::invalid_argument("right value can't be zero");

	T arr[] = {
		left / (T)interval.left,
		left / (T)interval.right,
		right / (T)interval.left,
		right / (T)interval.right
	};
	left = *min_element(begin(arr), end(arr));
	right = *max_element(begin(arr), end(arr));
}

template<typename T>
Interval<T>& Interval<T>::operator+(const Interval &interval) {
	return  *(new Interval(left + interval.left, right + interval.right));
}

template<typename T>
Interval<T>& Interval<T>::operator-(const Interval &interval) {
	return  *(new Interval(left - interval.right, right - interval.left));
}

template<typename T>
Interval<T> Interval<T>::operator*(const Interval &interval) {
	Interval temp;
	T arr[] = {
		left * interval.left,
		left * interval.right,
		right * interval.left,
		right * interval.right
	};
	temp.left = *min_element(begin(arr), end(arr));
	temp.right = *max_element(begin(arr), end(arr));
	return temp;
}

template<typename T>
Interval<T> Interval<T>::operator/(const Interval &interval) {
	if (right == 0 || interval.right == 0)
		throw invalid_argument("right value can't be zero");

	Interval temp;
	T arr[] = {
		left / (T)interval.left,
		left / (T)interval.right,
		right / (T)interval.left,
		right / (T)interval.right
	};
	temp.left = *min_element(begin(arr), end(arr));
	temp.right = *max_element(begin(arr), end(arr));
	return temp;
}

template<typename T>
Interval<T>& Interval<T>::operator=(const Interval &interval) {
	left = interval.left;
	right = interval.right;
	return *this;
}

template<typename T>
Interval<T> Interval<T>::concat(const Interval &interval) {
	if (interval.left < right)
	{
		return *(new Interval(
			min(left, right),
			max(interval.left, interval.right)
		));
	}
	else throw std::logic_error("distance too big");
}

template<typename T>
Interval<T> Interval<T>::inters(const Interval &interval) {
	if (this->right >= interval.left) {
		return *(new Interval(
			min(interval.left, interval.right),
			max(left, right)
		));
	}
	else throw logic_error("distance too big");
}

template<typename T>
void Interval<T>::isGenericTypeReal() {
	string type_name = typeid(T).name();
	if (
	!(
	type_name == typeid(float).name() ||
    type_name == typeid(double).name() ||
    type_name == typeid(long double).name()
		)
		)
		throw logic_error("type is not real");
}

template<typename T>
T Interval<T>::width()
{
	return right - left;
}

template<typename T>
T Interval<T>::radius()
{
	return (right - left) / 2.0;
}

template<typename T>
T Interval<T>::middle()
{
	return (right + left) / 2.0;
}

template<typename T>
T Interval<T>::iabs()
{
	return max(abs(left), abs(right));
}

template<typename T>
void Interval<T>::setLeft(const T &left) {
	this->left = left;
}

template<typename T>
void Interval<T>::setRight(const T &right) {
	this->right = right;
}

template<typename T>
T Interval<T>::getLeft() {
	return left;
}

template<typename T>
T Interval<T>::getRight() {
	return right;
}

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
	
#ifdef _MSC_VER
	system("pause");
#endif // _MSC_VER

#endif //DEBUG


	return 0;
}


