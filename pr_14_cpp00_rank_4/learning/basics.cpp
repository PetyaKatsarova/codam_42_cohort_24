#include <iostream>


// g++ arrays.cpp && ./a.out
int main (void) {
    char buff[512];
    std::cout << "bla " << std::endl;

    std::cout << "input a word: ";
    std::cin >> buff;
    std::cout << "u entered: [" << buff << "]" << std::endl;
}