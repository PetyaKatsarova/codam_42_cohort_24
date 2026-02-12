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
    t_list *curr = lst;
    t_list *next = NULL;
    t_list *prev = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return (prev);
}

void init_list(t_list **lst, int value)
{
    t_list *node, *cpy;

    node = (t_list *)malloc(sizeof(t_list));
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

// cc -Werror -Wextra -Wall list_reverse.c && ./a.out
// cc -g -Werror -Wextra -Wall list_reverse.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL;
    init_list(&lst, 1);
    init_list(&lst, 2);
    init_list(&lst, 3);
    init_list(&lst, 4);
    init_list(&lst, 5);

    lst = reverse_list(lst);
    while (lst)
    {
        t_list *temp = lst;
        printf("%d -> ", temp->data);
        lst = lst->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}