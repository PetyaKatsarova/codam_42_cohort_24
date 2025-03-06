#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort_list.h"

/*
Write a function that removes the N-th node from the end of a linked list.

t_list *remove_nth_from_end(t_list *lst, int n);
Example
1 -> 2 -> 3 -> 4 -> 5 -> NULL,  n = 2
Output
1 -> 2 -> 3 -> 5 -> NULL
Constraints
Must traverse the list only once (O(n) time complexity).
No extra memory allocation.
*/

t_list *remove_nth_from_end(t_list *lst, int n)
{
    t_list dummy = {0, lst}, *slow = &dummy, *fast = lst, *temp, *bla;

    while (n > 0 && fast)
    {
        fast =  fast->next; // if arr of 10, want to remove 3rd last, fast is now at 3rd node
        n--;
    }
    if (!fast)
    {
        temp = lst;
        bla = lst->next;
        free(lst);
        return (bla); // If n == list length, fast reaches NULL, indicating we must remove the first node.
    }
    while (fast != NULL)
    {
        fast = fast->next; // reached the NULL *node: from 10 - 3: moved 7 places
        slow = slow->next; // moved from head 7 places, left 3
    }
    temp = slow->next;
    slow->next = slow->next->next;
    free(temp);
    return (dummy.next);
}

void init_list(t_list **lst, int value)
{
    if (!lst) return; // if the passed pointer itself is NULL
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

// cc -Werror -Wextra -Wall list_remove_node3.c && ./a.out
// cc -g -Werror -Wextra -Wall list_remove_node3.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL, *cpy, *temp;
    init_list(&lst, 1);
    init_list(&lst, 2);
    init_list(&lst, 3);
    init_list(&lst, 4);
    cpy = remove_nth_from_end(lst, 4);
    while (cpy != NULL)
    {
        temp = cpy;
        printf("%d -> ", cpy->data);
        cpy = cpy->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}