#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort_list.h"

/*
Write a function that merges two sorted linked lists into one sorted list.

t_list *merge_sorted_lists(t_list *lst1, t_list *lst2);
Example
Input
List 1: 1 -> 3 -> 5 -> NULL
List 2: 2 -> 4 -> 6 -> NULL
Output
1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
Constraints
No extra memory allocation.
The merged list must be sorted.
*/

t_list *merge_sorted_lists(t_list *lst1, t_list *lst2)
{
    t_list dummy = {0, NULL}, *merged = &dummy;

    while (lst1 != NULL && lst2 != NULL)
    {
        if (lst1->data < lst2->data)
        {
            merged->next = lst1;
            lst1 = lst1->next;
        }
        else
        {
            merged->next = lst2;
            lst2 = lst2->next;
        }
        merged = merged->next;
    }
    merged->next = lst1 ? lst1 : lst2;
    return (dummy.next);
}

void init_lst(t_list **lst, int value)
{
    /*
    !! NB !!
    !lst checks if the passed pointer itself is NULL (should be checked first), prevents crash here: init_lst(NULL, 1); 
    !(*lst) checks if the list is empty.
    If lst is NULL, checking *lst causes segmentation fault.
    */
    if (!lst) return;
    t_list *node, *cpy;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node) return;
    node->data = value;
    node->next = NULL;
    if (*lst == NULL)
    {
        *lst = node;
        return;
    }
    cpy = *lst;
    while (cpy->next)
        cpy = cpy->next;
    cpy->next = node;    
}

// cc -Werror -Wextra -Wall list_merge2.c && ./a.out
// cc -g -Werror -Wextra -Wall list_merge2.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst1 = NULL, *lst2 = NULL, *merged, *cpy, *temp;

    init_lst(&lst1, 1);
    init_lst(&lst2, 2);
    init_lst(&lst1, 3);
    init_lst(&lst2, 4);
    init_lst(&lst1, 5);
    init_lst(&lst2, 6);
    init_lst(&lst1, 7);
    merged = merge_sorted_lists(lst1, lst2);
    cpy = merged;
    while (cpy)
    {
        temp = cpy;
        printf("%d -> ", cpy->data);
        cpy = cpy->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}