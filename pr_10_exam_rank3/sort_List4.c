#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sort_list.h"

/*
typedef struct s_list t_list;
*/

// t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
// {

// }

void append_node(t_list **lst, int value)
{
    t_list  *new;
    t_list  *temp;

    new = (t_list *)malloc(sizeof(t_list));
    if (!new) return;
    new->data = value;
    new->next = NULL;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    temp = *lst;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new;
}
// return true 1 if ascending, otherwise 0(false)
int ascending(int a, int b)
{
	return (a <= b);
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    t_list *start, *last;
    int     swapped, value;

    last = NULL;
    do
    {
        swapped = 0;
        start = lst; // start loop again
        while (start->next != last)
        {
            if (cmp(start->data, start->next->data) == 0)
            {
                swapped = 1;
                value = start->data;
                start->data = start->next->data;
                start->next->data = value;
            }
            start = start->next;
        }
        last = start; // exclude from loop last el: it is the highest num
    } while (swapped);
    return (lst);
}

/*
cc -Wall -Wextra -Werror sort_list4.c && ./a.out
cc -g -Wall -Wextra -Werror sort_list4.c && valgrind --leak-check=full ./a.out
*/
int main()
{
    t_list *head;
    t_list *temp;

    head = NULL;
    append_node(&head, 3);
    append_node(&head, -1);
    append_node(&head, 0);
    append_node(&head, 42);
    head = sort_list(head, ascending);

    while (head)
    {
        temp = head;
        printf("%d -> ", head->data);
        head = head->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}
