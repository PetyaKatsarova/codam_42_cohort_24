#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

/**
Implement a function template iter that takes 3 parameters and returns nothing.
• The first parameter is the address of an array.
• The second one is the length of the array, passed as a const value.
• The third one is a function that will be called on every element of the array.
Submit a main.cpp file that contains your tests. Provide enough code to generate a
test executable.
Your iter function template must work with any type of array. The third parameter
can be an instantiated function template.
The function passed as the third parameter may take its argument by const reference
or non-const reference, depending on the context.
Think carefully about how to support both const and non-const
elements in your iter function.

*/

template<typename T>
void incrementTemplate(T& val) { ++val; }

template<typename T>
void doubleValTemplate(T& val) {val *= 2; }

/* A func that takes const T& can accept BOTH const and non-const arguments. */
template<typename T>
void printTemplate (const T& val) { std::cout << val << " "; }

template<typename T, typename F>
void iter(T* arr, const size_t arr_len, F func) {
    for (size_t i = 0; i < arr_len; i++) {
        func(arr[i]);
    }
}

// for const arr
// template<typename T, typename F>
// void iter(const T* arr, const size_t len, F func) {
//     for (size_t i = 0; i < len; i++) {
//         func(arr[i]);
//     }
// }

#endif