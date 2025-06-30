#include "Harl.hpp"
#include <iostream>

void Harl::debug() {
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info() {
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger!" << std::endl;
}

void Harl::warning() {
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years..." << std::endl;
}

void Harl::error() {
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level) {
    std::string
}

/*
void Harl::complain(std::string level) {
	std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
	void (Harl::*methods[])() = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };

	for (int i = 0; i < 4; ++i) {
		if (level == levels[i]) {
			(this->*methods[i])(); // call the function using pointer to member
			return;
		}
	}

*/