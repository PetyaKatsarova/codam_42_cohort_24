#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

/* constructor using an initializer list:
PhoneBook::PhoneBook() → Constructor definition
: contactIndex(0), allContacts(0) → Initializer list
{} → Empty function body (nothing else done inside)
 */
PhoneBook::PhoneBook() : contactIndex(0), allContacts(0) {}

void PhoneBook::addContact() {
    contacts[contactIndex].setInfo();
    if (!contacts[contactIndex].isEmpty()) {
        contactIndex = (contactIndex + 1) % 8;
        if (allContacts < 8)
            allContacts++;
    }
}

void PhoneBook::searchContact() const {
    if (allContacts == 0) {
        std::cout << "Phonebook is empty.\n";
        return;
    }
    
    std::cout << std::endl;
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "nickName" << std::endl;

    for (int i = 0; i < allContacts; i++) {
        contacts[i].displayShort(i+1);
        std::cout << std::endl;
    }
    
    std::cout << "\nEnter index to view details: ";
    std::string input;
    std::getline(std::cin, input);
    if (input.length() == 1 && std::isdigit(input[0])) {
        int i = input[0] - '0';
        if (i >= 1 && i <= allContacts) {
            contacts[i-1].displayFull();
            return;
        }
    }
    std::cout << "Invalid index." << std::endl;
}