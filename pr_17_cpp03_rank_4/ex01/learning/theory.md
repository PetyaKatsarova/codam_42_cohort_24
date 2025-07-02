class ChildClass : public ParentClass
public: Inherits all public and protected members.

private: All inherited members become private (less useful).

protected: Rarely used.

Always use public for most inheritance cases,

Constructors, destructors, assignment operators are not inherited automatically, but:

You can call them from the derived class.

Since C++11, you can use using Base::Base; to inherit constructors
-----------------------------------------------------------
When you create a derived object, base constructor runs first, then derived
class Base {
public:
    Base() { std::cout << "Base\n"; }
};

class Child : public Base {
public:
    Child() { std::cout << "Child\n"; }
};

Child c;
=============================================================
Child can redefine base methods:

class Animal {
public:
    void makeSound() { std::cout << "Generic sound\n"; }
};

class Dog : public Animal {
public:
    void makeSound() { std::cout << "Bark\n"; }
};
But if you want runtime polymorphism (choosing the method at runtime), use virtual:

class Animal {
public:
    virtual void makeSound() { std::cout << "Generic sound\n"; }
};
Then:

Animal* a = new Dog();
a->makeSound(); // Bark, if virtual
====================================================
