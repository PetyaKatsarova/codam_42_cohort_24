#ifndef WRONG_CAT_HPP
#define WRONG_CAT_HPP

#include "WrongAnimal.hpp"

/*
Cat inherits all protected and public from Animal
*/
class WrongCat : public WrongAnimal {
    public:
        WrongCat();
        WrongCat(const WrongCat& other);
        WrongCat& operator=(const WrongCat& other);
        ~WrongCat();

        void makeSound() const;
};

#endif