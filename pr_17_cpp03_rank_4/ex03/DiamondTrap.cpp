#include "DiamondTrap.hpp"
#include <string>
#include <iostream>


DiamondTrap::DiamondTrap()
    : ClapTrap("Default_clap_name"), ScavTrap(), FragTrap(), name("Default") {
        hitPoints = FragTrap::hitPoints;
        energyPoints = ScavTrap::energyPoints;
        attackDamage = FragTrap::attackDamage;
        std::cout << "DiamondTrap default constructor called for\n";
}

DiamondTrap::DiamondTrap(const std::string& n)
 : ClapTrap(n + "_clap_name"), ScavTrap(), FragTrap(), name(n) {
    hitPoints = FragTrap::hitPoints;
    energyPoints = ScavTrap::energyPoints;
    attackDamage = FragTrap::attackDamage;
    std::cout << "DiamondTrap constructor called for " << name << std::endl;
 }

 // copy constr
 DiamondTrap::DiamondTrap(const DiamondTrap& other)
    :ClapTrap(other), ScavTrap(other), FragTrap(other), name(other.name) {
        std::cout << "DiamondTrap copy constructor called for " << name << std::endl;
}

// assignment operator
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    std::cout << "DiamondTrap assignment operator called\n";
    if (this != &other) {
        ClapTrap::operator=(other);
        name = other.name;
    }
    return *this;
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap destructor called for " << name << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target);
}

// shadowing: name var the same
void DiamondTrap::whoAmI() {
    std::cout << "I am " << name << ", and my ClapTrap name is " << ClapTrap::name << std::endl;
}
