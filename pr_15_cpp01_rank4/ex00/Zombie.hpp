
#ifndef _ZOMBIE_HPP
#define _ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {

	public:

		Zombie(const std::string& name);
		~Zombie();
		void announce(void) const;

	private:

		std::string name;
};

Zombie *newZombie(const std::string name);
void	randomChump(const std::string name);

#endif