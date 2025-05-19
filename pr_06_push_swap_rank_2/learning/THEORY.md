https://42-cursus.gitbook.io/guide/rank-02/push_swap/building-the-thing

### STACK estimated time to complete 60 hrs

    The stack is a region of memory that is used for function call management and local variable storage.
It has a last-in, first-out (LIFO) structure, which makes it well-suited for managing function calls and return addresses.
Characteristics of the Stack
Automatic Memory Management:

Local variables (including function parameters) are stored on the stack.
Memory allocated on the stack is automatically managed—when a function ends, its stack frame is popped off, and the memory is freed.
Limited Size:
The stack has a limited size that is set by the operating system or environment.
Recursion that goes too deep or allocating large variables on the stack can cause a stack overflow, which crashes the program.
Fast Allocation and Deallocation:
Memory allocation and deallocation on the stack are very fast because the allocation is simply adjusting the stack pointer.
This is why local variable access in C is generally fast.
Usage:
Function Calls: Each function call creates a stack frame that contains the function’s local variables, arguments, and return address.
Local Variables: Variables declared inside functions are stored on the stack.
Example:
void example() {
    int x = 10;   // 'x' is allocated on the stack.
    char buffer[20]; // 'buffer' is an array on the stack.
}
Here, x and buffer are stored on the stack. Once the function ends, the memory for x and buffer is automatically freed.

### HEAP

    The heap is a region of memory used for dynamic memory allocation.
It is managed by the programmer, and the memory allocated on the heap persists until it is explicitly freed.
Characteristics of the Heap
Manual Memory Management:
Memory on the heap is allocated using functions like malloc(), calloc(), or realloc().
It must be manually freed using free().
Forgetting to free heap memory leads to memory leaks.
Large and Flexible Size:
The heap is generally much larger than the stack, allowing for the allocation of large amounts of memory.
The size of the heap is limited by the available system memory.
Slower Allocation and Deallocation:
Allocation on the heap is slower compared to the stack because it involves more complex bookkeeping.
Allocations on the heap are more flexible, allowing for dynamic memory usage during runtime.
Usage:
The heap is used for dynamic data that needs to be accessed across multiple function calls or when the size of data is not known at compile time.
Example:
void example() {
    int *ptr = malloc(10 * sizeof(int));  // Allocate memory for 10 integers on the heap.
    if (ptr == NULL) {
        // Handle allocation failure
    }

    // Use the memory...

    free(ptr);  // Free the allocated memory when done.
}

Key Differences Between Stack and Heap
Aspect	Stack	Heap
Memory Management	Automatic	Manual (malloc and free)
Allocation Speed	Fast	Slower (due to complex bookkeeping)
Lifetime	Limited to scope	Until explicitly freed
Size Limit	Limited (set by OS, usually smaller)	Large (limited by system memory)
Error Handling	Stack overflow	Memory leaks or fragmentation
Use Cases	Local variables, function calls	Dynamic data, data that needs to persist across function calls
Example: Stack vs. Heap in Practice
Consider a program that needs to store an array of 1000 integers:

Using the Stack:

void example() {
    int arr[1000]; // Allocated on the stack
}
In this case, arr is allocated on the stack. If 1000 integers exceed the stack's available space, it might lead to a stack overflow.
Using the Heap:

void example() {
    int *arr = malloc(1000 * sizeof(int)); // Allocated on the heap
    if (arr == NULL) {
        // Handle memory allocation failure
    }

    // Use the array...

    free(arr); // Free the allocated memory
}
In this case, arr points to memory allocated on the heap, allowing for larger and more flexible allocation. You must call free(arr) when you are done using the array to avoid a memory leak.

### STACK VS HEAP
The stack is used for automatic memory allocation for local variables and function calls, with fast access but limited space.
The heap is used for dynamic memory allocation, offering flexible memory management at the cost of being slower and requiring manual control.
Proper use of both stack and heap is essential for memory-efficient, fast, and safe C programming. Improper use can lead to issues such as stack overflow (for the stack) or memory leaks (for the heap).
===========================================================================================

Complexiteit is een maatstaf voor de efficiëntie van je algoritme. Het idee is om:

Tijdcomplexiteit: Het aantal bewerkingen dat je nodig hebt om je gegevens te sorteren, zo laag mogelijk te houden.
Ruimtecomplexiteit: De hoeveelheid geheugen die je nodig hebt om je taak uit te voeren.

Time complexity describes the amount of time an algorithm needs to execute in relation to the size of the input. It is often expressed using Big O notation, such as:

O(1): Constant time – The algorithm always takes the same time, regardless of the size of the input.
O(log n): Logarithmic time – The time grows relatively slowly compared to the input size. Algorithms that halve the input at each step, like a binary search, have this complexity.
O(n): Linear time – The time required grows linearly with the input size. For example, a loop that iterates over each input value once.
O(n log n): Log-linear time – A common time complexity for efficient sorting algorithms like Merge Sort and Quick Sort.
O(n²): Quadratic time – The time grows quadratically with the input size. For example, a nested loop where each input value is compared with every other value.
===================================
 #### Debugger
 gcc -g -o main main.c 
 // need the -g to debug with debug symbols
// if you havent installed gdb do so
gdb main
(gdb) break 46
(gdb) break 57
(gdb) run
step
next
display myarr
print

Ga naar Run and Debug (Ctrl+Shift+D).
Klik op Create a launch.json file en selecteer C++ (GDB/LLDB).
Kies g++ of gcc als de compiler.

===================================================
command-line arguments, which are always passed as strings. That's why the correct type is char *argv[] (or equivalently char **argv). The arguments are strings because when you run a program, the arguments are passed from the command line as text.
=====================================================================

Radix Sort is a non-comparative sorting algorithm that works by sorting numbers digit by digit, starting from the least significant digit (LSD) to the most significant digit (MSD). It’s effective for sorting numbers or strings when the size of elements is fixed or when the range is limited.
===============================================================

Generative AI refers to a type of artificial intelligence that can create new content, such as text, images, music, videos, or even code, rather than simply analyzing or processing existing data.

Key Characteristics of Generative AI:
Content Creation: Unlike traditional AI models that classify or predict based on data, generative AI generates new data that mimics the patterns it has learned.
Training with Models: Generative AI models are often trained on a large dataset and then learn to generate new content that resembles the training data.
============================================
In a stack, the top element is the last element added, which is at index 0 if you think of it in a LIFO order, and it’s the element that will be popped first.
============================================================================
t_stack **stack is a pointer to the head pointer of the linked list:
*stack is the pointer to the head node (the first element of the stack).
**stack dereferences to the actual head node itself.
This double-pointer approach allows modifying the head pointer (*stack) itself, such as setting it to NULL after freeing the list.
Free all the nodes in the stack linked list.
Set the stack's head pointer to NULL after all nodes are freed, ensuring the caller doesn't accidentally use an invalid pointer.
void free_stack(t_stack **stack);

int main()
{
    t_stack *stack = malloc(sizeof(t_stack));
    stack->value = 42;
    stack->next = malloc(sizeof(t_stack));
    stack->next->value = 21;
    stack->next->next = NULL;

    free_stack(&stack);
    // At this point, stack == NULL, and all nodes are freed.
    return 0;
}

Pointers and Memory
In C, when you pass a pointer to a function, the function receives a copy of the pointer's value, not the pointer itself. Therefore:

If the function modifies the pointer (e.g., sets it to NULL), the original pointer in the calling code won't change.
To allow the function to modify the pointer itself (not just what it points to), you need to pass the address of the pointer — which is &stack.

if (stack_a == NULL || *stack_a != NULL)
    free_stack(stack_a);
stack_a == NULL: Checks if the stack_a pointer itself is NULL (i.e., no pointer was passed to this function for stack_a).
*stack_a != NULL: Checks if the stack (linked list) pointed to by stack_a is not empty.






