/*Exercise : 04
Sed is for losers
Turn-in directory : ex04/
Files to turn in : Makefile, main.cpp, *.cpp, *.{h, hpp}
Forbidden functions : std::string::replace
Create a program that takes three parameters in the following order: a filename and
two strings, s1 and s2.
It must open the file <filename> and copy its content into a new file
<filename>.replace, replacing every occurrence of s1 with s2.
Using C file manipulation functions is forbidden and will be considered cheating. All
the member functions of the class std::string are allowed, except replace. Use them
wisely!
Of course, handle unexpected inputs and errors. You must create and turn in your
own tests to ensure that your program works as expected.
*/

#include "Replace.hpp"
#include <iostream>

int main (int argc, char **argv) {
    if (argc != 4) {
		std::cerr << "Usage: ./replace <filename> <s1> <s2>\n";
		return 1;       
    }
    Replace bla(argv[1], argv[2], argv[3]);
    if (!bla.process())
        return (1);
    return (0);
}