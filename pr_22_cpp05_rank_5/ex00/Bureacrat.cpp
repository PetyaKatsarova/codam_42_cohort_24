#include "Bureacrat.hpp"

Bureacrat::Bureacrat(const std::string& name, int grade) : _name(name), _grade(0)
{
	if (grade < HIGHEST_GRADE)
		throw Bureacrat::GradeTooHighException();
	if (grade > LOWEST_GRADE)
		throw Bureacrat::GradeTooLowException();
	this->_grade = grade;
}

Bureacrat::Bureacrat(const Bureacrat &other) : _name(other._name), _grade(other._grade) {};

Bureacrat::~Bureacrat() =  default;

int Bureacrat::getGrade() const{
	return this->_grade;
}

std::string Bureacrat::getName() const {
	return this->_name;
}

const std::string* Bureacrat::getNamePtr() const { return &_name; } 

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

std::ostream &operator<<(std::ostream &os, const Bureacrat &b)
{
	return os << b.getName() << ", bureacrat grade " << b.getGrade() << '.';
}