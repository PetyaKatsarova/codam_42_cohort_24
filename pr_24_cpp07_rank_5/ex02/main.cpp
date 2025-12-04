#include <iostream> // includes <ios>-> includes <exception>->includes <stdexception> on many libstdc++ implementations. compiler gets std::out_of_range indirectly.
#include <string>
// #include <stdexcept> //Relying on indirect includes is undefined by the standard and may break on another compiler.
#include "Array.hpp"

// int main() {
//     Array<std::string> arr1;
//     Array<float> arr2(5);
//     try {
//         std::cout << "0: " << arr2[4] << "\n";
//         std::cout << arr1[4] << "\n";
//     } catch (const std::exception& e) {
//         std::cerr << e.what() << "\n";
//     }
//     return 0;
// }

/**
Without srand():
rand();  // Always same sequence: 41, 18467, 6334, ...
rand();  // Same every run
With srand(time(NULL)):
rand();  // Different sequence each run (based on time)
rand();  // Actually "random"
*/

#define MAX_VAL 47 // if max val is > 42 will have core dump: out of bounds
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL)); // Returns current time in seconds since 1970. Seeds random number generator
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand(); //generates "random" numbers based on seed
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        // calls cpy constr 'cause: tmp is being declared and initialized at the same time.
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        } else {
            std::cout << "saved: " << mirror[i] << "\n";
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cout << "-- index = - 2 --";
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cout << "numbers[MAX_VAL] : 1 too big --";
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    std::cout << "numbers[42] = " << numbers[42] << "\n";
    delete [] mirror;//
    return 0;
}