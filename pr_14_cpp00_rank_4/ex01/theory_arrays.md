1. std::array (from <array>)
Fixed size: Size set at compile time, cannot change.

Stack-allocated: Like int arr[5];

No dynamic memory management.

Zero-size is valid: std::array<int, 0> arr0;, but you can't access elements.

Swapping two arrays swaps all their elements individually (linear time).
Can be used with structured bindings and as tuples. A tuple is an ordered collection of elements, where each element can be of a different type.

#include <array>
#include <iostream>

int main() {
    std::array<int, 4> arr = {10, 20, 30, 40};
    for (size_t i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
    arr.fill(5);  // sets all elements to 5
    std::cout << arr.front() << " " << arr.back() << "\n";
    return 0;
}

Most used functions:

size() – Number of elements

fill(value) – Set all elements

front(), back() – First/last element

data() – Pointer to underlying data

operator[] – Element access

Iterators: begin(), end()

swap(arr2) – Swap with another array (elementwise)