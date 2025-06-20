#include "PhoneBook.hpp"
#include <iostream>

int main () {
    PhoneBook   pb;
    std::string command;

    while (true) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);

        if (command == "ADD" || command == "add")
            pb.addContact();
        else if (command == "SEARCH" || command == "search")
            pb.searchContact();
        else if (command == "EXIT" || command == "exit")
            break;
        else
            std::cout << "Unknown command. " << std::endl;
    }
    return (0);
}
