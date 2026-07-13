#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <ostream>
#include <string>

class bigint {

	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint& other);
		~bigint();
		bigint operator=(const bigint& other);

		std::string get_val() const;

		bigint 	operator+(const bigint& other) const;
		bigint& operator+=(const bigint& other);
		bigint& operator++();
		bigint	operator++(int);

		bigint 	operator<<(unsigned int n) const;
		bigint& operator<<=(unsigned int n);
		bigint	operator>>(const bigint& shift) const;
		bigint& operator>>=(const bigint& shift);

		bool operator>(const bigint& other) const;
		bool operator<(const bigint& other) const;
		bool operator>=(const bigint& other) const;
		bool operator<=(const bigint& other) const;
		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;

	std::string val;// default is private
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);

#endif