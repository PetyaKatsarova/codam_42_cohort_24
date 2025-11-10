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

AForm* Intern::makeForm(const std::string &name, const std::string &target) {
    if (name == "robotomy request") {
        std::cout << "Intern creates " << name << std::endl;
        return new RobotomyRequestForm(target);
    }
    if (name == "presidential pardon") {
        std::cout << "Intern creates " << name << std::endl;
        return new PresidentialPardonForm(target);
    }
    if (name == "schrubbery creation") {
        std::cout << "Intern creates " << name << std::endl;
        return new SchrubberyCreationForm(target);
    }
    std::cerr << "Error: Form '" << name << "' doesn't exist" << std::endl;
    return NULL;
}