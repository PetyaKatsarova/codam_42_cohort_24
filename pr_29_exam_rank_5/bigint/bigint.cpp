#include "bigint.hpp"
#include <sstream>
//c++ -Wall -Wextra -Wall main.cpp bigint.cpp && ./a.out

void	bigint::normalize() {
	std::size_t pos = 0;
	//err:2: was if,not while
	while (pos < _val.size() - 1 && _val[pos] == '0')
		pos++;
	_val = _val.substr(pos);
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
	std::string v1 = _val;
	std::string v2 = other.get_val();
	std::size_t len_v1 = v1.size();
	std::size_t len_v2 = v2.size();
	std::string result;
	int carry = 0;

	while (carry || len_v1 > 0 || len_v2 > 0) {
		std::size_t sum = carry;
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
	bigint temp(*this);
	std::size_t shift = other.to_size_t();

	if (other._val == "0" || _val == "0")
		return temp;

	temp._val.append(shift, '0');
	return temp;
}
	
bigint& bigint::operator<<=(const bigint& other) {
	*this = *this << other;
	return *this;
}

//bigint 	operator>>(const bigint& other) const {

//}
		
//1337 >> 2 == 13
bigint& bigint::operator>>=(const bigint& other) {
	std::size_t shift = other.to_size_t();
	if (_val == "0") return *this;

	if (_val.size() <= shift)
		_val = "0";
	else if (shift > 0){
		_val.erase(_val.size() - shift);
	}
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
