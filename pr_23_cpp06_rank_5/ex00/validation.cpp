#include "ScalarConverter.hpp"
#include <iostream>      // std::cout, std::cerr
#include <string>        // std::string, std::stoi, std::stof, std::stod
#include <limits>        // std::numeric_limits (for NaN, infinity)
#include <cmath>         // std::isnan, std::isinf
#include <climits>       // INT_MAX, INT_MIN
#include <cctype>        // std::isprint, std::isdigit



enum Type {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

static bool isInteger(const std::string &str) {
	size_t start = 0;
	if (str[0] == '-' || str[0] == '+')
		start = 1;
	for (size_t i = start; i < str.length(); i++) {
		if (!std::isdigit(str[i]))
			return false;
	}
	return str.length() > start;
}

/**
std::string::npos means "not found"
"3.14f" → numPart = "3.14" → finds . → returns true
"42f" → numPart = "42" → no . → returns false
*/
static bool isFloat(const std::string &str) {
	if (str.length() < 2 || str[str.length() - 1] != 'f')
		return false;
	std::string numPart = str.substr(0, str.length() - 1);
	return numPart.find('.') != std::string::npos;
}

static bool isDouble(const std::string &str) {
	return str.find('.') != std::string::npos && str[str.length() - 1] != 'f';
}

static Type detectType(const std::string &str) {
	if (str.length() == 3 && str[0] =='\'' && str[2] == '\'')
		return CHAR;
	// special floats
	if (str == "nanf" || str == "+inff" || str == "-inff")
		return FLOAT;
	if (str == "nan" || str == "+inf" || str == "-inf")
		return DOUBLE;
	if (isFloat(str))
		return FLOAT;
	if (isDouble(str))
		return DOUBLE;
	if (isInteger(str))
		return INT;
	return INVALID;
}

/**
Allowed functions: Any function to convert from a string to an int, a float, or a double.
*/
void ScalarConverter::convert(const std::string &literal) {
	std::cout << " convert " << literal << std::endl;
}