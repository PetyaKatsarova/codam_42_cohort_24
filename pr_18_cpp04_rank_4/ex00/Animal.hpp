#ifndef _ANIMAL_HPP
#define _ANIMAL_HPP

/*
<string> is the C++ standard library header for the std::string class.
<string.h> is the C header for C-style string functions (like strcpy, strlen), and does not provide std::string.

virtual example:
Animal* a = new Dog();
delete a;
If the destructor is not virtual, only Animal's destructor runs.
→ The Dog part is not cleaned up! This can cause memory leaks or bugs.
If the destructor is virtual, both Dog's and Animal's destructors run.
→ Everything is cleaned up properly!
*/
#include <string>

class Animal {
    protected:
        std::string type;

    public:
        Animal();
        Animal(const Animal& other);
        Animal& operator=(const Animal& other);
        virtual ~Animal();

        virtual void makeSound() const;
        std::string getType() const;
};

#endif