#include "Harl.hpp"
#include <iostream>

int main() {
    Harl harl;
    std::string input;

    while (true) {
        std::cout << "Enter log level (DEBUG, INFO, WARNING, ERROR or EXIT): ";
        std::getline(std::cin, input);

        if (input == "EXIT" || input == "exit")
            break;
        harl.complain(input);
    }
    return (0);
}