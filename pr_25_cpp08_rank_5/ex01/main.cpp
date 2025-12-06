#include <iostream>
#include <string>
#include "Span.hpp"

//int main() {
//	unsigned int max_size = 10000;
//	Span sp(max_size);
//	srand(time(NULL));
//	try {
//		std::cout << "-- started adding nums but out of bounds --" + std::to_string(max_size + 1) + "\n";
//		for (unsigned int i = 0; i < max_size+1; i++) { 
//			sp.addNumber(rand());
//		}
//		std::cout << "numbers[numbers.size()-1] = " << std::to_string(sp.getLastNum(max_size-1)) << "\n-- end adding 10000 nums --\n";
//	} catch (std::exception& e) {
//		std::cout << "*** hey STOP ADDING NUMS ***\n";
//		std::cerr << e.what() << std::endl;
//	}
//	try {
//		std::cout << "Shortest span =  " << sp.shortestSpan() << std::endl;
//	} catch (std::exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//	try {
//		std::cout << "Longest span = "<< sp.longestSpan() << std::endl;
//	} catch (std::exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//	std::cout << "test with N=0\n";
//		try {
//			Span sp2(0);
//			sp2.addNumber(42);
//			std::cout << "** this should not be printed\n";
//	} catch (std::exception& e) {
//		std::cout << "*** max size is 0 ***\n";
//		std::cerr << e.what() << std::endl;
//	}
//	return 0;
//}

// eval code
int main()
{
Span sp = Span(5);
sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);
std::cout << sp.shortestSpan() << std::endl;
std::cout << sp.longestSpan() << std::endl;
return 0;
}