#include "bigint.hpp"

bigint::bigint() : num(0){}

bigint::bigint(const unsigned int& n) : num(n){}

bigint::bigint(const bigint& other) {
	this->num = other.get_num();
}

bigint& bigint::operator=(const bigint& other) {
	if (this != &other) {
		this->num = other.get_num();
	}
	return *this;
}

bigint::~bigint(){}

const unsigned int& bigint::get_num() const {
	return num;
}
		
unsigned int& bigint::get_num() {
	return num;
}

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
	return os << obj.get_num();
}

