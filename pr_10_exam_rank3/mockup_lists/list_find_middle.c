#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Write a function that returns the middle node of a singly linked list.
If the list has an even number of nodes, return the second middle node.

t_list *find_middle(t_list *lst);
Example
1 -> 2 -> 3 -> 4 -> 5 -> NULL
Output: 3
1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL
Output: 4
Constraints
The function must only traverse the list once (O(n) time complexity).
No new memory allocations.
*/

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

t_list *find_middle(t_list *lst)
{
    t_list *fast = lst;
    t_list *slow = lst;

    while (fast != NULL && fast->next)
    {
        fast = fast->next->next; // 2 steps
        slow = slow->next;
    }
    return (slow);
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

void free_lst(t_list *lst)
{
    t_list *temp = NULL;
    
    while (lst)
    {
        temp = lst;
        lst =  lst->next;
        free(temp);
    }
}
// cc -Werror -Wextra -Wall list_find_middle.c && ./a.out
// cc -g -Werror -Wextra -Wall list_find_middle.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL, *cpy, *cpy2;

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
    cpy2 = find_middle(lst);
    while (cpy2 != NULL)
    {
        printf("%d -> ", cpy2->data);
        cpy2 = cpy2->next;
    }
    printf("NULL\n");
    free_lst(lst);
    return (0);
}