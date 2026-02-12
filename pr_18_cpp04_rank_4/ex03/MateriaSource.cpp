#include "MateriaSource.hpp"
#include <iostream>

MateriaSource::MateriaSource() {
    for (int i = 0; i < MAX_LEARN; i++) {
        learned[i] = nullptr;
    }
}

MateriaSource::MateriaSource(const MateriaSource& other) {
    for (int i = 0; i < MAX_LEARN; i++) {
        learned[i] = other.learned[i] ? other.learned[i]->clone() : nullptr;
    }
}

MateriaSource::~MateriaSource() {
    for (int i = 0; i < MAX_LEARN; i++) {
        delete learned[i];
    }
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
    if (this != &other) {
        for (int i = 0; i < MAX_LEARN; i++) {
            delete learned[i];
            learned[i] = other.learned[i] ? other.learned[i]->clone() : nullptr;
        }
    }
    return *this;
}

void MateriaSource::learnMateria(AMateria* m) {
    if (!m) return;
    
    for (int i = 0; i < MAX_LEARN; i++) {
        if (!learned[i]) {
            learned[i] = m;
            return;
        }
    }
    delete m;
}

AMateria* MateriaSource::createMateria(std::string const & type) {
    for (int i = 0; i < MAX_LEARN; i++) {
        if (learned[i] && learned[i]->getType() == type) {
            return learned[i]->clone();
        }
    }
    return nullptr;
}