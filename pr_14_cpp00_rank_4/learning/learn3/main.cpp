#include "Sample.hpp"
#include <stdio.h>
#include <iostream>

void sth(void) {
    Sample bla; // calls constructor
    std::cout << "num of instances in sth: " << Sample::getNumInst() << std::endl;
    return;
}

// creates twice Sample instances, which increments twice num
void sth2 () {
    Sample inst2;
    std::cout << "num of inst in sth2: " << Sample::getNumInst() << std::endl;
    sth();
    return;
}

//  g++ Sample3.cpp main.cpp && ./a.out
int main () {
    printf(" c still works...\n");
    
    std::cout << "num inst b4: " << Sample::getNumInst() << std::endl;
    sth2();
    std::cout << "num of inst after: " << Sample::getNumInst() << std::endl;
    return (0);
}