#include <string>
#include <iostream>
#include <string_view>

/**
std::string s = "Hello";
Allocates heap memory, copies "Hello" into it
When s destroyed, frees memory

std::string_view sv = "Hello";
Points to "Hello" in read-only memory
NO allocation, NO copy
When sv destroyed, does nothing (doesn't own the data)

void processString(std::string s) {  // COPIES entire string!
    std::cout << s;
}

std::string original = "Very long string...";
processString(original);  // Expensive copy!

void processString(std::string_view sv) {  // Just pointer + size!
    std::cout << sv;
}

std::string original = "Very long string...";
processString(original);  // No copy! Fast!
*/

void printName(std::string_view name) { // access anything
    std::cout << name << '\n';
}

//c++ -std=c++17 string_view_code.cpp && ./a.out

int main() {
    std::cout << "=== Test 1: Basic string_view ===" << std::endl;
    std::string_view sv1 = "Hello";
    printName(sv1);
   
    
    std::cout << "\n=== Test 2: From std::string ===" << std::endl;
    std::string str = "World";
    printName(str);  // No copy!
   
    
    std::cout << "\n=== Test 3: From C-string ===" << std::endl;
    const char* cstr = "C-style";
    printName(cstr);  // No conversion!
   
    
    std::cout << "\n=== Test 4: String literal ===" << std::endl;
    printName("Direct literal");
   
    
    std::cout << "\n=== Test 5: Substring (NO COPY!) ===" << std::endl;
    std::string_view original = "Hello World";
    // Points to "World"
    printName(original.substr(6));
   
    
    std::cout << "\n=== Test 6: Size and operations ===" << std::endl;
    std::string_view sv2 = "Test String";
    std::cout << "Size: " << sv2.size() << std::endl;
    std::cout << "First char: " << sv2.front() << std::endl;
    std::cout << "Last char: " << sv2.back() << std::endl;
    std::cout << "Is empty? " << (sv2.empty() ? "yes" : "no") << std::endl;
    
    std::cout << "\n=== Test 7: Remove prefix/suffix ===" << std::endl;
    std::string_view sv3 = "HelloWorld";
    sv3.remove_prefix(5);  // Remove "Hello"
    printName(sv3);  // "World"
   
    
    sv3 = "HelloWorld";
    sv3.remove_suffix(5);  // Remove "World"
    printName(sv3);  // "Hello"
   
    
    std::cout << "\n=== Test 8: Find ===" << std::endl;
    std::string_view sv4 = "Find the word";
    size_t pos = sv4.find("word");
    if (pos != std::string_view::npos) {
        std::cout << "Found 'word' at position: " << pos << std::endl;
        printName(sv4.substr(pos));  // "word"
       
    }
    
    std::cout << "\n=== Test 9: Compare ===" << std::endl;
    std::string_view sv5 = "abc";
    std::string_view sv6 = "abc";
    std::cout << "sv5 == sv6? " << (sv5 == sv6 ? "yes" : "no") << std::endl;
    std::cout << "sv5 < \"xyz\"? " << (sv5 < "xyz" ? "yes" : "no") << std::endl;
    
    std::cout << "\n=== Test 10: Multiple substrings (NO COPIES!) ===" << std::endl;
    std::string_view sentence = "The quick brown fox";
    printName(sentence.substr(0, 3));   std::cout << " ";  // "The"
    printName(sentence.substr(4, 5));   std::cout << " ";  // "quick"
    printName(sentence.substr(10, 5));  std::cout << " ";  // "brown"
    printName(sentence.substr(16));      // "fox"
    
    std::cout << "\n=== Test 11: Pass different types to printName ===" << std::endl;
    std::string stdStr = "std::string";
    const char* cString = "C-string";
    std::string_view svString = "string_view";
    
    printName(stdStr);   
    printName(cString);   std::cout << std::endl;
    printName(svString);  std::cout << std::endl;
    printName("literal"); std::cout << std::endl;
    
    std::cout << "\n=== Test 12: Starts with / Ends with (C++20) ===" << std::endl;
    // Only if using C++20:
    // std::string_view sv7 = "HelloWorld";
    // std::cout << "Starts with 'Hello'? " << sv7.starts_with("Hello") << std::endl;
    // std::cout << "Ends with 'World'? " << sv7.ends_with("World") << std::endl;
    
    return 0;
}
