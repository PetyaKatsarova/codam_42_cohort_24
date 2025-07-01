#include "Harl.hpp"
#include <iostream>

int main() {
    Harl harl;

    for (size_t i = 0; i < 5; ++i) {
        std::cout << "--- " << i + 1 << " ---" << std::endl;
        harl.complain("DEBUG");
        harl.complain("INFO");
        harl.complain("WARNING");
        harl.complain("ERROR");
        harl.complain("BLA");
    }
    return (0);
}