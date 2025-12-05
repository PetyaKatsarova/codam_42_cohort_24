#include <vector>
#include <list>
#include <array>
#include <iostream>
#include <cstdlib> // atoi()

#include "easyfind.hpp"

int main(int argc, char** argv) {
	std::vector<int> 	vec = {1, 2, 3, 4};
	std::array<int, 5> 	arr = {1, 2, 3, 4, 5};
	int num = 5;

	vec.push_back(6);
	vec.push_back(7);
	if (argc == 2)
			num = std::atoi(argv[1]); // returns 0 if not int
	try {
		auto it = 	easyfind(vec, num);
		auto it2 = 	easyfind(arr, num); // found
		std::cout << "in vector: " << *it << std::endl;
		std::cout << "in array : " << *it2 << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}