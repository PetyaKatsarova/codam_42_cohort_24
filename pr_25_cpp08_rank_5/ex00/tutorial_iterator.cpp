#include <vector>
#include <list>
#include <array>
#include <iostream>
#include <cstdlib> // atoi()

/**
 * iterator types for diff containers:
 * std::vector<int>::iterator
 * std::list<int>::iterator
 * std::array<int, 5>::iterator
 * 
 * An iterator is like a pointer that points to an element in a container. It lets you navigate through containers uniformly.
 */

int main(int argc, char** argv) {
	std::vector<int> vec = {10,20,30};
	std::vector<int>::iterator it = vec.begin(); // points for first el
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;
	return 0;
}