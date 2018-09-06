#pragma once

#ifndef INTERVALS_H
#define INTERVALS_H


#include <iostream>
#include <algorithm>
#include <typeinfo>

namespace ian { //IntervalANalysis

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
	left = * std::min_element( std::begin(arr), std::end(arr) );
	right = * std::max_element( std::begin(arr), std::end(arr) );
	return *this;
}

template<typename T>
Interval<T>& Interval<T>::operator/=(const Interval &interval) {
	if (right == 0 || interval.right == 0)
		throw std::invalid_argument("right value can't be zero");

	T arr[] = {
		left / (T) interval.left,
		left / (T) interval.right,
		right / (T) interval.left,
		right / (T) interval.right
	};
	left = * std::min_element( std::begin(arr), std::end(arr) );
	right = * std::max_element( std::begin(arr), std::end(arr) );
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
	temp.left = * std::min_element( std::begin(arr), std::end(arr) );
	temp.right = * std::max_element( std::begin(arr), std::end(arr));
	return temp;
}

template<typename T>
Interval<T> Interval<T>::operator/(const Interval &interval) {
	if (right == 0 || interval.right == 0)
		throw std::invalid_argument("right value can't be zero");

	Interval temp;
	T arr[] = {
		left / (T)interval.left,
		left / (T)interval.right,
		right / (T)interval.left,
		right / (T)interval.right
	};
	temp.left = * std::min_element( std::begin(arr), std::end(arr) );
	temp.right = * std::max_element( std::begin(arr), std::end(arr) );
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
			std::min(left, right),
			std::max(interval.left, interval.right)
		));
	}
	else throw std::logic_error("distance too big");
}

template<typename T>
Interval<T> Interval<T>::inters(const Interval &interval) {
	if (this->right >= interval.left) {
		return *(new Interval(
			std::min(interval.left, interval.right),
			std::max(left, right)
		));
	}
	else throw std::logic_error("distance too big");
}

template<typename T>
void Interval<T>::isGenericTypeReal() {
	std::string type_name = typeid(T).name();
	if (
		!(
			type_name == typeid(float).name() ||
			type_name == typeid(double).name() ||
			type_name == typeid(long double).name()
			)
		) 
		throw std::logic_error("type is not real");
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
	return std::max( std::abs(left), std::abs(right));
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

template<typename T>
std::ostream& operator<<(std::ostream &strm, Interval<T> &interval) {
  return strm << "Interval(" << interval.getLeft() << " " << interval.getRight() << ")" << std::endl;
}

}

#endif

