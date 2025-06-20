#include "Zombie.hpp"

#include <string>


/*
creates a zombie, names it, and makes it announce itself.
*/
void randomChump(std::string name) {
	// alloc on stack: auto-destroyed at end of scope:
	Zombie z(name);
	z.announce();
}