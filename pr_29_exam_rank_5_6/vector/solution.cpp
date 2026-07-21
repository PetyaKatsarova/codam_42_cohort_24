#include "solution.hpp"

vect2::vect2() : _v{0, 0} {}

vect2::vect2(int x, int y) : _v{x, y} {}

vect2::vect2(const vect2 &copy) {
	_v[0] = copy._v[0];
	_v[1] = copy._v[1];
}

vect2 &vect2::operator=(const vect2 &assign) {
	if (this != &assign)
	{
		_v[0] = assign._v[0];
		_v[1] = assign._v[1];
	}
	return *this;
}

vect2::~vect2() {}

//index operator
int &vect2::operator[](int indx) {
	return _v[indx];
}

const int &vect2::operator[](int indx) const {
	return _v[indx];
}

//compound assignment
vect2 &vect2::operator+=(const vect2 &other)
{
	_v[0] += other._v[0];
	_v[1] += other._v[1];
	return *this;
}

vect2 &vect2::operator-=(const vect2 &other) {
	_v[0] -= other._v[0];
	_v[1] -= other._v[1];
	return *this;
}

vect2 &vect2::operator*=(int scalar)
{
	_v[0] *= scalar;
	_v[1] *= scalar;
	return *this;
}

//incr/decr

vect2 &vect2::operator++() {
	++_v[0];
	++_v[1];
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 t(*this);
	++(*this);
	return t;
}

vect2 &vect2::operator--() {
	--_v[0];
	--_v[1];
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 t(*this);
	--(*this);
	return t;
}

//urnary minus

vect2 vect2::operator-() const {
	return vect2(-_v[0], -_v[1]);
}

//output

std::ostream &operator<<(std::ostream &out, const vect2 &v) {
	out << "{" << v[0] << ", " << v[1] << "}";
	return out;
}

//arithmetic

vect2 operator+(const vect2 &lhs, const vect2 &rhs) {
	vect2 res(lhs);
	res += rhs;
	return res;
}

vect2 operator-(const vect2 &lhs, const vect2 &rhs) {
	vect2 res(lhs);
	res -= rhs;
	return res;
}

vect2 operator*(const vect2 &v, int scalar) {
	vect2 res(v);
	res *= scalar;
	return res;
}

vect2 operator*(int scalar, const vect2 &v) {
	return v * scalar;
}

bool operator==(const vect2 &lhs, const vect2 &rhs) {
	return (lhs[0] == rhs[0] && lhs[1] == rhs[1]);
}

bool operator!=(const vect2 &lhs, const vect2 &rhs) {
	return !(lhs == rhs);
}