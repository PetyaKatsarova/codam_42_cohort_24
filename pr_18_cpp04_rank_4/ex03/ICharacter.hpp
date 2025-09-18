#ifndef _AANIMAL_HPP
#define _AANIMAL_HPP

#include "AMateria.hpp"
#include <string>

class ICharacter
{
public:
    virtual ~ICharacter() {}
    virtual std::string const & getName() const = 0;
    virtual void equip(AMateria* m) = 0;
    virtual void unequip(int i) = 0;
    virtual void use(int i, ICharacter& target) = 0;
};

#endif