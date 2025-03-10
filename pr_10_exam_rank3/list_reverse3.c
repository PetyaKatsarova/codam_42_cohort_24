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
    t_list *prev = NULL;
    t_list *curr = lst;
    t_list *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return (prev);
}

void init_lst(t_list **lst, int value)
{
    if (!lst) return; // if empty pointer to the first node
    t_list *node, *cpy;

    node = malloc(sizeof(t_list));
    if (!node) return;
    node->data = value;
    node->next = NULL;
    if (!*lst)
    {
        *lst = node;
        return;
    }
    cpy = *lst;
    while (cpy->next != NULL)
        cpy = cpy->next;
    cpy->next = node;    
}
// cc -Werror -Wextra -Wall list_reverse3.c && ./a.out
// cc -g -Werror -Wextra -Wall list_reverse3.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL, *cpy, *temp;
    init_lst(&lst, 1);
    init_lst(&lst, 2);
    init_lst(&lst, 3);
    init_lst(&lst, 4);
    init_lst(&lst, 5);

    cpy = reverse_list(lst);
    while(cpy != NULL)
    {
        temp = cpy;
        printf("%d -> ", cpy->data);
        cpy = cpy->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}