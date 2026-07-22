#include "bigint3_solution.hpp"
#include <sstream>
#include <iostream>

//------ free electrons funcs funcs ---------------
std::ostream& operator<<(std::ostream& os, const bigint& obj) {
	return os << obj.get_val();
}

bigint operator+(const bigint& lhs, const bigint& rhs) {
	bigint temp(lhs);
	temp += rhs;
	return temp;
}

// --------- end of free funcs

bigint::bigint() : val("0") {}

bigint::bigint(unsigned int n) {
	std::stringstream ss;
	ss << n;
	val = ss.str();
	normalize();
}

bigint::bigint(const bigint& other) : val(other.val) {}

bigint& bigint::operator=(const bigint& other) {
	if (this != &other)
		val = other.val;
	return *this;
}

bigint::~bigint() {}


std::string bigint::get_val() const {
	return val;
}

void bigint::normalize() {
	unsigned int i = 0;

	while (i + 1 < val.size() && val[i] == '0')
		i++;
	val.erase(0, i);
}

int bigint::compare(const bigint& other) const{
	if (val.size() > other.val.size())
		return 1;
	if (val.size() < other.val.size())
		return -1;
	if (val > other.val)
		return 1;
	if (val < other.val)
		return -1;
	return 0;	
}

bigint& bigint::operator+=(const bigint& other) {
	std::string result;
	std::string	v2 = other.val;
	unsigned int s1 = val.size();
	unsigned int s2 = other.val.size();
	int carry = 0;
// loop through each char digit
	while (carry || s1 > 0 || s2 > 0) {
		int sum = carry;
		if (s1 > 0)
			sum += val[--s1] - '0';
		if (s2 > 0)
			sum += v2[--s2] - '0';
		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;
	}
	val = result;
	normalize();
	return *this;
}

bigint& bigint::operator++() {
	*this += bigint(1);
	return *this;
}

bigint bigint::operator++(int) {
	bigint temp(*this);
	++(*this);
	return temp;
}

//42 << 3 == 42000
bigint bigint::operator<<(unsigned int shift) const {
	bigint temp(*this);

	if (val == "0" || shift == 0)
		return temp;
	temp.val.append(shift, '0');
	return temp;
}

bigint& bigint::operator<<=(unsigned int shift) {
	if (val == "0" || shift == 0)
		return *this;
	val.append(shift, '0');
	return *this;
}

// and (1337 >> 2 == 13))
bigint bigint::operator>>(const bigint& other) const {
	unsigned int shift = 0;
	bigint temp(*this);

	if (val == "0" || other.val == "0")
		return temp;
	for (unsigned int i = 0; i < other.val.size(); i++)
		shift = shift * 10 + (other.val[i] - '0');
	if (val.size() <= shift)
		temp.val = "0";
	else
		temp.val.erase(temp.val.size() - shift); //1234>>3: 4 -3 : erase from index 1, 3 digits
	return temp;
}

bigint& bigint::operator>>=(const bigint& other) {
	*this = *this >> other;
	return *this;
}

bool bigint::operator>(const bigint& other) const {
	return (compare(other) > 0);
}

bool bigint::operator<(const bigint& other) const {
	return (compare(other) < 0);
}

bool bigint::operator>=(const bigint& other) const {
	return (compare(other) >= 0);
}

bool bigint::operator<=(const bigint& other) const {
	return (compare(other) <= 0);
}

bool bigint::operator==(const bigint& other) const {
	return (compare(other) == 0);
}

bool bigint::operator!=(const bigint& other) const {
	return (compare(other) != 0);
}

