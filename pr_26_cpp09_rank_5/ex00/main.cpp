//to unzip file: tar -xzf cpp_09.tgz
/**
-x extract
-z gzip(decompress)
-f file (specify name)
tar -xzf cpp_09.tgz
*/
#include <iostream>
#include <stdexcept>
#include "BitcoinExchange.hpp"

// Your program must take a file as an argument.
int main(int argc, char** argv) {
    if (argc != 2) {
		return (std::cout << "Error: could not open file.\n", 1);
	}
	try {
		(void)argv[1];
		BitcoinExchange btc("data.csv");
		btc.printResult(argv[1]);
	} catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
    return 0;
}