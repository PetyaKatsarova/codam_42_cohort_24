#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>
#include <string>

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Animal

int main() {
    const int size = 10;
    Animal *animals[size];

    for (int i = 0; i < size/2; ++i)
        animals[i] = new Dog();
    for (int i = size/2; i < size; ++i)
        animals[i] = new Cat();
    for (int i = 0; i < size; ++i)
        animals[i]->makeSound();
    for (int i = 0; i < size; ++i)
        delete animals[i];
    std::cout << "\n--- Deep copy test ---\n";
    Dog dog1;
    dog1.getBrain()->setIdea(0, "Chase the cat!");
    std::cout << "dog1.getBrain()->getIdea(0)" << dog1.getBrain()->getIdea(0) << std::endl;
    Dog dog2 = dog1; // calls copy constructor
    dog2.getBrain()->setIdea(0, "Eat the bone!");
    std::cout << "dog2.getBrain()->getIdea(0)" << dog2.getBrain()->getIdea(0) << std::endl;
    std::cout << "dog1.getBrain()->getIdea(0)" << dog1.getBrain()->getIdea(0) << std::endl;
    return 0;
}