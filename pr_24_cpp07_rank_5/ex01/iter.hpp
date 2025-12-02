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

// takes non-const reference
template<typename T, typename F>
void iter(T* arr, size_t arr_len, F func) {
    for (size_t i = 0; i < arr_len; i++) {
        func(arr[i]);
    }
}

// for const arr
template<typename T, typename F>
void iter(const T* arr, size_t len, F func) {
    for (size_t i = 0; i < len; i++) {
        func(arr[i]);
    }
}

#endif