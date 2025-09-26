#include "Point.hpp"
#include <cmath>

/**
 * Binary Space Partitioning: BSP tree
@params a, b, c: The vertices of the triangle.
@params point: The point to check.
@returns: True if the point is inside the triangle. False otherwise.
if the point is a vertex or on an edge, it will return False.
To check if a point is inside a triangle, you use the same area formula as before, but you do it four times:
Find the area of the big triangle (A, B, C).
Find the area of the triangle made by the point and two triangle corners (P, B, C).
Find the area of the triangle made by the point and the other two corners (A, P, C).
Find the area of the triangle made by the point and the last two corners (A, B, P).
If the sum of the three small areas is exactly the same as the big triangle’s area, and none of the small areas are zero, then the point is inside the triangle.

Formulas:

Let (Ax, Ay), (Bx, By), (Cx, Cy) be the triangle’s corners, and (Px, Py) be the point.
Area_PBC + Area_APC + Area_ABP == Area_ABC
then the point is inside the triangle!
*/

/*
The formula used in that function to calculate the area of a triangle given its three points (A, B, C) is:
Area = | (Ax × (By − Cy) + Bx × (Cy − Ay) + Cx × (Ay − By)) / 2 |
(Ax, Ay) are the coordinates of point A
(Bx, By) are the coordinates of point B
(Cx, Cy) are the coordinates of point C
The vertical bars |...| mean you take the absolute value (so the area is always positive).
This is called the "shoelace formula" for the area of a triangle!
*/
static Fixed area(const Point &a, const Point &b, const Point &c) {
    Fixed area = (a.getX() * (b.getY() - c.getY()) + b.getX() * (c.getY() - a.getY()) + c.getX() * (a.getY() - b.getY())) / Fixed(2); 
    if (area < 0)
        area = area * Fixed(-1);
    return area;
}

/**
 * 1 is true
 * 0 is false
 */
bool bsp(Point const a, Point const b, Point const c, Point const p) {
    Fixed total = area(a, b, c);
    Fixed area1 = area(a, p, c);
    Fixed area2 = area(a, b, p);
    Fixed area3 = area(p, b, c);
    return (total == (area1 + area2 + area3) && area1 != 0 && area2 != 0 && area3 != 0);
}

int main() {
	Fixed 	bla;
	int		num = 4.8; // on purpose: to int cuts the decimal point nums, doesnt round

	bla.setRawBits(num);
	std::cout<<"int: " << num << std::endl;
	std::cout<<"raw bits: " << bla << std::endl;
	std::cout<<"to int: " << bla.toInt() << std::endl;

    Point a(0, 0);
    Point b(5, 0);
    Point c(0, 5);

    Point p1(1, 1);
    bool res = bsp(a, b, c, p1);
    std::cout << "***p1 (1,1) true: " << res << std::endl;

    Point p2(6, 6);
    std::cout << "*** p2 (6,6) outside: " << bsp(a, b, c, p2) << std::endl;
    Point p3(2.5, 0);
    std::cout << "*** p3 (2.5,0) on the edge, counted as outside: " << bsp(a, b, c, p3) << std::endl;
    Point p4(0, 0);
    std::cout << "*** p4 (0,0) On a vertex: counted outside: " << bsp(a, b, c, p4) << std::endl;
    Point p5(0.1, 0.1);
    std::cout << "*** p5 (0.1,0.1) inside: " << bsp(a, b, c, p5) << std::endl;

    return 0;
}
