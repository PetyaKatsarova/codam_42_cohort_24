#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"
#include <iostream>
#include <stdexcept>

template <typename T>
Array<T>::Array() : arr(NULL), len(0) {
    std::cout << "default constr\n";
}

/**
int* a = new int();  // () = value-initialize (sets to 0)
std::cout << *a;     // Output: 0
int* b = new int;    // No () = uninitialized (garbage)
std::cout << *b;     // Output: random value
*/
template <typename T>
Array<T>::Array(unsigned int num) : arr(new T[num]()), len(num) {
    std::cout << "constr with len: " << num << std::endl;
} 

// deep cpy using the = operator
template <typename T>
Array<T>::Array(const Array& other) : arr(NULL), len(0) {
   std::cout << "cpy constr\n";
   *this = other;
}

template <typename T>
Array<T>::~Array() {
    std::cout << "destructor for arr with len: " << this->len << "\n";
    delete[] arr;
}

/*
* dereferences the pointer
this = pointer to current object (0x1000)
*this = the object itself at 0x1000
But return type is &, so returns REFERENCE
*/
template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] arr;
        len = other.len;
        arr = new T[len];
        for (unsigned int i  =0; i < len; i++) {
            arr[i] = other.arr[i];
        }
    }
    std::cout << "operator=\n";
    return *this;
}

/**subscript operator: like built in arr[index] */
template <typename T>
T& Array<T>::operator[](unsigned int i) const {
    if (i >= len) {
        throw std::out_of_range("Index out of bounds\n");
    }
    return arr[i];
}

template <typename T>
unsigned int Array<T>::size() const {
    return len;
}

#endif