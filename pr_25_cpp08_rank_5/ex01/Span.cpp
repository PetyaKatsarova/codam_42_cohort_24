#include "Span.hpp"
#include <iostream>
#include <climits> // INT_MAX

Span::Span(unsigned int num) : N(num) {
	std::cout << "constructor with N: " << num << std::endl;
}

Span::Span(const Span& other) : N(other.N), numbers(other.numbers) {
	std::cout << "shallow cp constructor\n"; 
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
	if (N < numbers.size() + 1)
		throw std::runtime_error("Out of bounds; Vector container reached full capacity\n");
	numbers.push_back(num);
}

// iter through all el: find the shortest dist between any 2 elements value
unsigned int Span::shortestSpan() {
	unsigned int shortest = INT_MAX;

	return shortest;

}