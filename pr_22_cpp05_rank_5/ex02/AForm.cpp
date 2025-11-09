#include "AForm.hpp"
#include "Bureacrat.hpp"
#include <iostream>

AForm::AForm(const std::string &target, int sign_grade, int exec_grade) : target(target), signin_grade(sign_grade), execute_grade(exec_grade) {
    if (signin_grade < 1 || exec_grade < 1)
        throw AForm::GradeTooHighException();
    if (signin_grade > 150 || exec_grade > 150)
        throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm &other) : target(other.target), signin_grade(other.signin_grade), execute_grade(other.execute_grade), is_signed(other.is_signed) {}

AForm::~AForm() {}

const std::string& AForm::getTarget() const {
    return target;
}

int AForm::getReqSigninGrade() const {
    return signin_grade;  // Not is_signed!
}

int AForm::getReqExecuteGrade() const {
    return execute_grade;
}

bool AForm::getIsSigned() const {
    return is_signed;
}

void AForm::setIsSigned(bool signed_status) {
    is_signed = signed_status;
}

void AForm::beSigned(const Bureacrat &b) {
    if (b.getGrade() > signin_grade)
        throw AForm::GradeTooLowException();
    is_signed = true;
}

const char* AForm::GradeTooHighException::what() const noexcept {
    return "Grade too high";
}

const char* AForm::GradeTooLowException::what() const noexcept {
    return "Grade too low";
}

const char* AForm::FormNotSignedException::what() const noexcept {
    return "Form not signed";
}

bool AForm::validate_form_bureacrat(const Bureacrat &executor) const {
    if (!getIsSigned())
        throw AForm::FormNotSignedException();
    if (executor.getGrade() > getReqExecuteGrade())
        throw AForm::GradeTooLowException();
    return true;
}

std::ostream &operator<<(std::ostream &os, const AForm &form) {
    return os << form.getTarget()
    << " [signed: " << (form.getIsSigned() ? "yes" : "no") << ", req_sign=" << form.getReqSigninGrade() << ", req_exec=" << form.getReqExecuteGrade() << "]";
}