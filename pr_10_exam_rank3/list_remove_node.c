/*
Write a function that removes the N-th node from the end of a linked list.

Function Prototype
c
Copy
Edit
t_list *remove_nth_from_end(t_list *lst, int n);
Example
Input
rust
Copy
Edit
1 -> 2 -> 3 -> 4 -> 5 -> NULL,  n = 2
Output
rust
Copy
Edit
1 -> 2 -> 3 -> 5 -> NULL
Constraints
Must traverse the list only once (O(n) time complexity).
No extra memory allocation.
*/