A thread is a lightweight execution unit inside a process. Multiple threads in one process share memory (code/data), but each has its own stack.
Use threads to:
Do tasks in parallel (on multi-core CPUs)
Keep your program responsive (e.g., UI + background work)
#include <stdio.h>
#include <pthread.h>

void* say_hello(void* arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, say_hello, NULL);
    pthread_join(tid, NULL);
    return 0;
}
pthread_create starts a thread.
pthread_join waits for it to finish.

cc -pthread thread.c && ./a.out
=================================================
int id = *(int*)arg;
This line has two steps:

🔹 1. (int*)arg
This casts the void* to an int*.
arg is declared as void* in void* function(void* arg)
A void* can’t be directly dereferenced — we must cast it to the correct pointer type first
(int*)arg  → pointer to int
🔹 2. *(int*)arg
This dereferences the pointer to get the actual int value.
arg → pointer to int
* → get the value it points to
=========================================================
What is Clang?
Clang is a C, C++, and Objective-C compiler — a modern alternative to GCC (GNU Compiler Collection).
Key Points:
Developed as part of LLVM project
Very fast and modular
Gives clearer error messages than GCC
Often used with static analyzers, code formatters, and sanitizers
======================================================================
int xi = (int)x;               // Warning: casting pointer to int
(void *)(i + 1);               // Warning: casting int to pointer
You're abusing pointer types to pass/receive integers, which is:
non-portable
leads to undefined behavior
triggers warnings because int (4 bytes) ≠ void * (8 bytes on 64-bit)

intptr_t is an integer type that is guaranteed to be large enough to hold a pointer safely.
defined in : #include <stdint.h>
Why use intptr_t?
You can't safely cast between void * and int directly on 64-bit systems because:

void * = 8 bytes
int = 4 bytes
leads to warnings and data loss
So you use intptr_t to bridge them safely
====================================================================
A mutex (mutual exlusion) allows us to encapsulate blocks of code that should only be executed in one thread at a time. Put another way, it allows us to glue together a sequence of operations that would otherwise not be atomic, so that they are executed atomically. Put yet another way, it allows us to be certain that the intermediate state during a sequence of operations will not be observed or tampered with by another thread. 
=====================================================================
int bla = *(int *)x;
(int *)x	Cast x to a pointer to int	(int *)0x1234
*(int *)x	Dereference it to get the actual int value	42
int bla = *(int *)x;	Assign that value to variable bla	bla = 42
======================================================================

When to use detach?
Use pthread_detach():
When you don’t care when or how the thread ends.

Background workers, logging, cleanup threads, fire-and-forget tasks.

Don’t use detach if you need to:

Wait for a thread to finish.
Get its return value.

Ensure it finishes before exiting main.
Example difference:
With join:

pthread_create(&tid, NULL, func, NULL);
pthread_join(tid, NULL); // blocks until thread finishes
With detach:

pthread_create(&tid, NULL, func, NULL);
pthread_detach(tid); // returns immediately, no join later
=================================================================
1. Core
A core is the actual computing unit inside a CPU that performs instructions.
Each core can:
Fetch instructions from RAM
Process data
Write back results
Modern CPUs have multiple cores, allowing them to run multiple tasks in parallel (multitasking or parallel processing).
Your CPU has 14 cores, meaning it can process 14 separate instruction streams at once.

2. Thread
A thread is the smallest sequence of programmed instructions.
With Hyperthreading (Intel's tech), each physical core can handle 2 threads, acting like 2 logical cores.

Your CPU can handle 28 threads at once.
------------------------------------------------------------------
lscpu
------------------------------------------------------------------

3. Architecture
Your architecture is x86_64, which: Supports 32-bit and 64-bit instruction sets.
Means it's a 64-bit processor (can handle large memory, faster math, more data per cycle).

4. Caches
These are fast memory blocks inside the CPU:
L1: Closest to the core. Small but fastest.
L2: Bigger, slower than L1. Each core usually has one.
L3: Shared between all cores. Bigger, slower, good for shared data.
You have:
L1: 672 KB data + 448 KB instruction
L2: 28 MB (2 MB per core)
L3: 30 MB shared (for quick inter-core data access)

5. Virtualization (VT-x)
Intel's VT-x allows the CPU to run virtual machines efficiently by handling guest OS instructions directly in hardware instead of software
------------------------------------------------------




