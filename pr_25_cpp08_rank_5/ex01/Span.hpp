#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>

class Span {
	unsigned int		N;
	std::vector<int>	numbers;

	public:
		Span();
		Span(unsigned int n);
		Span(const Span& other);
		~Span();
		Span& operator=(const Span& other);

		void 	addNumber(int num);
		int 	shortestSpan();
		int 	longestSpan();
		int		getLastNum(unsigned int N) const;
};

#endif