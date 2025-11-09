#ifndef ROBOTOMY_REQ_FORM_HPP
#define ROBOTOMY_REQ_FORM_HPP

#include <string>
#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
    public:
        RobotomyRequestForm(const std::string &target);
        RobotomyRequestForm(const RobotomyRequestForm &other);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &other) = delete; // or???

        void execute(Bureacrat const &executor) const override;
};

#endif
