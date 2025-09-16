#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
    std::cout << "Brain: default constructor" << std::endl;
}

Brain::Brain(const Brain& other) {
    for (int i = 0; i < 100; ++i) {
        ideas[i] = other.ideas[i];
    }
    std::cout << "Brain: copy constructor" << std::endl;
}

Brain& Brain::operator=(const Brain& other) {
    if (this != &other) {
        for (int i = 0; i < 100; ++i)
            ideas[i] = other.ideas[i];
    }
    std::cout << "Brain: copy assignment operator" << std::endl;
    return *this;
}

Brain::~Brain() {
    std::cout << "Brain: destructor" << std::endl;
}

void Brain::setIdea(int i, const std::string& idea) {
    if (i >= 0 && i < 100)
        ideas[i] = idea;
}

std::string Brain::getIdea(int i) const {
    if ( i >= 0 && i < 100)
        return ideas[i];
    return "";
}