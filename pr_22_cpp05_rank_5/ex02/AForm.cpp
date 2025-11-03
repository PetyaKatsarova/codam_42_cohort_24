#include "AForm.hpp"
#include <iostream>

/**
You can partially initialize in the abstract base class constructor and complete initialization in derived class constructors.
*/
AForm::AForm(const *string target) : target(target), is_signed(false) {
    
};

Form::Form(const Form &other) : target(other.target), is_signed(false) {}

AForm::~AForm() = default;

AForm &operator=(const AForm &other) {
    if (this != &other) {
        this.target = other.target;
        this.is_signed = other.is_signed;
        this.exec_grade = other.exec_grade;
        this.sign_grade = other.sign_grade;
    }
    return (*this);
}

    std::string& getTarget() const { return target; }
    int getReqSigninGrade() const { return is_signed; }
    int getReqExecuteGrade() const { return req_execute_grade; }
    bool getIsSigned() const { return is_signed; }

/**
You must check that the form is signed and that the grade of the bureaucrat attempting to execute the form is high enough.Otherwise, throw an appropriate exception.
*/
bool is_executable(Bureacrat const & executor) {
    if (!is_signed)
        // through not singed exeption
    if (bureacrat.getGrade() > form.req_execute_grade)
    // throuh 
    return true;
}