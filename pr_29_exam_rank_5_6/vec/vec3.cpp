#include "vect.hpp"

vect::vect() : _v{0, 0} {}

vect::vect(int x, int y) : _v{x, y} {}

vect::vect(const vect& other) {
    _v[0] = other._v[0];
    _v[1] = other._v[1];
}

vect& vect::operator=(const vect& other) {
    if (this != &other) {
        _v[0] = other._v[0];
        _v[1] = other._v[1];
    }
    return *this;
}

vect::~vect() {}

int& vect::operator[](int idx) {
    return _v[idx];
}
    
const int& vect::operator[](int idx) const {
    return _v[idx];
}

std::ostream& operator<<(std::ostream& os, const vect& obj) {
    return os << "(" << obj[0] << ", " << obj[1] << ")";
}

vect& vect::operator+=(const vect& other) {
    _v[0] = _v[0] + other._v[0];
    _v[1] = _v[1] + other._v[1];
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

vect operator+(const vect& lhs, const vect& rhs) {
    vect temp(lhs);
    temp += rhs;
    return temp;
}