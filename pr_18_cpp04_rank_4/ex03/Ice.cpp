#include "Ice.hpp"

#include <iostream>

Ice::Ice() : AMateria("ice") {
    // std::cout << "Ice default constructor hoi :)" << std::endl;
}

Ice::Ice(const std::string &type) : AMateria(type) {}

Ice::Ice(const Ice& other) : AMateria(other) {}

Ice::~Ice() {
    // std::cout << "Ice destructor called" << std::endl;   
}

Ice& Ice::operator=(const Ice& other) {
    AMateria::operator=(other);
    return *this;
}  
    
AMateria* Ice::clone() const {
    return new Ice(*this);
}
void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}



