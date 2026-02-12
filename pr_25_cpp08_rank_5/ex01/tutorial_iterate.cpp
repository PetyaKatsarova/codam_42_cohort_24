#include <iostream>
#include <vector>
//#include 

int main() {
	std::vector<int> veckie = {1, 2, 3, 4, 5};

	// RANGE BASED ITERATION: With reference (to modify elements):
	for (int& v: veckie) {
		v*= 2;  // Modify elements
	}

	for (int v : veckie)
		std::cout << v << " ";
	std::cout << std::endl;

	for (size_t i = 0; i < veckie.size(); i++) {
		std::cout << veckie[i] << " ";
	}

	std::cout << "\n-- iteratate with IT --\n";
	for (std::vector<int>::iterator it = veckie.begin(); it != veckie.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// With auto (cleaner)
	for (auto it = veckie.begin(); it != veckie.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";
	// Const iterator (read-only)
	for (auto it = veckie.cbegin(); it != veckie.cend(); ++it) {
		std::cout << *it << " ";
	}

	std::cout << "\n";
	for (auto it = veckie.rbegin(); it < veckie.rend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";
	return 0;
}