/*
 Detect a Cycle in a Linked List (Floyd’s Algorithm)
Task
Write a function that checks if a linked list contains a cycle.

int has_cycle(t_list *lst);
Example
Input
1 -> 2 -> 3 -> 4 -> 5 -> 3 (loop back)
Output
1 (Cycle detected)
Input
1 -> 2 -> 3 -> 4 -> 5 -> NULL
Output
0 (No cycle)
Constraints
Use Floyd's Cycle Detection Algorithm (Tortoise and Hare).
No extra memory allocations (O(1) space complexity).
*/




/*
A cycle in a linked list occurs when a node’s next pointer points to a previous node in the list, creating an infinite loop.

1 → 2 → 3 → 4 → 5
         ↑    ↓
         6 ←  7
Here, node 7 points back to node 3, forming a cycle.
A normal list ends in NULL, but a cyclic list never ends.
Example Without a Cycle
1 → 2 → 3 → 4 → 5 → NULL
The last node (5) points to NULL, meaning no cycle exists.
🔍 Floyd’s Cycle Detection Algorithm (Tortoise and Hare)
Floyd’s Algorithm efficiently detects cycles in O(n) time and O(1) space using:

Slow pointer (tortoise) → Moves one step at a time.
Fast pointer (hare) → Moves two steps at a time.
How It Works
If there is no cycle, the fast pointer (hare) reaches NULL → No cycle detected.
If there is a cycle, the fast pointer (hare) will eventually meet the slow pointer (tortoise) → Cycle detected.
✅ Implementation of has_cycle()
int has_cycle(t_list *lst)
{
    t_list *tortoise = lst;  // Slow pointer
    t_list *hare = lst;      // Fast pointer

    while (hare != NULL && hare->next != NULL)
    {
        tortoise = tortoise->next;        // Move 1 step
        hare = hare->next->next;          // Move 2 steps

        if (tortoise == hare)             // Meeting point -> Cycle detected
            return (1);
    }
    return (0);  // If hare reaches NULL -> No cycle
}
Example Execution
1️⃣ Linked List with a Cycle
1 -> 2 -> 3 -> 4 -> 5 -> 3 (loop back)
Function Call: has_cycle(lst);
Output: 1 (Cycle detected)

2️⃣ Linked List Without a Cycle
1 -> 2 -> 3 -> 4 -> 5 -> NULL
Function Call: has_cycle(lst);
Output: 0 (No cycle)
*/