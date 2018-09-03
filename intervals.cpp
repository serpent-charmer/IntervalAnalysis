
#include <iostream>
#include <algorithm>
#define  DEBUG

template<typename T>
class Interval {
	public:
		Interval();
		Interval( const T &left, const T &right );
		Interval& operator+=(const Interval &interval );
		Interval& operator-=(const Interval &interval );
		Interval& operator*=(const Interval &interval );
		Interval& operator/=(const Interval &interval );
		Interval& operator+(const Interval &interval );
		Interval& operator-(const Interval &interval );
		Interval operator*(const Interval &interval );
		Interval operator/(const Interval &interval );
		Interval& operator=(const Interval &interval );
		void setLeft( const T &left );
		void setRight( const T &right );
		T getLeft( void );
		T getRight( void );
		Interval concat(const Interval &interval );
		Interval inters(const Interval &interval );
		T Wid();
		T Rad();
		T Med();
		T Abs();

	private:
		T left, right;	
};

template<typename T>
Interval<T>::Interval()
{
	this->left = 0;
	this->right = 0;
}

template<typename T>
Interval<T>::Interval(const T &left, const T &right) {
	this->left = left;
	this->right = right;
}

template<typename T>
Interval<T>& Interval<T>::operator+=(const Interval &interval) {
	this->left += interval.left;
	this->right += interval.right;
	return *this;
}

template<typename T>
Interval<T>& Interval<T>::operator-=(const Interval &interval) {
	this->left = this->left - interval.left;
	this->right = interval.right - this->right;
	return *this;
}

template<typename T>
Interval<T>& Interval<T>::operator*=(const Interval &interval) {
	
	long double arr[] = { this->left * interval.left, this->left * interval.right,
					this->right * interval.left, this->right * interval.right };
	this->left = *std::min_element(std::begin(arr), std::end(arr));
	this->right = *std::max_element(std::begin(arr), std::end(arr));
	return *this;
}

template<typename T>
Interval<T>& Interval<T>::operator/=(const Interval &interval) {
	if(this->right == 0 || interval.right == 0) 
		throw std::invalid_argument("right value can't be zero");

	long double arr[] = { this->left / (long double)interval.left, this->left / (long double)interval.right,
		this->right / (long double)interval.left, this->right / (long double)interval.right };
	this->left = *std::min_element(std::begin(arr), std::end(arr));
	this->right = *std::max_element(std::begin(arr), std::end(arr));
}

template<typename T>
Interval<T>& Interval<T>::operator+(const Interval &interval) {
	return  * ( new Interval(this->left + interval.left, this->right + interval.right));
}

template<typename T>
Interval<T>& Interval<T>::operator-(const Interval &interval) {
	return  * ( new Interval(this->left - interval.right, this->right - interval.left));
}

template<typename T>
Interval<T> Interval<T>::operator*(const Interval &interval) {
	Interval temp;
	long double arr[] = { this->left * interval.left, this->left * interval.right,
						this->right * interval.left, this->right * interval.right };
	temp.left = *std::min_element(std::begin(arr), std::end(arr));
	temp.right = *std::max_element(std::begin(arr), std::end(arr));
	return temp;
}

template<typename T>
Interval<T> Interval<T>::operator/(const Interval &interval) {
	if(this->right == 0 || interval.right == 0) 
		throw std::invalid_argument("right value can't be zero");

	Interval temp;
	long double arr[] = { this->left / (long double)interval.left, this->left / (long double)interval.right,
						this->right / (long double)interval.left, this->right / (long double)interval.right };
	temp.left = *std::min_element(std::begin(arr), std::end(arr));
	temp.right = *std::max_element(std::begin(arr), std::end(arr));
	return temp;
}

template<typename T>
Interval<T>& Interval<T>::operator=(const Interval &var) {
	this->left = var.left;
	this->right = var.right;
	return *this;
}

template<typename T>
Interval<T> Interval<T>::concat(const Interval &interval ) {
	if(interval.left < this->right)
	{
		return * ( new Interval( 
			std::min(this->left, this->right ),
			std::max( interval.left, interval.right )
		) );
	}
	else throw std::logic_error("distance too big");
}

template<typename T>
Interval<T> Interval<T>::inters(const Interval &interval ) {
	if(this->right >= interval.left) {
		return * ( new Interval( 
			std::min( interval.left, interval.right ),
			std::max(this->left, this->right )
		) );
	}
	else throw std::logic_error("distance too big");	
}

template<typename T>
T Interval<T>::Wid()
{
	
	return (this->right) -( this->left);
}

template<typename T>
T Interval<T>::Rad()
{
	return (this->right - this->left) / (long double)2;
}

template<typename T>
T Interval<T>::Med()
{
	return (this->right + this->left) / (long double)2;
}

template<typename T>
T Interval<T>::Abs()
{
	return max(abs(this->left), abs(this->right));
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

using namespace std;
int main() {

#ifdef DEBUG
  Interval<double> a(1, 3);
  Interval<double> b(-1, 5);
  
  Interval<double> res;

  cout << "a(" << a.getLeft() << " , " << a.getRight() << ")"  ;
  cout << "\tb(" << b.getLeft() << " , " << b.getRight() << ")" << endl<<endl;
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

  cout << " wid(a):\t " << "(" << a.Wid() << ")" << endl;
  cout << " rad(a):\t " << "(" << a.Rad() << ")" << endl;
  cout << " med(a):\t " << "(" << a.Med() << ")" << endl;
  cout << " abs(a):\t " << "(" << a.Abs() << ")" << endl;
#endif
  
  
  return 0;
}
 