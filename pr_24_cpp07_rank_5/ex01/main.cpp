#include "iter.hpp"
#include <iostream>

void printInt(int& n) {
    std::cout << n << " ";
}

void doubleVal(int& n) { n *= 2; }

int main() {
    std::cout << "=== Test 1: Print Integer Array ===" << std::endl;
    int intArr[] = {1, 2, 3, 4, 5};
    size_t intLen = 5;
    
    std::cout << "Original: ";
    iter(intArr, intLen, printInt);
    std::cout << std::endl;

    std::cout << "\n=== Test 2: Modify Integer Array (Double the int in arr) ===" << std::endl;
    std::cout << "Before: ";
    iter(intArr, intLen, printInt);
    std::cout << std::endl;
    
    iter(intArr, intLen, doubleVal);
    
    std::cout << "After:  ";
    iter(intArr, intLen, printInt);
    std::cout << std::endl;

    return 0;
}