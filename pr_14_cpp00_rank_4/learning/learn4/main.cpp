#include <iostream>
#include "Sample.hpp"

// g++ Sample.cpp main.cpp && ./a.out
int main() { 
    Sample  instance; // triggers Sample::Sample():num(0) and constructor is called
    Sample *instancePointer = &instance;

    int     Sample::*integerPointer = NULL;
    // declare var f that cna store a pointer to a mem func of class Sample
    void    (Sample::*f)(void) const;

    integerPointer = &Sample::num;

    std::cout << "Val of mem num: " << instance.num << std::endl;
    instance.*integerPointer = 21;
    std::cout << "val of mem num: " << instance.num << std::endl;
    instancePointer->*integerPointer = 42;
    std::cout << "val of mem num: " << instance.num << std::endl;

    f = &Sample::fun;

    (instance.*f)();
    (instancePointer->*f)();
    return 0;
}