https://www.youtube.com/watch?v=0NwsayeOsd4

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

std stands for standard namespace in C++.
It contains all standard library functions, types, and objects (like cout, cin, string, etc).

If you write std::cout:
You access cout specifically from the std (standard) namespace.

This is the recommended, explicit way.

Example:

cpp
Copy
std::cout << "Hello";
If you write using namespace std;:
You no longer need to prefix with std::.

This can make code shorter but risks name clashes in bigger projects.

Example:

cpp
Copy
using namespace std;
cout << "Hello"; // std:: prefix not needed
-------------------------------------------------------------------

C++
Person p;
Creates the object directly on the stack.
Memory is automatically managed.
No need to manually delete.

Person* p = new Person();
Creates the object on the heap.
Returns a pointer.
You must call delete p; when done to avoid memory leaks.

Java
Person p = new Person();
Always allocates on the heap.
You always use pointers (references) in Java.
Garbage collector manages memory.
-------------------------------------------------------------------