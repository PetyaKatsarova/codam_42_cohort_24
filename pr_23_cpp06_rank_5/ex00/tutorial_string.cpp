#include <string>
#include <iostream>

/**
std::string Modern c++
*/
int main() {
    // default constructor
    std::string s1; // empty string
    std::cout << "empty str: " << s1 << std::endl;

    // from c-string
    std::string s2 = "Hello";
    std::string s3("World");

    // cpy constr
    std::string s4 = s2;
    std::string s5(s2);

    // substring from another str
    std::string s6(s2, 1, 3); // "ell" (start at index 1, len 3)

    std::string s7(5, 'x'); // "xxxxx"
    
    // from iterators
    std::string s8(s2.begin(), s2.end());
    std::cout << "s8 begin-end: " << s8 << "\n";

    // memory management
    std::string s = "Hello";

    // capacity operations
    size_t cap = s.capacity(); // cur capacity
    size_t len = s.size(); // curr len same s length()
    bool empty = s.empty();

    // reserver memory(doesnt change size)
    s.reserve(100); // ensures capacity >=100, prevents reallocations!!

    // shrink to fit(reduce capacity to match size)
    s.shrink_to_fit();

    // resize (changes size, may add/remove chars)
    s.resize(10); // if larger, fill with '\0
    s.resize(10, 'x'); // fills new space with 'x'
    
    // clear content(size becomes 0, capacity unchanged)
    s.clear();

    // mem alloc, short str(typically <= 15-23 chars) stored in obj iteslf
    std::string small = "hi"; // no heap alloc

    // longer strings use heap
    std::string large = "this is much longer string that exceeds SSO(small string optimization)";

    std::cout << "Size: " << large.size() << "\n";
    std::cout << "Capacity: " << large.capacity() << "\n";
    return 0;
}