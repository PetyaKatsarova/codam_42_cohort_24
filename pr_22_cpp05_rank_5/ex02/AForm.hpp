#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureacrat; // fwd declaration

class AForm {
    private:
        const std::string   target;
        const int           signin_grade;
        const int           execute_grade;
        bool                is_signed;

    public:
        AForm(const std::string &target, int sign_grade, int exec_grade);
        AForm(const AForm &other);
        AForm &operator=(const AForm &other) = delete;
        virtual ~AForm();

        const std::string& getTarget() const;
        int getReqSigninGrade() const;
        int getReqExecuteGrade() const;
        bool getIsSigned() const;

		static int validate_grade(int gr);
        void setIsSigned(bool is_signed);
        void beSigned(const Bureacrat &b);

        bool validate_form_bureacrat(const Bureacrat &b) const;
        virtual void execute(Bureacrat const & executor) const = 0;
    
        class GradeTooHighException : public std::exception {
            public:
                const char* what() const noexcept override;
        };

        class GradeTooLowException : public std::exception {
            public:
                const char* what() const noexcept override;
        };

        class FormNotSignedException : public std::exception {
            public:
                const char* what() const noexcept override;
        };
};

std::ostream &operator<<(std::ostream &os, const AForm &Aform);

#endif