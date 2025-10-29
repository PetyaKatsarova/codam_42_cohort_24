#ifndef BUREACRAT_HPP
#define BUREACRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureacrat {
	private:
		const std::string	 _name;
		int				 	_grade;

		static const int HIGHEST_GRADE = 1;
		static const int LOWEST_GRADE = 150;

	public:
		Bureacrat(const std::string name, int grade);
		Bureacrat(const Bureacrat &other);
		Bureacrat &operator=(const Bureacrat &other);
		~Bureacrat();

		const std::string getName();
		const int getGrade();

		void incrementGrade();
		void decrementGrade();

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