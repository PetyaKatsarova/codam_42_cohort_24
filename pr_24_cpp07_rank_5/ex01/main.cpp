#include "iter.hpp"
#include <iostream>
#include <string>

void strCapitalizeFirst(std::string& str) { 
    if (!str.empty())
        str[0] = std::toupper(str[0]);
}

int main() {
    int intArr[] = {1, 2, 3, 4, 5};
    const size_t arrLen = 5;

    std::cout << "\n-- Test 1: int array --\n" << std::endl;
    std::cout << "Before: ";
    iter(intArr, arrLen, printTemplate<int>);
    std::cout << std::endl;
    
    iter(intArr, arrLen, doubleValTemplate<int>);
    
    std::cout << "After:  ";
    iter(intArr, arrLen, printTemplate<int>);
    std::cout << std::endl;
    std::cout << "-- const int arr --\n";
    const int constIntArr[] = {11, 22, 33, 44, 55};
    iter(constIntArr, arrLen, printTemplate<int>);
    std::cout << "\n";

    std::cout << "\n-- Test 2: double --\n";
    double doubleArr[] = {1.42, 2.42, 3.4242, 4.42, 5.42};

    std::cout << "Before: ";
    iter(doubleArr, arrLen, printTemplate<double>);
    std::cout << std::endl;
    
    iter(doubleArr, arrLen, doubleValTemplate<double>);
    
    std::cout << "After:  ";
    iter(doubleArr, arrLen, printTemplate<double>);
    std::cout << std::endl;
    std::cout << "-- const int arr --\n";
    const double constdoubleArr[] = {11.42, 22.42, 33.42, 44.42, 55.42};
    iter(constdoubleArr, arrLen, printTemplate<double>);
    std::cout << "\n";

    std::cout << "\n-- Test 3: string --\n";
    std::string strArr[] = {"hello", "world", "we", "come", "happy"};

    std::cout << "Before: ";
    iter(strArr, arrLen, printTemplate<std::string>);
    std::cout << std::endl;
    
    iter(strArr, arrLen, strCapitalizeFirst);
    std::cout << "After:  ";
    iter(strArr, arrLen, printTemplate<std::string>);
    std::cout << std::endl;
    std::cout << "-- const str arr --\n";
    const std::string conststrArr[] = {"11", "22", "33", "44", "55"};
    iter(conststrArr, arrLen, printTemplate<std::string>);
    std::cout << "\n";
    return 0;
}