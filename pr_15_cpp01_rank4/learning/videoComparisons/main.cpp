#include "Sample.hpp"
#include <iostream>

// g++ main.cpp Sample.cpp && ./a.out
int main() {
    Sample instance1(42); // constr called
    Sample instance2(42); // constr called 

    if (&instance1 == &instance1) // yes
        std::cout << "instance1 and isntance1 r physically equal" << std::endl;
    else
        std::cout << "instance1 and isntance1 r not physically equal" << std::endl;
    if (&instance1 == &instance2) //no
        std::cout << "instance1 and isntance2 r physically equal" << std::endl;
    else
        std::cout << "instance1 and isntance2 r not physically equal" << std::endl;

    if (instance1.compare(&instance1) == 0) // yes
        std::cout << "instance1 and isntance1 r structurally equal" << std::endl;
    else
        std::cout << "instance1 and isntance1 r not structurally equal" << std::endl;
    
        if (instance1.compare(&instance2) == 0)
        std::cout << "instance1 and isntance2 r structurally equal" << std::endl;
    else
        std::cout << "instance1 and isntance2 r not structurally equal" << std::endl;
    return (0);
}