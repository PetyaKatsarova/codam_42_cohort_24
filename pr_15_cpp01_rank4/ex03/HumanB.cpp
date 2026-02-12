#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string &name) : name(name), weapon(nullptr) {
	std::cout << "HumanB created with name: " << name << std::endl;
}

HumanB::~HumanB() {
	std::cout << "HumanB named '" << name << "' destroyed." << std::endl;
}

void HumanB::setWeapon(Weapon &weapon) {
	this->weapon = &weapon;
	std::cout << "Weapon set for HumanB named '" << name << "': " << weapon.getType() << std::endl;
}

void HumanB::attack() const {
	if (weapon) {
		std::cout << name << " attacks with their " << weapon->getType() << std::endl;
	} else {
		std::cout << name << " has no weapon to attack with." << std::endl;
	}
}
