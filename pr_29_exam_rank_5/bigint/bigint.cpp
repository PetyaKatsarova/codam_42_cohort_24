#include "bigint.hpp"
#include <sstream>

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
	return (os << obj.get_val());
}

bigint::bigint() : val("0") {}

bigint::bigint(unsigned int n){
	std::stringstream ss;
	ss << n;
	val = ss.str();
}

bigint::bigint(const bigint& other) : val(other.val) {}

bigint::~bigint() {}

bigint bigint::operator=(const bigint& other) {
	if (this != &other)
		val = other.val;
	return *this;
}

std::string bigint::get_val() const { return val; }

bigint bigint::operator+(const bigint& other) const {
	std::string v1 = val;
	std::string v2 = other.get_val();
	std::string result;
	int size_this = v1.size();
	int size_other = v2.size();
	int carry = 0;

	while (carry || size_this > 0 || size_other > 0) {
		int sum = carry;
		if (size_this > 0)
			sum += v1[--size_this] - '0';
		if (size_other > 0)
			sum += v2[--size_other] - '0';
		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;
	}
	bigint res;
	res.val = result;
	return res;
}

bigint& bigint::operator+=(const bigint& other) {
	*this = *this + other;
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
bigint	bigint::operator>>(const bigint& shift) const {
	unsigned int n = 0;
	unsigned int len = shift.val.size();
	std::string result = val;

	for (unsigned int i = 0; i < len; i++)
		n = n * 10 + (shift.val[i] - '0');
	
	if (result == "0" || n >= result.size())
		result = "0";
	else
	 {
		result.erase(result.size() - n);
	}
	bigint temp(*this);
	temp.val = result;
	return temp;
}
	
bigint& bigint::operator>>=(const bigint& shift) {
	*this = *this >> shift;
	return *this;
}

bool bigint::operator>(const bigint& other) const {
	if (val.size() != other.val.size())
		return val.size() > other.val.size();
	return (val > other.val);
}

bool bigint::operator<(const bigint& other) const {
	if (val.size() != other.val.size())
		return val.size() < other.val.size();
	return (val < other.val);
}

bool bigint::operator>=(const bigint& other) const {
	return (*this == other || *this > other);
}
bool bigint::operator<=(const bigint& other) const {
	return (*this == other || *this < other);
}
bool bigint::operator==(const bigint& other) const {
	if (val.size() != other.val.size())
		return false;
	return val == other.val;
}
bool bigint::operator!=(const bigint& other) const {
	if (val.size() != other.val.size())
		return true;
	return val != other.val;
}
