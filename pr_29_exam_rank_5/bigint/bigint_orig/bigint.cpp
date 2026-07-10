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

const std::string& bigint::get_val() const { return val; }

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
	return (os << obj.get_val());
}

bigint bigint::operator+(const bigint& other) const {
	std::string v1 = val;
	std::string v2 = other.get_val();
	std::string result;

	unsigned int i = v1.size();
	unsigned int j = v2.size();
	unsigned int carry = 0;

	while (carry || i > 0 || j > 0) {
		unsigned int sum = carry;
		if (i > 0)
			sum += v1[--i] - '0';
		if (j > 0)
			sum += v2[--j] - '0';
		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;
	}
	bigint bla;
	bla.val = result;
	return bla;
}

bigint& bigint::operator+=(const bigint& other) {
	*this = *this + other;
	return *this;
}

bigint& bigint::operator++() {
	*this = *this + bigint(1);
	return *this;
}

bigint bigint::operator++(int) {
	bigint temp(*this);
	++(*this);
	return temp;
}

// 42 << 3 == 42000
bigint bigint::operator<<(unsigned int n) const {
	bigint res(*this);
	if (n > 0)
		res.val.append(n, '0');
	return res;
}

bigint& bigint::operator<<=(unsigned int n) {
	val.append(n, '0');
	return *this;
}

//337 >> 2
bigint& bigint::operator>>=(const bigint& other) {
	std::string other_val = other.get_val();
	unsigned int num = 0;
	for (int i = 0; i < other_val.size(); i++) {
		num = num * 10 + (other_val[i] - '0');
	}
	if (num >= val.size())
		val = "0";
	else
		val.erase(val.size() - num);
	return *this;
}

bool bigint::operator<(const bigint& other) const {
	if (val.size() != other.val.size()) {
		return val.size() < other.get_val().size();
	}
	return val < other.get_val();
}

bool bigint::operator>(const bigint& other) const {
	if (val.size() != other.val.size()) {
		return val.size() > other.get_val().size();
	}
	return val > other.get_val();
}

bool bigint::operator==(const bigint& other) const {
	return (val == other.get_val());
}

bool bigint::operator!=(const bigint& other) const {
	return (val != other.get_val());
}

bool bigint::operator >=(const bigint& other) const {
	return (*this > other || *this == other);
}

bool bigint::operator <=(const bigint& other) const {
	return (*this < other || *this == other);
}