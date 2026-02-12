<iomanip> stands for "input/output manipulators"

It provides functions that change how things print with std::cout.

Function	What it does
std::setw(n)	Sets the width of the next output field
std::setfill(c)	Fills empty space with character c
std::setprecision(n)	Sets decimal precision for floats
std::left / std::right	Align text left or right

auto formatField = [](const std::string &str) {
    return str.length() > 10 ? str.substr(0, 9) + "." : str;
};

keyword:                 meaning:
auto	          Let the compiler figure out the variable type
formatField	      Variable name — this is a lambda function
[]	              Start of the lambda (anonymous function)
(const std::string &str)	Parameter: takes a string by reference
{ ... }	          Function body
