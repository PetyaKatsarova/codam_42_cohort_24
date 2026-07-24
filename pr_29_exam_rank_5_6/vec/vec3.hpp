#ifndef vect_HPP
#define vect_HPP

#include <ostream>

class vect {
private:
    int _v[2];
public:
    vect();
    vect(int x, int y);
    vect(const vect& other);
    vect& operator=(const vect& other);
    ~vect();
    
    int& operator[](int idx);
    const int& operator[](int idx) const;

    vect& operator+=(const vect& other);
    vect& operator++();
    vect operator++(int);

};

std::ostream& operator<<(std::ostream& os, const vect& obj);

vect operator+(const vect& lhs, const vect& rhs);

#endif