
#ifndef _CLAP_TRAP
#define _CLAP_TRAP

// #include <iostream>
#include <string>

class ClapTrap {

    protected:
        std::string     name;
        unsigned int    hitPoints;
        unsigned int    energyPoints;
        unsigned int    attackDamage;

    public:
        ClapTrap();
        ClapTrap(const std::string& name);
        ClapTrap(const ClapTrap& other); // copy: creates new obj
        ClapTrap& operator = (const ClapTrap& other); // copy assignement: assigns new vals to existing obj
        virtual ~ClapTrap(); // for inheritance

        virtual void attack(const std::string& target); // to be able to override
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        void setAttackDamage(unsigned int ad);
};

#endif