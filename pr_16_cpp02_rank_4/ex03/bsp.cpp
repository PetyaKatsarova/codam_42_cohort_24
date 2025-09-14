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
    Fixed area = ((a.getX() * (b.getY() - c.getY()) + b.getX() * (c.getY() - a.getY()) + c.getX() * (a.getY() - b.getY())) / Fixed(2));
    if (area < 0)
        area = area * Fixed(-1);
    return area;
}

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
bool bsp( Point const a, Point const b, Point const c, Point const point) {
	// 3angle big: abc

	// 3angle 1: pbc

	// if none of 3==0 && 3aangle area 1+ 2+3=big return true
	return (false);
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

/**
 * 
 * #include "Point.h"

/*
BSP (Binary Space Partitioning) - Triangle Point Test
For 12-year-olds: "Is the dot inside the triangle?"

IMAGINE:
- You have a triangle made of 3 corners (like a slice of pizza)
- You have a dot somewhere on the paper
- Question: Is the dot inside the pizza slice or outside?

THE MATH TRICK:
1. A triangle has 3 sides (edges)
2. For each side, we ask: "Is the dot on the LEFT or RIGHT of this side?"
3. If the dot is on the SAME SIDE for all 3 edges, it's INSIDE!
4. If the dot is on DIFFERENT SIDES for any edge, it's OUTSIDE!

HOW WE CHECK "LEFT OR RIGHT":
- We use a magic math formula called "cross product"
- If the result is positive (+), the dot is on one side
- If the result is negative (-), the dot is on the other side  
- If the result is zero (0), the dot is exactly ON the line

EXAMPLE:
Triangle corners: A(0,0), B(3,0), C(1,3) - like a mountain
Test dot: P(1,1)
- Check side AB: Is P left or right of line AB? 
- Check side BC: Is P left or right of line BC?
- Check side CA: Is P left or right of line CA?
- If all answers are "same side" → P is INSIDE!
*/

// Helper function: Calculate which side of a line the point is on
// Returns positive if point is on one side, negative if on other side, zero if on the line
Fixed sign(Point p1, Point p2, Point p3) {
    // This is the "cross product" formula: (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)
    // It tells us the orientation of three points
    return (p1.getX() - p3.getX()) * (p2.getY() - p3.getY()) - (p2.getX() - p3.getX()) * (p1.getY() - p3.getY());
}

// Main BSP function: Check if point is inside triangle
bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed d1, d2, d3;
    bool has_neg, has_pos;
    
    // Check which side of each triangle edge our point is on
    d1 = sign(point, a, b);  // Side AB
    d2 = sign(point, b, c);  // Side BC  
    d3 = sign(point, c, a);  // Side CA
    
    // Check if we have both positive and negative results
    has_neg = (d1 < Fixed(0)) || (d2 < Fixed(0)) || (d3 < Fixed(0));
    has_pos = (d1 > Fixed(0)) || (d2 > Fixed(0)) || (d3 > Fixed(0));
    
    // If we have both positive AND negative, point is outside
    // If all are same sign (all positive OR all negative), point is inside
    // If any is exactly zero, point is on an edge (we return false per requirements)
    return !(has_neg && has_pos) && !(d1 == Fixed(0) || d2 == Fixed(0) || d3 == Fixed(0));
}
 */