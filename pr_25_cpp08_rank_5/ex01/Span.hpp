#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>

/**
Develop a Span class that can store a maximum of N integers. N is an unsigned int variable and will be the only parameter passed to the constructor.
This class will have a member function called addNumber() to add a single number
to the Span. It will be used in order to fill it. Any attempt to add a new element if there
are already N elements stored should throw an exception.
Next, implement two member functions: shortestSpan() and longestSpan()
They will respectively find out the shortest span or the longest span (or distance, if
you prefer) between all the numbers stored, and return it. If there are no numbers stored,
or only one, no span can be found. Thus, throw an exception.
 */

class Span {
	public: // for testing : change to private
	unsigned int		N;
	std::vector<int>	numbers;

	public:
		Span(unsigned int n);
		Span(const Span& other);
		~Span();
		Span& operator=(const Span& other);

		void 			addNumber(int num);
		unsigned int 	shortestSpan();
		unsigned int 	lonestSpan();
};

#endif