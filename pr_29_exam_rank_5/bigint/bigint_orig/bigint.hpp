#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint
{
private:
	std::string value;

	void removeLeadingZeros();

public:
	bigint();
	bigint(unsigned int n);
	bigint(const bigint& other);
	~bigint();

	bigint& operator=(const bigint& other);

	// addition
	bigint operator+(const bigint& other) const;
	bigint operator+(unsigned int n) const;
	bigint& operator+=(const bigint& other);

	// increment
	bigint& operator++();
	bigint operator++(int);

	// digit shift
	bigint operator<<(unsigned int shift) const;
	bigint operator>>(const bigint& shift) const;
	bigint& operator<<=(unsigned int shift);
	bigint& operator>>=(const bigint& shift);

	// comparison
	bool operator<(const bigint& other) const;
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
	bool operator==(const bigint& other) const;
	bool operator!=(const bigint& other) const;

	//friend is a C++ keyword that allows a non-member function (or another class) to access a class's private and protected members.
	friend std::ostream& operator<<(std::ostream& os, const bigint& n);
};

#endif