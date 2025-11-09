#include <iostream>
#include "Bureacrat.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "SchrubberyCreationForm.hpp"

// c++ -std=c++11 -Wall -Wextra -Werror main.cpp && ./a.out
/**
c++ -std=c++11 main.cpp & ./a.out
cool:
c++ -std=c++11 [main.cpp](http://_vscodecontentref_/0) & — starts compilation in background (doesn't wait)
./a.out — immediately tries to run (but a.out doesn't exist yet because compilation is still running)
Result: No such file or directory

 c++ -std=c++11 -Wall -Wextra -Werror \
    main.cpp \
    Bureacrat.cpp \
    AForm.cpp \
    SchrubberyCreationForm.cpp \
    RobotomyRequestForm.cpp \
    PresidentialPardonForm.cpp \
    -o main && ./main
*/
int main() {
    printf("Hello W\n");
    Bureacrat burie("Burie", 46);
    Bureacrat b2("B2", 42);
    RobotomyRequestForm robo_form("robo_form");
    PresidentialPardonForm trump_form("trump_form");
    SchrubberyCreationForm shrub_form("shrub_form");

    std::cout << "b1: " << burie << "b2: " << b2 << std::endl;

    try {
         burie.signForm(robo_form);
	burie.executeForm(robo_form);

    b2.signForm(trump_form);
    b2.signForm(shrub_form);
    b2.executeForm(trump_form);
    b2.executeForm(shrub_form);
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}