Memory Allocation

Stack vs Heap

Stack: local variables (int x;) auto-freed.

Heap: dynamic, via new/delete.

int* p = new int(5);    // allocate one int, initialize to 5
// use *p...
delete p;               // free it
Arrays on heap

int* arr = new int[10]; // 10-element array
// use arr[0]…arr[9]
delete[] arr;
======================================
void incr(int& v) { v++; }
int main() {
    int a = 1;
    incr(a);    // a becomes 2
}
=========================================

struct S { int x; };
int S::* px = &S::x;    // pointer-to-member
S s{42};
std::cout << s.*px;     // prints 42
