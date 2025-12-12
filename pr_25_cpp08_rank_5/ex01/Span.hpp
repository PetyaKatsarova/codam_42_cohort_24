#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

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

		/**
		 * container.insert() is more efficient than .addNum() because:
		 * Single allocation: insert can calculate the total size needed upfront and allocate memory once, while multiple push_back calls may trigger multiple reallocations as the vector grows.

		Bulk copy: The range insert can use optimized memory copy operations (like std::copy or memcpy for trivial types) to move all elements at once, which is more cache-friendly.

		No repeated capacity checks: Each push_back checks if reallocation is needed, while insert does this once.
		 * */
		template<typename Iterator>
		void addRange(Iterator begin, Iterator end) {
			size_t len = std::distance(begin, end);
			if (numbers.size() + len > N)
				throw std::runtime_error("Not enough space in Span");
			numbers.insert(numbers.end(), begin, end);
		}
};

#endif