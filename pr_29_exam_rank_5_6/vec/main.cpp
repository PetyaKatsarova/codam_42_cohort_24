/*
obj - (x, y) -> class = value
small operator-overloading lab
turning a user-defined type into a usable value type
value - manipulation using operators
syntax to express oprations
additoin
subtraction
scalar multiplication
unary minus
use of reference
use of const
*/
#include "vec3.hpp"
#include <iostream>

int main()
{
	vect v1;
	vect v2(1, 2);
	const vect v3(v2);
	vect v4 = v2;

	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v3: " << v3 << std::endl;
	std::cout << "v4: " << v4 << std::endl;

	std::cout << "++v4 = " << ++v4 << std::endl;
	std::cout << "v4++ = " << v4++ << std::endl;
	std::cout << "v4 = " << v4 << std::endl;
	// std::cout << v4-- << std::endl;
	// std::cout << --v4 << std::endl;
	// v2 += v3;
	// std::cout << "v2 += v3 = " << v2 << std::endl;
	// v1 -= v2;
	// v2 = v3 + v3 * 2;
	// v2 = 3 * v2;

	// v2 += v2 += v3;
	// v1 *= 42;

	// v1 = v1 - v1 + v1;
	// std::cout << "v1:" << v1 << std::endl;
	// std::cout << "v2:" << v2 << std::endl;
	// std::cout << "-v2:" << -v2 << std::endl;

	// std::cout << "v1[1]:" << v1[1] << std::endl;
	// v1[1] = 12;
	// std::cout << "v1[1]:" << v1[1] << std::endl;
	// std::cout << "v3[1]:" << v3[1] << std::endl;

	// std::cout << "v1 == v3 " << (v1 == v3) << std::endl;
	// std::cout << "v1 == v1 " << (v1 == v1) << std::endl;
	// std::cout << "v1 != v3 " << (v1 != v3) << std::endl;
	// std::cout << "v1 != v1 " << (v1 != v1) << std::endl;
	return (0);
}