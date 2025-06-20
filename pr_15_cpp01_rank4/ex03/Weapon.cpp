#include "Weapon.hpp"
#include <iostream>
#include <string>


Weapon::Weapon(const std::string& type) : type(type) {
	std::cout << "Weapon created with type: " << type << std::endl;
}

Weapon::~Weapon() {
	std::cout << "Weapon of type '" << type << "' destroyed." << std::endl;
}
void Weapon::setType(const std::string& newType) {
	type = newType;
	std::cout << "Weapon type set to: " << type << std::endl;
}

const std::string& Weapon::getType() const {
	return type;
}
