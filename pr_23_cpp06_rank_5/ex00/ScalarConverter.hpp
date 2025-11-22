#ifndef SCALARCONVERTER__HPP
#define SCALARCONVERTER__HPP

#include <string>

/**
convert str* literal to int, float, char, double
*/
class ScalarConverter {
	public:
		ScalarConverter() = delete;
        ScalarConverter(const ScalarConverter &) = delete;
        ScalarConverter &operator=(const ScalarConverter &) = delete;
        ~ScalarConverter() = delete;

		static void convert(const std::string* str);
};

#endif