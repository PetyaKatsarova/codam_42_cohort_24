#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() : name("") {
	std::cout << name << " has been born!" << std::endl;
}

Zombie::~Zombie()  {
	std::cout << name << " has been destroyed." << std::endl;
}

void Zombie::announce() const {
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(const std::string &name) {
		std::cout << " Zombie has been given name: " << name << std::endl;
	this->name = name;
}