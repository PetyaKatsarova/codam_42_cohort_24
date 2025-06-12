/**
 * std::string: length(), substr(), empty(), getline()
 * <iomanip>: std::setw, std::right
 */

 #include "PhoneBook.hpp"
 #include <iostream>
 #include <iomanip>

 void Contact::setInfo() {
    std::cout << "First name: ";
    std::getline(std::cin, firstName);

    std::cout << "Last name: ";
    std::getline(std::cin, lastName);

    std::cout << "nickName: ";
    std::getline(std::cin, nickName);

    std::cout << "Phone num: ";
    std::getline(std::cin, phoneNum);

    std::cout << "Darkest secret: ";
    std::getline(std::cin, darkestSecret);

    if (firstName.empty() || lastName.empty() || nickName.empty() ||
        phoneNum.empty() || darkestSecret.empty()) {
        std::cout << "All fields must be filled!" << std::endl;
        *this = Contact(); // Reset contact
    }
 }

bool Contact::isEmpty() const {
    return firstName.empty();
}

void Contact::displayShort(int i) const {
    auto formatField = [](const std::string &str) {
        return str.length() > 10 ? str.substr(0, 9) + "." : str;
    };

    std::cout << std::setw(10) << i << "|"
    << std::setw(10) << formatField(firstName) << "|"
    << std::setw(10) << formatField(lastName) << "|"
    << std::setw(10) << formatField(nickName) << "|";
}

void Contact::displayFull() const {
    std::cout << "First Name: " << firstName << std::endl;
    std::cout << "Last Name: " << lastName << std::endl;
    std::cout << "nickName: " << nickName << std::endl;
    std::cout << "Phone Number: " << phoneNum << std::endl;
    std::cout << "Darkest Secret: " << darkestSecret << std::endl;
}
