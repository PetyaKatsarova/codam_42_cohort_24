#ifndef SCALARCONVERTER__HPP
#define SCALARCONVERTER__HPP

#include <string>
#include <optional>

/**
convert str* literal to int, float, char, double
*/
class ScalarConverter {
	public:
		ScalarConverter() = delete;
        ScalarConverter(const ScalarConverter&) = delete;
        ScalarConverter& operator=(const ScalarConverter&) = delete;
        ~ScalarConverter() = delete;

        static void convert(const std::string& str);

     private:
        static std::optional<double> parse(const std::string& literal);
        static void printChar(std::optional<double> value);
        static void printInt(std::optional<double> value);
        static void printFloat(std::optional<double> value);
        static void printDouble(std::optional<double> value);
};

#endif