#ifndef _Cat_HPP
#define _Cat_HPP

#include "Animal.hpp"

/*
Cat inherits all protected and public from Animal
*/
class Cat : public Animal {
    public:
        Cat();
        Cat(const Cat& other);
        Cat& operator=(const Cat& other);
        ~Cat();

        void makeSound() const;
};

#endif