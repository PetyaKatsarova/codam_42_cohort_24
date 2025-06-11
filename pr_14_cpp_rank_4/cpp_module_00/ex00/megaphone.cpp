/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   megaphone.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 14:25:05 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/06/11 15:57:49 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype> // .toupper(), isalpha(), isspace() etc: char classification

int main(int argc, char **argv) {

	if (argc == 1) {
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		for (size_t j = 0; j < arg.length(); j++) {
			std::cout << (char)std::toupper(arg[j]); // toupper is only for char
		}
	}
	std::cout << std::endl;
	return (0);
}