#include "Dog.hpp"
#include <string>
#include <iostream>

Dog::Dog() {
    type = "Dog";
    brain = new Brain();
    std::cout << "Dog: default constr." << std::endl;
}

/*
Animal(other) calls the Animal copy constructor with the Dog object as the argument.
*/
Dog::Dog(const Dog& other) : Animal(other) {
    type = other.type;
    brain = new Brain(*other.brain);
    std::cout << "Dog: copy constr.\n";
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog: Copy assignment operator called" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        type = other.type;
        if (brain)
            delete(brain);
        brain = new Brain(*other.brain);
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog destroyed!" << std::endl;
    delete brain;
}

void Dog::makeSound() const {
    std::cout << "Bau bau" << std::endl;
}

Brain* Dog::getBrain() const {
    return brain;
}