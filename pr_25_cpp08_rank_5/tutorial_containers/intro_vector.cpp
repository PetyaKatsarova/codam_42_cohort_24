#include <iostream>
#include <vector>
#include <algorithm>

/**
STL = Standard Template Library

Containers: Store collections of data
Algorithms: Operations on containers
Iterators: Connect containers and algorithms
------------------------------------------
std::vector<int> vec;
vec.push_back(10);
vec.push_back(20);

// Memory layout:
┌─────────────────┐         ┌─────────────────┐
│ STACK           │         │ HEAP            │
├─────────────────┤         ├─────────────────┤
│ vec object:     │         │ [10][20]        │
│   ptr ─────────┼────────>│                 │
│   size = 2     │         └─────────────────┘
│   capacity = ? │
└─────────────────┘
No delete needed! Vector destructor handles it automatically
------------------------------------------
std::vector<int>::iterator it = vec.begin();
//                         ^^
//                         Points to first element

// Memory:
vec → [10][20][30]
      ↑
      it (begin)
--------------------------------------------------
*/

// NB! VECTOR IS DYNAMIC ARRAY
void vectorDemo() {
    std::vector<int> vec;
    std::vector<int> vec2(5); // 5 els, default 0
    std::vector<int> vec3(5, 42); // 5 els, val 42
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    std::cout << "vec[0] = " << vec[0] << std::endl;
    std::cout << "vec.at(1) = " << vec.at(1) << std::endl;
    std::cout << "vec.front() = " << vec.front() << std::endl;
    std::cout << "vec.back() = " << vec.back() << std::endl;

    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Empty: " << vec.empty() << std::endl; // 0 = not empty

    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    vec.pop_back();
    vec.clear(); // clear all: 
}

//c++ intro_vector.cpp && ./a.out
int main() {
    vectorDemo();
    return 0;
}