#include "Form.hpp"

Form::Form(const std::string &name, int req_execute_grade, int req_signin_grade) : _name(name), _req_execute_grade(req_execute_grade), _req_signin_grade(req_signin_grade), _is_signed(false) {
    if (_req_execute_grade < HIGHEST_GRADE || _req_signin_grade < HIGHEST_GRADE)
        throw Form::GradeTooHighException();
    if (_req_execute_grade > LOWEST_GRADE || _req_signin_grade > LOWEST_GRADE)
        throw Form::GradeTooLowException();
}

Form::Form(const Form &other)
    : _name(other._name)
    , _req_execute_grade(other._req_execute_grade)
    , _req_signin_grade(other._req_signin_grade)
    , _is_signed(other._is_signed)
{}

~Form() {} = default;

const std::string& getName() const {
    return this->_name;
}
const int getReqSigninGrade() const {
    return this->_req_signin_grade;
}
const int getReqExecuteGrade() const {
    return this->_req_execute_grade;
}
const bool getIsSigned() const {
    return this->_is_signed;
}

void beSigned(Bureacrat &b) {
// todo...

Form::GradeTooHighException : what() const noexcept override{
    return "Grade too high";
}

Form::GradeTooLowException : waht() const noexcept override {
    return "Grade too low";
}

std::ostream &operator<<(std::ostream &os, const Form &form) {
    return os << form.getName()
              << " [signed:" << (form.getIsSigned() ? "yes" : "no")
              << ", req_sign=" << form.getReqSinginGrade()
              << ", req_exec=" << form.getReqExecuteGrade() << ']';
}