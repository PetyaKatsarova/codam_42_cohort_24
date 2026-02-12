#include <iostream>
#include "Sample.hpp"


// constructor
Sample::Sample(void) {
    std::cout << "Constructor caled" << std::endl;
    this->bla = 42;
    std::cout << "this->bla: " << this->bla << std::endl;
    this->bar();
    return ; 
}


// destructor
Sample::~Sample(void) {
    std::cout << "Destructor called" << std::endl;
    return ;  // no need for the return
}

// member func
void Sample::bar(void) {
    std::cout << "Member func bar called" << std::endl;
    return ;
}