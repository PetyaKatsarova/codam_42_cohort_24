#include "PresidentialPardonForm.hpp"
#include "Bureacrat.hpp"
#include <iostream>
#include <random>

PresidentialPardonForm::
PresidentialPardonForm(const std::string &target) : AForm(target, 25, 5) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) : AForm(other){}

void PresidentialPardonForm::execute(Bureacrat const &executor) const {
    validate_form_bureacrat(executor);
    std::cout << this->getTarget() << " has been pardoned by Zaphod Beeblebrox.\n";
}

