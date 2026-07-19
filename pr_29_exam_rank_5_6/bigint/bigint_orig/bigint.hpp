#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <ostream>
#include <string>
#include <cstddef> // c compatability standard definitions for std:size_t

class bigint {
	private:
		std::string val;// default is private
		void 	normalize();
		int		compare(const bigint& other) const;
		size_t	to_size_t() const;

	public:
		bigint();
		bigint(unsigned int n);
		bigint(const bigint& other);
		~bigint();
		bigint& operator=(const bigint& other);

		std::string get_val() const;

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
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);

bigint 	operator+(const bigint& lhs,  const bigint& rhs);

#endif