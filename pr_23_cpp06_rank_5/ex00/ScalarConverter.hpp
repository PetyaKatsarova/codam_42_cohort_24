#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <string>

class ScalarConverter {
	public:
	 	ScalarConverter() = delete;
        ScalarConverter(const ScalarConverter &) = delete;
        ScalarConverter &operator=(const ScalarConverter &) = delete;
        ~ScalarConverter() = delete;

		static void convert(const std::string& literal);
};

#endif