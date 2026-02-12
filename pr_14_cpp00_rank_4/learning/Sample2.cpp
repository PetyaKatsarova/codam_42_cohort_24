#include <iostream>
#include "Sample2.hpp"

// initialization list
Sample2::Sample2(char p1, int p2, float p3) : a1(p1), a2(p2), a3(p3), q4(22) {
    std::cout << "Constructor called" << std::endl;
    std::cout << "a1, a2, a3, q4: " << this->a1 << " " << this->a2 << " " << this->a3 << " " << this->q4 << std::endl;
    return ;
}

Sample2::~Sample2(void) {
    std::cout << "Destructor called" << std::endl;
    return ;
}

// const word: bar() promises not to change the state of the object.
void Sample2::bar(void) const {
    std::cout << "func bar called" << std::endl;
    std::cout << "this->p3 = " << this->a3 << std::endl;
    std::cout << "this->p4 = " << this->q4 << std::endl;
    // this->q4 = 0; not allowed !
}