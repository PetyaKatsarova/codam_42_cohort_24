#include "Zombie.hpp"

#include <string>

void randomChump(std::string name) {
	// alloc on stack: auto-destroyed at end of scope:
	Zombie z(name);
	z.announce();
}