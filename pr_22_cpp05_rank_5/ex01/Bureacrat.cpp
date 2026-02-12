#include "Bureacrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <string>

Bureacrat::Bureacrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
	if (this->_grade < HIGHEST_GRADE)
		throw Bureacrat::GradeTooHighException();
	if (this->_grade > LOWEST_GRADE)
		throw Bureacrat::GradeTooLowException();
}

Bureacrat::Bureacrat(const Bureacrat &other) : _name(other._name), _grade(other._grade) {}

Bureacrat::~Bureacrat(){}

std::string Bureacrat::getName() const {
	return this->_name;
}

int Bureacrat::getGrade() const{
	return this->_grade;
}

void Bureacrat::setGrade(int grade) {
	if (grade > LOWEST_GRADE)
		throw Bureacrat::GradeTooLowException();
	if (grade < HIGHEST_GRADE)
		throw Bureacrat::GradeTooHighException();
	_grade = grade;
}

void Bureacrat::incrementGrade(){
	if (this->_grade - 1 < HIGHEST_GRADE)
		throw Bureacrat::GradeTooHighException();
	--this->_grade;
}

void Bureacrat::decrementGrade(){
	if (this->_grade + 1 > LOWEST_GRADE)
		throw Bureacrat::GradeTooLowException();
	++this->_grade;
}

const char* Bureacrat::GradeTooHighException::what() const noexcept {
	return "Grade too high";
}

const char* Bureacrat::GradeTooLowException::what() const noexcept {
	return "Grade too low";
}

/**
 modify the signForm() member function in the Bureaucrat class. This function must call Form::beSigned() to attempt to sign the form. If the form is signed
successfully, it will print something like:
<bureaucrat> signed <form>
Otherwise, it will print something like:
<bureaucrat> couldn’t sign <form> because <reason>.
*/

void Bureacrat::signForm(Form &form) {
	try {
		form.beSigned(*this);
		std::cout << this->getName() << " singed " << form.getName() << std::endl;
	} catch (const std::exception &e) {
		std::cout << this->getName() << " couldn't sign " << form.getName() << " because " << e.what() << std::endl;
	}
}

std::ostream &operator<<(std::ostream &os, const Bureacrat &b)
{
	return os << b.getName() << ", bureacrat grade " << b.getGrade() << '.';
}