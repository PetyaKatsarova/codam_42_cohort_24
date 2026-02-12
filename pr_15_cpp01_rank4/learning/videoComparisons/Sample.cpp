#include <iostream>
#include "Sample.hpp"


// constructor
Sample::Sample(int num) : _foo(num) {
    std::cout << "Constructor caled" << std::endl;
    return ; 
}

// destructor
Sample::~Sample(void) {
    std::cout << "Destructor called" << std::endl;
    return ;  // no need for the return
}

int Sample::getFoo(void) const {
    return this->_foo;
}

// if curr obj.field > otherObj.field returns 1, if smaller return -1, if equal returns 0
int Sample::compare(const Sample *other) const {
    
    if (this->_foo < other->getFoo())
        return (-1);
    else if (this->_foo > other->getFoo())
        return (1);
    return (0);
}