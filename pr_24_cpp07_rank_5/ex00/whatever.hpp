#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

/**
Templates allow you to write ONE function that works with ANY type.
*/

// swap 2 values
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// return smallest, if == return second
template<typename T>
T const& min(T const& a, T const& b) {
    return (a < b) ? a : b;
}

// return largest, if == return second
template<typename T>
T const& max(T const& a, T const& b) {
    return (a > b) ? a : b;
}

#endif