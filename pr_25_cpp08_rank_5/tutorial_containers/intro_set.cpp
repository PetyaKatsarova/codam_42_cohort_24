#include <set>
#include <iostream>

/** Set (Unique Elements, Sorted) */
void setDemo() {
    std::set<int> s;
    
    // Insert
    s.insert(10);
    s.insert(20);
    s.insert(10);  // Duplicate ignored
    s.insert(5);
    
    // Size (only 3 elements: 5, 10, 20)
    std::cout << "Size: " << s.size() << std::endl;
    
    // Find
    if (s.find(10) != s.end()) {
        std::cout << "10 found!" << std::endl;
    }
    
    // Iteration (sorted order)
    for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";  // Output: 5 10 20
    }
    std::cout << std::endl;
    
    // Erase
    s.erase(10);
}

int main() {
    setDemo();
    return 0;
}