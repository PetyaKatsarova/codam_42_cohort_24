//Forbidden functions: std::typeinfo

// These four classes don’t have to be designed in the Orthodox Canonical Form.
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "generator.hpp"


#include <iostream>

/**
 * An aggregate is a simple aggregate object type: essentially a struct/union/array that has no user-declared constructors, no private/protected non-static data members, no virtual functions, and no virtual base classes. (Practically: a plain data‑holding struct.)
Aggregate initialization (brace init) initializes members directly, in declaration order, without calling a user constructor. Data data = {val1, val2} or Data data2{val1, val2}
arr aggregate: int a[] = {1,2,3};
 */
int main() {
	Base* suprise1 = generate();
	Base* suprise2 = generate();
	identify(suprise1);
	identify(suprise2);
	identify(suprise1);
	identify(suprise2);
	identify(suprise1);
	identify(suprise2);
	delete suprise1;
	delete suprise2;

	//identify(&a);
	return 0;
}