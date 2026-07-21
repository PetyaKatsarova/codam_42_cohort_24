#ifndef VECT_HPP
#define VECT_HPP

#include <ostream>

class vect {
private:
	int vec[2];

public:
	vect();
	vect(int x, int y);
	vect(const vect& other);
	vect& operator=(const vect& other);
	~vect();

	const int& operator[](int idx) const;
	int& operator[](int idx);

	// binary operators(operations)
	vect& operator+=(const vect& other);
	vect& operator++();
	vect operator++(int);
	vect& operator--();
	vect operator--(int);
	vect& operator-=(const vect& other);
	vect& operator*=(int num);

	// urinary operator(like - is num = - num)
	vect& operator-();
	
	bool operator==(const vect& other) const;
	bool operator!=(const vect& other) const;
};

std::ostream& operator<<(std::ostream& os, const vect& obj);

vect operator+(const vect& lhs, const vect& rhs);
vect operator-(const vect& lhs, const vect& rhs);
vect operator*(int num, const vect& other);
vect operator*(const vect& other, int num);

#endif