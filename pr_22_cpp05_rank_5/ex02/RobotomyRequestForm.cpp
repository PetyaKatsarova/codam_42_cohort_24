#include "RobotomyRequestForm.hpp"
#include "Bureacrat.hpp"
#include <iostream>
#include <random>

RobotomyRequestForm::
RobotomyRequestForm(const std::string &target) : AForm(target, 72, 45) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other){}

void RobotomyRequestForm::execute(Bureacrat const &executor) const {
    validate_form_bureacrat(executor);
    std::cout << "** BZZZZZZ ** DRRRR * DRBZ ** " << std::endl;
    // 50% success rate otherwise failed
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0,1);

    // returns 0 or 1, with 50% probability
    if (dist(gen) == 0) {
        std::cout << getTarget() << " has been robotomized successfully!" << std::endl;
    } else {
        std::cout << "Robotomy failed on " << getTarget() << "!" << std::endl;
    }
}

