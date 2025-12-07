//to unzip file: tar -xzf cpp_09.tgz
/**
-x extract
-z gzip(decompress)
-f file (specify name)
tar -xzf cpp_09.tgz
*/
#include <iostream>

// Your program must take a file as an argument.
int main(int argc, char** argv) {
    if (argc != 2)
        std::cout << "Wakie wakie: please add an argument\n";
    std::cout << "tra la la\n";
    return 0;
}