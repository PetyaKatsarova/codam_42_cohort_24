std::string is a class defined as a specialization of the std::basic_string template with char as the element type.

It acts like a dynamic array (container) of characters, with extra string-specific methods.

3. How does std::string treat characters and encoding?
std::string treats its contents as bytes (type char).

It doesn’t “understand” or process encoding (ASCII, UTF-8, etc.)—it just stores and manipulates sequences of bytes.

Operations like .length(), .size(), iterators, etc. count bytes—not Unicode characters.

Example: "é" in UTF-8 is 2 bytes, but std::string("é").size() is 2, not 1.
============================================================

Top 10 most used std::string functions:

size() / length()
Returns the number of characters (bytes) in the string.
str.size();  // or str.length();
empty()
Checks if the string is empty.
if (str.empty()) { /* ... */ }
operator+= / append()
Concatenates another string or character.
str += " world";
str.append(" world");
operator[] / at()
Accesses character at given index (with or without bounds checking).
char c = str[2];
char d = str.at(2);  // throws if out of range
substr(pos, len)
Returns a substring starting at pos, length len.
std::string sub = str.substr(1, 4);
find(sub)
Finds the first occurrence of sub and returns its index, or npos if not found.
size_t pos = str.find("cat");
replace(pos, len, newstr)
Replaces part of the string with newstr.
str.replace(2, 3, "abc");
erase(pos, len)
Erases part of the string.
str.erase(1, 2);
insert(pos, str2)
Inserts a string at a specified position.
str.insert(3, "yo");
c_str()
Returns a C-style (null-terminated) const char* pointer for compatibility with C functions.
printf("%s", str.c_str());

clear() — Empties the string (str.clear();)
compare() — Lexicographical comparison (str1.compare(str2))

-----------------------------------
Construction & Assignment
Constructors
-----------------------------------

std::string s; // default (empty)

std::string s("hello"); // from C-string

std::string s(10, 'a'); // repeat character

std::string s(str); // copy/move constructor

Assignment

str = "text"; // from C-string

str = other; // from another string

str.assign("hello");

str.assign(5, 'x');
------------------------
ELEMENT ACCESS
------------------------
operator[]

at()

front() // first character

back() // last character

data() // returns pointer to data
--------------------------
Capacity
--------------------------
empty()

size() / length()

max_size() // max possible size

reserve(n) // reserve capacity

capacity() // current capacity

shrink_to_fit() // reduce memory usage
--------------------------------------
Modifiers
--------------------------------------
clear() // erase all contents

insert(pos, str)

insert(pos, n, char)

insert(pos, first, last) // insert from another range

erase(pos, len)

erase(iter)

push_back(char)

pop_back()

append(str)

append(n, char)

append(first, last)

operator+=

replace(pos, len, str)

replace(first, last, str)

swap(str) // swap contents with another string
----------------------------------------------
String Operations
copy(dest, n, pos) // copy substring to char array

substr(pos, len) // substring

compare(str) // compare with another string

compare(pos, len, str)

starts_with(prefix) // C++20

ends_with(suffix) // C++20
----------------------------------------------
Search
find(str, pos) // find substring

find(char, pos)

rfind(str, pos) // find last occurrence

rfind(char, pos)

find_first_of(str, pos)

find_last_of(str, pos)

find_first_not_of(str, pos)

find_last_not_of(str, pos)
-----------------------------------------------
Iterators
begin(), end()

cbegin(), cend()

rbegin(), rend()

crbegin(), crend()
------------------------------------------------
