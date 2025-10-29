#include "Bureacrat.hpp"

Bureacrat::Bureacrat(const std::string& name, int grade) : _name(name), _grade(grade)
{
	if (this->_grade < HIGHEST_GRADE)
		throw Bureacrat::GradeTooHighException();
	if (this->_grade > LOWEST_GRADE)
		throw Bureacrat::GradeTooLowException();
}

Bureacrat::Bureacrat(const Bureacrat &other) : _name(other._name), _grade(other._grade) {};

Bureacrat::~Bureacrat() =  default;

/**
_name is not copied because is const, cant be changed after initiation
*/
Bureacrat &Bureacrat::operator=(const Bureacrat &other)
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

int Bureacrat::getGrade() const{
	return this->_grade;
}

const std::string& Bureacrat::getName() const {
	return this->_name;
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

std::ostream &operator<<(std::ostream &os, const Bureacrat &b)
{
	return os << b.getName() << ", bureacrat grade " << b.getGrade() << '.';
}