#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort_list.h"

/*
Write a function that returns the middle node of a singly linked list.
If the list has an even number of nodes, return the second middle node.

t_list *find_middle(t_list *lst);
Example
1 -> 2 -> 3 -> 4 -> 5 -> NULL
Output
3
1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
Output
4
Constraints
The function must only traverse the list once (O(n) time complexity).
No new memory allocations.
*/

t_list *find_middle(t_list *lst)
{
    t_list  *cpy;
    int     list_len = 0; 

    cpy = lst;
    while (cpy != NULL)
    {
        list_len++;
        cpy = cpy->next;
    }
    list_len = list_len / 2;
    while (list_len > 0)
    {
        lst = lst->next;
        list_len--;
    }
    return (lst);
}

void init_node(t_list **lst, int value)
{
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
        cpy= cpy->next;
    cpy->next = node;
}
// cc -Werror -Wextra -Wall list_find_middle.c && ./a.out
// cc -g -Werror -Wextra -Wall list_find_middle.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL, *temp = NULL, *cpy;

    init_node(&lst, 1);
    init_node(&lst, 2);
    init_node(&lst, 3);
    init_node(&lst, 4);
    // init_node(&lst, 5);
    cpy = lst;

    while (cpy != NULL)
    {
        printf("%d -> ", cpy->data);
        cpy = cpy->next;
    }
    printf("NULL\nMiddle node:\n");
    lst = find_middle(lst);
    while (lst != NULL)
    {
        temp = lst;
        printf("%d -> ", lst->data);
        lst = lst->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}