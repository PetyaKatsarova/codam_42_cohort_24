2. std::vector (from <vector>)
Dynamic size: Can grow/shrink at runtime.

Heap-allocated (unless small, with optimizations).

Manages memory itself.

Much more flexible than std::array, but slightly slower due to heap use.

Example:

cpp
Copy
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40};
    v.push_back(50);
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << "\n";
    v.pop_back();  // removes last element
    v.resize(2);   // now contains only first 2 elements
    std::cout << v.front() << " " << v.back() << "\n";
    return 0;
}
Most used functions:

size() – Number of elements

push_back(val) – Add at end

pop_back() – Remove last

resize(newsize) – Set size (truncate or extend)

clear() – Remove all elements

empty() – Is vector empty

front(), back() – First/last element

at(idx) – Checked access

operator[] – Direct access (no bounds check)

insert(pos, val) – Insert at position

erase(pos) – Remove at position

swap(vec2) – Swap contents (fast, pointer swap)

begin(), end() – Iterators