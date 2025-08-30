
Shallow copy: Copies member values directly. If a member is a pointer, both objects point to the same memory. Changing the value via one object affects the other.
Deep copy: Allocates new memory for pointer members and copies the actual data. Changing the value in one object does NOT affect the other.
class Example {
    int* data;
public:
    Example(int val) : data(new int(val)) {}
    // Deep copy constructor
    Example(const Example& other) : data(new int(*other.data)) {}
    ~Example() { delete data; }
};

Example a(5);
Example b = a; // Deep copy: b.data is a separate copy
*b.data = 10;  // Changes only b, not a
======================================
In C++, the Orthodox Canonical Form requires every class to implement four special member functions:

1. Default Constructor
------------------------

Initializes an object with default values.
class Example {
public:
    Example() { /* initialize members */ }
};
Example e; // Calls default constructor

2. Copy Constructor
--------------------------

Creates a new object as a copy of an existing object.
class Example {
public:
    Example(const Example& other) { /* copy members from other */ }
};
Example e1;
Example e2 = e1; // Calls copy constructor

3. Copy Assignment Operator

Assigns the contents of one object to another existing object.
class Example {
public:
    Example& operator=(const Example& other) {
        if (this != &other) {
            // copy members from other
        }
        return *this;
    }
};
Example e1, e2;
e2 = e1; // Calls copy assignment operator
===============================
#include <iostream>
class Example {
    int* data;
public:
    Example() : data(new int(0)) { std::cout << "Default constructor\n"; }
    Example(const Example& other) : data(new int(*other.data)) { std::cout << "Copy constructor\n"; }
    Example& operator=(const Example& other) {
        std::cout << "Copy assignment operator\n";
        if (this != &other) *data = *other.data;
        return *this;
    }
    ~Example() { std::cout << "Destructor\n"; delete data; }
};

int main() {
    Example a;         // Default constructor
    Example b = a;     // Copy constructor
    Example c;         
    c = b;             // Copy assignment operator
    // Destructors called automatically at end of scope
}
-------------------------------
https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point.html

https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point_representation.html

In floating-point representation:

Exponent (e):
This part determines the scale or magnitude of the number. It tells you how many times to multiply or divide the mantissa by a power of two. It allows floating-point numbers to represent very large or very small values.

Mantissa (m) (also called significand):
This part holds the actual digits of the number (the significant bits). It represents the precision of the number.

Example:
For the number 1.23 × 10^4,

1.23 is the mantissa
4 is the exponent
In binary floating-point, the value is:
value = (−1)^s × mantissa × 2^(exponent)

So, exponent = "how big/small", mantissa = "the digits/precision".
--
float is 4 bytes
double is 8 bytes
===========================
The symbol ^ means "raised to the power of" (exponentiation).

For example, 2^3 means 2 raised to the power of 3, which is 2 × 2 × 2 = 8.
2^-1 means 1 divided by 2^1, which is 1/2 = 0.5.
10^-2 means 1 divided by 10^2, which is 1/100 = 0.01.
So, 2^x means "2 to the power of x".
==============================
 seeeeeeeemmmmmmmmmmmmmmmmmmmmmmm    meaning
31                              0    bit #

s = sign bit, e = exponent, m = mantissa
in general: number = (sign ? -1:1) * 2^(exponent) * 1.(mantissa bits)


Property	Value for float	Value for double
Largest representable number	3.402823466e+38	1.7976931348623157e+308
Smallest number without losing precision	1.175494351e-38	2.2250738585072014e-308
Smallest representable number(*)	1.401298464e-45	5e-324
Mantissa bits	23	52
Exponent bits	8	11
Epsilon(**)	1.1929093e-7	2.220446049250313e-16


For float:
Largest representable number: 3.402823466e+38
This means 3.402823466 × 10^38 (a huge number, 3.4 followed by 38 zeros).
Smallest number without losing precision: 1.175494351e−38
This means 1.175494351 × 10^−38 (a very tiny number, 0.000...1175 with 37 zeros after the decimal).
--------------------------------------
Normally, floating-point numbers use an "implied leading 1" in the mantissa, so the value looks like:
number = (sign) × 2^(exponent) × 1.(mantissa bits)

But, if the exponent bits are all zero, the "implied leading 1" disappears.
Instead, the number is:
number = (sign) × 2^(smallest exponent) × 0.(mantissa bits)

This lets you represent very tiny numbers, called "denormalized" or "subnormal" numbers.

The smallest possible value is when the exponent is at its lowest (for float, −126) and the mantissa is shifted all the way to the right (23 bits for float).
That’s why the smallest value is 2^(-126-23), which is much smaller than the normal minimum.
Summary:

Normal numbers: exponent ≠ 0, use "1.mantissa"
Subnormal numbers: exponent = 0, use "0.mantissa" (no leading 1), lets you get even smaller values
This trick helps avoid a sudden jump to zero and allows for gradual underflow.

The number 2^(-126-23) represents the smallest positive subnormal (denormalized) value that a float can store in IEEE 754 format.

−126 is the smallest exponent for a float.
23 is the number of mantissa bits for a float.
When the exponent bits are zero, and the mantissa has only the last bit set, the value is:

2^(-126-23) = 2^(-149) ≈ 1.401298464e-45
-------------------------
The "e-7" means "times 10 to the power of -7", which moves the decimal point 7 places to the left.
and if only -7 is to the power of 2
------------------------------




