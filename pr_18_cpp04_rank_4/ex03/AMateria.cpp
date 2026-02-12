#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>

AMateria::AMateria() : type("") {
    std::cout << "AMateria default constructor hoi :)" << std::endl;
}

AMateria::AMateria(const std::string& type) : type(type) {
    std::cout << "AM type constructor hoi :)" << std::endl;
}

AMateria::AMateria(const AMateria& other) : type(other.type) {
    std::cout << "Copy AMateria constructor hoi :)" << std::endl;
}

AMateria::~AMateria() {
    std::cout << "AMateria destructor called" << std::endl;   
}

AMateria& AMateria::operator=(const AMateria& other) {
    if (this != &other) {
        type = other.type;
    }
    std::cout << "AMateria: Copy assignment operator called" << std::endl;
    return *this;
}

std::string const & AMateria::getType() const {
    return type;
}

 void AMateria::use(ICharacter& target) {
    (void)target;
    std::cout << "** AMateria base use func" << std::endl;
 }
