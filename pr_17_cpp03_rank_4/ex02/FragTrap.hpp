#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"
#include <string>

 class FragTrap : public ClapTrap {
    public:
        FragTrap();
        FragTrap(const std::string& name);
        FragTrap(const FragTrap& other); // create new obj
        FragTrap& operator=(const FragTrap& other);
        ~FragTrap();

        void attack(const std::string& target); // override
        void highFivesGuys(void);
};
 
#endif