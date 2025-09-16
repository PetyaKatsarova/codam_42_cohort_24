#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>
#include <string>

int main() {
// const Animal* meta = new Animal();
// const Animal* j = new Dog();
// const Animal* i = new Cat();
// std::cout << j->getType() << " " << std::endl;
// std::cout << i->getType() << " " << std::endl;
// i->makeSound(); //will output the cat sound!
// j->makeSound();
// meta->makeSound();

// std::cout << "***** Wrong cat ******\n" << std::endl;
// const WrongAnimal* wa = new WrongAnimal();
// const WrongAnimal* wc = new WrongCat();
// std::cout << wa->getType() << " " << std::endl;
// std::cout << wc->getType() << " " << std::endl;
// wa->makeSound(); //will output the cat sound!
// wc->makeSound();

// std::cout << "**** EXTRA TESTS ****\n" << std::endl;
// std::cout << "=== Correct tests ===" << std::endl;
// const Animal* a = new Cat();
// a->makeSound();

// Cat c1;
// Animal* ac = &c1;
// ac->makeSound(); 

// Animal* zoo[2];
// zoo[0] = new Dog();
// zoo[1] = new Cat();
// for (int k = 0; k < 2; ++k)
//     zoo[k]->makeSound();

Dog d1;
Animal baseDog = d1; // object slicing: copies only the Animal part of dog1
baseDog.makeSound(); // always calls Animal

Animal& baseDog2 = d1;
baseDog2.makeSound(); // dog
return 0;
}