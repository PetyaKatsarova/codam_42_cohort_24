#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <stdexcept>

std::string joinArgs(int argc, char* argv[]) {
    std::ostringstream oss;
    for (int i = 1; i < argc; ++i) {
        oss << argv[i] << " ";
    }
    return oss.str();
}

int main(int argc, char* argv[]) {
    std::vector<int> arrV =  {4, 1, 7, 2, 9, 5};
    std::deque<int> arrDeq = {4, 1, 7, 2, 9, 5};

    PmergeMe bla(arrV, arrDeq);
    
    // todo: give 2 options: receive as 1 str"1 22 2" or as separate argvs: 1 22 2
    if (argc > 1) {
        try {        
            bla.setArrV(joinArgs(argc, argv));
            bla.setArrD(joinArgs(argc, argv));
        } catch (const std::exception& e) {
                std::cerr << "Error\n";
                return 1;
        }
    } 
    
    timespec v_start, v_end;
    std::cout << "Before: ";
    bla.printContainer(bla.getArrV()); // end with "\n"
 
    clock_gettime(CLOCK_MONOTONIC, &v_start);
    bla.fordJohnsonSortVector();
    clock_gettime(CLOCK_MONOTONIC, &v_end);

    std::cout << "After:  ";
    bla.printContainer(bla.getArrV());

    std::cout << "Time to process a range of " << bla.getArrV().size()
              << " elements with std::vector : " << PmergeMe::elapsedUs(v_start, v_end) << " us\n";

    clock_gettime(CLOCK_MONOTONIC, &v_start);
    bla.fordJohnsonSortDeque();
    clock_gettime(CLOCK_MONOTONIC, &v_end);

    std::cout << "Time to process a range of " << bla.getArrD().size()
              << " elements with std::deque : " << PmergeMe::elapsedUs(v_start, v_end) << " us\n";
    return 0;
}
