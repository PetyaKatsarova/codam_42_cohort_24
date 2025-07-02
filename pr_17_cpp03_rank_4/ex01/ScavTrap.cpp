#include "ScavTrap.hpp"
#include <iostream>

// Default constructor
ScavTrap::ScavTrap()
    : ClapTrap("DefaultScav") {
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;
    std::cout << "ScavTrap default constructor called for " << name << std::endl;
}

// Param constructor
ScavTrap::ScavTrap(const std::string& name)
    : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;
    std::cout << "ScavTrap named constructor called for " << name << std::endl;
}

// Copy constructor
ScavTrap::ScavTrap(const ScavTrap& other)
    : ClapTrap(other) {
    std::cout << "ScavTrap copy constructor called for " << name << std::endl;
}

// Assignment operator
ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    std::cout << "ScavTrap assignment operator called\n";
    if (this != &other) {
        ClapTrap::operator=(other); // delegate to base assignment
    }
    return *this;
}

// Destructor
ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap destructor called for " << name << std::endl;
}

// Override attack
void ScavTrap::attack(const std::string& target) {
    if (hitPoints == 0 || energyPoints == 0) {
        std::cout << "ScavTrap " << name << " can't attack.\n";
        return;
    }
    --energyPoints;
    std::cout << "ScavTrap " << name
              << " slashes " << target
              << " for " << attackDamage << " damage! "
              << "(Energy left: " << energyPoints << ")\n";
}

// Unique method
void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << name << " is now in Gate keeper mode.\n";
}
