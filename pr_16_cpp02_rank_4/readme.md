C++ - Module 02
Ad-hoc polymorphism, operator overloading
and the Orthodox Canonical class form
Summary: This document contains the exercises of Module 02 from the C++ modules.
Version: 8.2
Contents
I Introduction 2
II General rules 3
III New rules 6
IV Exercise 00: My First Class in Orthodox Canonical Form 7
V Exercise 01: Towards a more useful fixed-point number class 9
VI Exercise 02: Now we’re talking 11
VII Exercise 03: BSP 13
VIII Submission and Peer-Evaluation 15

C++ - Module 02
Ad-hoc polymorphism, operator overloading
and the Orthodox Canonical class form
• Note that unless explicitly stated otherwise, the using namespace <ns_name> and friend keywords are forbidden. Otherwise, your grade will be -42.

From now on, all your classes must be designed in the Orthodox Canonical Form,
unless explicitly stated otherwise. They will then implement the four required member
functions below:
• Default constructor
• Copy constructor
• Copy assignment operator
• Destructor
Split your class code into two files. The header file (.hpp/.h) contains the class
definition, whereas the source file (.cpp) contains the implementation.
6
Chapter IV
Exercise 00: My First Class in
Orthodox Canonical Form
Exercise : 00
My First Class in Orthodox Canonical Form
Turn-in directory : ex00/
Files to turn in : Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
Forbidden functions : None
You think you know integers and floating-point numbers. How cute.
Please read this 3 pages article (1, 2, 3) to discover that you don’t. Go on, read it.
Until today, every number you used in your code was basically either an integer or a
floating-point number, or any of their variants (short, char, long, double, and so forth).
After reading the article above, it’s safe to assume that integers and floating-point numbers have opposite characteristics.
But today, things will change. You are going to discover a new and awesome number
type: fixed-point numbers! Forever missing from the scalar types of most languages,
fixed-point numbers offer a valuable balance between performance, accuracy, range and
precision. That explains why fixed-point numbers are particularly applicable to computer
graphics, sound processing or scientific programming, just to name a few.
As C++ lacks fixed-point numbers, you’re going to add them. This article from
Berkeley is a good start. If you have no idea what Berkeley University is, read this
section of its Wikipedia page.
7
C++ - Module 02
Ad-hoc polymorphism, operator overloading
and the Orthodox Canonical class form
Create a class in Orthodox Canonical Form that represents a fixed-point number:
• Private members:
◦ An integer to store the fixed-point number value.
◦ A static constant integer to store the number of fractional bits. Its value
will always be the integer literal 8.
• Public members:
◦ A default constructor that initializes the fixed-point number value to 0.
◦ A copy constructor.
◦ A copy assignment operator overload.
◦ A destructor.
◦ A member function int getRawBits( void ) const;
that returns the raw value of the fixed-point value.
◦ A member function void setRawBits( int const raw );
that sets the raw value of the fixed-point number.
Running this code:
#include <iostream>
int main( void ) {
Fixed a;
Fixed b( a );
Fixed c;
c = b;
std::cout << a.getRawBits() << std::endl;
std::cout << b.getRawBits() << std::endl;
std::cout << c.getRawBits() << std::endl;
return 0;
}
Should output something similar to:
$> ./a.out
Default constructor called
Copy constructor called
Copy assignment operator called // <-- This line may be missing depending on your implementation
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
$>
8
Chapter V
Exercise 01: Towards a more useful
fixed-point number class
Exercise 01
Towards a more useful fixed-point number class
Turn-in directory : ex01/
Files to turn in : Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
Allowed functions : roundf (from <cmath>)
The previous exercise was a good start, but our class is pretty useless. It can only
represent the value 0.0.
Add the following public constructors and public member functions to your class:
• A constructor that takes a constant integer as a parameter.
It converts it to the corresponding fixed-point value. The fractional bits value
should be initialized to 8, like in exercise 00.
• A constructor that takes a constant floating-point number as a parameter.
It converts it to the corresponding fixed-point value. The fractional bits value
should be initialized to 8, like in exercise 00.
• A member function float toFloat( void ) const;
that converts the fixed-point value to a floating-point value.
• A member function int toInt( void ) const;
that converts the fixed-point value to an integer value.
And add the following function to the Fixed class files:
• An overload of the insertion («) operator that inserts a floating-point representation
of the fixed-point number into the output stream object passed as a parameter.
9
C++ - Module 02
Ad-hoc polymorphism, operator overloading
and the Orthodox Canonical class form
Running this code:
#include <iostream>
int main( void ) {
Fixed a;
Fixed const b( 10 );
Fixed const c( 42.42f );
Fixed const d( b );
a = Fixed( 1234.4321f );
std::cout << "a is " << a << std::endl;
std::cout << "b is " << b << std::endl;
std::cout << "c is " << c << std::endl;
std::cout << "d is " << d << std::endl;
std::cout << "a is " << a.toInt() << " as integer" << std::endl;
std::cout << "b is " << b.toInt() << " as integer" << std::endl;
std::cout << "c is " << c.toInt() << " as integer" << std::endl;
std::cout << "d is " << d.toInt() << " as integer" << std::endl;
return 0;
}
Should output something similar to:
$> ./a.out
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Copy assignment operator called
Destructor called
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
$>
10
Chapter VI
Exercise 02: Now we’re talking
Exercise 02
Now we’re talking
Turn-in directory : ex02/
Files to turn in : Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp
Allowed functions : roundf (from <cmath>)
Add public member functions to your class to overload the following operators:
• The 6 comparison operators: >, <, >=, <=, ==, and !=.
• The 4 arithmetic operators: +, -, *, and /.
• The 4 increment/decrement (pre-increment and post-increment, pre-decrement and
post-decrement) operators, which will increase or decrease the fixed-point value by
the smallest representable ϵ, such that 1 + ϵ > 1.
Add these four public overloaded member functions to your class:
• A static member function min that takes two references to fixed-point numbers as
parameters, and returns a reference to the smallest one.
• A static member function min that takes two references to constant fixed-point
numbers as parameters, and returns a reference to the smallest one.
• A static member function max that takes two references to fixed-point numbers as
parameters, and returns a reference to the greatest one.
• A static member function max that takes two references to constant fixed-point
numbers as parameters, and returns a reference to the greatest one.
11
C++ - Module 02
Ad-hoc polymorphism, operator overloading
and the Orthodox Canonical class form
It’s up to you to test every feature of your class. However, running the code below:
#include <iostream>
int main( void ) {
Fixed a;
Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
std::cout << a << std::endl;
std::cout << ++a << std::endl;
std::cout << a << std::endl;
std::cout << a++ << std::endl;
std::cout << a << std::endl;
std::cout << b << std::endl;
std::cout << Fixed::max( a, b ) << std::endl;
return 0;
}
Should output something like (for greater readability, the constructor/destructor messages are removed in the example below):
$> ./a.out
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
$>
If you ever do a division by 0, it is acceptable that the program
crashes
12
Chapter VII
Exercise 03: BSP
Exercise 03
BSP
Turn-in directory : ex03/
Files to turn in : Makefile, main.cpp, Fixed.{h, hpp}, Fixed.cpp,
Point.{h, hpp}, Point.cpp, bsp.cpp
Allowed functions : roundf (from <cmath>)
Now that you have a functional Fixed class, it would be nice to use it.
Implement a function that indicates whether a point is inside a triangle or not. Very
useful, isn’t it?
BSP stands for Binary Space Partitioning. You are welcome. :)
You can pass this module without completing exercise 03.
13
C++ - Module 02
Ad-hoc polymorphism, operator overloading
and the Orthodox Canonical class form
Let’s start by creating the Point class in Orthodox Canonical Form that represents
a 2D point:
• Private members:
◦ A Fixed const attribute x.
◦ A Fixed const attribute y.
◦ Anything else useful.
• Public members:
◦ A default constructor that initializes x and y to 0.
◦ A constructor that takes two constant floating-point numbers as parameters.
It initializes x and y with those parameters.
◦ A copy constructor.
◦ A copy assignment operator overload.
◦ A destructor.
◦ Anything else useful.
To conclude, implement the following function in the appropriate file:
bool bsp( Point const a, Point const b, Point const c, Point const point);
• a, b, c: The vertices of our beloved triangle.
• point: The point to check.
• Returns: True if the point is inside the triangle. False otherwise.
Thus, if the point is a vertex or on an edge, it will return False.
Implement and turn in your own tests to ensure that your class behaves as expected.
14
Chapter VIII
Submission and Peer-Evaluation
Turn in your assignment in your Git repository as usual. Only the work inside your
repository will be evaluated during the defense. Don’t hesitate to double-check the names
of your folders and files to ensure they are correct.
???????????? XXXXXXXXXX = $3$$d6f957a965f8361750a3ba6c97554e9f
15