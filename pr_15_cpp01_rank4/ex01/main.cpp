#include "Zombie.hpp"
#include <iostream>


void zombieHordeTest(int N, const std::string& name) {
	Zombie* horde = zombieHorde(N, name);
	if (horde) {
		for (int i = 0; i < N; ++i) {
			horde[i].announce(); // Announce each zombie
		}
		delete[] horde; // Clean up allocated memory
	} else {
		std::cout << "Failed to create zombie horde." << std::endl;
	}
}

int main() {
	std::cout << "---------- Test with 5 --------------" << std::endl;
	zombieHordeTest(5, "Zombie");
	std::cout << "---------- Test with 0 --------------" << std::endl;
	zombieHordeTest(0, "Zombie"); // Test with invalid number of zombies
	std::cout << "---------- Test with -3 --------------" << std::endl;
	zombieHordeTest(-3, "Zombie"); // Test with negative number of zombies	

	return 0;
}
