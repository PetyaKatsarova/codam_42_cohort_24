#include "bigint.hpp"
#include <sstream>

//c++ -Wall -Wextra -Wall main.cpp bigint.cpp && ./a.out

void bigint::normalize() {
	size_t i = 0;
	while (_val.size() - 1 > i && _val[i] == '0')
		i++;
	_val.erase(i);
}

int	bigint::compare(const bigint& other) const {
	if (_val.size() > other.get_val().size())
		return 1;
	if (_val.size() < other.get_val().size())
		return -1;
	if (_val > other.get_val())
		return 1;
	if (_val < other.get_val())
		return -1; // was 1 err:1
	return 0;
}

std::size_t bigint::to_size_t() const {
	std::size_t n = 0;
	for (std::size_t i = 0; i < _val.size(); i++)
		n = n * 10 + (_val[i] - '0');
	return n;
}

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
	return os << obj.get_val();
}

bigint operator+(const bigint& lhs, const bigint& rhs) {
	bigint r(lhs);
	r += rhs;
	return r;
}

// ----------- END HELPERS ----------------------

bigint::bigint() : _val("0"){}

bigint::bigint(unsigned int n) {
	std::stringstream ss;
	ss << n;
	_val = ss.str();
}

bigint::bigint(const bigint& other) : _val(other.get_val()) {}

bigint& bigint::operator=(const bigint& other) {
	if (this != &other)
		_val = other._val;
	return *this;
}

bigint::~bigint() {}

std::string bigint::get_val() const {
	return _val;
}

bigint& bigint::operator+=(const bigint& other) {
	std::string result;
	std::string v1 = _val;
	std::string v2 = other.get_val();
	int carry = 0;
	unsigned int len_v1 = v1.size();
	unsigned int len_v2 = v2.size();

	while (carry > 0 || len_v1 > 0 || len_v2 > 0) {
		int sum = carry;
		if (len_v1 > 0)
			sum += v1[--len_v1] - '0';
		if (len_v2 > 0)
			sum += v2[--len_v2] - '0';
		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;
	}
	_val = result;
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

//42 << 3 == 42000 todo: had to be param: size_t or unsigned int??
bigint 	bigint::operator<<(const bigint& other) const {
	unsigned int shift = 0;
	bigint res(*this);
	for (unsigned int i = 0; i < other._val.size(); i++)
		shift = shift * 10 + (other._val[i] - '0');
	if (res._val == "0" || shift == 0)
		return res;
	res._val.append(shift, '0');
	return res;
}
	
bigint& bigint::operator<<=(const bigint& other) {
	*this = *this << other;
	return *this;
}

//1337 >> 2 == 13; 12345 >> 2 ; erase(5 - 2=3 from i 3)
bigint 	bigint::operator>>(const bigint& other) const {
	bigint res(*this);
	unsigned int shift = 0;
	unsigned int othersize = other._val.size();
	unsigned int valsize = res._val.size();

	if ((other._val) == "0" || res._val == "0")
		return res;
	for (unsigned int i = 0; i < othersize; i++)
		shift = shift * 10 + (other._val[i] - '0');
	if (shift > valsize)
		res._val = "0";
	else
		res._val.erase(valsize - shift);
	return res;
}
		
//1337 >> 2 == 13
bigint& bigint::operator>>=(const bigint& other) {
	*this = *this >> other;
	return *this;
}

bool	bigint::operator>(const bigint& other) const {
	return compare(other) > 0;
}

bool	bigint::operator<(const bigint& other) const {
	return compare(other) < 0;
}

bool	bigint::operator>=(const bigint& other) const {
	return compare(other) >= 0;
}

bool	bigint::operator<=(const bigint& other) const {
	return compare(other) <= 0;
}

bool	bigint::operator==(const bigint& other) const {
	return compare(other) == 0;
}

bool	bigint::operator!=(const bigint& other) const {
	return compare(other) != 0;
}
