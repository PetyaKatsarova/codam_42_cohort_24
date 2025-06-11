#include <iostream>

//using namespace std;

/**
 * -O2 is a compiler optimization flag.
Tells the compiler to optimize your code for speed and efficiency (level 2).
Enables a wide range of optimizations like inlining functions, loop unrolling, and removing unused code.The program runs faster, but compilation may take a bit longer.

Levels:
-O0: No optimization (default, fastest to compile, easiest to debug)
-O1: Basic optimization
-O2: Good balance (commonly used)
-O3: Maximum optimization (can make binaries larger)
-Os: Optimize for size
Recommended for most release builds, not for debugging.
 */
//g++ -std=c++11 -Wall -Wextra -Werror -O2 hello_w.cpp -o hello_w && ./hello_w

class Person {
	public:
	std::string first;
	std::string last;

	void printFullStr() {
		std::cout << first << " " << last << std::endl;
	}
};

namespace mymath {
    int add(int a, int b) { return a + b; }
}

int result = mymath::add(2, 3); // Uses the function inside the 'mymath' namespace

int main()
{
	Person p;
	std::cout << "Hello Wrold! Cool, it's working :)\n";
	p.first = "Tra la la";
	p.last = "ku ku";

	p.printFullStr();
	return (0);
}