#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>

class bigint {
	private:
		unsigned int num;

	public:
		bigint();
		bigint(const unsigned int& n);
		bigint(const bigint& other);
		bigint& operator=(const bigint& other);
		~bigint();

		const unsigned int& get_num() const;
		unsigned int& get_num();
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);

#endif
