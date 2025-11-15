#ifndef BUREACRAT_HPP
#define BUREACRAT_HPP

#include <string>
#include <iostream>
#include <exception>

/**
 * Copy assignement is not allowed because cant reassign a const string name
 */
class Bureacrat {
	private:
		const std::string	 _name; // read only
		int				 	_grade;

		static const int HIGHEST_GRADE = 1;
		static const int LOWEST_GRADE = 150;

	public:
		const std::string* getNamePtr() const; // for testing purposes
		
		Bureacrat(const std::string &name, int grade);
		Bureacrat(const Bureacrat &other);
		Bureacrat &operator=(const Bureacrat &other) = delete;
		~Bureacrat();

		std::string getName() const;
		int getGrade() const;

		void incrementGrade();
		void decrementGrade();

		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const noexcept override;
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const noexcept override;
		};
};

std::ostream  &operator<<(std::ostream &os, const Bureacrat &b);

#endif