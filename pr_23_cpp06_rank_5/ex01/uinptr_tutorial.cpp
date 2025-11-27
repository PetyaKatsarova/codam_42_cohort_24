#include <cstdint> // c standard int for uintptr_t
#include <string>
#include <iostream>

// c++ uinptr_tutorial.cpp && ./a.out
int main() {
    // int x = 42;
    // int *ptr = &x;

    // // Convert pointer to integer
    // uintptr_t num = reinterpret_cast<uintptr_t>(ptr);
    
    // std::cout << "=== Values ===" << std::endl;
    // std::cout << "x (value)           = " << x << std::endl;
    // std::cout << "*ptr (value via ptr)= " << *ptr << std::endl;
    
    // std::cout << "\n=== Addresses ===" << std::endl;
    // std::cout << "&x (address of x)   = " << &x << std::endl;
    // std::cout << "ptr (address of x)  = " << ptr << std::endl;
    // std::cout << "num (address as int)= " << num << std::endl;
    
    // std::cout << "\n=== Pointer Variables ===" << std::endl;
    // std::cout << "&ptr (where ptr lives) = " << &ptr << std::endl;
    // std::cout << "&num (where num lives) = " << &num << std::endl;
    
    // std::cout << "\n=== Convert Back ===" << std::endl;
    // int *ptr2 = reinterpret_cast<int*>(num);
    // std::cout << "*ptr2 (value via converted ptr) = " << *ptr2 << std::endl;

    // reinterpret_cast converts between unrelated types (like pointer ↔ integer)
    double d = 3.14;
    double* p = &d;

    // Treat pointer bits as integer
    uintptr_t bits = reinterpret_cast<uintptr_t>(p);

    // Treat integer bits as pointer
    double* p2 = reinterpret_cast<double*>(bits);
    
    return 0;
}

/*
cppdouble d = 3.14;
double* p = &d;

// Treat pointer bits as integer
uintptr_t bits = reinterpret_cast<uintptr_t>(p);

// Treat integer bits as pointer
double* p2 = reinterpret_cast<double*>(bits);
Step 3: What is a Data structure?
Just a struct/class with some members.
Example:
cppstruct Data {
    int id;
    std::string name;
    float value;
};
Step 4: Serialize/Deserialize pattern
cppData original;
original.id = 100;

// Pointer → integer
uintptr_t serialized = serialize(&original);

// Integer → pointer
Data* restored = deserialize(serialized);

// restored == &original (TRUE)
Step 5: Class requirements

Not instantiable (delete constructors)
Two static methods
Methods do type conversion only

Pattern:
cppclass Serializer {
    Serializer() = delete;
public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};
Now try implementing it yourself!RetryYMhey what i includeFor ex01, include:
cpp#include <cstdint>  // for uintptr_t
#include <string>   // if Data has std::string
#include <iostream> // for testing output
That's all you need.RetryYMcstdint> hwat stands for that?cstdint = C Standard Integers
Contains fixed-width integer types like:

uint8_t (8-bit unsigned)
int32_t (32-bit signed)
uintptr_t (unsigned int that holds pointers)

The c prefix means it's the C++ version of C's stdint.h.
*/