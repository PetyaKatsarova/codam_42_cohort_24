/**
 Vector manages heap memory automatically
 std::vector<int>::iterator it = vec.begin();
 vec.end() - Does NOT Point to \0
end() is PAST the Last Element - invalid position
----------------------------------
when key doesnt exist:
std::map<std::string, int> ages;

ages["Beky"] = 25;
ages["Oscar"] = 30;
ages.insert(std::make_pair("Mutsi", 42));

// Map state:
// { "Beky": 25, "Mutsi": 42, "Oscar": 30 }

std::cout << ages["aBeky"];  // ← Access non-existent key
//                 ^^^^^^^^
//                 Map automatically creates:
//                 ages["aBeky"] = 0 (default int value)

// Map state after:
// { "Beky": 25, "Mutsi": 42, "Oscar": 30, "aBeky": 0 }
mapped_type& operator[](const key_type& key); whats mapped_type?

// Bad - creates entry if doesn't exist
if (ages["aBeky"] == 0) {
    std::cout << "Not found\n";
}

// Good - doesn't create entry
if (ages.find("aBeky") != ages.end()) {
    std::cout << "aBeky's age: " << ages["aBeky"] << std::endl;
} else {
    std::cout << "aBeky not found\n";
}
    int a, b, c;
file >> a >> b >> c;
//   ^^   ^^   ^^
//   Reads three integers in sequence

// File: "10 20 30"
// Result: a=10, b=20, c=30
------------------------------
std::stringstream: A stream that operates on strings (instead of files or console).
convert str to num and v versa
- - -  - - -  - - - 
std::string str = "123";
int num;

std::stringstream ss(str);
ss >> num;

std::cout << num;  // Output: 123 (as integer)

int num = 456;
std::stringstream ss;

ss << num;  // Insert number into stream
std::string str = ss.str();  // Extract as string

std::cout << str;  // Output: "456" (as string)

std::string data = "2024 12 10";
int year, month, day;

std::stringstream ss(data);
ss >> year >> month >> day;

std::cout << year << "-" << month << "-" << day;
// Output: 2024-12-10
*/

#include <iostream>
#include <fstream>
#include <sstream> // file.rdbuf();
#include <string>
// !!NB!! insert key next to delete!!

void readLineByLine(std::ifstream& file) {
    // read line by line
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

void readWordByWord(std::ifstream& file) {
    std::string word;
    // >> extraction operator
    // 1. Skip leading whitespace (spaces, tabs, newlines)
    // 2. Read characters until whitespace
    // 3. Store in 'word'
    // 4. Stop at whitespace
    while (file >> word) {
        std::cout << word << std::endl;
    }
}

void readCharByChar(std::ifstream& file) {
    char c;
    while (file.get(c))
        std::cout << c;
}

std::string readEntireFile(std::ifstream& file) {
    std::stringstream buffer;
    buffer << file.rdbuf(); // efficient: read entire file in 1 operation
    return buffer.str();

}

// valgrind --leak-check=full ./a.out main.cpp
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Hey, u need to input file name.\n";
    }
    std::ifstream file(argv[1]);// open file

    if (!file.is_open()) {
        std::cerr << "Err: could not open file\n";
        return 1;
    };
    // readLineByLine(file);
    // readWordByWord(file);
    // readCharByChar(file);
    std::string tralala =readEntireFile(file);
    std::cout << tralala  << std::endl;
    file.close();
    // std::string manages memory automatically: no need to delete/free even if returned as on the heap
    return 0;
}
