#include "sort_list.h"
#include <stdio.h>
#include <stdlib.h>

int ascending (int a, int b)
{
    return (a <= b); // returns 1 if true, and 0 if wrong
}

t_list *push_node(t_list **lst, int data)
{
    t_list  *node;
    t_list  *last = *lst;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node) return (NULL);

    node->data = data;
    node->next = NULL;
    if (*lst == NULL)
    {
        *lst = node;
        return (node);
    }
    while (last->next != NULL)
        last = last->next;
    last->next = node;
    return (node);
}

void free_lst(t_list *lst)
{
    t_list *temp;

    while (lst != NULL)
    {
        temp = lst;
        lst = lst->next;
        free(temp);
    }
}

void print_lst(t_list *lst)
{
    t_list  *temp;
    int     count = 0;

    temp = lst;
    while (temp != NULL)
    {
        printf("[%d] %d\n", ++count, temp->data);
        temp = temp->next;
    }
}

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
    t_list  *temp;
    t_list  *last;
    int     swapped;
    int     count = 0;

    if (!lst) return (NULL);
    last = NULL;
    do
    {
        swapped = 0;
        temp = lst; // start next loop from beggining again!
        while (temp->next != last) // last is the new largest num
        {
            int bla = cmp(temp->data, temp->next->data);
            if (bla == 0)
            {
                int storage = temp->data;
                temp->data = temp->next->data;
                temp->next->data = storage;
                swapped = 1;
                printf("loop count: %d\n", ++count);
            }
            temp = temp->next;
        }
        last = temp; // doesnt loop through the last, which is largest value
    } while (swapped);
    return (lst);    
}

// cc -Wall -Wextra -Werror sort_list2.c && ./a.out
// cc -g -Wall -Wextra -Werror sort_list2.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *lst = NULL;
    push_node(&lst, 5);
    push_node(&lst, 3);
    push_node(&lst, -8);
    push_node(&lst, 17);
    push_node(&lst, -42);

    sort_list(lst, ascending);
    print_lst(lst);
    free_lst(lst);
    return (0);
}
