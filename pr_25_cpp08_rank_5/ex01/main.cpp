#include <iostream>
#include <string>
#include "Span.hpp"

int main() {
	unsigned int max_size = 10000;
	Span sp(max_size);
	srand(time(NULL));
	try {
		std::cout << "-- started adding nums but out of bounds --" + std::to_string(max_size + 1) + "\n";
		for (unsigned int i = 0; i < max_size+1; i++) { 
			sp.addNumber(rand());
		}
		std::cout << "numbers[numbers.size()-1] = " << std::to_string(sp.getLastNum(max_size-1)) << "\n-- end adding 10000 nums --\n";
	} catch (std::exception& e) {
		std::cout << "*** hey STOP ADDING NUMS ***\n";
		std::cerr << e.what() << std::endl;
	}
	try {
		std::cout << "Shortest span =  " << sp.shortestSpan() << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::cout << "Longest span = "<< sp.longestSpan() << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << "test with N=0\n";
	try {
			Span sp2(0);
			sp2.addNumber(42);
			std::cout << "** this should not be printed\n";
	} catch (std::exception& e) {
		std::cout << "*** max size is 0 ***\n";
		std::cerr << e.what() << std::endl;
	}
	Span sp3(10000);
	std::vector<int> bigVec(10000);

	for (int i = 0; i < 10000; i++) {
		bigVec[i] = i;
	}
	sp3.addRange(bigVec.begin(), bigVec.end());
	
	std::cout << "Added 10,000 numbers from vector!" << std::endl;
	std::cout << "Shortest: " << sp3.shortestSpan() << std::endl;  // 1
	std::cout << "Longest: " << sp3.longestSpan() << std::endl;    // 9999

	std::cout << "test with N=MAX_SIZE+1\n";
	try {
		sp3.addNumber(42);
		std::cout << "** this should not be printed\n";
	} catch (std::exception& e) {
		std::cout << "*** out of bounds ***\n";
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Added 5 numbers from !" << std::endl;
	Span sp4(10);
	int arr[] = {10, 20, 30, 40, 50};
	
	sp4.addRange(arr, arr + 5);  // Pointer arithmetic works!
	
	std::cout << "Shortest: " << sp4.shortestSpan() << std::endl;  // 10
	std::cout << "Longest: " << sp4.longestSpan() << std::endl;    // 40
	
	return 0;
}

// eval code
//int main()
//{
//Span sp = Span(5);
//sp.addNumber(6);
//sp.addNumber(3);
//sp.addNumber(17);
//sp.addNumber(9);
//sp.addNumber(11);
//std::cout << sp.shortestSpan() << std::endl;
//std::cout << sp.longestSpan() << std::endl;
//return 0;
//}