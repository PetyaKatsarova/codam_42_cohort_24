#include <iostream>
#include <array>      // std::array
#include <vector>     // std::vector
#include <list>       // std::list
#include <algorithm>  // std::find

int main() {
    // 1. std::array - fixed size, stack allocated
    std::array<int, 5> arr = {10, 20, 30, 40, 50};
    
    std::cout << "Array size: " << arr.size() << std::endl;
    std::cout << "First element: " << arr[0] << std::endl;
    std::cout << "Last element: " << arr.back() << std::endl;
    
    // Iterate
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 2. std::vector - dynamic size, heap allocated
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    vec.push_back(6);  // Add element
    std::cout << "Vector size: " << vec.size() << std::endl;
    
    // 3. std::list - doubly linked list
    std::list<int> lst = {100, 200, 300};
    
    lst.push_front(50);  // Add to front
    lst.push_back(400);  // Add to back
    
    // 4. Find element using iterators
    auto it = std::find(arr.begin(), arr.end(), 30);
    if (it != arr.end()) {
        std::cout << "Found: " << *it << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
    
    // 5. Using iterators manually
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    return 0;
}