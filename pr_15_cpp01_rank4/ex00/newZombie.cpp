#include "Zombie.hpp"

#include <string>

/*
creates a zombie, names it, and returns it so you can use it outside
of the function scope.
*/
Zombie *newZombie(std::string name) {
	// alloc on heap: lives till del is called
	return new Zombie(name);
}