#include "Fixed.hpp"
#include <iostream>
#include <cmath>

int main( void ) {
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;

// my tests
// std::cout << "*********** BOOL *************\n";
//Fixed first(10);
//Fixed second (4.99f);
//Fixed third (10);

//std::cout << " first.toFloat = " << first.toFloat() << " second.toInt = "  << second.toInt() << std::endl;

//std::cout << " first > second true: " << (first > second) << std::endl;
//std::cout << " first(10) > third(10) false: " << (first > third) << std::endl;
//std::cout << " second > first(10) false: " << (second > first) << std::endl;
//std::cout << "************************\n";
//std::cout << "first(10) >= second true: " << (first >= second) << std::endl;
//std::cout << "first(10) >= third(10) true: " << (first >= third) << std::endl;
//std::cout << "second >= first(10) false: " << (second >= first) << std::endl;
//std::cout << "************************\n";
//std::cout << "first(10) <= second false: " << (first <= second) << std::endl;
//std::cout << "first(10) <= third(10) true: " << (first <= third) << std::endl;
//std::cout << "second <= first(10) true: " << (second <= first) << std::endl;
//std::cout << "************************\n";
//std::cout << "first(10) == third(10) true: " << (first == third) << std::endl;
//std::cout << "first(10) == second false: " << (first == second) << std::endl;
//std::cout << "************************\n";
//std::cout << "first(10) != third(10) false: " << (first != third) << std::endl;
//std::cout << "first(10) != second true: " << (first != second) << std::endl;

//std::cout << "************MATH OPERATIONS************\n";
//std::cout << "first(10) + second = " << (first + second) << std::endl;
//std::cout << "first(10) - second = " << (first - second) << std::endl;
//std::cout << "first(10) + third(10) = " << (first + third) << std::endl;
//std::cout << "second - first(10)  " << (second - first) << std::endl;

//std::cout << "************************\n";
//std::cout << "first(10) * second = " << (first * second) << std::endl;
//std::cout << "first(10) * third(10) = " << (first * third) << std::endl;
//std::cout << "second * first(10) = " << (second * first) << std::endl;

//std::cout << "************************\n";
//std::cout << "first(10) / second = " << (first / second) << std::endl;
//std::cout << "first(10) / third(10) = " << (first / third) << std::endl;
//std::cout << "second / first(10) = " << (second / first) << std::endl;

//std::cout << "************************\n";
//std::cout << "Fixed::max(first, second) " << Fixed::max(first, second) << std::endl;
//std::cout << "Fixed::max(second, first) " << Fixed::max(second, first) << std::endl;
//std::cout << "Fixed::min(first, second) " << Fixed::min(first, second) << std::endl;
//std::cout << "Fixed::min (second, first) " << Fixed::min(second, first) << std::endl;

return 0;
}