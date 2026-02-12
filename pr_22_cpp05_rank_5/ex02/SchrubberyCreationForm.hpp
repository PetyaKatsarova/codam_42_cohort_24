/**
SchrubberyCreationForm: Required grades: sign 145, exec 137
Creates a file <target>_schrubbery in the working directory and writes ASCII trees
inside it.
*/

#ifndef SCHRUBBERY_CREATION_FORM_HPP
#define SCHRUBBERY_CREATION_FORM_HPP

#include <iostream>
#include "AForm.hpp"

class Bureacrat;

class SchrubberyCreationForm : public AForm {

    public:
        SchrubberyCreationForm(const std::string &target);

        void execute(Bureacrat const &executor) const override;
};

#endif