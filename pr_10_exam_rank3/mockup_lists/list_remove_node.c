#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

t_list *remove_nth_from_end(t_list *lst, int n)
{
    t_list  dummy = {0, lst};
    t_list  *fast = lst;
    t_list  *slow = &dummy;
    t_list  *temp = NULL;

    while (n > 0)
    {
        if (!fast) return (lst);
        fast = fast->next;
        n--;
    }
    if (!fast)
    {
        temp = lst;
        lst = lst->next;
        free(temp);
        return (lst);
    }
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    temp = slow->next; // the node to rmv
    if (temp)
    {
        slow->next = slow->next->next;
        free(temp);
    }
    return (dummy.next);
}

void init_lst(t_list **lst, int value)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node) return;
    node->data = value;
    node->next = NULL;
    t_list *cpy;
    
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
// cc -Werror -Wextra -Wall list_remove_node.c && ./a.out
// cc -g -Werror -Wextra -Wall list_remove_node.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL;
    init_lst(&lst, 1);
    init_lst(&lst, 2);
    init_lst(&lst, 3);
    init_lst(&lst, 4);
    init_lst(&lst, 5);

    lst = remove_nth_from_end(lst, 5);
    while (lst != NULL)
    {
        t_list *temp = lst;
        printf("%d -> ", lst->data);
        lst = lst->next;
        free(temp);
    }
    printf("NULL\n");    
    return (0);
}