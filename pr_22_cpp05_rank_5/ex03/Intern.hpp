#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <iostream>
#include "AForm.hpp"

class Intern {
    public:
        Intern();
        Intern(const Intern &other);
        ~Intern();
        Intern& operator=(const Intern& other);

        AForm* makeForm(const std::string &name, const std::string &target);

        class FormNotFoundException : public std::exception {
            private:
                std::string         formName;
                mutable std::string msg; // mutable so what() can modify it

            public:
                FormNotFoundException(const std::string &formName);
                virtual ~FormNotFoundException() noexcept;
                virtual const char* what() const noexcept override;
        };
};

#endif