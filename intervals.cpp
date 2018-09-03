#include <iostream>
#include <algorithm>

using namespace std;

class Interval {
	public:
	 Interval( const long double left, const long double right );
	 Interval operator+=( Interval interval );
	 Interval operator-=( Interval interval );
	 Interval operator*=( Interval interval );
	 Interval operator/=( Interval interval );
	 Interval operator+( Interval interval );
	 Interval operator-( Interval interval );
	 Interval operator*( Interval interval );
	 Interval operator/( Interval interval );
	 Interval operator=( Interval interval );
	 void setLeft( const long double l );
	 void setRight( const long double r );
	 long double getLeft( void );
	 long double getRight( void );
	 Interval concat( Interval interval );
	 Interval inters( Interval interval );
	private:
	 long double left, right;
	
};

Interval::Interval(long double l, long double r) {
 left = l;
 right = r;
}

Interval Interval::operator+=(Interval interval) {
	left += interval.getLeft();
	right += interval.getRight();
	return *this;
}

Interval Interval::operator-=(Interval interval) {
	left = left - interval.getRight();
	right = interval.getRight() - right;
	return *this;
}

Interval Interval::operator*=(Interval interval) {
	register long double poss[3];
	poss[0]	= left * right;
	poss[1] = left * interval.getRight();
	poss[2] = interval.getLeft() * right;
	poss[3] = interval.getLeft() * interval.getRight();
	setLeft(poss[0]);
	register int i = 0;
	for(i = 1; i < 4; i++) 
		if(poss[i] < left)
			setLeft(poss[i]);
	setRight(poss[0]);
	for(i = 1; i < 4; i++)
		if(poss[i] > right)
			setRight(poss[i]);
		
	delete(&poss);
	delete(&i);
	
	return *this;
}

Interval Interval::operator/=(Interval interval) {
	if(right == 0 || interval.getRight() == 0) 
		throw invalid_argument("right value can't be zero");
	Interval temp = * ( new Interval(left, interval.getLeft()) );
	Interval temp1 = * ( 
	new Interval( 
	1 / interval.getRight(),
	1 / right) );
	* (this) = temp * temp1;
	delete(&temp);
	delete(&temp1);
	return * ( this );
}

Interval Interval::operator+(Interval interval) {
	return  * ( new Interval(left + interval.getLeft(), right + interval.getRight()));
}

Interval Interval::operator-(Interval interval) {
	return  * ( new Interval(left - interval.getRight(), interval.getRight() - right));
}

Interval Interval::operator*(Interval interval) {
	register long double poss[3], tmp0, tmp1;
	poss[0]	= left * right;
	poss[1] = left * interval.getRight();
	poss[2] = interval.getLeft() * right;
	poss[3] = interval.getLeft() * interval.getRight();
	tmp0 = poss[0];
	register int i = 0;
	for(i = 1; i < 4; i++) 
		if(poss[i] < left)
			tmp0 = poss[i];
	tmp1 = poss[0];
	for(i = 1; i < 4; i++)
		if(poss[i] > right)
			tmp1 = poss[i];
		
	delete(&poss);
	delete(&i);
	return * ( new Interval(tmp0, tmp1 ) );
}

Interval Interval::operator/(Interval interval) {
	if(right == 0 || interval.getRight() == 0) 
		throw invalid_argument("right value can't be zero");
	
	register long double poss[3], tmp0, tmp1;
	poss[0]	= left / right;
	poss[1] = left / interval.getRight();
	poss[2] = interval.getLeft() / right;
	poss[3] = interval.getLeft() / interval.getRight();
	
	tmp0 = poss[0];
	register int i = 0;
	for(i = 1; i < 4; i++) 
		if(poss[i] < left)
			tmp0 = poss[i];
	tmp1 = poss[0];
	for(i = 1; i < 4; i++)
		if(poss[i] > right)
			tmp1 = poss[i];
	
	delete(&poss);
	delete(&i);
	return * ( new Interval(tmp0, tmp1 ) );
}

Interval Interval::operator=(Interval interval) {
	left = interval.getLeft();
	right = interval.getRight();
}


Interval Interval::concat( Interval interval ) {
	if(interval.getLeft() < right)
	{
		return * ( new Interval( 
		min( left, right ),
		max( interval.getLeft(), interval.getRight() ) 
		) );
	}
	else throw logic_error("distance too big");
}

Interval Interval::inters( Interval interval ) {
	if(right >= interval.getLeft()) {
		return * ( new Interval( 
		min( interval.getLeft(), interval.getRight() ),
		max( left, right )
		) );
	}
	else throw logic_error("distance too big");
	
}

void Interval::setLeft(const long double l) {
 left = l;
}

void Interval::setRight(const long double r) {
 right = r;
}

long double Interval::getLeft() {
 return left;
}

long double Interval::getRight() { 
 return right;
}

int main() {
	
  Interval inter = *( new Interval(1, 3) );
  Interval inter1 = *( new Interval(-1, 5) );
  
  Interval res = inter;
  cout << "=" << res.getLeft() << " " << res.getRight() << endl;
  
  res = inter + inter1;
  cout << "+" << res.getLeft() << " " << res.getRight() << endl;
  
  res = inter - inter1;
  cout << "-" << res.getLeft() << " " << res.getRight() << endl;
  
  res = inter * inter1;
  cout << "*" << res.getLeft() << " " << res.getRight() << endl;
  
  res = inter / inter1;
  cout << "/" << res.getLeft() << " " << res.getRight() << endl;
  
  res = inter.concat(inter1);
  cout << "concat" << res.getLeft() << " " << res.getRight() << endl;
  
  res = inter.inters(inter1);
  cout << "inters" << res.getLeft() << " " << res.getRight() << endl;
  
  return 0;
}
 