#include <iostream>
#include "Span.hpp"

int main() {
	Span sp(3);

	try {
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		std::cout << sp.numbers[0] << "  " << sp.numbers[1] << "  " << sp.numbers[2] << "  " << std::endl;
		sp.addNumber(9);
		sp.addNumber(11);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}