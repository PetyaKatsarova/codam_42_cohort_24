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