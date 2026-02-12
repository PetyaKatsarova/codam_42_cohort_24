#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : _raw_bits(0) {}

/**
 * num << 8 = num * 256
 */
Fixed::Fixed(const int num) {
    _raw_bits = num << _FRACTALPART;
}

/**
    roundf returns a float rounded to the nearest integer value, but the type is still float.
*/
Fixed::Fixed(const float fnum) {
    _raw_bits = static_cast<int> (fnum * (1 << _FRACTALPART));
}

Fixed::Fixed(const Fixed &other) {
    _raw_bits = other._raw_bits;
}

Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other) {
        _raw_bits = other._raw_bits;
    }
    return *this;
}

Fixed::~Fixed()  {}

int Fixed::getRawBits() const { return _raw_bits; }

void Fixed::setRawBits(int const raw) { _raw_bits = raw; }

float Fixed::toFloat( void ) const {
    float res = static_cast<float> (_raw_bits) / (1 << _FRACTALPART);
    return res;
}

int Fixed::toInt( void ) const {
    return _raw_bits >> _FRACTALPART;
}

std::ostream &operator<<(std::ostream &os, const Fixed &obj) {
    os << obj.toFloat();
    return os;
}

bool Fixed::operator>(const Fixed& other) const {
	return (_raw_bits > other._raw_bits);
}

bool Fixed::operator<(const Fixed& other) const {
	return (_raw_bits < other._raw_bits);
}

bool Fixed::operator>=(const Fixed& other) const {
	return (_raw_bits >= other._raw_bits);
}

bool Fixed::operator<=(const Fixed& other) const {
	return (_raw_bits <= other._raw_bits);
}

bool Fixed::operator!=(const Fixed& other) const {
	return (_raw_bits != other._raw_bits);
}

bool Fixed::operator==(const Fixed& other) const {
	return (_raw_bits == other._raw_bits);
}

Fixed Fixed::operator+(const Fixed& other) const {
    Fixed result;
    result.setRawBits(_raw_bits + other._raw_bits);
	return result;
}

Fixed Fixed::operator-(const Fixed& other) const {
    Fixed res;
    res.setRawBits(_raw_bits - other._raw_bits);
	return res;
}

// >> divide by 2
Fixed Fixed::operator*(const Fixed& other) const {
    int res = (static_cast<long long>(_raw_bits) * other._raw_bits) >> _FRACTALPART;
    Fixed bla;
    bla.setRawBits((res));
    return bla;
}

/*
num / 0 causes a runtime error (division by zero), which usually results in a crash or undefined behavior. returns  a new obj
In fixed-point arithmetic, when you divide two numbers that are already scaled by 2^8, you need to compensate:
Fixed Fixed::operator/(const Fixed& other) const {
	if (other._raw_bits == 0)
		throw std::runtime_error("Division by zero is not allewed");
    long long temp = (static_cast<long long> (_raw_bits) << _FRACTALPART ) / other._raw_bits;   
    Fixed bla;
    bla.setRawBits(static_cast<int>(temp));
	return bla;
}
*/
Fixed Fixed::operator/(const Fixed& other) const {
	if (other._raw_bits == 0)
		throw std::runtime_error("Division by zero is not allowed");
    int temp = (static_cast<long long> (_raw_bits) << _FRACTALPART ) / other._raw_bits;   
    Fixed bla;
    bla.setRawBits(temp);
	return bla;
}

// returns ref to the same obj
Fixed &Fixed::operator++(){
    this->_raw_bits++;
    return *this;
}

Fixed &Fixed::operator--(){
    this->_raw_bits--;
    return *this;
}

// post incr
Fixed Fixed::operator++(int){
    Fixed temp(*this);
    this->_raw_bits++;
    return temp;
}

// post decr
Fixed Fixed::operator--(int){
    Fixed temp(*this);
    this->_raw_bits--;
    return temp;
}
 
Fixed& Fixed::max(Fixed &a, Fixed &b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}

Fixed& Fixed::min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}
