#include "FragTrap.hpp"
#include <iostream>

int main() {
    std::cout << "--- Constructor test ---\n";
    FragTrap frag("Fraggy");

    std::cout << "\n--- Attack test ---\n";
    frag.setAttackDamage(42);
    frag.attack("TargetOne");

    std::cout << "\n--- Repair test ---\n";
    frag.beRepaired(25);

    std::cout << "\n--- Take damage test ---\n";
    frag.takeDamage(10);

    std::cout << "\n--- High fives test ---\n";
    frag.highFivesGuys();

    std::cout << "\n--- Copy constructor test ---\n";
    FragTrap fragCopy(frag);
    fragCopy.attack("CopiedTarget");

    std::cout << "\n--- Assignment operator test ---\n";
    FragTrap anotherFrag;
    anotherFrag = frag;
    anotherFrag.attack("AssignedTarget");

    std::cout << "\n--- End ---\n";
    return 0;
}