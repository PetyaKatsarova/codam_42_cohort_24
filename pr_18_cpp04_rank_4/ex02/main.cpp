#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"
#include <iostream>
#include <string>

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Animal

int main() {
    const int size = 4;
    AAnimal* animals[size];

    for (int i = 0; i < size/2; ++i)
        animals[i] = new Dog();
    for (int i = size/2; i < size; ++i)
        animals[i] = new Cat();

    std::cout << "\n--- Sounds ---\n";
    for (int i = 0; i < size; ++i)
        animals[i]->makeSound();

    std::cout << "\n--- Cleanup ---\n";
    for (int i = 0; i < size; ++i)
        delete animals[i];

    return 0;
}
