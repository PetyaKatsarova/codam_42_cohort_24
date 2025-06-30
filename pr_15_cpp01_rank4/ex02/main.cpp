#include <iostream>

int main()
{

    std::string str = "HI THIS IS BRAIN";
    std::string *strPtr = &str;
    std::string &strRef = str;

    std::cout << "str mem address: " << &str << std::endl;
    std::cout << "strPtr mem address: " << strPtr << std::endl;
    std::cout << "strRef mem address: " << &strRef << std::endl;

    std::cout << "str val address: " << str << std::endl;
    std::cout << "strPtr val address: " << *strPtr << std::endl;
    std::cout << "strRef val address: " << strRef << std::endl;
    return (0);
}