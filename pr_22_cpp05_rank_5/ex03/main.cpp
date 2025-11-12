#include "Bureacrat.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "SchrubberyCreationForm.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>

int main() {
    Intern intern;
    AForm* robo_form = NULL;
    AForm* presi_form = NULL;
    AForm* schrub_form = NULL;
    AForm* invalid_form = NULL;

    try {
        robo_form = intern.makeForm("robotomy request", "Robot");  //sing  72, exec  45
        presi_form = intern.makeForm("presidential pardon", "President"); //sign 25, exec 5
        // AForm* schrub_form = NULL;
        schrub_form = intern.makeForm("schrubbery creation", "Schrub"); //sign 145, exec 137
        printf("-- invalid form name --\n");
        invalid_form = intern.makeForm("invalid form", "Bla");
    } catch (std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        delete robo_form;
        delete presi_form;
        delete invalid_form;
        delete schrub_form;
        return 1; // valgrind will return error 1
        // return 0;
    }

    Bureacrat b("Boss", 42);
    b.signForm(*robo_form); // yes
    b.signForm(*presi_form); // no
    b.signForm(*schrub_form); // yes
    b.signForm(*invalid_form);

    // b.signForm(*invalid_form);

    b.executeForm(*robo_form); // yes
    b.executeForm(*presi_form); // no
    b.executeForm(*schrub_form); // yes

    delete robo_form;
    delete presi_form;
    delete schrub_form;
    delete invalid_form;

    return 0;
}