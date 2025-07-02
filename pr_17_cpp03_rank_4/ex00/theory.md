If you don’t define all for canonical form:

The compiler creates default versions.
These do a shallow copy — just copy each member as-is.
That’s fine for std::string, int, etc.
Not fine if you allocate memory or manage resources manually.
-----------------------------------------------------------
Canonical form includes:

Function                    Purpose
-----------------------------------------------------------
Default constructor 	    Creates new empty/default object
Copy constructor	        Creates new object from another
Copy assignment operator	Copies data from one object to another existing object
Destructor	                Cleans up when object is destroyed

These manage your object’s lifecycle: creation → copying → assignment → destruction.

. Why Are They Important?
When a class holds:

Heap memory (new / malloc)

File handles

Network sockets

Pointers to resources
Then you must control how they’re copied, assigned, and cleaned. If not, you'll get:
Memory leaks
Double frees
Crashes

This is Rule of 3 (nowadays replaced by Rule of 5 for C++11 and beyond).
-----------------------------------------------
copy constructor:
class Person {
public:
    Person(const Person& other); // Copy constructor
};
cpp
Copy code
Person::Person(const Person& other) {
    std::cout << "Copied!" << std::endl;
    // copy fields like: this->name = other.name;
}

Person p2(p1);
Person p2 = p1;
Passed by value to a function: void greet(Person p);
Returned by value from function: Person create();
----------------------------------------------
Copy Assignment Operator
class Person {
public:
    Person& operator=(const Person& other);
};
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        std::cout << "Assigned!" << std::endl;
        // Copy fields: this->name = other.name;
    }
    return *this;
}

Person p1, p2; p2 = p1;
---------------------------------------------
Function	       When it's triggered
Constructor	       When you create a new object: ClapTrap a("bot");
Copy constructor   When you pass or return by value, or do: ClapTrap b = a;
Assignment	       When object already exists: b = a;
Destructor	       When object goes out of scope, or delete is called
------------------------------------------------
Common Mistakes to Avoid
Forgetting self-assignment check in operator=

Not using initializer list (especially for consts and refs)

Returning wrong type from assignment (void or ClapTrap instead of ClapTrap&)

Not freeing memory in destructor when using new
-----------------------------------------------
int main() {
    ClapTrap a("A");
    ClapTrap b = a;     // Copy constructor
    ClapTrap c("C");
    c = a;              // Copy assignment
    return 0;           // All destructors called
}