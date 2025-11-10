std::random_device

A true random number generator (or as close as possible to true randomness)
Gets randomness from the operating system (e.g., urandom on Linux, hardware entropy on modern CPUs)
Used to seed other pseudo-random generators
Non-deterministic — different results each run
example:
std::random_device rd;
unsigned int seed = rd();  // Get a random seed value (e.g., 3847562)
----------------------------
static std::mt19937 gen(rd()); 
Mersenne Twister pseudo-random number generator
19937 = the period (2^19937 - 1) — an astronomically large cycle before repeating
Very high quality randomness (passes statistical tests)
Fast and deterministic (same seed → same sequence)
--------------------------------
gen(rd())

Constructs the generator and seeds it with a random value from rd()
rd() calls random_device to get one random number (e.g., 3847562)
This seed initializes the Mersenne Twister's internal state
-----------------------
NB!!!
int result = dist(gen);  // Returns 0 or 1 with 50% probability each
----------------------------
┌─────────────────────┐
│ std::random_device  │  ← Gets true randomness from OS
│       rd            │
└──────────┬──────────┘
           │
           │ rd() → produces seed (e.g., 3847562)
           ▼
┌─────────────────────┐
│   std::mt19937      │  ← Mersenne Twister (pseudo-random)
│      gen(seed)      │     Initialized with seed
└──────────┬──────────┘
           │
           │ gen() → produces large random number (e.g., 823947561)
           ▼
┌─────────────────────┐
│ uniform_int_dist    │  ← Maps large number to [0, 1]
│   dist(0, 1)        │
└──────────┬──────────┘
           │
           │ dist(gen) → returns 0 or 1
           ▼
    ┌──────────────┐
    │ if (... == 0)│  ← Check result
    └──────┬───────┘
           │
      ┌────┴────┐
      │         │
     0 (50%)   1 (50%)
      │         │
   Success    Failure
   ======================================================
   Tutorial: this. vs this-> in C++
Key Rule:
this is a POINTER in C++
Use this-> (arrow) to access members via pointer
this. (dot) is INVALID in C++
Why this is a pointer:
In C++, this is automatically a pointer to the current object:

class MyClass {
    int value;
    
    void printValue() {
        // this has type: MyClass* (pointer)
        std::cout << this->value << std::endl;
    }
};


Language	this type	Syntax
C++	Pointer (MyClass*)	this->member
Java	Reference	this.member
Python	Reference (self)	self.member
JavaScript	Object reference	this.member
=============================================
When you throw an exception, the program doesn't exit immediately. Instead:

Execution stops at the throw point
Stack unwinding begins (destructors are called)
Control transfers to the nearest matching catch block
Execution continues after the catch block

try {
    burie.signForm(robo_form);
    burie.executeForm(robo_form);
    
    testie.signForm(trump_form);
    testie3.signForm(trump_form); // ← Throws exception here!
    testie2.signForm(trump_form); // ← THIS LINE NEVER EXECUTES
    
} catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
}
// ← Execution continues here after catch
---------------------------------------------