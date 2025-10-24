om cpp default is private, u have to declare public
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

// 2. throw() - PROMISES NO exception
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
main()
  ↓
try {
  ↓
  Bureacrat b("Alice", 0);
    ↓
    Constructor calls: if (grade < 1)
      ↓
      throw GradeTooHighException();  ← THROWS!
      ↓
      (Jump to catch!)
}
  ↓
catch (std::exception &e) {
  ↓
  e.what()  ← Calls what()
    ↓
    what() returns: "Grade is too high!"
    ↓
    (what() is safe, promises throw(), so no new exceptions)
}
===================================
