cpp default is private, u have to declare public
class Derived : public Base { };      // Public inheritance
class Derived : protected Base { };   // Protected inheritance
class Derived : private Base { };     // Private inheritance

class Derived : Base { };  // Default is PRIVATE inheritance!
========================
What is operator<<?
operator<< = Overloaded insertion operator

Allows you to print objects like:
Bureacrat alice("Alice", 50);
std::cout << alice << std::endl;  // ← Uses operator<<
std::ostream &operator<<(std::ostream &os, const Bureacrat &b);
    ↑          ↑              ↑            ↑
    |          |              |            |
   return    operator<<    left side   right side
   type      overload      (output)    (Bureacrat)
   std::ostream &operator<<(std::ostream &os, const Bureacrat &b)
{
	return os << b.getName() << ", bureacrat grade " << b.getGrade() << '.';
}

============================

What are exceptions?

Errors/issues detected during runtime
Stop normal execution, jump to handler
Alternative to returning error codes

#include <iostream>
#include <exception>

int main()
{
    try {
        int a = 10;
        int b = 0;
        if (b == 0)
            throw std::runtime_error("Division by zero!");
        std::cout << a / b << std::endl;
    }
    catch (std::runtime_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (...) {  // Catch any exception
        std::cout << "Unknown error" << std::endl;
    }
    return 0;
}
std::exception (abstract base)
    ├─ std::runtime_error
    ├─ std::logic_error
    ├─ std::bad_alloc
    └─ YOUR custom exceptions
        ├─ GradeTooHighException
        └─ GradeTooLowException

=======================================
Can You Just throw Without try-catch?
Technically YES, but it CRASHES your program!

// ❌ BAD - Just throw, no catch
int main()
{
    throw std::runtime_error("Something went wrong!");
    // Program crashes here!
    // Uncaught exception termination
    return (0);
}

terminate called after throwing an instance of 'std::runtime_error'
  what():  Something went wrong!
Aborted (core dumped)

int divide(int a, int b)
{
    if (b == 0)
        throw std::runtime_error("Division by zero!");
    return (a / b);
}

int main()
{
    try {
        int result = divide(10, 0);  // Throws exception
        std::cout << "Result: " << result << std::endl;
    }
    catch (std::runtime_error &e) {  // ← Catches exception!
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Program continues normally!
    std::cout << "Program finished" << std::endl;
    return (0);
}
==========================================

// 1. throw keyword - THROWS an exception
throw Bureacrat::GradeTooHighException();

// 2. throw() - PROMISES NO exception: depricated from c++98
virtual const char* what() const throw();


1. throw keyword - CREATES Exception
void Bureacrat::Bureacrat(const std::string name, int grade)
{
    if (grade < 1)
        throw Bureacrat::GradeTooHighException();  // ← THROWS exception
        // Stops execution, jumps to catch block
}

2. throw() Specification - PROMISES NO Exception
const char* what() const throw()
{
    return ("Grade is too high!");  // ← Returns normally, NO exception
}
============================
What is a Namespace?
Namespace = Container for names (classes, functions, variables)

Prevents naming conflicts when multiple libraries have same names.

==============================
// Without namespace - CONFLICT!
class Exception { };      // My exception
class Exception { };      // Someone else's exception
// ❌ ERROR! Two classes with same name!

// With namespace - NO CONFLICT!
namespace MyLib {
    class Exception { };
}

namespace OtherLib {
    class Exception { };
}

// Use them:
MyLib::Exception e1;      // ✅ My exception
OtherLib::Exception e2;   // ✅ Other's exception

using MyNamespace::MyClass;
using MyNamespace::myFunction;

MyClass obj;        // ✅ No need for MyNamespace::
myFunction();       // ✅ No need for MyNamespace::
---------------------------------
// std:: is a namespace!
std::string name;       // std::string from namespace std
std::cout << name;      // std::cout from namespace std
std::exception e;       // std::exception from namespace std

// Or with using:
using namespace std;
string name;            // ✅ No std:: needed
cout << name;           // ✅ No std:: needed
=======================================
friend = Grants access to private members
Breaks encapsulation when needed for specific functions/classes.

class BankAccount {
    private:
        double _balance;
    
    public:
        friend void printBalance(const BankAccount &account);
};

void printBalance(const BankAccount &account)
{
    std::cout << account._balance;  // ✅ Can access private _balance!
}

int main()
{
    BankAccount acc;
    printBalance(acc);  // ✅ Works
}
===========================================
class BankAccount {
    private:
        double _balance;
    
    public:
        friend class Auditor;  // ✅ Auditor can access private members
};

class Auditor {
    public:
        void inspect(const BankAccount &account) {
            std::cout << account._balance;  // ✅ Can access!
        }
};
===============================================
using namespace:
// Bureacrat.hpp
namespace Government {
    class Bureacrat {
        private:
            std::string _name;
            int _grade;
        
        public:
            Bureacrat(const std::string name, int grade);
            
            class GradeTooHighException : public std::exception {
                public:
                    virtual const char* what() const throw();
            };
    };
}
// Usage
Government::Bureacrat alice("Alice", 50);

class Bureacrat {
    private:
        std::string _name;
        int _grade;
    
    public:
        Bureacrat(const std::string name, int grade);
        
        // Grant access to insertion operator
        friend std::ostream &operator<<(std::ostream &os, const Bureacrat &b);
};

std::ostream &operator<<(std::ostream &os, const Bureacrat &b)
{
    os << b._name << ", bureaucrat grade " << b._grade << ".";
    return (os);  // ✅ Can access private members!
}
===============================================
#include <string>       // ✅ Declares std::string
using namespace std;    // ✅ Creates shortcut

int main()
{
    string name = "Alice";  // ✅ Works! (shortcut)
    cout << name << endl;   // ✅ Works! (shortcuts)
    return (0);
}
===========================================
#include <string>      // ← Need this for std::string
#include <iostream>    // ← Need this for std::cout, std::ostream
#include <exception>   // ← Need this for std::exception
=======================================
// file1.h
class MyClass { };

// file2.h
#include "file1.h"  // ← Includes MyClass

// main.cpp
#include "file1.h"  // ← Includes MyClass AGAIN
#include "file2.h"  // ← file2.h includes file1.h AGAIN!
==========================================
sobj address: tatic_cast<const void*>(&b)
This is the address of the Bureacrat object (b) itself.
It points to the start of the object in memory (on the stack if local variable).
Each object (becky, cpy, etc.) gets its own memory location.

name_addr: static_cast<const void*>(b.getNamePtr())

This is the address of the _name member inside the Bureacrat object.
_name is a const std::string member.
When you copy-construct, a new std::string is created for the copy, so its address is different from the original.
Each object's _name lives inside its own object, so the address is different for each instance.

buf_addr: static_cast<const void*>(b.getNamePtr()->c_str())
This is the address of the internal character buffer managed by the std::string object.
When you copy a std::string, a new buffer is allocated for the copy (deep copy).
So, even if the string contents are the same, the buffer addresses are different for each object.


