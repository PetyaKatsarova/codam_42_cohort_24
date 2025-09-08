# include "Point.h"

Point::Point() : x(0), y(0) {
    std::cout << "Point default constructor called" << std::endl;    
}

/*
x(x) calls the Fixed(float) constr
*/
Point::Point(const float x, const float y) : x(x), y(y) {
    std::cout << "Point float constructor called" << std::endl;
}

Point::Point(const Point &other) : x(other.x), y(other.y) {
    std::cout << "Point copy constructor called" << std::endl;
}

Point &Point::operator=(const Point &other) {
    std::cout << "Point copy assignment operator called" << std::endl;
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Point::~Point() {
    std::cout << "Point destr. called" << std::endl;
}

Fixed Point::getX() const { return x; }

Fixed Point::getY() const { return y; }
