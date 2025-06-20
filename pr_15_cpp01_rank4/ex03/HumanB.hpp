#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <string>

class HumanB {


	public:
		HumanB(const std::string &name);
		~HumanB();

		void setWeapon(Weapon &weapon);
		void attack() const;

	private:
		std::string name;
		Weapon *weapon;

};

#endif