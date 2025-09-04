#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : _raw_bits(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int num) {
    std::cout << "Int constructor called" << std::endl;
    _raw_bits = num << _FRACTALPART;
}

/*
    roundf returns a float rounded to the nearest integer value, but the type is still float.
*/
Fixed::Fixed(const float fnum) {
    std::cout << "Float constructor called" << std::endl;
    _raw_bits = static_cast<int> (roundf(fnum * (1 << _FRACTALPART)));
}

Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called\n";
    _raw_bits = other._raw_bits;
}

Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called\n";
    if (this != &other) {
        _raw_bits = other._raw_bits;
    }
        return *this;
}

Fixed::~Fixed()  {
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits() const {
    std::cout << "getRawBits member function called\n";
    return _raw_bits;
}

void Fixed::setRawBits(int const raw) {
    _raw_bits = raw;
    std::cout << "setRawBits member function called\n";
}

float Fixed::toFloat( void ) const {
    float res = static_cast<float> (_raw_bits) / (1 << _FRACTALPART);
    return res;
}

int Fixed::toInt( void ) const {
    return (_raw_bits >> _FRACTALPART);
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
	return ( Fixed(_raw_bits + other._raw_bits));
}

Fixed Fixed::operator-(const Fixed& other) const {
	return ( Fixed(_raw_bits - other._raw_bits));
}

Fixed Fixed::operator*(const Fixed& other) const {
	return ( Fixed(_raw_bits * other._raw_bits));
}

/*
num / 0 causes a runtime error (division by zero), which usually results in a crash or undefined behavior.
*/
Fixed Fixed::operator/(const Fixed& other) const {
	if (other._raw_bits == 0)
		throw std::runtime_error("Division by zero is not allewed");
	return ( Fixed(_raw_bits / other._raw_bits));
}

