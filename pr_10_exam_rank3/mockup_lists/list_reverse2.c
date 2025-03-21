#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

t_list *reverse_list(t_list *lst)
{
    t_list *cpy = lst, *prev = NULL, *next = NULL;

    while (cpy)
    {
        next = cpy->next;
        cpy->next = prev;
        prev = cpy;
        cpy = next;
    }
    return (prev);
}

void init_lst(t_list **lst, int value)
{
    if (!lst) return;
    t_list *node;
    t_list *cpy;

    node = malloc(sizeof(t_list));
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

// cc -Werror -Wextra -Wall list_reverse2.c && ./a.out
// cc -g -Werror -Wextra -Wall list_reverse2.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL;
    t_list *cpy;

    init_lst(&lst, 1);
    init_lst(&lst, 2);
    init_lst(&lst, 3);
    init_lst(&lst, 4);
    init_lst(&lst, 5);
    lst = reverse_list(lst);
    cpy = lst;

    while (lst) {
        printf("%d->", lst->data);
        lst = lst->next;
    }
    while (cpy)
    {
        t_list *temp = cpy;
        cpy = cpy->next;
        free(temp);
    }
    return (0);
}

