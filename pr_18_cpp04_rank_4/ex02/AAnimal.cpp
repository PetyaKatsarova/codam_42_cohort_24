#include "AAnimal.hpp"
#include <string>
#include <iostream>

AAnimal::AAnimal() : type("AAnimal") {
    std::cout << "AAnimal: default constr." << std::endl;
}

AAnimal::AAnimal(const AAnimal& other) : type(other.type) {
    std::cout << "AAnimal: copy constr.\n";
}

AAnimal& AAnimal::operator=(const AAnimal& other) {
    std::cout << "AAnimal: Copy assignment operator called" << std::endl;
    if (this != &other)
        type = other.type;
    return *this;
}

std::string AAnimal::getType() const {
    return type;
}

AAnimal::~AAnimal() {
    std::cout << "AAnimal destroyed!" << std::endl;
}
