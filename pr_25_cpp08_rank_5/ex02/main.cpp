#include "MutantStack.hpp"
#include <iostream>

int main() {
    MutantStack<int> mstack;
    
    mstack.push(5);
    mstack.push(17); 
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    // Works like normal stack
    std::cout << "Top element: " << mstack.top() << std::endl;
    
    // Can iterate (the magic!)
    std::cout << "Iterate forward: ";
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop works!
    std::cout << "Range-for: ";
    for (int x : mstack) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    
    // Reverse iteration
    std::cout << "Reverse iterate: ";
    for (auto rit = mstack.rbegin(); rit != mstack.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
    
    return 0;
}