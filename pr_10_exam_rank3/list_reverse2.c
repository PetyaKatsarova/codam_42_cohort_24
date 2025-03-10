#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort_list.h"

/*
Write a function that reverses a singly linked list in place.

t_list *reverse_list(t_list *lst);
Example
Input
1 -> 2 -> 3 -> 4 -> 5 -> NULL
Output
5 -> 4 -> 3 -> 2 -> 1 -> NULL
Constraints
No new allocations allowed.
The function should modify the list in place.
Return the new head of the reversed list.
*/

t_list *reverse_list(t_list *lst)
{
    t_list *curr = lst;
    t_list *prev = NULL;
    t_list *next = NULL; // placeholder for curr->next node

    // example: 1 2 3 4
    while (curr != NULL)
    {
        next = curr->next; // 2 - 3
        curr->next = prev; // null - 1
        prev = curr; // 1 - 2
        curr = next; // 2 - 3
    }
    return (prev);
}

