
#include "Base.hpp"
#include "generator.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <random>
#include <iostream>

/**
 * std::random_device rd;

rd is like a tiny machine that gives you a random starting number (a seed). It asks the operating system for randomness (or falls back to a built‑in source).
std::mt19937 gen(rd());

gen is a pseudo‑random number engine (think of it as a random number factory).
gen(rd()) means “start the factory with the seed we got from rd”. That makes the factory produce different sequences each run.
std::uniform_int_distribution<int> dist(0, 2);

dist is a translator that takes the factory’s raw output and gives you a number evenly chosen from 0, 1, or 2.
“uniform” means all choices (0,1,2) are equally likely.
 */

/**
It randomly instantiates A, B, or C and returns the instance as a Base pointer
*/

Base * generate(void) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> dist(0, 2);

	int n = dist(gen);
	if (n == 0) return new A;
	if (n == 1) return new B;
	return new C;
}

/**
 * Pointer overload (identify(Base* p))
Accepts nullptr and can explicitly handle it (prints "null").
Uses dynamic_cast<T*>(p) which returns nullptr on mismatch (easy, no exceptions).
Useful when callers naturally have a pointer (e.g. generate() returns Base*).

Reference overload (identify(Base& p))
Reference cannot be null — caller guarantees a live object.
if use dynamic_cast<T&>(p) which throws std::bad_cast on mismatch; catch it to try the next type.
 */

 /**
  * randomly instantiates A, B, or C and returns the instance as a Base pointer.
  */
void identify(Base* p) {
	if (!p) { std::cout << "null\n"; return; }
	if (dynamic_cast<A*>(p)) { std::cout << "A\n"; return; }
	if (dynamic_cast<B*>(p)) { std::cout << "B\n"; return; }
	if (dynamic_cast<C*>(p)) { std::cout << "C\n"; return; }
	std::cout << "unknown\n";
}

/**
 * prints the actual type of the object referenced by p: "A", "B", or "C". 	 Using a pointer inside this function is forbidden.
	Including the typeinfo header is forbidden.
 */
void    identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A\n";
		return;
	} catch (...) {}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B\n";
		return;
	} catch (...) {}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C\n";
		return;
	} catch (...) {}
	std::cout << "unknown\n";
}
