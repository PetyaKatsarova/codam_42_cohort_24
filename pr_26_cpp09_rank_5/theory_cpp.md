** A reference is an alias - another name for an existing variable. Once bound, it always refers to that object.

int x = 10;
int& ref = x;  // ref is now another name for x
ref = 20;      // x is now 20

int* ptr = &x; // ptr holds the address of x
*ptr = 30;     // x is now 30

References cannot be null - they must be initialized to a valid object
References cannot be rebound - they always refer to the same object
Pointers can be null, can point to different things, need dereferencing (*ptr)
---------------------------------------------
** RAII (Resource Acquisition Is Initialization)
Core principle: Tie resource lifetime to object lifetime.

Acquire resource in constructor
Release resource in destructor
The C++ compiler guarantees destructors run when objects go out of scope

// Good RAII C++ code:
class FileHandle {
    FILE* f;
public:
    FileHandle(const char* name) : f(fopen(name, "r")) {
        if (!f) throw std::runtime_error("Can't open file");
    }
    ~FileHandle() { 
        if (f) fclose(f);  // Always runs, even on exceptions!
    }
    FILE* get() { return f; }
};

void goodFunction() {
    FileHandle file("data.txt");
    // ... do work ...
    if (error) return;  // No leak - destructor auto-called
}  // Destructor called here automatically
------------------------------------------------

Smart pointers are RAII wrappers around raw pointers that auto-delete memory.
unique_ptr - Exclusive ownership

// Old C way:
int* ptr = new int(42);
delete ptr;  // Must remember!

// Modern C++ way:
std::unique_ptr<int> ptr = std::make_unique<int>(42);
// No delete needed - auto-deleted when ptr goes out of scope

// Only ONE unique_ptr can own the object
std::unique_ptr<int> ptr1 = std::make_unique<int>(10);
// std::unique_ptr<int> ptr2 = ptr1;  // ERROR: Can't copy!
std::unique_ptr<int> ptr2 = std::move(ptr1);  // OK: Transfer ownership
// Now ptr1 is null, ptr2 owns the memory

**shared_ptr - Shared ownership

std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::shared_ptr<int> ptr2 = ptr1;  // Both own it (ref count = 2)
std::shared_ptr<int> ptr3 = ptr1;  // ref count = 3
// Memory deleted only when ALL shared_ptrs are destroyed
ptr1.reset();  // ref count = 2
ptr2.reset();  // ref count = 1
// ptr3 still alive, memory still valid

Use shared_ptr when: Multiple owners, unclear who should delete.
Cost: shared_ptr has overhead (reference counting), unique_ptr has almost zero overhead.
----------------------------------------
Move Semantics & Rvalue References
The problem: Copying large objects is expensive.
std::vector<int> createBigVector() {
    std::vector<int> v(1000000);  // 1 million elements
    return v;  // Without move: expensive copy!
}

std::vector<int> myVec = createBigVector();

** Move semantics: Instead of copying, "steal" the internal data.

// Move constructor: steal resources from temporary
std::vector<int> vec1(1000000);
std::vector<int> vec2 = std::move(vec1);  
// vec2 now owns vec1's data, vec1 is empty
// No copying - just pointer swap!

class Buffer {
    char* data;
    size_t size;
public:
    // Copy constructor (expensive)
    Buffer(const Buffer& other) {
        size = other.size;
        data = new char[size];
        memcpy(data, other.data, size);  // Copy all bytes
    }
    
    // Move constructor (cheap)
    Buffer(Buffer&& other) noexcept {
        data = other.data;      // Steal pointer
        size = other.size;
        other.data = nullptr;   // Leave other empty
        other.size = 0;
    }
};
-------------------------------------
** Multithreading: True parallelism

Multiple CPU cores running simultaneously
OS schedules threads
Heavy: thread creation is expensive (MB of stack, OS overhead)
Dangerous: race conditions, need locks/mutexes
Use for: CPU-intensive parallel work

#include <thread>

void task1() { /* work */ }
void task2() { /* work */ }

std::thread t1(task1);  // Run on separate OS thread
std::thread t2(task2);  // Run on another OS thread
t1.join();
t2.join();

** Coroutines: Cooperative multitasking

Single thread, functions can pause/resume
Lightweight: minimal overhead, millions possible
Safe: no race conditions (no true parallelism)
Use for: I/O-bound tasks, async operations

#include <coroutine>

// Simplified example (C++20)
Task asyncReadFile() {
    auto data = co_await readAsync("file.txt");  // Pause here
    // Function resumes when read completes
    process(data);
}

// While waiting, other coroutines can run on same thread

Threads: 4 chefs in kitchen, each cooking different dish simultaneously
Coroutines: 1 chef switching between dishes while waiting for oven/boiling water
---------------------------------------
rvalue: read only, can be only on the rhs of =
int x = 42;        // 42 is an rvalue (literal, no address)
// int* p = &42;   // ERROR: can't take address of rvalue

int y = x + 5;     // "x + 5" is an rvalue (temporary result)
// &(x + 5);       // ERROR: temporary has no address

int z = getValue(); // return value is an rvalue (temporary)
--------------------------
T& = lvalue reference (binds to lvalues)
T&& = rvalue reference (binds to rvalues, enables move semantics)
std::move(x) = cast lvalue to rvalue (tells compiler "treat as temporary")


















