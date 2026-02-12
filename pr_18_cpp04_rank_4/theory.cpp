#include <iostream>
using namespace std;

class Animal {
public:
    Animal() { cout << "Animal constructor\n"; }
    Animal(const Animal& other) { cout << "Animal copy constructor\n"; }
    virtual ~Animal() { cout << "Animal destructor\n"; }
    virtual void makeSound() { cout << "Generic animal sound\n"; }
    int age = 5;
};

class Dog : public Animal {
public:
    Dog() { cout << "Dog constructor\n"; }
    Dog(const Dog& other) : Animal(other) { cout << "Dog copy constructor\n"; }
    ~Dog() { cout << "Dog destructor\n"; }
    void makeSound() override { cout << "Woof! Woof!\n"; }
    void wagTail() { cout << "Tail wagging!\n"; }
};

void demonstrateValueSemantics() {
    cout << "\n=== VALUE SEMANTICS (no & or *) ===\n";
    
    Dog myDog;
    cout << "Created myDog\n";
    
    // COPYING - creates new objects
    Animal copyAnimal = myDog;  // Object slicing! Only Animal part copied
    cout << "Made copyAnimal from myDog\n";
    
    copyAnimal.makeSound();  // Always Animal sound, even if virtual
    // copyAnimal.wagTail();  // ERROR! Animal doesn't have wagTail()
    
    cout << "Addresses:\n";
    cout << "myDog:       " << &myDog << "\n";
    cout << "copyAnimal:  " << &copyAnimal << "\n";
    cout << "Different objects!\n";
}

void demonstrateReferences() {
    cout << "\n=== REFERENCES (using &) ===\n";
    
    Dog myDog;
    cout << "Created myDog\n";
    
    // ALIASING - same object, different name
    Animal& refAnimal = myDog;  // No copying! refAnimal IS myDog
    Dog& refDog = myDog;        // Also no copying
    
    cout << "Made references\n";
    
    refAnimal.makeSound();  // Calls Dog::makeSound() due to polymorphism
    refDog.makeSound();     // Also calls Dog::makeSound()
    refDog.wagTail();       // Works! refDog knows it's a Dog
    
    cout << "Addresses:\n";
    cout << "myDog:     " << &myDog << "\n";
    cout << "refAnimal: " << &refAnimal << "\n";
    cout << "refDog:    " << &refDog << "\n";
    cout << "Same object!\n";
    
    // Modify through reference
    refAnimal.age = 10;
    cout << "myDog.age = " << myDog.age << " (changed through reference)\n";
}

void demonstratePointers() {
    cout << "\n=== POINTERS (using *) ===\n";
    
    Dog myDog;
    cout << "Created myDog\n";
    
    // POINTING - storing address of object
    Animal* ptrAnimal = &myDog;  // Pointer to myDog (as Animal)
    Dog* ptrDog = &myDog;        // Pointer to myDog (as Dog)
    
    cout << "Made pointers\n";
    
    ptrAnimal->makeSound();  // Calls Dog::makeSound() due to polymorphism
    ptrDog->makeSound();     // Also calls Dog::makeSound()
    ptrDog->wagTail();       // Works! ptrDog knows it's a Dog
    
    cout << "Addresses:\n";
    cout << "myDog:      " << &myDog << "\n";
    cout << "ptrAnimal:  " << ptrAnimal << "\n";
    cout << "ptrDog:     " << ptrDog << "\n";
    cout << "Same address!\n";
    
    // Modify through pointer
    ptrAnimal->age = 15;
    cout << "myDog.age = " << myDog.age << " (changed through pointer)\n";
    
    // Pointer can be reassigned
    Dog anotherDog;
    ptrDog = &anotherDog;
    cout << "ptrDog now points to anotherDog\n";
}

void functionExamples() {
    cout << "\n=== FUNCTION PARAMETERS ===\n";
    
    // Function taking by VALUE (copy)
    auto byValue = [](Animal animal) {
        cout << "byValue: ";
        animal.makeSound();  // Always Animal sound (sliced)
        animal.age = 99;     // Only changes the copy
    };
    
    // Function taking by REFERENCE
    auto byReference = [](Animal& animal) {
        cout << "byReference: ";
        animal.makeSound();  // Polymorphic call
        animal.age = 99;     // Changes original
    };
    
    // Function taking by POINTER
    auto byPointer = [](Animal* animal) {
        cout << "byPointer: ";
        animal->makeSound(); // Polymorphic call
        animal->age = 99;    // Changes original
    };
    
    Dog testDog;
    cout << "Original age: " << testDog.age << "\n";
    
    byValue(testDog);
    cout << "After byValue: " << testDog.age << "\n";  // Unchanged
    
    byReference(testDog);
    cout << "After byReference: " << testDog.age << "\n";  // Changed
    
    testDog.age = 5;  // Reset
    byPointer(&testDog);
    cout << "After byPointer: " << testDog.age << "\n";  // Changed
}

void dynamicAllocation() {
    cout << "\n=== DYNAMIC ALLOCATION ===\n";
    
    // Stack allocation (automatic cleanup)
    {
        Dog stackDog;
        cout << "stackDog created on stack\n";
    }  // stackDog automatically destroyed here
    cout << "stackDog destroyed\n";
    
    // Heap allocation (manual cleanup required)
    Dog* heapDog = new Dog();  // Must use pointer for heap objects
    cout << "heapDog created on heap\n";
    heapDog->makeSound();
    delete heapDog;  // Manual cleanup
    cout << "heapDog manually destroyed\n";
}

int main() {
    cout << "C++ References, Pointers, and Values Tutorial\n";
    cout << "=============================================\n";
    
    demonstrateValueSemantics();
    demonstrateReferences();
    demonstratePointers();
    functionExamples();
    dynamicAllocation();
    
    cout << "\n=== SUMMARY ===\n";
    cout << "VALUE (no & or *): Creates copies, object slicing possible\n";
    cout << "REFERENCE (&):     Alias to existing object, no copying\n";
    cout << "POINTER (*):       Stores address, can be reassigned, allows NULL\n";
    
    return 0;
}