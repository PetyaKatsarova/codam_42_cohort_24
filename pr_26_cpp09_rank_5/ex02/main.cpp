#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>

int main() {
    std::vector<int> arrV = {1, 42, 3, 22, 7};
    std::deque<int> arrDeq = {1, 42, 3, 22, 7};

    PmergeMe bla(arrV, arrDeq);
    
    timespec v_start, v_end;

    // test algorithm with vector container
    clock_gettime(CLOCK_MONOTONIC, &v_start);
    bla.fordJohnsonSortVector();
    clock_gettime(CLOCK_MONOTONIC, &v_end);

    std::cout << "Vector time: "
            << PmergeMe::elapsedUs(v_start, v_end)
            << " us\n"; // microseconds

    // test algorithm with deque
    clock_gettime(CLOCK_MONOTONIC, &v_start);
    bla.fordJohnsonSortDeque();
    clock_gettime(CLOCK_MONOTONIC, &v_end);

    std::cout << "Deque time: "
            << PmergeMe::elapsedUs(v_start, v_end)
            << " us\n"; // microseconds
    
    return 0;
}
