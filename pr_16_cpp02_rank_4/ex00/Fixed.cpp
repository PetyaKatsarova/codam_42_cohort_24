#include "Fixed.hpp"
#include <iostream>

Fixed::Fixed() : _raw_bits(0) {
	std::cout << "Default constructor called" << std::endl;
}

/*
Copy constructor → creates a new object as a copy.
Fixed a; Fixed b(a); copy constr: change val in 1 obj,
doesnt change the other
If you don’t define a copy constructor, C++ automatically generates a default copy constructor that copies every member (_value = other._value).
*/
Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called\n";
    _raw_bits = other._raw_bits;
}

/*
Copy assignment operator → existing object takes the value of another.
Fixed a; Fixed b; b = a;
*/
Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called\n";
    if (this != &other) {
        _raw_bits = other._raw_bits;
    }
        return *this;
}

Fixed::~Fixed()  {
	std::cout << "Fixed destructor called" << std::endl;
}

int Fixed::getRawBits() const {
    std::cout << "getRawBits member function called\n";
    return _raw_bits;
}

void Fixed::setRawBits(int const raw) {
    _raw_bits = raw;
    std::cout << "setRawBits member function called\n";
}
