#include "WrongCat.hpp"
#include <string>
#include <iostream>

WrongCat::WrongCat() {
    type = "WrongCat";
     std::cout << "WrongCat: default constr." << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : Animal(other) {
    type = other.type;
    std::cout << "WrongCat: copy constr.\n";
}

WrongCat& WrongCat::operator=(const WrongCat& other) {
    std::cout << "WrongCat: Copy assignment operator called" << std::endl;
    if (this != &other)
        Animal::operator=(other);
    return *this;
}

WrongCat::~WrongCat() {
    std::cout << "WrongCat destroyed!" << std::endl;
}

void WrongCat::makeSound() const {
    std::cout << "Miao miao" << std::endl;
}
