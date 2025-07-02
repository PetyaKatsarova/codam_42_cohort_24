#include "ClapTrap.hpp"
#include <iostream>

int main() {
    ClapTrap a("A");
    ClapTrap b = a;     // Copy constructor
    ClapTrap c("C");
    c = a;              // Copy assignment

    std::cout << "-------- attack -------" << std::endl;
    b.setAttackDamage(42);
    b.attack("Enemy");
    std::cout << "----------- repair -------" << std::endl;
    b.beRepaired(22);
    std::cout << "-------- take damage ----------" << std::endl;
    b.takeDamage(3);
    std::cout << "-------- funcs end -------" << std::endl;

    return 0;           // All destructors called
}