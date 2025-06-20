/*
Exercise : 03

9
C++ - Module 01
Memory allocation, pointers to members,
references and switch statements
If your implementation is correct, executing the following code will print an attack
with "crude spiked club" followed by a second attack with "some other type of club" for
both test cases:
int main()
{
{
Weapon club = Weapon("crude spiked club");
HumanA bob("Bob", club);
bob.attack();
club.setType("some other type of club");
bob.attack();
}
{
Weapon club = Weapon("crude spiked club");
HumanB jim("Jim");
jim.setWeapon(club);
jim.attack();
club.setType("some other type of club");
jim.attack();
}
return 0;
}
Do not forget to check for memory leaks.
In which case do you think it would be best to use a pointer to
Weapon? And a reference to Weapon? Why? Think about it before
starting this exercise.
*/
#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"
#include <iostream>

int main() {
	std::cout << "---- weapon test ----" << std::endl;
	Weapon club = Weapon("crude spiked club");
	std::cout << "---- HumanA test ----" << std::endl;
	HumanA bob("Bob", club);
	std::cout << "---- HumanA attacks ----" << std::endl;
	bob.attack();
	std::cout << "---- Weapon set other Type ----" << std::endl;
	club.setType("some other type of club");
	std::cout << "---- HumanA attacks ----" << std::endl;
	bob.attack();

	std::cout << std::endl;
	std::cout << "---- weapon test ----" << std::endl;
	Weapon club2 = Weapon("crude spiked club2");
	std::cout << "---- HumanB test ----" << std::endl;
	HumanB jim("Jim");
	std::cout << "---- HumanB set weapon ----" << std::endl;
	jim.setWeapon(club2);
	std::cout << "---- HumanB attacks ----" << std::endl;
	jim.attack();
	std::cout << "---- Weapon set other Type ----" << std::endl;
	club2.setType("some other type of club2");
	std::cout << "---- HumanB attacks ----" << std::endl;
	jim.attack();
	
	return 0;
}