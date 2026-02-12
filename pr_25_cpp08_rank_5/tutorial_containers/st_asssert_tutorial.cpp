#include <cassert>

void checkPosiitve(int x) {
	static_assert(sizeof(int) == 4, " int must be 4 bytes");
	// check at compile time that int is 4 bytes
}

int main() {
	int x = 5;
	assert(x > 0 && "x must be positive"); // run time assert:aborted, core dumped

	static_assert(sizeof(int) > 0, " int has size"); // compile time failt
	static_assert(5>3, "math works");
	return 0;
}