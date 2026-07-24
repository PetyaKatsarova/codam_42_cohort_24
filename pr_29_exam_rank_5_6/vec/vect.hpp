#ifndef VECT_HPP
#define VECT_HPP

#include <iostream>

class vect {
private:
    int _v[2];

public:
    vect();
    vect(int x, int y);
    vect(const vect& other);
    vect& operator=(const vect& other);
    ~vect();

    // members: modify *this or required by language
    vect& operator+=(const vect& rhs);
    vect& operator-=(const vect& rhs);
    vect& operator*=(int scalar);

    vect& operator++();
    vect  operator++(int);
    vect& operator--();
    vect  operator--(int);

    vect operator-() const;              // unary minus stays member (single operand, *this)

    int&       operator[](int i);
    const int& operator[](int i) const;
};

// non-members: symmetric operators
vect operator+(vect lhs, const vect& rhs);
vect operator-(vect lhs, const vect& rhs);
vect operator*(vect v, int scalar);
vect operator*(int scalar, vect v);

bool operator==(const vect& lhs, const vect& rhs);
bool operator!=(const vect& lhs, const vect& rhs);

std::ostream& operator<<(std::ostream& os, const vect& v);

#endif