#include "ValidationHelper.hpp"
#include "ScalarConverter.hpp"
#include <iostream>

int main() {
	const char* bla = "bla";
	ScalarConverter::convert(bla);
	//std::cout << "is digit: " << ValidationHelper::isInteger("42") << std::endl;
	//std::cout << "is digit: " << ValidationHelper::isInteger("-42") << std::endl;
	//std::cout << "is digit: " << ValidationHelper::isInteger("4+2") << std::endl;
	//std::cout << "is digit: " << ValidationHelper::isInteger("42b") << std::endl;

	std::cout << "is float 42f: " << ValidationHelper::isFloat("42f") << std::endl; // no
	std::cout << "is float: " << ValidationHelper::isFloat("-42.0000f") << std::endl; //y
	std::cout << "is float: " << ValidationHelper::isFloat("4+2") << std::endl; // n
	std::cout << "is float: " << ValidationHelper::isFloat("4.0o9f") << std::endl; //n
	return 0;
}