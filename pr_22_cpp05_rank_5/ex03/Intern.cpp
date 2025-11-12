#include "Intern.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "SchrubberyCreationForm.hpp"
#include <iostream>

enum FormType {
    ROBOTOMY,
    PRESEDENTIAL,
    SCHRUBBERY
};

// FACTORY PATTERN
Intern::Intern() {
    std::cout << "Intern created" << std::endl;
}

Intern::Intern(const Intern &other) {
    (void) other;
    std::cout << "Intern cp constr" << std::endl;
}

Intern::~Intern() {
    std::cout << "Intern destroyed" << std::endl;
}
Intern& Intern::operator=(const Intern& other) {
    (void) other;
    return *this;
}

// AForm* Intern::makeForm(const std::string &name, const std::string &target) {
//     if (name == "robotomy request") {
//         std::cout << "Intern creates " << name << std::endl;
//         return new RobotomyRequestForm(target);
//     }
//     if (name == "presidential pardon") {
//         std::cout << "Intern creates " << name << std::endl;
//         return new PresidentialPardonForm(target);
//     }
//     if (name == "schrubbery creation") {
//         std::cout << "Intern creates " << name << std::endl;
//         return new SchrubberyCreationForm(target);
//     }
//     std::cerr << "Error: Form '" << name << "' doesn't exist" << std::endl;
//     return NULL;
// }

static AForm* createRobotomy(const std::string &target) {
    return new RobotomyRequestForm(target);
}

static AForm* createPresidential(const std::string &target) {
    return new PresidentialPardonForm(target);
}

static AForm* createSchrubbery(const std::string &target) {
    return new SchrubberyCreationForm(target);
}

/**
AForm*  (*creators[3])  (const std::string &)
  ↓          ↓              ↓
Return    Array of      Function
 type     function       parameter
         pointers

const std::string* stringPointers[3] {
 &str1,
 &str2,
 &str3
}; ptr to strings
& has 2 Meanings
1. In Type Declaration → const std::string &name  // & means REFERENCE
2. In Expression → Address-of (Pointer) : &str1  // & means ADDRESS-OF (get pointer)
         */

Intern::FormNotFoundException::FormNotFoundException(const std::string &formN) : formName(formN) {}

Intern::FormNotFoundException::~FormNotFoundException() noexcept {}

const char* Intern::FormNotFoundException::what() const noexcept {
    msg = "Error: Form '" + formName + "' doesn't exist, wrong name";
    return msg.c_str(); // returns the address of first char of the msg str
}

AForm* Intern::makeForm(const std::string &name, const std::string &target) {
    const std::string formNames[3] = {
        "robotomy request",
        "presidential pardon",
        "schrubbery creation"
    };
    
    AForm* (*creators[3])(const std::string &) = {
        &createRobotomy, // address of func is &
        &createPresidential,
        &createSchrubbery
    };
    
    for (int i = 0; i < 3; i++) {
        if (name == formNames[i]) {
            std::cout << "Intern creates " << name << std::endl;
            return creators[i](target);
        }
    }
    
    throw Intern::FormNotFoundException(name);
}