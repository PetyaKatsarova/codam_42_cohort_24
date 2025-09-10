#ifndef _ANIMAL_HPP
#define _ANIMAL_HPP

#include <string>
/*
<string> is the C++ standard library header for the std::string class.
<string.h> is the C header for C-style string functions (like strcpy, strlen), and does not provide std::string.

Without virtual: the base function runs, even if the object is from a child class.
With virtual: the child's version runs, like you expect.
*/

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