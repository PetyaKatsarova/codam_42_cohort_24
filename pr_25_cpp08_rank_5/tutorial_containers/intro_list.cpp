#include <list>
#include <algorithm>
#include <iostream>

// LIST = DOUBLY LINKED LIST
void listDemo() {
    std::list<int> lst;

    lst.push_back(10);
    lst.push_front(5);
    lst.push_back(15);

    // no random access like vector
    std::cout << "Front: " << lst.front() << std::endl;
    std::cout << "Back: " << lst.back() << std::endl;

    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}

// c++ -std=c++17 intro_list.cpp && ./a.out
int main() {
    listDemo();
    return 0;
}