#include "ScavTrap.hpp"
#include <iostream>

int main() {
    ClapTrap clappy("Clappy");
    ScavTrap scavy("Scavy");

    std::cout << "--------clappy attack -------\n";
    clappy.setAttackDamage(42);
    clappy.attack("ClappyEnemy");

    std::cout << "--------scavy attack -------\n";
    scavy.setAttackDamage(42);
    scavy.attack("ScavyEnemy");

    std::cout << "----------- repair -------" << std::endl;
    clappy.beRepaired(22);
    scavy.beRepaired(22);
    std::cout << "-------- take damage ----------\n";
    clappy.takeDamage(3);
    scavy.takeDamage(3);
    
    std::cout << "-------- guard gate ----------\n";
    scavy.guardGate();

    std::cout << "-------- copy constructor test ----------\n";
    ScavTrap scavyCopy(scavy); // Calls ScavTrap copy constructor
    scavyCopy.attack("EnemyCopy");
     std::cout << "-------- end funcs ----------\n";
    return 0;           // All destructors called
}