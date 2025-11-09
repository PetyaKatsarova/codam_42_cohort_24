/**
PresidentialPardonForm: Required grades: sign 25, exec 5
Informs that <target> has been pardoned by Zaphod Beeblebrox.
*/

#ifndef PRESEDENTIAL_PARDON_FORM_HPP
#define PRESEDENTIAL_PARDON_FORM_HPP

#include <string>
#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
    public:
        PresidentialPardonForm(const std::string &target);
        PresidentialPardonForm(const PresidentialPardonForm &other);
        PresidentialPardonForm &operator=(const PresidentialPardonForm &other) = delete; // or???

        void execute(Bureacrat const &executor) const override;
};

#endif