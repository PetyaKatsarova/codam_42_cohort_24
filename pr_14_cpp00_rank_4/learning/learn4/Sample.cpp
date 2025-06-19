#include <iostream>
#include "Sample.hpp"


// constructor
Sample::Sample() : num(0) {
    std::cout << "Constructor caled" << std::endl;
    return ; 
}


// destructor
Sample::~Sample(void) {
    std::cout << "Destructor called" << std::endl;
    return ;  // no need for the return
}

void Sample::fun(void) const {
    std::cout << "Mem fun bar called" << std::endl;
    return;
}