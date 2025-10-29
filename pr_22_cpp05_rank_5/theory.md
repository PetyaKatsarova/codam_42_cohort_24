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
HOWEVER±

You DON'T Need try/catch in the Constructor!
constructors can throw exceptions without needing try/catch blocks inside them.
BUT±
int main()
{
    try
    {
        Bureacrat b1("Alice", 0);    // Too high grade - will throw
        std::cout << b1 << std::endl;
    }
    catch (const Bureacrat::GradeTooHighException& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (const Bureacrat::GradeTooLowException& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
================================
noexcept marks a function as “does not throw exceptions”.
If a noexcept function throws, the program calls std::terminate().
Syntax:
unconditional: void f() noexcept;
conditional: void f() noexcept(expr); where expr is a compile-time boolean.
Modern replacement for deprecated throw() exception specification.
noexcept(true) ≡ noexcept
noexcept(false) ≡ no effect (function may throw)
noexcept(expr) is computed at compile time.
If a noexcept function allows an exception to escape, std::terminate() is invoked.
noexcept is part of a function’s type for overload resolution.

#include <iostream>
#include <exception>

void bad() noexcept {
    throw std::runtime_error("boom"); // program will call std::terminate()
}

int main() {
    try {
        bad(); // terminate, catch won't run
    } catch(...) {
        std::cout << "caught\n"; // never reached
    }
}

template<typename T>
void swap_local(T &a, T &b) noexcept(noexcept(T(std::move(a)))) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

struct S {
    S() = default;
    S(S&&) noexcept = default; // mark move ctor noexcept so containers will move S
    S& operator=(S&&) noexcept = default;
};
=================================
puts writes a C string to stdout and appends a newline.

Prototype: int puts(const char *s);
Header: #include <stdio.h>
Behavior: writes s then a '\n' to stdout (equivalent to fputs(s, stdout); putchar('\n');)
Return: non‑negative on success, EOF on error.
#include <stdio.h>

int main(void) {
    puts("hello"); // prints "hello\n"
    return 0;
}
================================
Yes. new T(...) allocates memory from the free store (heap) and constructs a T there.
You get a pointer. Example: T *p = new T(args);
Who frees it?
You must free heap memory yourself: delete p; — this calls T::~T() then frees memory.
For arrays: T *a = new T[n]; → delete[] a;

Stack (automatic) vs heap (dynamic)

Stack (automatic): lifetime tied to scope, destroyed automatically

{
    T obj(args); // ctor called
} // dtor called automatically when scope exits

Heap (dynamic): lives until you delete it.
T* p = new T(args); // ctor
delete p;           // dtor + free

Best practice — prefer RAII / smart pointers

Use std::unique_ptr and std::shared_ptr instead of raw new/delete

auto u = std::make_unique<T>(args);   // unique ownership
auto s = std::make_shared<T>(args);   // shared ownership

Smart pointer destructors call delete automatically when they go out of scope.
Why prefer smart pointers?
Avoid leaks on exceptions.
Clear ownership semantics.
Move semantics friendly (unique_ptr).
Common instantiation patterns
============================
automatic obj:
MyClass a(arg1, arg2);

dynamic + raw pointer:
MyClass* p = new MyClass(arg1);
delete p;

unique pointer recommended:
auto p = std::make_unique<MyClass>(arg1);

shared pointer:
auto p = std::make_shared<MyClass>(arg1);
===============================

Short answer — struct and class are the same except for defaults. Use struct for plain-data/aggregates, class for encapsulation.

Key differences

Member default access:
struct → members are public by default
class → members are private by default
Base-class default inheritance:
struct Derived : Base { } → public Base
class Derived : Base { } → private Base
Otherwise identical: both can have constructors, methods, static members, templates, inheritance, access specifiers, noexcept, override, etc.

In modern C++ (C++11+) the distinction is only stylistic/defaults.
Choose by intent: struct = data, class = abstraction.
================================

Short tutorial — what smart pointers are, when to use each, best practice + examples.

Concept

Smart pointers manage dynamic object lifetime automatically (RAII). They free memory when no longer used — avoid manual new/delete and leaks.
Types: std::unique_ptr (exclusive ownership), std::shared_ptr (shared ownership), std::weak_ptr (non-owning observer).
Best practice

Prefer std::unique_ptr by default. Use std::shared_ptr only when multiple owners required. Use std::weak_ptr to break cycles and to observe without owning.
Create with factory functions: std::make_unique, std::make_shared.
Don’t mix raw new/delete with smart pointers; avoid calling get() unless necessary.
Pass unique_ptr by value (transfer) or by reference-to-pointer; pass shared_ptr by value when you need to extend ownership, or const& if only reading.
Unique ownership (recommended):
#include <memory>

auto p = std::make_unique<MyClass>(arg); // allocate
p->doSomething();
auto p2 = std::move(p);                  // transfer ownership
if (!p) /* p is null */

Shared ownership:
#include <memory>
auto s1 = std::make_shared<MyClass>(arg);
{
    auto s2 = s1;            // shared ownership, use_count++ 
}                            // s2 destroyed, use_count--
std::cout << s1.use_count();
