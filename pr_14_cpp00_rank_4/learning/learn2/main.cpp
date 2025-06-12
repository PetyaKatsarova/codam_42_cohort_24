#include "Sample.hpp"
#include <stdio.h>
#include <iostream>


//  g++ Sample.cpp main.cpp && ./a.out
int main () {
    printf(" c still works...\n");

    Sample instance(22);
    Sample instance2(22);
    std::cout << "bla: " << instance.getBla() << std::endl;
    std::cout << "bla: " << instance.compare(&instance2) << std::endl;
    return (0);
}