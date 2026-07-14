#include "bigint.hpp"
#include <sstream>
#include <algorithm> // std::reverse(begin, end)

// ------------ helpers ----------------
/* rmv leading 0s */
void bigint::normalize() {
	std::size_t pos = 0;
	while (pos < val.length() - 1 && val[pos] == '0')
		pos++; // having min 1 digit
	if (pos > 0)
		val = val.substr(pos);
}

int bigint::compare(const bigint& other) const {
	if (val.length() < other.val.length()) 
		return -1;

	if (val.length() > other.val.length()) 
		return 1;

	for (std::size_t i = 0; i < val.length(); i++) {
		if (val[i] < other.val[i])
			return -1;
		if (val[i] > other.val[i])
			return 1;
	}
	return 0;
}

std::size_t	bigint::to_size_t () const {
	std::size_t num = 0;
	for (std::size_t i = 0; i < val.size(); i++) // size() returns size_t
		num = num * 10 + (val[i] - '0');
	return num;
}

bigint 	operator+(const bigint& lhs,  const bigint& rhs) {
	bigint temp(lhs);
	temp += rhs;
	return temp;
}

// -------------- end helpers --------------

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
	return (os << obj.get_val());
}

bigint::bigint() : val("0") {}

bigint::bigint(unsigned int n){
	std::stringstream ss;
	ss << n;
	val = ss.str();
}

/*
Shallow copy: copies the pointer, both objects point to same data.
  Deep copy: copies the actual data, each object has its own.
*/
bigint::bigint(const bigint& other) : val(other.val) {}

bigint::~bigint() {}

bigint& bigint::operator=(const bigint& other) {
	if (this != &other)
		val = other.val;
	return *this;
}

std::string bigint::get_val() const { return val; }

bigint& bigint::operator+=(const bigint& other) {
	std::string v1 = val;
	std::string v2 = other.get_val();
	std::string result;
	std::size_t size_this = v1.size();
	std::size_t size_other = v2.size();
	int carry = 0;

	while (carry || size_this > 0 || size_other > 0) {
		int sum = carry;
		if (size_this > 0)
			sum += v1[--size_this] - '0';
		if (size_other > 0)
			sum += v2[--size_other] - '0';
		result += char((sum % 10) + '0');
		carry = sum / 10;
	}
	std::reverse(result.begin(), result.end());
	val = result;
	normalize();
	return *this;
}

bigint& bigint::operator++() {
	*this = *this + bigint(1);
	return *this;
}

bigint	bigint::operator++(int) {
	bigint temp(*this);
	++(*this);
	return temp;
}

// 42 << 3 == 42000
bigint bigint::operator<<(unsigned int n) const {
	bigint temp(*this);
	if (n > 0 && temp.val != "0")
		temp.val.append(n, '0');	
	return temp;
}

bigint& bigint::operator<<=(unsigned int n) {
	*this = *this << n;
	return *this;
}

// 1337 >> 2 == 13
bigint	bigint::operator>>(const bigint& other) const {
	bigint temp(*this);
	size_t shift = other.to_size_t();
	if (temp.val == "0" || shift >= temp.val.size())
		temp.val = "0";	
	else
		temp.val.erase(temp.val.size() - shift);
	return temp;
}
	
bigint& bigint::operator>>=(const bigint& shift) {
	*this = *this >> shift;
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
