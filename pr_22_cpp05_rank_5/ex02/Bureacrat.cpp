#include "Bureacrat.hpp"
#include "AForm.hpp"
#include <iostream>

Bureacrat::Bureacrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
	if (this->_grade < HIGHEST_GRADE)
		throw Bureacrat::GradeTooHighException();
	if (this->_grade > LOWEST_GRADE)
		throw Bureacrat::GradeTooLowException();
}

Bureacrat::Bureacrat(const Bureacrat &other) : _name(other._name), _grade(other._grade) {}

Bureacrat::~Bureacrat(){}

/**
_name is not copied because is const, cant be changed after initiation
*/
Bureacrat& Bureacrat::operator=(const Bureacrat &other)
{
	if (this != &other)
	{
		if (other._grade < HIGHEST_GRADE)
			throw Bureacrat::GradeTooHighException();
		if (other._grade > LOWEST_GRADE)
			throw Bureacrat::GradeTooLowException();

		// name cant be assigned
		this->_grade = other._grade;
	}
	return (*this);
}

const std::string& Bureacrat::getName() const {
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

void Bureacrat::signForm(AForm &form) {
	try {
		form.beSigned(*this);
		std::cout << this->getName() << " singed " << form << std::endl;
	} catch (const std::exception &e) {
		form.setIsSigned(false);
		std::cout << this->getName() << " couldn't sign " << form << " because " << e.what() << std::endl;
	}
}

void Bureacrat::executeForm(AForm const & form) const {
	try {	
		form.execute(*this);
		std::cout << this->getName() << " executed " << form.getTarget();
	} catch (const std::exception &e) {
		std::cout << this->getName() << " couldn't execute " << form.getTarget() << " because " << e.what() << std::endl;
	}
}

std::ostream &operator<<(std::ostream &os, const Bureacrat &b)
{
	return os << b.getName() << ", bureacrat grade " << b.getGrade() << std::endl;
}