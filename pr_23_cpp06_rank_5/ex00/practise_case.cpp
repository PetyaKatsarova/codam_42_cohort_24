#include <cmath>
#include <iostream>

/**
use reinterpret_cast<long>(&val) for ptr to int
low-level memory manipulation
hardware/sys programming
*/
int main() {
    int val = 42;
    long addr = reinterpret_cast<long>(&val);

    std::cout << "long addr: " << addr << std::endl;
    // convert long to hex
    std::cout << "address 0x: " << std::hex << addr << std::endl;

    float f = 342.0f;
    int *intPtr = reinterpret_cast<int*>(&f);
    std::cout << "dangerous-alignment issues(intPtr shows bit representation of float): " << *intPtr << std::endl;
    std::cout << "intPtr addr: " << intPtr << "\n";
    return 0;
}