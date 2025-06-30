#include <iostream>
#include <string>
#include "HumanA.hpp"
#include "Weapon.hpp"

HumanA::HumanA(const std::string &name, Weapon &weapon) : name(name), weapon(weapon) {
	std::cout << "HumanA created with name: " << name << " and weapon type: " << weapon.getType() << std::endl;
}

HumanA::~HumanA() {
	std::cout << "HumanA named '" << name << "' destroyed." << std::endl;
}
void HumanA::attack() const {
	std::cout << name << " attacks with their " << weapon.getType() << std::endl;
}