#include <map>
#include <string>
#include <iostream>

// Map (Key-Value Pairs, Sorted by key)
void mapDemo() {
    std::map<std::string, int> ages;

    ages["Beky"] = 25;
    ages["Oscar"] = 30;
    ages.insert(std::make_pair("Mutsi", 42));

    std::cout << "aBeky's age: " << ages["aBeky"] << std::endl; // = 0 and map automatically creates entry with key aBecky = 0
    std::cout << "Beky's age: " << ages["Beky"] << std::endl;
    if (ages.find("Oscar") != ages.end()) {
        std::cout << "Oscar found!\n";
    }

    // it->first is key, it->second is value
    for (std::map<std::string, int>::iterator it = ages.begin(); it != ages.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    ages.erase("Oscar");
    std::cout << "Size: " << ages.size() << std::endl;
}

// c++ -std=c++17 intro_map.cpp && ./a.out
int main() {
    mapDemo();
    return 0;
}