#ifndef _ICE_HPP
#define _ICE_HPP

#include <string>
#include <iostream>
#include "AMateria.hpp"
#include "ICharacter.hpp"

class Ice : public AMateria {

    public:
        Ice();
        Ice(const std::string &type);
        Ice(const Ice& other);
        Ice& operator=(const Ice& other);
        ~Ice();

        virtual AMateria* clone() const override;
        virtual void use(ICharacter& target) override;
};

#endif