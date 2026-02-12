#include <vector>
#include <list>
#include <array>
#include <iostream>
#include <cstdlib> // atoi()

#include "easyfind.hpp"

int main(int argc, char** argv) {
	std::vector<int> 	vec = {1, 2, 3, 4};
	std::array<int, 5> 	arr = {1, 2, 3, 4, 5};
	std::list<int>		lst = {1, 10, 20, 30, 40};
	int num = 5;

	vec.push_back(6);
	vec.push_back(7);
	if (argc == 2)
			num = std::atoi(argv[1]); // returns 0 if not int
	try {
		auto it = 	easyfind(vec, num);
		std::cout << "in vector: " << *it << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << " vector" << std::endl;
	}
	try {
		auto it2 = 	easyfind(arr, num);
		std::cout << "in array: " << *it2 << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << " array" << std::endl;
	}
	try {
		auto it3 = easyfind(lst, num);
		std::cout << "in list: " << *it3 << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << " list" << std::endl;
	}

	return 0;
}