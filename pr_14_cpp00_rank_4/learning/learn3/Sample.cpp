
#include <iostream>
#include "Sample.hpp"


// constructor
Sample::Sample() {
    std::cout << "Constructor caled" << std::endl;
    Sample::_numInst += 1;
    return; 
}


// destructor
Sample::~Sample(void) {
    std::cout << "Destructor called" << std::endl;
    Sample::_numInst -= 1;
    return;  // no need for the return
}

int Sample::getNumInst(void) {
    return Sample::_numInst;
}

int Sample::_numInst = 0;