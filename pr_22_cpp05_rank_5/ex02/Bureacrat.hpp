#ifndef BUREACRAT_HPP
#define BUREACRAT_HPP

#include <string>
#include <iostream>
#include <exception>
#include "AForm.hpp"

class AForm; // forward declaration to avoid circular include

class Bureacrat {
	private:
		const std::string	 _name;
		int				 	_grade;
		static const int HIGHEST_GRADE = 1;
		static const int LOWEST_GRADE = 150;

	public:
		Bureacrat(const std::string &name, int grade);
		Bureacrat(const Bureacrat &other);
		Bureacrat &operator=(const Bureacrat &other) = delete;
		~Bureacrat();

		const std::string& getName() const;
		int getGrade() const;
		void setGrade(int grade);

		void incrementGrade();
		void decrementGrade();
		static int validate_grade(int grade);

		void signForm(AForm &form);
		void executeForm(AForm const & form) const;

		class GradeTooHighException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};

		class GradeTooLowException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};
};

std::ostream  &operator<<(std::ostream &os, const Bureacrat &b);

#endif