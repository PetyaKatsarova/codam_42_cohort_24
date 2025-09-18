#include "Character.hpp"
#include <iostream>

Character::Character(std::string const & name) : name(name) {
    for (int i = 0; i < MAX_SLOTS; i++) {
        inventory[i] = nullptr;
    }
}

Character::Character(const Character& other) : name(other.name) {
    for (int i = 0; i < MAX_SLOTS; i++) {
        inventory[i] = other.inventory[i] ? other.inventory[i]->clone() : nullptr;
    }
}

Character::~Character() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        delete inventory[i];
    }
}

Character& Character::operator=(const Character& other) {
    if (this != &other) {
        name = other.name;
        for (int i = 0; i < MAX_SLOTS; i++) {
            delete inventory[i];
            inventory[i] = other.inventory[i] ? other.inventory[i]->clone() : nullptr;
        }
    }
    return *this;
}

std::string const & Character::getName() const { return name; }

void Character::equip(AMateria* m) {
    if (!m) return;
    
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (!inventory[i]) {
            inventory[i] = m;
            return;
        }
    }
}

void Character::unequip(int i) {
    if (i >= 0 && i < MAX_SLOTS) {
        inventory[i] = nullptr;
    }
}

void Character::use(int i, ICharacter& target) {
    if (i >= 0 && i < MAX_SLOTS && inventory[i]) {
        inventory[i]->use(target);
    }
}