#include "ScalarConverter.hpp"
#include <iostream>
#include <optional>
#include <cmath> // nan staff

/**
cpp 17: optional<double> is a wrapper type(vocabulary type) represent val that my or may not be present, contains single element
std::optional<int> divide(int a, int b) {
    if (b == 0)
        return std::nullopt;  // No value (error case)
    return a / b;             // Has value (success)
}
*/

/*
 * SPECIAL VALUES REFERENCE
 * ========================
 * nan      : Not a Number (double)    - 0.0/0.0, sqrt(-1), inf-inf
 * nanf     : Not a Number (float)     - Same as nan, but float type
 * +inf/inf : Positive Infinity (dbl)  - 1.0/0.0, value too large
 * +inff    : Positive Infinity (flt)  - Same as +inf, but float type
 * -inf     : Negative Infinity (dbl)  - -1.0/0.0, value too small
 * -inff    : Negative Infinity (flt)  - Same as -inf, but float type
 */

 /*
 double value = 42.5;
 Read from RIGHT to LEFT:
*(long long*)&value
           ^^^^^^  Step 1: &value - Get address of value
  ^^^^^^^^^        Step 2: (long long*) - Cast to long long pointer
 ^                 Step 3: * - Dereference to get the value

 double value = 42.5;
double* ptr = &value;  // "give me the ADDRESS where value is stored"

double value = 42.5;
void* generic_ptr = &value;           // Generic pointer
long long* int_ptr = (long long*)&value;  // Cast to long long pointer
This says: "treat this address as if it points to a long long"
We're LYING to the compiler about what type is at that address
 */

//  static void nonValues() {
// 	double nan1 = 0.0/0.0; // -nan
// 	std::cout << "0/0 = " << nan1 << '\n';

// 	double nan2 = std::sqrt(-1.0);
// 	std::cout << "sqrt(-1.0) = " << nan2 << '\n';

// 	double inf = 1.0 / 0.0;
// 	double nan3 = inf - inf;
// 	std::cout << "inf - inf = " << nan3 << '\n';  // nan
// }

/**
 * argv is const char*
 */
int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <literal>\n";
		return 1;
	}
	std::cout << "argv = " << argv[1] << "\n";
	ScalarConverter::convert(argv[1]);
	return 0;
}