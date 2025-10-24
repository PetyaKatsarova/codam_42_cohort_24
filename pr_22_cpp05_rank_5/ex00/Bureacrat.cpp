#include "Bureacrat.hpp"

/**
 *  Member initialization order - Must initialize all members in initializer list
	Can't validate before initializing - _grade must exist before assignment
	Temporary safe state - Set to 0, then validate and assign real value * 
 */
Bureacrat::Bureacrat(const std::string name, int grade) : _name(name), _grade(grade)
{
	if (this->_grade < HIGHEST_GRADE)
		throw Bureacrat::GradeTooHighException();
	if (this->_grade > LOWEST_GRADE)
		throw Bureacrat::GradeTooLowException();
}

Bureacrat::Bureacrat(const Bureacrat &other) : _name(other._name), _grade(other._grade) {};

Bureacrat &Bureacrat::operator=(const Bureacrat &other)
{
	if (this != &other)
	{
		this->_name = other._name;
		this->_grade = other._grade;
	}
	return (*this);
}