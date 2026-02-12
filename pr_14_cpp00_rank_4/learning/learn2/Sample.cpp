#include <iostream>
#include "Sample.hpp"


// constructor
Sample::Sample(int val) {
    std::cout << "Constructor caled" << std::endl;
    this->_bla = val;
    return ; 
}


// destructor
Sample::~Sample(void) {
    std::cout << "Destructor called" << std::endl;
    return ;  // no need for the return
}

int Sample::getBla(void) const {
    return this->_bla;
}

int Sample::compare(Sample *other) const {
    if (this->_bla < other->getBla())
        return (-1);
    else if (this->_bla > other->getBla())
        return (1);
    return (0);
}