#include <cstdint> // c standard int for uintptr_t
#include <string>
#include <iostream>

// c++ uinptr_tutorial.cpp && ./a.out
int main() {
     int x = 42;
     int *ptr = &x;

    // // Convert pointer to integer
     uintptr_t num = reinterpret_cast<uintptr_t>(ptr); // address of ptr as int
    
     std::cout << "=== Values ===" << std::endl;
     std::cout << "x (value)           = " << x << std::endl;
     std::cout << "*ptr (value via ptr)= " << *ptr << std::endl;
    
     std::cout << "\n=== Addresses ===" << std::endl;
     std::cout << "&x (address of x)   = " << &x << std::endl;
     std::cout << "ptr (address of x)  = " << ptr << std::endl;
     std::cout << "num (address as int)= " << num << std::endl;
    
     std::cout << "\n=== Pointer Variables ===" << std::endl;
     std::cout << "&ptr (where ptr lives) = " << &ptr << std::endl;
     std::cout << "&num (where num lives) = " << &num << std::endl;
    
     std::cout << "\n=== Convert Back ===" << std::endl;
     int *ptr2 = reinterpret_cast<int*>(num);
     std::cout << "*ptr2 (value via converted ptr) = " << *ptr2 << std::endl;

    // reinterpret_cast converts between unrelated types (like pointer ↔ integer)
    double d = 3.14;
    double* p = &d;

    // Treat pointer bits as integer
    uintptr_t bits = reinterpret_cast<uintptr_t>(p);

    // Treat integer bits as pointer
    double* p2 = reinterpret_cast<double*>(bits);
    
    return 0;
}
