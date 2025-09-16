#ifndef _AANIMAL_HPP
#define _AANIMAL_HPP

#include <string>
#include <iostream>

/**
    abstract class: make it simply by declaring at least one pure virtual function
    (assign val which means: This function must be implemented by derived classes.)
    virtual void makeSound() const = 0; Animal cannot be instantiated
*/

class AAnimal {
    protected:
        std::string type;

    public:
        AAnimal();
        AAnimal(const AAnimal& other);
        AAnimal& operator=(const AAnimal& other);
        virtual ~AAnimal();

        virtual void makeSound() const = 0;
        std::string getType() const;
};

#endif