#include "Span.hpp"
#include <iostream>
#include <climits> // INT_MAX
#include <stdexcept>
#include <algorithm>

Span::Span() : N(5) { std::cout << "default container created with N=5\n"; }

Span::Span(unsigned int num) : N(num) {
	std::cout << "constructor with N: " << num << std::endl;
}

Span::Span(const Span& other) : N(other.N), numbers(other.numbers) {
	std::cout << "deep cp constructor\n"; 
}

Span::~Span() { std::cout << "End game\n"; }

//std::vector has its own assignment operator that does deep copy automatically
/**
 *  object.member ← object
	pointer->member ← pointer
	this->member ← this is always a pointer
 */
Span& Span::operator=(const Span& other) {
	if (this != &other) {
		N = other.N;
		numbers = other.numbers; // automatic deep cpy
	}
	return *this; // returns reference
}

void Span::addNumber(int num) {
	if (numbers.size() >= N)
		throw std::runtime_error("Span is full.\n");
	numbers.push_back(num);
}

// vector.size() = unsigned int: brute force: O(n*n)
//int Span::shortestSpan() {
//	if (numbers.size() < 2)
//		throw std::runtime_error("Not enough elements to find span");

//	int shortest = INT_MAX;
//	int diff = 0;

//	for (unsigned int i = 0; i < numbers.size(); ++i) {
//		for (unsigned int j = i + 1; j < numbers.size(); ++j) {
//			int temp = numbers[i] - numbers[j];
//			diff = (temp > 0) ?  temp : temp*(-1);
//			shortest = (shortest > diff) ? diff : shortest;
//		}
//	}
//	return shortest;
//}

/**
 * 

Approach	    | Time Complexity	|  Comparisons for 1000 elements
--------------------------------------------------------------------
nested loops	|  O(n²)			|	~500,000 comparisons
Sort + adjacent	| O(n log n)		|	~10,000 (sort) + 999 (loop)
---------------------------------------------------------------------
 */
int Span::shortestSpan() {
	if (numbers.size() < 2)
		throw std::runtime_error("Not enough elements to find span");

	std::vector<int> sorted = numbers;
	std::sort(sorted.begin(), sorted.end());
	int shortest = INT_MAX;
	for (unsigned int i = 0; i < sorted.size() - 1; ++i) {
		int diff = sorted[i + 1] - sorted[i];
		if (diff < shortest)
			shortest = diff;
	}
	return shortest;
}

// Sort version     | O(n log n)      | ~133,000 ops  
//int Span::longestSpan() {
//	if (numbers.size() < 2)
//		throw std::runtime_error("Not enough elements to find span");

//	std::vector<int> sorted = numbers;
//	std::sort(sorted.begin(), sorted.end());
//	return (sorted.back() - sorted.front());
//}

// faster: Min/Max version  | O(n)            | ~20,000 ops  for 10 k nums
int Span::longestSpan() {
	if (numbers.size() < 2)
		throw std::runtime_error("Not enough elements to find span");

	int max = *std::max_element(numbers.begin(), numbers.end());
	int min = *std::min_element(numbers.begin(), numbers.end());
	return (max - min);
}

int Span::getLastNum(unsigned int index) const {
	if (index >= numbers.size())
		throw std::runtime_error("Index out of bounds.");
	return numbers[index];
}