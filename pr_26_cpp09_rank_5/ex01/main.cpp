#include "RPN.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, const char** argv) {
    if (argc != 2) {
        std::cout << "Please give input: 2 2 * 3 + \n";
        return 1;
    }

    RPN test;
	try {
		if (!test.validateInput(argv[1])) {
			std::cerr << "Error: invalid input\n";
			return 1;
		}
    	std::cout << "Result = " << test.calculate(argv[1]) << std::endl;
		// easy tests:
		const char* test1 = "8 2 5 * + 1 3 2 * + /"; // (8 +  2 * 5) / (1 + 3 * 2)
		std::cout << "Expected 2, result = " << test.calculate(test1) << std::endl;
		 // Test 2: Division by zero should be handled
		 try {
			    const char* test2 = "5 0 /"; // 5 / 0 = undefined (should crash or error)
        	std::cout << "Expected error, result = " << test.calculate(test2) << std::endl;
		 } catch (std::exception& e) {
			std::cerr << e.what();
		 }
        
        // Test 3: Multiple subtractions (order matters)
        const char* test3 = "9 5 3 - -"; // 9 - (5 - 3) = 9 - 2 = 7
        std::cout << "Expected 7, result = " << test.calculate(test3) << std::endl;
        
        // Test 4: Complex nested operations
        const char* test4 = "1 2 + 3 4 + * 5 -"; // (1+2) * (3+4) - 5 = 3*7 - 5 = 21 - 5 = 16
        std::cout << "Expected 16, result = " << test.calculate(test4) << std::endl;
        
        // Test 5: Single number (edge case - no operations)
        const char* test5 = "7"; // 7 = 7
        std::cout << "Expected 7, result = " << test.calculate(test5) << std::endl;
        
        // Test 6: All operations in sequence
        const char* test6 = "8 4 2 / + 3 * 1 -"; // (8 + 4/2) * 3 - 1 = (8+2)*3 - 1 = 10*3 - 1 = 30 - 1 = 29
        std::cout << "Expected 29, result = " << test.calculate(test6) << std::endl;
		return 0;
	} catch (std::exception& e) {
		std::cerr << e.what();
		return 1;
	}
}
