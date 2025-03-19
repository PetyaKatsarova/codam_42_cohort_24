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

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next; // middle
    }
    // if (fast->next) this was for the while (fast.next && fast.next.next)
    //     slow = slow->next;
    return (slow);
}

void init_lst(t_list **lst, int val)
{
    if (!lst) return;
    t_list *node;
    t_list *cpy;

    node = malloc(sizeof(t_list));
    if (!node) return;
    node->data = val;
    node->next = NULL;
    if (!*lst)
    {
        *lst = node;
        return;
    }
    cpy = *lst;
    while (cpy->next)
    {
        cpy = cpy->next;
    }
    cpy->next = node;
}

// cc -g -Wall -Werror -Wextra list_find_middle2.c && ./a.out
// cc -g -Wall -Werror -Wextra list_find_middle2.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL;
    t_list *temp = NULL;
    init_lst(&lst, 1);
    init_lst(&lst, 2);
    init_lst(&lst, 3);
    init_lst(&lst, 4);
    init_lst(&lst, 5);
    // init_lst(&lst, 6); // middle = 4
    t_list *middle = find_middle(lst);
    printf("middle: %d\n", middle->data);
    while (lst->next)
    {
        temp = lst;
        lst = lst->next;
        free(temp);
    }
    free(lst);
    return (0);
}