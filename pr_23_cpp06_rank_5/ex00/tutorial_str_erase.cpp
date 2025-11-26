#include <string>
#include <iostream>

/**
!NB! str.erase() and what it returns: are not equal: they are teh same object! but have diff address
*/
int main() {
    std::string bla = "blaBla";
    std::string erased = bla.erase(0, 2);

    std::cout << "bla[" << bla << "]\n";
    std::cout << "era[" << erased << "]\n";
    std::cout << "&bla[" << &bla << "]\n";
    std::cout << "&era[" << &erased << "]\n";

    erased += "XXX";
    std::cout << "modify erased to verify they r separtate\n";
    std::cout << "bla[" << bla << "]\n";
    std::cout << "era[" << erased << "]\n";
    return 0;
}