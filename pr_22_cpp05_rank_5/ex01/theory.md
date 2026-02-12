int and bool are built‑in (primitive) C++ types — not in namespace std and need no header.
There is no type named std::bool — your code must use plain bool.
If you need fixed-width integers use <cstdint> and types like std::int32_t.
std::string is in namespace std and requires #include <string>.
std::boolalpha is a stream manipulator (in <iostream>) — that’s different from the bool type.
===================================
.data() function:

Returns a pointer to the internal character array of the std::string.
For std::string, .data() returns const char* pointing to the string's buffer.
Example: "crazy".data() → pointer to 'c' in memory.
=====================================
static_cast = compile-time type conversion (checked by compiler, no runtime overhead).
const void* = generic pointer type (points to any data, read-only).
Why cast? Without it, std::cout << const char* prints the string content ("crazy"), not the address. Casting to const void* forces std::cout to print the pointer value (memory address like 0x7ffc1234abcd).
========================================
"static" in static_cast:

Means the cast is resolved at compile time (compiler checks if conversion is valid).
Compilation = translating your C++ source code into machine code (executable). Compiler checks types, syntax, performs optimizations.
=========================================
Comparison: Object address vs Buffer address

// Object address (where std::string object lives):
static_cast<const void*>(&b.getName())
// Example output: 0x7ffc1234

// Buffer address (where char data is stored):
static_cast<const void*>(b.getName().c_str())
// Example output: 0x55ab5678 (usually different, might be heap-allocated)

Expression	          What it prints	                Use case
&b.getName()	      Address of std::string object	   Check if copy created a new object
b.getName().c_str()	  Address of char buffer ("Bob")	Check if string data was deep-copied
b.getName()	          String content ("Bob")	        Print the actual string
==============================================================
.data() vs .c_str() — What's the Difference?

Both return a pointer to the character buffer, but with a subtle historical difference:

.c_str() — C-String Pointer (Guaranteed Null-Terminated)
Returns const char* pointing to a null-terminated C-style string.
Guaranteed to have '\0' at the end.
Use when interfacing with C APIs that expect null-terminated strings (e.g., printf, fopen, etc.).

data() — Raw Data Pointer
const char* data() const;  // C++11/14
char* data();              // C++17+ (non-const overload)

Returns const char* pointing to the character buffer.
In C++11/14: Guaranteed null-terminated (same as .c_str()).
In C++17+: Also provides a non-const overload for modifying strings.
Use when you need a raw pointer to the data (e.g., for printing addresses, binary operations).

const char* ptr = form.getName().data();
// ptr points to: "crazy\0" (same as c_str in modern C++)