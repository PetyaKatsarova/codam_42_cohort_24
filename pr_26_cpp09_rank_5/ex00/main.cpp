//to unzip file: tar -xzf cpp_09.tgz
/**
-x extract
-z gzip(decompress)
-f file (specify name)
tar -xzf cpp_09.tgz
*/
#include <iostream>
#include "BitcoinExchange.hpp"

// Your program must take a file as an argument.
int main(int argc, char** argv) {
    if (argc != 2)
        return (std::cout << "Error: could not open file.\n", 1);
    BitcoinExchange btc;
	//if (!btc.validateInput(argv[1])) if a line is not valid: print msg and move to next one
	//	return 1; // all err msgs are in the inside code
    //btc.loadDb(argv[1]);
    btc.processInput(argv[1]);
    return 0;
}