#include "vect.hpp"

/*
Binary minus (subtraction) takes two operands, one on each side:
vect operator-(const vect& lhs, const vect& rhs);  // a - b
a - b → "lhs minus rhs".
-----
Unary minus (negation) takes one operand, on its right:
vect operator-() const;  // -a
This is -a → "give me the negated version of a". For our vector that'd be (-x, -y).
So the distinction is purely operand count:

cpp
vect a(3, 4), b(1, 1);
vect c = a - b; binary-> calls operator-(const vect&, const vect&)-> (2, 3)
vect d = -a;    unary -> calls operator-() const                  -> (-3, -4)

!!!NB!!! omg:
operator*(int, const vect&)   // matches:  int * vect   →  2 * v
operator*(const vect&, int)   // matches:  vect * int   →  v * 2

The first parameter = left operand, second = right operand. C++ picks the overload by matching operand types in order. v * 2 is (vect, int), so it needs (const vect&, int). Your existing one is (int, const vect&) — reversed, doesn't match.

Same param types, swapped positions → two different functions. You need both.
*/

vect::vect() : vec{0, 0} {}

vect::vect(int x, int y) : vec{x, y} {}

vect::vect(const vect& other) {
	vec[0] = other.vec[0];
	vec[1] = other.vec[1];
}

vect& vect::operator=(const vect& other) {
	if (this != &other) {
		vec[0] = other.vec[0];
		vec[1] = other.vec[1];
	}
	return *this;
}

vect::~vect() {}

// ------------- free funcs ------------------
std::ostream& operator<<(std::ostream& os, const vect& obj) {
	return os << "(" << obj[0] << ", " << obj[1] << ")";
}

vect operator+(const vect& lhs, const vect& rhs) {
	vect temp(lhs);
	temp += rhs;
	return temp;
}

vect operator-(const vect& lhs, const vect& rhs) {
	vect temp(lhs);
	temp -= rhs;
	return temp;
}

// NB!! outside class so can do int + obj and obj + int
vect operator*(int num, const vect& other) {
	vect temp(other);
	temp *= num;
	return temp;
}

vect operator*(const vect& other, int num) {
	vect temp(other);
	temp *= num;
	return temp;
}

//------------------------ end of free funcs ---------------------

int& vect::operator[](int i) {
	return vec[i];
}

const int& vect::operator[](int i) const {
		return vec[i];
}

vect& vect::operator+=(const vect& other) {
	vec[0] += other.vec[0];
	vec[1] += other.vec[1];
	return *this;
}

vect& vect::operator++() {
	*this += vect(1, 1);
	return *this;
}

vect vect::operator++(int) {
	vect temp(*this);
	++(*this);
	return temp;
}

vect& vect::operator-=(const vect& other) {
	vec[0] -= other.vec[0];
	vec[1] -= other.vec[1];
	return *this;
}

vect& vect::operator--() {
	*this -= vect(1, 1);
	return *this;
}

vect vect::operator--(int) {
	vect temp(*this);
	--(*this);
	return temp;
}

vect& vect::operator*=(int num) {
	vec[0] *= num;
	vec[1] *= num;
	return *this;
}

vect& vect::operator-() {
	vec[0] = -vec[0];
	vec[1] = -vec[1];
	return *this;
}

bool vect::operator==(const vect& other) const {
	return (vec[0] == other.vec[0] && vec[1] == other.vec[1]);
}
	
bool vect::operator!=(const vect& other) const {
	return (vec[0] != other.vec[0] || vec[1] != other.vec[1]);
}
