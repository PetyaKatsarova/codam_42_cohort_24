#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort_list.h"

/*
 Write a function that removes duplicate values from a sorted linked list (in ascending order). The function must modify the list in place without allocating new nodes.

void remove_duplicates(t_list *lst);
Example Input/Output
Input List
1 -> 1 -> 2 -> 3 -> 3 -> 4 -> 5 -> 5 -> NULL
Output List (After remove_duplicates(lst))
1 -> 2 -> 3 -> 4 -> 5 -> NULL
Constraints
The list must be sorted before calling the function.
You cannot allocate new nodes.
You must modify the existing linked list in place
*/

void remove_duplicates(t_list *sorted_lst)
{
    t_list *temp, *cpy;

    // temp is not a copy; it is just a pointer to the actual list.
    // Changes made to temp->next affect the original list because it directly points to sorted_lst
    cpy = sorted_lst;
    while (cpy != NULL && cpy->next != NULL)
    {
        if (cpy->data == cpy->next->data)
        {
            temp = cpy->next;
            cpy->next = cpy->next->next;
            free(temp);
        }
        else
            cpy = cpy->next;
    }
}

void init_lst(t_list **lst, int value)
{
    t_list *node, *cpy;

    node = (t_list*)malloc(sizeof(t_list));
    if (!node) return;
    node->data = value;
    node->next = NULL;
    cpy = *lst;
    if (!*lst)
    {
        *lst = node;
        return;
    }
    while (cpy->next != NULL)
        cpy = cpy->next;
    cpy->next = node;
}
// cc -Wall -Wextra -Werror rmv_dups_list.c && ./a.out
// cc -g -Wall -Wextra -Werror rmv_dups_list.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *temp;
    t_list *lst = NULL;

    init_lst(&lst, 1);
    init_lst(&lst, 1);
    init_lst(&lst, -22);
    init_lst(&lst, -22);
    init_lst(&lst, 4);
    init_lst(&lst, 1);
    init_lst(&lst, 37);
    t_list *cpy = lst;

    while (cpy != NULL)
    {
        printf("%d -> ", cpy->data);
        cpy = cpy->next;
    }
    printf("NULL\nDUPS REMOVED:\n");
    remove_duplicates(lst);
    cpy = lst;
    while (cpy != NULL)
    {
        printf("%d -> ", cpy->data);
        temp = cpy;
        cpy = cpy->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}