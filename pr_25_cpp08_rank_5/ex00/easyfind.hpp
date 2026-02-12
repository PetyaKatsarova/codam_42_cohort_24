#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm> // find() searches by value
#include <stdexcept> // std::runtime_error

/**
std::array<T, N>: fixed size arr container: fixed at compile time, on the stack, faster(no allocation), declare: std::array<int, 5> cant resize

std::vector<T>: dynamic aray container(can grow/shrink), on the heap, slower, std::vector(int) vec, can resize
*/

/**
 * Iterator = a pointer-like object that points to an element in a container.
 * Generic access - works with ANY container (vector, list, array, etc.)
Standard return type - std::find returns an iterator
Flexibility - can navigate, dereference, or pass to other algorithms
 */

 /*
 Associative containers = containers that store elements in a sorted order and allow fast lookup by key (not by index/position)
std::set - unique sorted values
std::map - key-value pairs (like a dictionary)
std::multiset - sorted values (duplicates allowed)
std::multimap - key-value pairs (duplicate keys allowed)

An iterator is like a pointer that points to an element in a container. It lets you navigate through containers uniformly.
 */
template<typename C> // container
typename C::iterator easyfind(C& c, int num) {
	typename C::iterator it = std::find(c.begin(), c.end(), num);
	if (it == c.end())
		throw std::runtime_error("num[" + std::to_string(num) + "] not found in");
	return it;
}

#endif