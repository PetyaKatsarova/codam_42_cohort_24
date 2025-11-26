#include "ScalarConverter.hpp"
#include <iostream>
#include <cmath>
#include <limits> // std::numeric_limits<>: for <int> max, min, <float>::infinity(), <double>::quiet_NaN()
#include <iomanip>

std::optional<double> ScalarConverter::parse(const std::string& literal) {
    if (literal.empty())    return std::nullopt;

    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'') 
        return static_cast<double>(literal[1]);

    if (literal.length() == 1 && !std::isdigit(literal[0]))
        return static_cast<double>(literal[0]);

    if (literal == "nan" || literal == "nanf")
        return std::numeric_limits<double>::quiet_NaN();
    if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff")
        return std::numeric_limits<double>::infinity();
    if (literal == "-inf" || literal == "-inff")
        return -std::numeric_limits<double>::infinity();

    // numeric
    try {
        size_t pos;
        double val =std::stod(literal, &pos);
        if (pos != literal.length() && !(pos == literal.length()-1 && literal[pos] == 'f'))
            return std::nullopt;
        return val;
    } catch(...) {
        return std::nullopt;
    }
}

void ScalarConverter::printChar(std::optional<double> opt_val) {
    std::cout << "char: ";
    if (!opt_val.has_value()) {
        std::cout << "impossible\n";
        return;
    }

    double val = opt_val.value();
    bool impossible = std::isnan(val) || std::isinf(val) || val < 0 || val > 127;
    bool nonDisplay = !impossible && (val < 32 || val == 127);
    std::cout << (impossible ? "impossible" : nonDisplay ? "Non displayable" : 
                  "'" + std::string(1, static_cast<char>(val)) + "'") << "\n";
}

void ScalarConverter::printInt(std::optional<double>opt_val) {
    if (!opt_val.has_value()) {
        std::cout << "impossible\n";
        return;
    }
    
    double val = opt_val.value();
    bool impossible = std::isnan(val) || std::isinf(val) ||
                    val > std::numeric_limits<int>::max() ||
                    val < std::numeric_limits<int>::min();
    std::cout << "Int: " << (impossible ? "impossible" : std::to_string(static_cast<int>(val))) << '\n';
}

void ScalarConverter::printDouble(std::optional<double> opt_val) {
    if (!opt_val.has_value()) {
        std::cout << "impossible\n";
        return;
    }
    
    double val = opt_val.value();
    std::cout << "double: ";
    if (std::isnan(val)) std::cout << "nan\n";
    else if (std::isinf(val)) std::cout << (val > 0 ? "+inf" : "-inf") << "\n";
    else std::cout << std::fixed << std::setprecision(1) << val << std::endl;
}

void ScalarConverter::printFloat(std::optional<double> opt_val) {
    if (!opt_val.has_value()) {
        std::cout << "impossible\n";
        return;
    }
    
    double val = opt_val.value();
    std::cout << "float: ";
    if (std::isnan(val)) std::cout << "nanf\n";
    else if (std::isinf(val)) std::cout << (val > 0 ? "+inff" : "-inff") << "\n";
    else std::cout << std::fixed << std::setprecision(1) << static_cast<float>(val) <<  "f\n";
}

void ScalarConverter::convert(const std::string& argv) {
    auto result = parse(argv);
    if (!result) {
        std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n";
        return;
    }

    double val = *result;
    printChar(val);
    printInt(val);
    printFloat(val);
    printDouble(val);
}
