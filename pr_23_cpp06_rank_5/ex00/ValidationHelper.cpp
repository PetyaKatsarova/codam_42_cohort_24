#include "ValidationHelper.hpp"
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

/**
 * not protected int overflow
 */
bool ValidationHelper::isInteger(const std::string &str) {
	if (str.empty())
		return false;
	size_t start = 0;
	if (str[0] == '-' || str[0] == '+')
		start = 1;
	if (start == str.size())
		return false;
	for (size_t i = start; i < str.length(); i++) {
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}
	return str.length() > start;
}

/**
std::string::npos means "not found"
first check if it ends on f
second check if it has a dot(.)
third check all chars are digits
*/
bool ValidationHelper::isFloat(const std::string &str) {
	if (str.length() < 2 || str.back() != 'f')
		return false;
	std::string numPart = str.substr(0, str.length() - 1); // rm f

	size_t i = 0;
	if (numPart[i] == '+' || numPart[i] == '-')
		++i;
	if (i == numPart.size())
		return false;
	bool hasDot = false;

	for (; i < numPart.size(); ++i) {
		if (numPart[i] == '.') {
			if (hasDot == true)
				return false;
			hasDot = true;
			continue; // not to enter the next if
		}
		if (!std::isdigit(static_cast<unsigned char>(numPart[i])))
			return false;
	}
	return hasDot;
}

//static bool isDouble(const std::string &str) {
//	return str.find('.') != std::string::npos && str[str.length() - 1] != 'f';
//}

//static Type detectType(const std::string &str) {
//	if (str.length() == 3 && str[0] =='\'' && str[2] == '\'')
//		return CHAR;
//	// special floats
//	if (str == "nanf" || str == "+inff" || str == "-inff")
//		return FLOAT;
//	if (str == "nan" || str == "+inf" || str == "-inf")
//		return DOUBLE;
//	if (isFloat(str))
//		return FLOAT;
//	if (isDouble(str))
//		return DOUBLE;
//	if (isInteger(str))
//		return INT;
//	return INVALID;
//}
