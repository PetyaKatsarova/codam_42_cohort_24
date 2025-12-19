#include "RPN.hpp"
#include <iostream>

int main(int argc, char**argv) {
    // do we check if ends in int? thats wrong?
    if (argc != 2) {
        std::cout << "Please give input: 2 2 * 3 + \n";
        return 1;
    }

    RPN test(argv[1]);
    for (size_t i = 0; i < test._nums.size(); i++) {
        std::cout << test._nums.top() << " ** ";
    }
    // std::cout << argv[1] << std::endl;
    return 0;
}