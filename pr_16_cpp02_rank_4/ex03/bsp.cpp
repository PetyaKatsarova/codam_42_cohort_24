#include "Point.h"

/*
The formula used in that function to calculate the area of a triangle given its three points (A, B, C) is:

Area = | (Ax × (By − Cy) + Bx × (Cy − Ay) + Cx × (Ay − By)) / 2 |

Where:

(Ax, Ay) are the coordinates of point A
(Bx, By) are the coordinates of point B
(Cx, Cy) are the coordinates of point C
The vertical bars |...| mean you take the absolute value (so the area is always positive).
This is called the "shoelace formula" for the area of a triangle!
*/
static Fixed area(const Point &a, const Point &b, const Point &c) {
    Fixed temp = ((a.getX() * (b.getY() - c.getY()) + b.getX() * (c.getY() - a.getY()) + c.getX() * (a.getY() - b.getY())) / Fixed(2));
    if (temp < 0)
        temp = temp * Fixed(-1);
    return temp;
}

/*
a, b, c: The vertices of our beloved triangle.
• point: The point to check.

Returns: True if the point is inside the triangle. False otherwise.
Thus, if the point is a vertex or on an edge, it will return False.

To check if a point is inside a triangle, you use the same area formula as before, but you do it four times:

Find the area of the big triangle (A, B, C).
Find the area of the triangle made by the point and two triangle corners (P, B, C).
Find the area of the triangle made by the point and the other two corners (A, P, C).
Find the area of the triangle made by the point and the last two corners (A, B, P).
If the sum of the three small areas is exactly the same as the big triangle’s area, and none of the small areas are zero, then the point is inside the triangle.

Formulas:

Let (Ax, Ay), (Bx, By), (Cx, Cy) be the triangle’s corners, and (Px, Py) be the point.

Area_ABC = | (Ax × (By − Cy) + Bx × (Cy − Ay) + Cx × (Ay − By)) / 2 |
Area_PBC = | (Px × (By − Cy) + Bx × (Cy − Py) + Cx × (Py − By)) / 2 |
Area_APC = | (Ax × (Py − Cy) + Px × (Cy − Ay) + Cx × (Ay − Py)) / 2 |
Area_ABP = | (Ax × (By − Py) + Bx × (Py − Ay) + Px × (Ay − By)) / 2 |
If:

Area_PBC > 0
Area_APC > 0
Area_ABP > 0
Area_PBC + Area_APC + Area_ABP == Area_ABC
then the point is inside the triangle!

For a 12-year-old:
It’s like cutting the big triangle into three smaller triangles using your point. If the three pieces fit perfectly back into the big triangle, and none of them are just a line (area zero), your point is inside!
*/
bool bsp( Point const a, Point const b, Point const c, Point const point) {

}

int main() {
    Point a(0, 0);
    Point b(5, 0);
    Point c(0, 5);

    // Inside the triangle
    Point p1(1, 1);
    std::cout << "p1 (1,1) inside: " << bsp(a, b, c, p1) << std::endl;

    Point p2(6, 6);
    std::cout << "p2 (6,6) outside: " << bsp(a, b, c, p2) << std::endl;


    Point p3(2.5, 0);
    std::cout << "p3 (2.5,0) on the edge, counted as outside: " << bsp(a, b, c, p3) << std::endl;

    Point p4(0, 0);
    std::cout << "p4 (0,0) On a vertex: counted outside: " << bsp(a, b, c, p4) << std::endl;

    // Very close to edge, but inside
    Point p5(0.01, 0.01);
    std::cout << "p5 (0.01,0.01) inside: " << bsp(a, b, c, p5) << std::endl;

    return 0;
}