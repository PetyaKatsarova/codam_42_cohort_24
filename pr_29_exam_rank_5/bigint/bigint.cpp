#include "bigint.hpp"
#include <sstream>

bigint::bigint() : val("0"){}

//std::stringstream is a stream that reads from and writes to a string in memory instead of a file or the console.
//stream insertion operator (operator<<).
//str() = "Give me the entire contents of your internal string."
bigint::bigint(unsigned int n) {
	std::stringstream ss;
	ss << n;
	val = ss.str();
}

bigint::bigint(const bigint& other) {
	val = other.val;
}

bigint::~bigint(){}

bigint&  bigint::operator=(const bigint& other) {
	if (this != &other) {
		this->val = other.val;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
	//bigint tmp(obj);
	//tmp.rmvLeading0s();
	return os << obj.val;
}

//void bigint::rmvLeading0s() {
//	while(val.size() > 1 && val[0] == '0')
//		val.erase(0, 1); // rmv 1 char, at index 0
//}

bigint bigint::operator+(const bigint& other) const {
	std::string a = val;
	std::string b = other.val;
	std::string result;

	int i = a.size() - 1;
	int j = b.size() - 1;
	int carry = 0;

	while (carry || i >= 0 || j >= 0) {
		int sum = carry;
		if (i >= 0)
			sum += a[i--] - '0';
		if ( j >= 0)
			sum += b[j--] - '0';
		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;
	}
	bigint bla;
	bla.val = result;
	return bla;
}
		
//bigint bigint::operator+(unsigned int n) const {
//	return (*this + bigint(n));
//}

bigint& bigint::operator+=(const bigint& other) {
	*this = *this + other;
	return *this;
}

// val++: return same obj incremented by 1 == ++val
bigint& bigint::operator++() {
	*this += bigint(1);
	return *this;
}

// == val++ return old val object but ++this obj
bigint  bigint::operator++(int) {
	bigint tmp(*this);
	++(*this);
	return tmp;
}