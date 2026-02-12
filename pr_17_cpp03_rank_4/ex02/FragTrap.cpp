#include "FragTrap.hpp"
#include <iostream>

/**
 *  

FragTrap has a special ability too:
void highFivesGuys(void);
This member function displays a positive high-fives request on the standard output.
 */

FragTrap::FragTrap()
    : ClapTrap("DefaultFrag") {
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;
    std::cout << "FragTrap default constructor called for " << name << std::endl;
}

FragTrap::FragTrap(const std::string& name)
    : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;
    std::cout << "FragTrap constructor called for " << name << std::endl;
}

// Copy constructor
FragTrap::FragTrap(const FragTrap& other)
    : ClapTrap(other) {
    std::cout << "FragTrap copy constructor called for " << name << std::endl;
}

// Assignment operator
FragTrap& FragTrap::operator=(const FragTrap& other) {
    std::cout << "FragTrap assignment operator called\n";
    if (this != &other) {
        ClapTrap::operator=(other); // delegate to base assignment
    }
    return *this;
}

// Destructor
FragTrap::~FragTrap() {
    std::cout << "FragTrap destructor called for " << name << std::endl;
}

// Override attack
void FragTrap::attack(const std::string& target) {
    if (hitPoints == 0 || energyPoints == 0) {
        std::cout << "FragTrap " << name << " can't attack.\n";
        return;
    }
    --energyPoints;
    std::cout << "FragTrap " << name
              << " slashes " << target
              << " for " << attackDamage << " damage! "
              << "(Energy left: " << energyPoints << ")\n";
}

void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << name << " positively gives high five :)\n";
}
