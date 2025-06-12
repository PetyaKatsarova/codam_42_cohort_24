#include "PhoneBook.hpp"
#include <iostream>

int main () {
    PhoneBook   pb;
    std::string command;

    while (true) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);

        if (command == "ADD")
            pb.addContact();
        else if (command == "SEARCH")
            // std::cout << "search under construction" << std::endl;
            pb.searchContact();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Unknown command. " << std::endl;
    }
    return (0);
}
