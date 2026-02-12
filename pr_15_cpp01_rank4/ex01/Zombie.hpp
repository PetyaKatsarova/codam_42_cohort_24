
#ifndef _ZOMBIE_HPP
#define _ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {

	public:

		Zombie();
		~Zombie();
		void announce(void) const;
		void setName(const std::string &name);

	private:

		std::string name;
};

Zombie* zombieHorde( int N, std::string name );

#endif