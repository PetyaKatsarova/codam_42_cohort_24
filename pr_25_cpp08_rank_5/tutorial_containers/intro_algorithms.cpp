#include <algorithm>
#include <vector>
#include <iostream>

template <typename Container>
void printContainer(const Container& c) {
    for (const auto& el : c) std::cout << el << " ";
    std::cout << std::endl;
}

/**
The () after std::greater<int> is because std::greater is a class template, not a function.

std::greater<int> defines a functor (an object that can be called like a function via operator()).

std::sort expects a callable object as the comparison.
std::greater<int> comp; // create an object
std::sort(vec.begin(), vec.end(), comp); // works the same
*/
void sortDemo() {
    std::vector<int> vec;
    vec.push_back(30);
    vec.push_back(10);
    vec.push_back(20);
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Sort ascending
    std::sort(vec.begin(), vec.end());
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Sort descending
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void findDemo() {
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(20);
    
    // Find element
    std::vector<int>::iterator it = std::find(vec.begin(), vec.end(), 20);
    if (it != vec.end()) {
        std::cout << "Found at index: " << (it - vec.begin()) << std::endl;
    }
    
    // Count occurrences
    int count = std::count(vec.begin(), vec.end(), 20);
    std::cout << "Count of 20: " << count << std::endl;
}

void minMaxDemo() {
    std::vector<int> vec;
    vec.push_back(30);
    vec.push_back(10);
    vec.push_back(20);
    
    // Min element
    std::vector<int>::iterator minIt = std::min_element(vec.begin(), vec.end());
    std::cout << "Min: " << *minIt << std::endl;
    
    // Max element
    std::vector<int>::iterator maxIt = std::max_element(vec.begin(), vec.end());
    std::cout << "Max: " << *maxIt << std::endl;
}

void copyFillDemo() {
    std::vector<int> src(5, 10);
    std::vector<int> dst(5);
    printContainer<std::vector<int>>(src);
    std::copy(src.begin(), src.end(), dst.begin());
    std::fill(dst.begin(), dst.end(), 42);
    std::fill_n(dst.begin(), 3, 99);  // Fill first 3 elements
}

int main() {
    sortDemo();
    std::cout << "-- FIND VECTOR --\n";
    findDemo();
    std::cout << "-- MIN/MAX VECTOR --\n";
    minMaxDemo();
    std::cout << "-- CPY/FILL  --\n";
    copyFillDemo();
    return 0;
}