// #include "bigint.hpp"
// #include "bigint1.hpp"
#include "bigint3.hpp"
#include <iostream>

int main()
{

	const bigint a(42);
	bigint b(21), c, d(1234), e(d);

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "--------------------\n";
	std::cout << "a + b = " << a + b << std::endl;
	std::cout << "(c += a) = " << (c += a) << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "++b = " << ++b << std::endl;
	std::cout << "b++ = " << b++ << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "(b << 10) + 42 = " << (b << 10) + 42 << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d >> 2) = " << (d >> (const bigint)2) << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "(d < a) = " << (d < a) << std::endl;
	std::cout << "(d > a) = " << (d > a) << std::endl;
	std::cout << "(d == a) = " << (d == a) << std::endl;
	std::cout << "(d != a) = " << (d != a) << std::endl;
	std::cout << "(d <= a) = " << (d <= a) << std::endl;
	std::cout << "(d >= a) = " << (d >= a) << std::endl;
	std::cout << "-------------- edge cases << && <<=---------\n";
	//bigint test(62);
	//std::cout << "test=" << test <<"\n";
	//std::cout << "test<<0 = " << (test<<0) <<"\n";
	//std::cout << "test=" << test <<"\n";
	//std::cout << "test<<=2 = " << (test<<=2) <<"\n";
	//std::cout << "test=" << test <<"\n";
	//std::cout << "-------------- edge cases >> && >>=---------\n";
	//std::cout << "test>>0 = " << (test>>(const bigint)0) <<"\n";
	//std::cout << "test=" << test <<"\n";
	//std::cout << "test>>=2 = " << (test>>=(const bigint)2) <<"\n";
	//std::cout << "test=" << test <<"\n";
	//std::cout << "test>>4 = " << (test>>(const bigint)4) <<"\n";
	//std::cout << "test=" << test <<"\n";
	//std::cout << "-------------- edge cases 2 >> && >>=---------\n";
	//bigint test2(1234);
	//std::cout <<"test2 = " << test2 << std::endl;
	//std::cout << "test2>>1 = " << (test2>>(const bigint)1) <<"\n";
	//std::cout << "test2=" << test2 <<"\n";
	//std::cout << "test2>>=2 = " << (test2>>=(const bigint)2) <<"\n";
	//std::cout << "test2=" << test2 <<"\n";
	//std::cout << "-------------- carry / normalization test ---------\n";
	//bigint many9(999999999);
	//std::cout << "many9 = " << many9 <<"\n";
	//std::cout << "many9 + 1 = " << (many9 + bigint(1)) <<"\n";
	//std::cout << "many9 += 1 = " << (many9 += bigint(1)) <<"\n";
	//std::cout << "many9 = " << many9 <<"\n";
	//std::cout << "many9 == 1000000000 = " << (many9 == bigint(1000000000)) <<"\n";
	//std::cout << "-------------- 50 nines carry test ----------------\n";
	//bigint fifty_nines(9);
	//for (int i = 0; i < 149; i++)
	//	fifty_nines = (fifty_nines << 1) + bigint(9);
	//std::cout << "fifty_nines = " << fifty_nines <<"\n";
	//std::cout << "fifty_nines + 1 = " << (fifty_nines + bigint(1)) <<"\n";
	//std::cout << "fifty_nines += 1 = " << (fifty_nines += bigint(1)) <<"\n";
	//std::cout << "fifty_nines = " << fifty_nines <<"\n";
	return 0;
}

/*
In computer science, a bignum is an object representing an arbitrary precision
number. This is useful when you want to store a number bigger than SIZE_MAX
without any loss of precision. This is often achieved by 

storing the number as
an array or a string containing its different "parts".

Create a class called bigint that will store an arbitrary precision unsigned
integer.

Your class must support addition, comparison, and "digitshift" (similar to bitshift,
but instead of shifting the bits, you will shift the digits in base 10, e.g.,
(42 << 3 == 42000) and (1337 >> 2 == 13)).

Your bigint must be printable with the << operator (in base 10), and the output
should not contain any leading zeros.

You will find a main in this directory that must work with your class.

This exercise has to comply with the C++98 standard.
*/