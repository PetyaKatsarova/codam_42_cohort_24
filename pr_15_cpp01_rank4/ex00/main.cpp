#include "Zombie.hpp"

//c++ -Wall -Wextra -Werror main.cpp Zombie.cpp newZombie.cpp randomChump.cpp -o zombies
int main( ){

	// on the heap
	Zombie *z1 = newZombie("Heapie");
	z1->announce();
	delete z1;

	// on the stack
	randomChump("Stackie");
	// no need to del, destructor runs at func exit

	return (0);
}