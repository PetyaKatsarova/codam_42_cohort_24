Every header in the C++ Standard Library simply tells the compiler “please make these names available,” but all of those names live inside the std namespace. The header <fstream> provides you with three main classes:

std::ifstream → input file stream

std::ofstream → output file stream

std::fstream → file stream (both input & output)

Even though the header is called <fstream>, the classes it defines are still in namespace std. That’s why you write:

cpp
Copy
Edit
#include <fstream>

std::ifstream infile("myfile.txt");
std::ofstream outfile("out.txt");

Why the mismatch between header name and namespace?
Header names group related functionality:

<vector> for std::vector,

<map> for std::map,

<sstream> for std::istringstream, std::ostringstream, etc.

Namespaces prevent name collisions. Every symbol in the Standard Library lives in std::, regardless of what header you included.

Remember: any time you include a standard header, its contents go into std. If you ever see an unqualified name like ifstream, it either means the author did a using namespace std; (not recommended in headers) or a using std::ifstream; at the top of their file.
============================================
found = line.find(s1, pos))
line: the full text string.

s1: the substring you want to find.

pos: the index to start searching from.
pos = found + s1.length();
line = "aba";
s1   = "a";
pos  = 0;

// 1st find:
found = line.find("a", 0); // found = 0
pos   = 0 + 1;             // pos   = 1

// 2nd find:
found = line.find("a", 1); // found = 2
pos   = 2 + 1;             // pos   = 3

// 3rd find:
found = line.find("a", 3); // found = npos → stop


std::string::npos is a static constant of type size_t (an unsigned integer type). It’s defined as the largest possible size_t value (typically (size_t)-1) and is returned by string-search functions (like find) to mean “no position” (i.e. not found).


line.find(s1, pos) returns:

the index of the next s1 occurrence ≥ pos, or

std::string::npos if not found.
