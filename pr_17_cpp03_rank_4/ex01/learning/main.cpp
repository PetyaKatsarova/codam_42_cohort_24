#include <iostream>

class Animal {
public:
    void eat() {
        std::cout << "Eating\n";
    }
};

class Dog : public Animal {
public:
    void bark() {
        std::cout << "Barking\n";
    }
};


int main() {
    Dog d;

    d.eat();
    d.bark();
    return (0);
}