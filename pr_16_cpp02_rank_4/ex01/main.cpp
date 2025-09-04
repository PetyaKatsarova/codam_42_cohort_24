#include "Fixed.hpp"
#include <iostream>


/*
When you assign 42.42f, it gets converted to the closest possible fixed-point value, which is 42.4219. This small difference is due to rounding and limited precision in the fixed-point format. This is normal and expected for fixed-point arithmetic.
*/
int main( void ) {
    Fixed a;
    Fixed const b( 10 );
    Fixed const c( 42.42f );
    Fixed const d( b );
    a = Fixed( 1234.4321f );

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;
    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

	// my tests
	Fixed num (10);
	Fixed fnum (42.42f);
	std::cout << "num is " << num.toFloat() << " as a float" << std::endl;
	std::cout << "fnum is " << fnum.toFloat() << " as a float" << std::endl; 
    return 0;
}