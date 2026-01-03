#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <string>
#include <stdexcept>
#include <sstream>

int main(int argc, char* argv[]) {
    std::vector<int> arrV = {4, 1, 7, 2, 9, 5};
    std::deque<int> arrDeq = {1, 42, 3, 22, 7};

    PmergeMe bla(arrV, arrDeq);
    
    if (argc == 2) {
        try {        
            bla.setArrV(argv[1]); // for vector
        } catch (const std::exception& e) {
                std::cerr << e.what() << "\n";
                return 1;
        }
    } 
    
    timespec v_start, v_end;

    // test algorithm with vector container
    clock_gettime(CLOCK_MONOTONIC, &v_start);
    bla.fordJohnsonSortVector();
    clock_gettime(CLOCK_MONOTONIC, &v_end);

    std::cout << "Vector time: "
            << PmergeMe::elapsedUs(v_start, v_end)
            << " us\n"; // microseconds

    // test algorithm with deque
//     clock_gettime(CLOCK_MONOTONIC, &v_start);
//     bla.fordJohnsonSortDeque();
//     clock_gettime(CLOCK_MONOTONIC, &v_end);

//     std::cout << "Deque time: "
//             << PmergeMe::elapsedUs(v_start, v_end)
//             << " us\n"; // microseconds
    
    return 0;
}
