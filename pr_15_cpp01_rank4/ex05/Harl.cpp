#include "Harl.hpp"
#include <iostream>

void Harl::debug() {
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info() {
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning() {
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." << std::endl;
}

void Harl::error() {
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level) {
    std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR"};
	// array of pointers to member functions 
	void (Harl::*funcs[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	int flag = 1;

	// size_t = long unsigned int
	for (size_t i = 0; i < sizeof(levels) / sizeof(levels[0]); ++i) {
		if (level == levels[i]) {
			(this->*funcs[i])();
			flag = 0;
		}
	}
	if (flag)
		std::cout << "Naughty naughty. You can choose from: DEBUG, INFO, WARNING, ERROR" << std::endl;
}

/*
!!NB!!
 sizeof(levels[0]) means:
The size in bytes of the first element of the array, i.e., levels[0], which is a std::string.

In most systems, sizeof(std::string) returns the same fixed number, usually 24 or 32 bytes, because it's just the size of the string object, not the text.

It does not depend on the actual length of the string like "DEBUG" vs "ERROR"
-------------------------------------

void sayHello() {
  std::cout << "Hi!\n";
}
sayHello;    // refers to the function
sayHello();  // Calls it
---------------------------
void Harl::say(std::string message)
Then the pointer type would be:

void (Harl::*methods[])(std::string)
And the call would look like:

(this->*methods[i])("hello");
*/
