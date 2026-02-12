#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureacrat; // fwd declaration

/**
T& operator=(const T&) = delete; tells the compiler: do not provide/allow copy‑assignment.
Any code that tries a = b; will be a compile‑time error.
Use it to enforce immutability when you have const members (like _name) or want to forbid assignment.
*/
class Form {
    private:
        const std::string   _name;
        const int           _req_signin_grade;
        const int           _req_execute_grade;
        bool                _is_signed;

        static const int HIGHEST_GRADE = 1;
		static const int LOWEST_GRADE = 150;

    public:
        Form(const std::string &name, int req_signin_grade, int req_execute_grade);
        Form(const Form &other);
        Form &operator=(const Form &other) = delete;
        ~Form() = default;

        std::string getName() const;
        int getReqSigninGrade() const;
        int getReqExecuteGrade() const;
        bool getIsSigned() const;

        void setIsSigned(bool is_signed);
        void beSigned(const Bureacrat &b);
    
        class GradeTooHighException : public std::exception {
            public:
            	virtual const char* what() const noexcept override;
        };

        class GradeTooLowException : public std::exception {
            public:
            	virtual const char* what() const noexcept override;
        };
};

std::ostream &operator<<(std::ostream &os, const Form &form);

#endif