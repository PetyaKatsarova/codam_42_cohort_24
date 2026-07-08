#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
	private:
		std::string val;

		void rmvLeading0s();

	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint& other);
		~bigint();

		bigint& operator=(const bigint& other);

		friend std::ostream& operator<<(std::ostream& os, const bigint& obj);

		// addition
		bigint operator+(const bigint& other) const;
		bigint operator+(unsigned int n) const;
		bigint& operator+=(const bigint& other);

		// increment
		bigint& operator++();
		bigint  operator++(int);
};

#endif