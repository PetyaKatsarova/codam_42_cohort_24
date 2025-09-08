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
//std::cout << "***********BOOL*************\n";
//Fixed first(10);
//Fixed second (4.42f);
//Fixed third (10);

//std::cout << " first(10) > second(4.42) true: " << (first > second) << std::endl;
//std::cout << " first(10) > third(10) false: " << (first > third) << std::endl;
//std::cout << " second(4.42) > first(10) false: " << (second > first) << std::endl;
//std::cout << "************************\n";
//std::cout << "first(10) >= second(4.42) true: " << (first >= second) << std::endl;
//std::cout << "first(10) >= third(10) true: " << (first >= third) << std::endl;
//std::cout << "second(4.42) >= first(10) false: " << (second >= first) << std::endl;
//std::cout << "************************\n";
//std::cout << "first(10) <= second(4.42) false: " << (first <= second) << std::endl;
//std::cout << "first(10) <= third(10) true: " << (first <= third) << std::endl;
//std::cout << "second(4.42) <= first(10) true: " << (second <= first) << std::endl;
//std::cout << "************************\n";
//std::cout << "first(10) == third(10) true: " << (first == third) << std::endl;
//std::cout << "first(10) == second(4.42) false: " << (first == second) << std::endl;
//std::cout << "************************\n";
//std::cout << "first(10) != third(10) false: " << (first != third) << std::endl;
//std::cout << "first(10) != second(4.42) true: " << (first != second) << std::endl;

// std::cout << "************MATH OPERATIONS************\n";
// Fixed first(10);
// Fixed second(4.42f);
// Fixed third(10);

// std::cout << "************MATH OPERATIONS************\n";
// std::cout << "first(10) + second(4.42) raw num: " << (first + second) << std::endl;
// std::cout << "first(10) + second(4.42): real int: 14.42" << ((first + second)/256) << std::endl;
// std::cout << "first(10) + third(10): " << (first + third) << std::endl;
// std::cout << "second(4.42) + first(10): " << (second + first) << std::endl;

// std::cout << "************************\n";
// std::cout << "first(10) - second(4.42): " << (first - second) << std::endl;
// std::cout << "first(10) - third(10): " << (first - third) << std::endl;
// std::cout << "second(4.42) - first(10): " << (second - first) << std::endl;

// std::cout << "************************\n";
// std::cout << "first(10) * second(4.42): " << (first * second) << std::endl;
// std::cout << "first(10) * third(10): " << (first * third) << std::endl;
// std::cout << "second(4.42) * first(10): " << (second * first) << std::endl;

// std::cout << "************************\n";
// std::cout << "first(10) / second(4.42): " << (first / second) << std::endl;
// std::cout << "first(10) / third(10): " << (first / third) << std::endl;
// std::cout << "second(4.42) / first(10): " << (second / first) << std::endl;

return 0;
}