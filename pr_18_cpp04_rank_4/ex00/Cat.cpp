#include "Cat.hpp"
#include <string>
#include <iostream>

Cat::Cat() {
    type = "Cat";
     std::cout << "Cat: default constr." << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
    type = other.type;
    std::cout << "Cat: copy constr.\n";
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat: Copy assignment operator called" << std::endl;
    if (this != &other)
        Animal::operator=(other);
    return *this;
}

Cat::~Cat() {
    std::cout << "Cat destroyed!" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Miao miao" << std::endl;
}
