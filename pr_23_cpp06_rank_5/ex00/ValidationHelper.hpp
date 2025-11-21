#ifndef VALIDATION_HELPER_HPP
#define VALIDATION_HELPER_HPP

#include <string>

class ValidationHelper {
	public:
		ValidationHelper() = delete;
        ValidationHelper(const ValidationHelper &) = delete;
        ValidationHelper &operator=(const ValidationHelper &) = delete;
        ~ValidationHelper() = delete;

		static bool isInteger(const std::string &str);
		static bool isFloat(const std::string &str);
};

#endif