#include <iostream>
#include "Bureacrat.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "SchrubberyCreationForm.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

int main() {
    Intern intern;
    AForm* robo_form = intern.makeForm("robotomy request", "Robot");  //sing  72, exec  45
    AForm* presi_form = intern.makeForm("presidential pardon", "President"); //sign 25, exec 5
    // AForm* schrub_form = NULL;
    AForm* schrub_form = intern.makeForm("schrubbery creation", "Schrub"); //sign 145, exec 137

    if (!robo_form || !presi_form || !schrub_form) {
        std::cerr << "Form creation failed!" << std::endl;
        delete robo_form;
        delete presi_form;
        delete schrub_form;
        return 1;
    }

    Bureacrat b("Boss", 42);
    b.signForm(*robo_form); // yes
    b.signForm(*presi_form); // no
    b.signForm(*schrub_form); // yes

    b.executeForm(*robo_form); // yes
    b.executeForm(*presi_form); // no
    b.executeForm(*schrub_form); // yes

    delete robo_form;
    delete presi_form;
    delete schrub_form;
    return 0;
}