#include <iostream>
#include "Bureacrat.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "SchrubberyCreationForm.hpp"

int main() {
    RobotomyRequestForm robo_form("robo_form"); // sing  72, exec  45
    PresidentialPardonForm trump_form("trump_form"); //sign 25, exec 5
    SchrubberyCreationForm shrub_form("shrub_form");  //sign 145, exec 137

    try {
        printf("------ sign/exec presidential form ------------\n");
        Bureacrat testie("testie", 24);
        Bureacrat testie1("testie1", 25);
        Bureacrat testie2("testie2", 5);
        Bureacrat testie3("testie3", 26);
        testie.signForm(trump_form); // 25 or less
        testie1.signForm(trump_form);
        testie3.signForm(trump_form); // fail
        testie2.signForm(trump_form);
        testie.executeForm(trump_form); // fail
        testie2.executeForm(trump_form); // success

        printf("------ sign/exec RobotomyRequestForm ------------\n"); //sing > 72, exec > 45
        Bureacrat t1("t1", 72); //sign - yes, exec - no
        Bureacrat t2("t2", 73); // sign - no
        Bureacrat t3("t3", 46); // sign - yes, exec - no
        Bureacrat t4("t4", 44); // all yes
        t1.signForm(robo_form);
        t2.signForm(robo_form);
        t3.signForm(robo_form); // fail
        t4.signForm(robo_form);
        t1.executeForm(robo_form); // fail
        t3.executeForm(robo_form); // fail
        t4.executeForm(robo_form); // success

        printf("------ sign/exec SchrubberyCreationForm ------------\n"); //sign 145, exec 137
        Bureacrat t11("t11", 138); //sign - yes, exec - no
        Bureacrat t12("t12", 146); // sign - no
        Bureacrat t13("t13", 145); // sign - yes, exec - no
        Bureacrat t14("t14", 137); // all yes

        t11.signForm(shrub_form);
        t12.signForm(shrub_form); // fail
        t13.signForm(shrub_form); // success 145
        t14.signForm(shrub_form);
        t11.executeForm(shrub_form); // fail
        t12.executeForm(shrub_form); // fail
        t14.executeForm(shrub_form); // success
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        printf("-- second try ---\n");
        Bureacrat zero("z", 0);
    } catch (const std::exception &e) {
        std::cerr << "naughty, naughty... " << e.what() << std::endl;
    }
    return 0;
}