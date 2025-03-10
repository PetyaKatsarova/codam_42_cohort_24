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
    if (!lst1) return (lst2);
    if (!lst2) return (lst1);

    t_list dummy = {0, NULL};
    t_list *merged = &dummy; // stores the address of dummy

    while (lst1 != NULL && lst2 != NULL)
    {
        if (lst1->data > lst2->data)
        {
            merged->next = lst2;
            lst2 = lst2->next;
        }
        else
        {
            merged->next = lst1;
            lst1 = lst1->next;
        }
        merged = merged->next;
    }
    merged->next = (lst1 ? lst1 : lst2);
    return (dummy.next);
}

void init_list(t_list **lst, int value)
{
    t_list *node, *cpy;

    if (!lst) return;
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
    while (cpy->next)
        cpy = cpy->next;
    cpy->next = node;
}

// cc -Werror -Wextra -Wall list_merge.c && ./a.out
// cc -g -Werror -Wextra -Wall list_merge.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst1 = NULL;
    t_list *lst2 = NULL;
    t_list *merged, *temp;

    init_list(&lst1, 1);
    init_list(&lst1, 3);
    init_list(&lst1, 5);
    init_list(&lst2, 2);
    init_list(&lst2, 4);
    init_list(&lst2, 6);

    merged = merge_sorted_lists(lst1, lst2);
    while (merged != NULL)
    {
        printf("%d -> ", merged->data);
        temp = merged;
        merged = merged->next;
        free(temp);
    }
    printf("NUL\n");
    return (0);
}

/*
IF I have only t_list dummy, *tail = &dummy;
dummy is not initialized, so its data field contains garbage.
tail = &dummy; makes tail point to dummy.
tail->next = NULL; sets dummy.next = NULL;, making it a valid empty node.
*/