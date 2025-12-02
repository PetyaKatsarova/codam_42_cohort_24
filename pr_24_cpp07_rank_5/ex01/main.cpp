#include "iter.hpp"
#include <iostream>
#include <string>

void printIntConst(const int& n) { std::cout << n << " "; }

void doubleVal(int& n) { n *= 2; }

void printStr(std::string& str) { std::cout << str << " "; }

void printConstStr(const std::string& str) { std::cout << str << " "; }

void strCapitalizeFirst(std::string& str) { 
    if (!str.empty())
        str[0] = std::toupper(str[0]);
}

template<typename T>
void incrementTemplate(T& val) { ++val; }

template<typename T>
void printTemplate (const T& val) { std::cout << val << " "; }

int main() {
    int intArr[] = {1, 2, 3, 4, 5};
    size_t intLen = 5;

    std::cout << "\n=== Test 1: Modify Integer Array (Double the int in arr) and print const int arr ===" << std::endl;
    std::cout << "Before: ";
    iter(intArr, intLen, printIntConst);
    std::cout << std::endl;
    
    iter(intArr, intLen, doubleVal);
    
    std::cout << "After:  ";
    // iter(intArr, intLen, printTemplate<int>);
    iter(intArr, intLen, printIntConst);
    std::cout << std::endl;

    std::cout << "\n-------------- TEST STRINGS ---------------------\n";
    const std::string constStrArr[] = {"hello", "world", "we",  "come", "in",  "peace"};
    std::string strArr[] = {"hello", "world", "we",  "come", "in",  "peace"};

    std::cout << "\n-- print const str arr --\n";
    // iter(constStrArr, 6, printStr); // for testing showing err
    iter(constStrArr, 6, printConstStr); 
    std::cout << "\n-- capitalize and print str arr --\n";
    iter(strArr, 6, strCapitalizeFirst);
    iter(strArr, 6, printStr); 
    std::cout << "\n";

    std::cout << "\n=== Test 5: Multiple Increments ===\n" << std::endl;
    float multiArr[] = {0.0f, 10.10f, 20.20f, 30.30f};
    std::cout << "Original: ";
    iter(multiArr, 4, printTemplate<float>);
    std::cout << "\nIncrement: \n";
    iter(multiArr, 4, incrementTemplate<float>);
    iter(multiArr, 4, printTemplate<float>);
    std::cout << "\n";
    return 0;
}