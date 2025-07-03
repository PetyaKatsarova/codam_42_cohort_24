#include "ClapTrap.hpp"
#include <iostream>
#include <string>

ClapTrap::ClapTrap() : name("default"), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "ClapTrap default constructor\n";
}

ClapTrap::ClapTrap(const std::string& n) : name(n), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "ClapTrap constructor for " << name << "\n";
}

ClapTrap::ClapTrap(const ClapTrap& other) {
    *this = other;
    std::cout << "ClapTrap copy constructor\n";
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    if (this != &other) {
        name = other.name;
        hitPoints = other.hitPoints;
        energyPoints = other.energyPoints;
        attackDamage = other.attackDamage;
    }
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap destructor for " << name << "\n";
}

void ClapTrap::attack(const std::string& target) {
    if (energyPoints > 0 && hitPoints > 0) {
        std::cout << "ClapTrap " << name << " attacks " << target << " causing " << attackDamage << " damage!\n";
        energyPoints--;
    } else
        std::cout << "ClapTrap " << name << " can't attack!\n";
}

void ClapTrap::takeDamage(unsigned int amount) {
    hitPoints -= (hitPoints < amount) ? hitPoints : amount;
    std::cout << "ClapTrap " << name << " takes " << amount << " damage!\n";
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (energyPoints > 0 && hitPoints > 0) {
        hitPoints += amount;
        energyPoints--;
        std::cout << "ClapTrap " << name << " repairs for " << amount << "\n";
    } else
        std::cout << "ClapTrap " << name << " can't repair!\n";
}

void ClapTrap::setAttackDamage(unsigned int ad) {
    attackDamage = ad;
}
