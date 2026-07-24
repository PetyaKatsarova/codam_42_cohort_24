#include "vect.hpp"

vect::vect() { _v[0] = 0; _v[1] = 0; }

vect::vect(int x, int y) { _v[0] = x; _v[1] = y; }

vect::vect(const vect& other) { *this = other; }

vect& vect::operator=(const vect& other) {
    if (this != &other) {
        _v[0] = other._v[0];
        _v[1] = other._v[1];
    }
    return *this;
}

vect::~vect() {}

// ---- members ----

vect& vect::operator+=(const vect& rhs) {
    _v[0] += rhs._v[0];
    _v[1] += rhs._v[1];
    return *this;
}

vect& vect::operator-=(const vect& rhs) {
    _v[0] -= rhs._v[0];
    _v[1] -= rhs._v[1];
    return *this;
}

vect& vect::operator*=(int scalar) {
    _v[0] *= scalar;
    _v[1] *= scalar;
    return *this;
}

vect& vect::operator++() {
    ++_v[0];
    ++_v[1];
    return *this;
}

vect vect::operator++(int) {
    vect old(*this);
    ++(*this);
    return old;
}

vect& vect::operator--() {
    --_v[0];
    --_v[1];
    return *this;
}

vect vect::operator--(int) {
    vect old(*this);
    --(*this);
    return old;
}

vect vect::operator-() const {
    return vect(-_v[0], -_v[1]);
}

int& vect::operator[](int i) {
    return _v[i];
}

const int& vect::operator[](int i) const {
    return _v[i];
}

// ---- non-members: built on members ----

// lhs by value = free working copy
vect operator+(vect lhs, const vect& rhs) {
    lhs += rhs;
    return lhs;
}

vect operator-(vect lhs, const vect& rhs) {
    lhs -= rhs;
    return lhs;
}

vect operator*(vect v, int scalar) {
    v *= scalar;
    return v;
}

vect operator*(int scalar, vect v) {
    v *= scalar;                       // 3 * v now works
    return v;
}

bool operator==(const vect& lhs, const vect& rhs) {
    return lhs[0] == rhs[0] && lhs[1] == rhs[1];   // via public [], no friend needed
}

bool operator!=(const vect& lhs, const vect& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const vect& v) {
    os << "(" << v[0] << ", " << v[1] << ")";
    return os;
}