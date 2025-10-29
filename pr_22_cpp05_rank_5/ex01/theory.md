int and bool are built‑in (primitive) C++ types — not in namespace std and need no header.
There is no type named std::bool — your code must use plain bool.
If you need fixed-width integers use <cstdint> and types like std::int32_t.
std::string is in namespace std and requires #include <string>.
std::boolalpha is a stream manipulator (in <iostream>) — that’s different from the bool type.
