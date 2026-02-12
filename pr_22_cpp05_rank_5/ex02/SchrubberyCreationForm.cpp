#include "SchrubberyCreationForm.hpp"
#include "Bureacrat.hpp"
#include "AForm.hpp"
#include <fstream>
#include <iostream> 
#include <stdexcept>

SchrubberyCreationForm::SchrubberyCreationForm(const std::string &target) : AForm(target, 145, 137) {};

// SchrubberyCreationForm::SchrubberyCreationForm(const SchrubberyCreationForm &other) : AForm(other) {}

void SchrubberyCreationForm::execute(Bureacrat const &executor) const {
    validate_form_bureacrat(executor);

    // create the file
    std::string fname = this->getTarget() + "_schrubbery";
    std::ofstream file(fname);

    if (!file.is_open())
            throw std::runtime_error("Err, could not create file " + fname);
    file << "       _-_\n"
         << "    /~~   ~~\\\n"
         << " /~~         ~~\\\n"
         << "{               }\n"
         << " \\  _-     -_  /\n"
         << "   ~  \\\\ //  ~\n"
         << "_- -   | | _- _\n"
         << "  _ -  | |   -_\n"
         << "      // \\\\\n"
         << "       _-_\n"
         << "    /~~   ~~\\\n"
         << " /~~         ~~\\\n"
         << "{               }\n"
         << " \\  _-     -_  /\n"
         << "   ~  \\\\ //  ~\n"
         << "_- -   | | _- _\n"
         << "  _ -  | |   -_\n"
         << "      // \\\\\n";
    
		// Not required file.closed() — the ofstream destructor flushes and closes the file (even during stack unwinding). Explicit close is fine and more explicit.
    std::cout << "Schrubbery created in " << fname << std::endl;
}
