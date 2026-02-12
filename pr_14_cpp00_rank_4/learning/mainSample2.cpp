#include "Sample2.hpp"

// g++ mainSample2.cpp Sample2.cpp && ./a.out
int main() {
    Sample2 s2('P', 42, 3.7);
    Sample2 s22('K', 3, 3.14f);
    s2.bar();
    return (0);
}