#include <fstream>
#include <iostream> 
#include <stdexcept> // std::runtime_error
/**
What is std::ofstream?
output file stream — used for writing to files
Automatically creates the file if it doesn't exist
Overwrites the file if it already exists
*/

// std::string filename = "bla_bla";
// file.open(filename);
// or


//c++ -std=c++11 -Wall -Wextra -Werror tutorial_file.cpp && ./a.out
int main() {
    try {
        std::string fname = "bla_bla";
        std::ofstream file(fname);

        if (!file.is_open())
            throw std::runtime_error("Err, could not create file " + fname);
        // write to file
        file << "Hello world\n";
        file << "Shouting child.\n";
        std::cout << "File created successfully: " << fname << std::endl;
        // File closes automatically when going out of scope
    } catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}