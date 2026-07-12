#include "bigint.hpp"
#include <sstream>

bigint::bigint() : val("0") {}

bigint::bigint(unsigned int n) {
	std::stringstream ss;
	ss << n;
	val = ss.str();
}

bigint::bigint(const bigint& other) : val(other.val) {}
	
bigint::~bigint() {}

bigint& bigint::operator=(const bigint& other) {
	if (this != &other)
		val = other.get_val();
	return *this;
}

const std::string& bigint::get_val() const {
	return val;
}

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
	return (os << obj.get_val());
}

bigint bigint::operator+(const bigint& other) const{
	std::string val_this = val;
	std::string val_other = other.get_val();
	std::string result;

	int end_this = val.size() - 1;
	int end_other = val_other.size() - 1;
	int carry = 0;

	while (carry || end_this >= 0 || end_other >= 0) {
		int sum = carry;
		if (end_this >= 0)
			sum += val_this[end_this--] - '0';
		if (end_other >= 0)
			sum += val_other[end_other--] - '0';
		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;
	}
	bigint temp;
	temp.val = result;
	return temp;
}

bigint& bigint::operator+=(const bigint& other) {
	*this = *this + other;
	return *this;
}

bigint& bigint::operator++() {
	*this = * this + bigint(1);
	return *this;
}

bigint bigint::operator++(int) {
	bigint temp(*this);
	++(*this);
	return temp;
}

//42 << 3 == 42000
bigint bigint::operator<<(unsigned int n) const {
	bigint result(*this);

	if (n == 0 || result.val == "0")
		return result;
	result.val.append(n, '0');
	return result;
}

bigint& bigint::operator<<=(unsigned int n) {
	*this = *this << n;
	return *this;
}

// 1337 >> 2 == 13
bigint bigint::operator>>(const bigint& other) const {
	size_t n = 0;
	size_t s = other.val.size();
	bigint result(*this);

	for (size_t i = 0; i < s; i++)
		n = n * 10 + (other.val[i] - '0');

	if (n >= result.val.size())
		result.val = "0";
	else
		result.val.erase(result.val.size() - n);
	return result;
}

bigint& bigint::operator>>=(const bigint& other) {
	*this = *this >> other;
	return *this;
}

bool bigint::operator<(const bigint& other) const {
	if (val.size() != other.val.size())
		return val.size() < other.val.size();
	return val < other.val;
}

bool bigint::operator>(const bigint& other) const {
	if (val.size() != other.val.size())
		return val.size() > other.val.size();
	return val > other.val;
}

bool bigint::operator<=(const bigint& other) const {
	return (*this < other || *this == other);
}

bool bigint::operator>=(const bigint& other) const {
	return (*this > other || *this == other);
}

bool bigint::operator==(const bigint& other) const {
	return (val == other.get_val());
}

bool bigint::operator!=(const bigint& other) const {
	return (val != other.get_val());
}