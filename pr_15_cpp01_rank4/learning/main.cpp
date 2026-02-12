#include <iostream>

int main() {
	printf("tra la la\n");

	struct S { int x; };
	// px doesn’t point at any one object’s x;  
	// it describes “where x lives inside S.”  
	int S::* px = &S::x;    // pointer-to-member
	S s{42};
	std::cout << s.*px;     // prints 42

	return (0);
}