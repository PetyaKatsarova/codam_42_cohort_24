#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <type_traits> // is_same_v

/**
The function passed as the third parameter may take its argument by const reference or non-const reference, depending on the context.
Think carefully about how to support both const and non-const
elements in your iter function.

*/

template<typename T>
void incrementTemplate(T& val) {
    static_assert(std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, double>,
                  "incrementTemplate only supports int, float, or double");
    ++val;
}

template<typename T>
void doubleValTemplate(T& val) {
    static_assert(std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, double>,
                  "doubleValTemplate only supports int, float, or double");
    val *= 2;
}

/* A func that takes const T& can accept BOTH const and non-const arguments.
The template automatically adapts based on whether is passed: a const or non-const array.
No need of two separate overloads or any special handling—the type deduction does it all.
*/
template<typename T>
void printTemplate (const T& val) { std::cout << val << " "; }

template<typename T, typename F>
void iter(T* arr, const size_t arr_len, F func) {
    for (size_t i = 0; i < arr_len; i++) {
        func(arr[i]);
    }
}

#endif