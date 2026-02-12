#include "Form.hpp"
#include "Bureacrat.hpp"

/**
Form::~Form() = default; // defaulted out-of-class
Form::~Form() {} // user-provided empty body
*/
Form::Form(const std::string &name, int req_signin_grade, int req_execute_grade) : _name(name), _req_signin_grade(req_signin_grade), _req_execute_grade(req_execute_grade), _is_signed(false) {
    if (_req_execute_grade < HIGHEST_GRADE || _req_signin_grade < HIGHEST_GRADE)
        throw Form::GradeTooHighException();
    if (_req_execute_grade > LOWEST_GRADE || _req_signin_grade > LOWEST_GRADE)
        throw Form::GradeTooLowException();
}

Form::Form(const Form &other)
    : _name(other._name)
    , _req_signin_grade(other._req_signin_grade)   // match header order
    , _req_execute_grade(other._req_execute_grade)
    , _is_signed(other._is_signed)
{}

std::string Form::getName() const {
    return this->_name;
}
int Form::getReqSigninGrade() const {
    return this->_req_signin_grade;
}
int Form::getReqExecuteGrade() const {
    return this->_req_execute_grade;
}
bool Form::getIsSigned() const {
    return this->_is_signed;
}

void Form::setIsSigned(bool is_signed) {
    this->_is_signed = is_signed;
}

/**
 It changes the form’s status to signed if the bureaucrat’s grade is high enough
(greater than or equal to the required one). Remember, grade 1 is higher than grade 2.
If the grade is too low, throw a Form::GradeTooLowException.
*/
void Form::beSigned(const Bureacrat &b) {
    if (b.getGrade() > this->getReqSigninGrade())
        throw Form::GradeTooLowException();
    setIsSigned(true);
}

const char* Form::GradeTooHighException::what() const noexcept {
    return "Grade too high";
}

const char* Form::GradeTooLowException::what() const noexcept {
    return "Grade too low";
}

std::ostream &operator<<(std::ostream &os, const Form &form) {
    return os << form.getName()
              << " [signed:" << (form.getIsSigned() ? "yes" : "no")
              << ", req_sign=" << form.getReqSigninGrade()
              << ", req_exec=" << form.getReqExecuteGrade() << ']';
}