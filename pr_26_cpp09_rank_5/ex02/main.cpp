#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[]) {
    std::vector<int> arrV =  {4, 1, 7, 2, 9, 5};
    std::deque<int> arrDeq = {4, 1, 7, 2, 9, 5};

    PmergeMe bla(arrV, arrDeq);
    
    if (argc > 1) {
        try {
            std::string input = bla.joinArgs(argc, argv); // in case input like: 42 2 24 22
            bla.setArrV(input);
            bla.setArrD(input);
        } catch (const std::exception& e) {
                std::cerr << "Error\n";
                return 1;
        }
    } 
    
    timespec start, end;
    std::cout << "Before: ";
    bla.printContainer(bla.getArrV()); // end with "\n"
 
    clock_gettime(CLOCK_MONOTONIC, &start);
    bla.fordJohnsonSortVector();
    clock_gettime(CLOCK_MONOTONIC, &end);

    std::cout << "After:  ";
    bla.printContainer(bla.getArrV());

    std::cout << "Time to process a range of " << bla.getArrV().size()
              << " elements with std::vector : " << PmergeMe::elapsedUs(start, end) << " us\n";

    clock_gettime(CLOCK_MONOTONIC, &start);
    bla.fordJohnsonSortDeque();
    clock_gettime(CLOCK_MONOTONIC, &end);

    std::cout << "Time to process a range of " << bla.getArrD().size()
              << " elements with std::deque : " << PmergeMe::elapsedUs(start, end) << " us\n";
    return 0;
}
