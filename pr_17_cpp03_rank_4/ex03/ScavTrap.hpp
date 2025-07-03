#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <string>

/**
 * ScavTrap inherits virtually from ClapTrap to avoid duplication in DiamondTrap.
 */
 class ScavTrap : virtual public ClapTrap {
    public:
        ScavTrap();
        ScavTrap(const std::string& name);
        ScavTrap(const ScavTrap& other); // create new obj
        ScavTrap& operator=(const ScavTrap& other);
        ~ScavTrap();

        void attack(const std::string& target); // override
        void guardGate(); // new method   
};
 
#endif