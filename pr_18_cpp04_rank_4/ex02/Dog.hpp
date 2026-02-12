#ifndef _DOG_HPP
#define _DOG_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

/*
Dog inherits all protected and public from Animal
*/
class Dog : public AAnimal {
    private:
        Brain* brain;

    public:
        Dog();
        Dog(const Dog& other);
        Dog& operator=(const Dog& other);
        ~Dog();

        void makeSound() const;
        Brain *getBrain() const;
};

#endif