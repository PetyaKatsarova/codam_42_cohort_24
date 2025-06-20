#include "Zombie.hpp"

/*
must allocate N Zombie objects in a single allocation. Then, it must initialize the
zombies, giving each of them the name passed as a parameter. The function returns a
pointer to the first zombie.
*/

Zombie* zombieHorde( int N, std::string name ) {
	if (N <= 0) {
		std::cerr << "Error: Number of zombies must be greater than 0." << std::endl;
		return nullptr;
	}

	// The runtime asks for enough raw bytes to hold N Zombie objects contiguously and create n zombie obj with name from default constr

	Zombie* horde = new Zombie[N];

	for (int i = 0; i < N; ++i)
		horde[i].setName(name);

	return horde; // Return pointer to the first Zombie in the horde
}
