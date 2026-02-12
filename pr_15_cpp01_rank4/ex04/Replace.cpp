#include "Replace.hpp"
#include <fstream>
#include <iostream>
#include <string>

Replace::Replace(const std::string &file, const std::string &s1, const std::string &s2) : filename(file), s1(s1), s2(s2){}

bool Replace::process() {
    if (s1.empty()) {
        std::cerr << "Err: s1 cant be emty." << std::endl;
        return (false);
    }

    //Open a file named bal.txt so we can read from it
    // ifstream: input file stream: read text files line-by-line or word-by-word.
    std::ifstream infile(filename);
    if (!infile) {
		std::cerr << "Error: cannot open file " << filename << "\n";
		return false;        
    }

    //std::endl → replaced with '\n' for performance (avoids flushing).
    std::ofstream outfile(filename + ".replace");
	if (!outfile) {
		std::cerr << "Error: cannot create output file.\n";
		return false;
	}

    std::string line;
    while (std::getline(infile, line)) {
        size_t pos = 0;
        while ((pos = line.find(s1, pos)) != std::string::npos) {
            line = line.substr(0, pos) + s2 + line.substr(pos + s1.length());
            pos += s2.length();
        }
        outfile << line << std::endl;
    }
    //infile.close() and outfile.close() → optional, handled automatically on destruction.
    return (true);
}