#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
    private:
        void debug();
        void info();
        void warning();
        void error();

    public:
        void complain( std::string level );
};

#endif

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