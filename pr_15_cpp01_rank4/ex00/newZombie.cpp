#include "Zombie.hpp"

#include <string>

Zombie *newZombie(std::string name) {
	// alloc on heap: lives till del is called
	return new Zombie(name);
}