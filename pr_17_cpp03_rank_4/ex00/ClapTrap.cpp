#include "ClapTrap.hpp"
#include <iostream>
#include <string>

//Use const std::string& name in both header and source for performance (no unnecessary copy).
ClapTrap::ClapTrap(const std::string& name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0){
    std::cout << "ClapTrap with name " << name << " ,hitPoints=10, energhyPoints=10 and attackPoints=0 was created" << std::endl;
}

//Use initializer list to be cleaner and slightly faster:
ClapTrap::ClapTrap(const ClapTrap& other)
: name(other.name), hitPoints(other.hitPoints),
  energyPoints(other.energyPoints), attackDamage(other.attackDamage) {
    std::cout << "Copied!" << std::endl;
}


//Correct: checks self-assignment, copies members.
// Tip: Always return *this (it allows chaining like a = b = c;).
ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    if (this != &other) {
        std::cout << "Assigned!" << std::endl;
        name = other.name;
        attackDamage = other.attackDamage;
        energyPoints = other.energyPoints;
        hitPoints = other.hitPoints;
    }
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "Destroyed!" << std::endl;
    // delete dynamic memory if any
}

void ClapTrap::setAttackDamage(unsigned int ad) {
    this->attackDamage = ad;
}

void ClapTrap::attack(const std::string& target) {
    if (hitPoints == 0) {
        std::cout << "ClaTrap " << name << " has no hit points left and cant attack" << std::endl;
        return;
    }
    if (energyPoints == 0) {
        std::cout << "ClapTrap " << name << " has no energy left to attack" << std::endl;
        return;
    }
    --energyPoints;
    std::cout << "ClapTrap " << name
              << " attacks " << target
              << ", causing " << attackDamage
              << " points of damage! (Energy left: " << energyPoints << ")"
              << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
        if (hitPoints == 0) {
        std::cout << "ClaTrap " << name << " has no hit points left and cant repair itself" << std::endl;
        return;
    }
    if (energyPoints == 0) {
        std::cout << "ClapTrap " << name << " has no energy left to attack" << std::endl;
        return;
    }
    hitPoints += amount;
    --energyPoints;
    std::cout << "ClapTrap " << name
              << " repairs with " << amount << " hit points.\n"
              << "New hitPoints = " << hitPoints
              << "(Energy left: " << energyPoints << ")"
              << std::endl;
}

// hitPoints -= amount
void ClapTrap::takeDamage(unsigned int amount) {
        if (hitPoints == 0) {
        std::cout << "ClapTrap " << name << " has 0 hitPoints can't take more damage." << std::endl;
        return;
    }

    if (amount >= hitPoints)
        hitPoints = 0;
    else
        hitPoints -= amount;

    std::cout << "ClapTrap " << name
              << " takes " << amount << " points of damage! "
              << "Remaining hitPoints: " << hitPoints << std::endl;
}