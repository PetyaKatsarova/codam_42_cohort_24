#include "sort_list.h"
#include <stdio.h>
#include <stdlib.h>

/*
Returns 0 if false: not ascending order, and 1 if true: ascending
*/
int ascending(int a, int b)
{
	return (a <= b);
}
/*
If not init, inits the list, else pushes the new node at the end of the list
Returns the newly created node.
*/
t_list *push_node(t_list **list, int data)
{
    t_list *node = (t_list *)malloc(sizeof(t_list));
    t_list *last = *list;

    if (!node) return (NULL);
    node->data = data;
    node->next = NULL;
    if (*list == NULL)
    {
        *list = node;
        return (node);
    }
    while (last->next != NULL)
        last = last->next;
    last->next = node;
    return (node);
}

void free_list(t_list *list)
{
    t_list *temp;

    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
    
}

void print_list(t_list *list)
{
    t_list  *temp;
    int     count;

    temp = list;
    count = 0;
    while (temp != NULL)
    {
        printf("[%d] %d\n", ++count, temp->data);
        temp = temp->next;
    }
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    t_list  *temp;
    int     swapped;
    t_list  *last;

    temp = lst;
    last = NULL;
    do
    {
        swapped = 0;
        temp = lst;
        while (temp->next != last)
        {
            if (cmp(temp->data, temp->next->data) == 0)
            {
                int t = temp->data;
                temp->data = temp->next->data;
                temp->next->data = t;
                swapped = 1;
            }
            temp = temp->next;
        }
        last = temp;        
    } while (swapped);
    return (lst);
}

// cc -Wall -Wextra -Werror sort_list3.c && ./a.out
// cc -g -Wall -Wextra -Werror sort_list3.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *list = NULL;
    push_node(&list, 5);
    push_node(&list, 3);
    push_node(&list, 8);
    push_node(&list, -8);
    push_node(&list, 42);
    sort_list(list, ascending);

    print_list(list);
    free_list(list);
}