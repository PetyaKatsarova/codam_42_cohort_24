https://www.geeksforgeeks.org/cpp-tutorial

--------------------------------------------------------------
• By Odin, by Thor! Use your brain!!!
=============================================================
A class in Orthodox Canonical Form defines all of these:

Default constructor

Copy constructor

Copy assignment operator

Destructor

Move constructor (C++11+)

Move assignment operator (C++11+)

Example:

cpp
Copy
Edit
class Example {
public:
    Example();                          // Default constructor
    Example(const Example&);            // Copy constructor
    Example& operator=(const Example&); // Copy assignment
    ~Example();                         // Destructor
    Example(Example&&);                 // Move constructor
    Example& operator=(Example&&);      // Move assignment
};
================================================================
**TODO**
You will have to implement a lot of classes. This can seem tedious,
unless you’re able to script your favorite text editor.
================================================================