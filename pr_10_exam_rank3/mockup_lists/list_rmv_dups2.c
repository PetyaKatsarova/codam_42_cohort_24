#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

void remove_duplicates(t_list *lst)
{
	t_list  *cpy = lst;
    t_list  *temp;
    
    while (cpy->next)
    {
        if (cpy->data == cpy->next->data)
        {
            temp = cpy->next;
            cpy->next = cpy->next->next;
            free(temp);
        }
        else {
            cpy = cpy->next;
        }
    }
}

void init_list(t_list **lst, int value)
{
    if (!lst) return;
    t_list *temp = *lst;

    t_list *node = malloc(sizeof(t_list));
    if (!node) return;
    node->data = value;
    node->next = NULL;
    if (!*lst)
    {
        *lst = node;
        return;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = node;
}

// cc -Wall -Wextra -Werror list_rmv_dups2.c && ./a.out
// cc -g -Wall -Wextra -Werror list_rmv_dups2.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *temp;
    t_list *lst = NULL;

    init_list(&lst, 1);
    init_list(&lst, 1);
    init_list(&lst, -22);
    init_list(&lst, -22);
    init_list(&lst, 4);
    init_list(&lst, 1);
    init_list(&lst, 37);
    init_list(&lst, 37);
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

    return (0);
}
