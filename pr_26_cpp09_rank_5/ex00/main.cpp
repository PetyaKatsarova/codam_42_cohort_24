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
        std::cout << "Error: could not open file.\n";
    std::cout << "tra la la\n";
    BitcoinExchange btc;
    (void) argv;
    btc.loadDb("test_data.csv");
    // btc.processInput(argv[1]);
    return 0;
}