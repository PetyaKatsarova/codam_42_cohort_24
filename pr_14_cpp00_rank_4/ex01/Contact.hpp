#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
private:
    std::string firstName, lastName, nickName;
    std::string phoneNum, darkestSecret;

public:
    void setInfo();
    void displayShort(int i) const;
    void displayFull() const;
    bool isEmpty() const;
};

#endif