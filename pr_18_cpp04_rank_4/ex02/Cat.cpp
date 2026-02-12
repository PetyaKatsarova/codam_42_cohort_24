#include "Cat.hpp"
#include <string>
#include <iostream>

Cat::Cat() {
    type = "Cat";
    brain = new Brain();
    std::cout << "Cat: default constr." << std::endl;
}

Cat::Cat(const Cat& other) : AAnimal(other) {
    type = other.type;
    brain = new Brain(*other.brain);
    std::cout << "Cat: copy constr.\n";
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat: Copy assignment operator called" << std::endl;
    if (this != &other) {
        AAnimal::operator=(other);
        type = other.type;
        if (brain)
            delete brain;
        brain = new Brain(*other.brain);
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "Cat destroyed!" << std::endl;
    delete brain;
}

void Cat::makeSound() const {
    std::cout << "Miao miao" << std::endl;
}

Brain* Cat::getBrain() const {
    return brain;
}
