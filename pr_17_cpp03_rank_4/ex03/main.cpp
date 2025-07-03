#include "DiamondTrap.hpp"
#include <iostream>

int main() {
    std::cout << "\n ------------ Creating DiamondTrap...\n";
    DiamondTrap d1("Diamond");

    std::cout << "\n ------------ Testing attack() (from ScavTrap)...\n";
    d1.attack("Target");

    std::cout << "\n ------------ Testing takeDamage() & beRepaired() (from ClapTrap)...\n";
    d1.takeDamage(30);
    d1.beRepaired(20);

    std::cout << "\n ------------ Testing whoAmI()...\n";
    d1.whoAmI();

    std::cout << "\n ------------ Testing copy constructor...\n";
    DiamondTrap d2(d1);
    d2.whoAmI();

    std::cout << "\n ------------ Testing assignment operator...\n";
    DiamondTrap d3;
    d3 = d1;
    d3.whoAmI();

    std::cout << "\n Destructor test (on return)...\n";
    return 0;
}
