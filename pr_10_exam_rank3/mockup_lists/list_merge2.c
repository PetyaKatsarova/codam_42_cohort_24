#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

t_list *merge_sorted_lists(t_list *lst1, t_list *lst2)
{
    if (!lst1) return lst2;
    if (!lst2) return lst1;
    t_list dummmy = {0, NULL}, *merged = &dummmy;

    while (lst1 && lst2)
    {
        if (lst1->data < lst2->data)
        {
            merged->next = lst1;
            lst1 = lst1->next;
        }
        else {
            merged->next = lst2;
            lst2 = lst2->next;
        }
        merged = merged->next;
    }
    if (lst1)
        merged->next = lst1;
    else
        merged->next = lst2;
    return (dummmy.next);
}

void init_lst(t_list **lst, int val)
{
    t_list *node, *cpy;
    node = malloc(sizeof(t_list));
    if (!node) return;
    node->next = NULL;
    node->data = val;

    if (!*lst)
    {
        *lst = node;
        return;
    }
    cpy = *lst;
    while (cpy->next)
        cpy = cpy->next;
    cpy->next = node;
}

// cc -Wall -Wextra -Werror list_merge2.c && ./a.out
int main()
{
    t_list *merged, *temp;
    t_list *bla = NULL;
    init_lst(&bla, 1);
    init_lst(&bla, 3);
    init_lst(&bla, 37);

    t_list *bla2 = NULL;
    init_lst(&bla2, 0);
    init_lst(&bla2, 2);
    init_lst(&bla2, 42);
    merged = merge_sorted_lists(bla, bla2);

    while (merged) {
        printf("%d->", merged->data);
        temp = merged;
        merged = merged->next;
        free(temp);
    }
    printf("NULL\n");

    return (0);
}