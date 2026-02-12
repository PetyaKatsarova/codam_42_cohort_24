#include "WrongAnimal.hpp"
#include <string>
#include <iostream>

WrongAnimal::WrongAnimal() : type("WrongAnimal") {
    std::cout << "WrongAnimal: default constr." << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) : type(other.type) {
    std::cout << "WrongAnimal: copy constr.\n";
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other) {
    std::cout << "WrongAnimal: Copy assignment operator called" << std::endl;
    if (this != &other)
        type = other.type;
    return *this;
}

void WrongAnimal::makeSound() const {
    std::cout << "A weird Wronganimal sound grrrrrr.." << std::endl;
}

std::string WrongAnimal::getType() const {
    return type;
}

WrongAnimal::~WrongAnimal() {
    std::cout << "WrongAnimal destroyed!" << std::endl;
}
