#include <iostream>
#include "Array.hpp"

/*
*/
#define MAX_VAL 15
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
		std::cerr << "numbers[-2] " << std::endl;
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 42; // out of bound
    }
    catch(const std::exception& e)
    {
		std::cerr << "numbers[MAX_VAL]=42" << std::endl;
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
	for (int i = 0; i < numbers.size(); i++) {
		std::cout << numbers[i] << ", ";
	}
	std::cout << std::endl;
    delete [] mirror;//
    return 0;
}