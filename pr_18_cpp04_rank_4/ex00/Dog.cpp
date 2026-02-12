#include "Dog.hpp"
#include <string>
#include <iostream>

Dog::Dog() {
    type = "Dog";
    std::cout << "Dog: default constr." << std::endl;
}

/*
Animal(other) calls the Animal copy constructor with the Dog object as the argument.
*/
Dog::Dog(const Dog& other) : Animal(other) {
    type = other.type;
    std::cout << "Dog: copy constr.\n";
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog: Copy assignment operator called" << std::endl;
    if (this != &other)
        Animal::operator=(other);
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog destroyed!" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "Bau bau" << std::endl;
}