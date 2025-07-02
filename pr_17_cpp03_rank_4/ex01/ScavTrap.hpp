#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"
#include <string>

/**
 * ScavTrap is a subclass (child) of ClapTrap
It inherits all members of ClapTrap
But it overrides some behavior (like attack())
It adds a new function: guardGate()

You do not need to redeclare or reimplement inherited constructors in ScavTrap unless you want to change their behavior (e.g. print different messages, set different initial values).
 */

 class ScavTrap : public ClapTrap {
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