/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   megaphone.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/16 16:42:36 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/01/16 17:25:31 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

// std:: refers to the standard library in c, so we only use std:: when using 
// functions, types or objects from that library. 
// Length is already included in str

// std::string is like char *
// str = the variable name we give it.
// argv[i] is what we assign to str.

// std::cout prints the result of what's behind it.
// static_cast<char> converts the result of std::toupper() to a char.
// std::toupper returns an int, so we convert it to a char using static_cast.

int	main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		for (int i = 1; i < argc; i++)
		{
			std::string str = argv[i];
			for (int j = 0; j < str.length(); j++)
				std::cout << static_cast<char>(std::toupper(str[j]));
		}
		std::cout << std::endl;
	}
	return (0);
}