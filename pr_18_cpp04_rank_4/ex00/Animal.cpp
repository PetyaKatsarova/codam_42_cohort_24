#include "Animal.hpp"
#include <string>
#include <iostream>

Animal::Animal() : type("Animal") {
    std::cout << "Animal: default constr.\n;";
}

Animal::Animal(const Animal& other) : type(other.type) {
    std::cout << "Animal: copy constr.\n";
}

Animal& Animal::operator=(const Animal& other) {
    std::cout << "Animal: Copy assignment operator called" << std::endl;
    if (this != &other)
        type = other.type;
    return *this;
}

void Animal::makeSound() const {
    std::cout << "A weird animal sound grrrrrr.." << std::endl;
}

std::string Animal::getType() const {
    return type;
}

Animal::~Animal() {
    std::cout << "Animal destroyed!" << std::endl;
}
