#ifndef _Cat_HPP
#define _Cat_HPP

#include "Animal.hpp"
#include "Brain.hpp"

/*
Cat inherits all protected and public from Animal
*/
class Cat : public Animal {
    private:
        Brain* brain;

    public:
        Cat();
        Cat(const Cat& other);
        Cat& operator=(const Cat& other);
        ~Cat();

        void makeSound() const;
        Brain* getBrain() const;
};

#endif