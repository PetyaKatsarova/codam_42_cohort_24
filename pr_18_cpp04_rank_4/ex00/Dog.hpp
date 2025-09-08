#ifndef _DOG_HPP
#define _DOG_HPP

#include "Animal.hpp"
#include <iostream>

/*
Dog inherits all protected and public from Animal
*/
class Dog : public Animal {
    public:
        Dog();
        Dog(const Dog& other);
        Dog& operator=(const Dog& other);
        ~Dog();

        void makeSound() const {
            std::cout << "Bau bau\n";
        }

        
};

#endif