#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>
/**
In all cases, the base class AForm must be an abstract class and should therefore be
renamed AAForm. Keep in mind that the Aform’s attributes need to remain private and
that they belong to the base class.

All of them take only one parameter in their constructor: the target of the Aform. For
example, "home" if you want to plant shrubbery at home.
Now, add the execute(Bureaucrat const & executor) const member function to
the base form and implement a function to execute the form’s action in the concrete
classes. You must check that the form is signed and that the grade of the bureaucrat attempting to execute the form is high enough. Otherwise, throw an appropriate exception.
Whether you check the requirements in every concrete class or in the base class (and
then call another function to execute the form) is up to you. However, one way is more
elegant than the other.
*/

class Bureacrat; // fwd declaration

class AForm {
    protected:
        std::string         target;
        const int           signin_grade;
        const int           execute_grade;
        bool                is_signed;

        // static const int HIGHEST_GRADE = 1;
		// static const int LOWEST_GRADE = 150;

    public:
        AForm(const std::string &target);
        AForm(const AForm &other);
        AForm &operator=(const AForm &other);
        virtual ~AForm();

        const std::string& getTarget() const;
        int getReqSigninGrade() const;
        int getReqExecuteGrade() const;
        bool getIsSigned() const;

        void setIsSigned(bool is_signed);
        void beSigned(const Bureacrat &b);

        bool is_executable(Bureacrat const & executor);
        void execute(Bureaucrat const & executor) const = 0;
    
        class GradeTooHighException : public std::exception {
            public:
            const char* what() const noexcept override;
        };

        class GradeTooLowException : public std::exception {
            public:
            const char* what() const noexcept override;
        };
};

std::ostream &operator<<(std::ostream &os, const AForm &Aform);

#endif