#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort_list.h"

int ascending(int a, int b)
{
	return (a <= b);
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    t_list  *head, *last_node;
    int     swapped, temp;

    last_node = NULL;
    do
    {
        head = lst;
        swapped = 0;
        while (head->next != last_node)
        {
            if (cmp(head->data, head->next->data) == 0)
            {
                temp = head->data;
                head->data = head->next->data;
                head->next->data = temp;
                swapped = 1;
            }
            head = head->next;
        }
        last_node = head;
    } while (swapped);
    return (lst);
}

/*
t_list **lst (double pointer)	Modifies the original lst in main() directly, u simply do: void init_lst(t_list **lst, int value)
t_list *lst (single pointer)	Returns a new head pointer, requiring reassignment.

t_list *lst (Single Pointer, Returning New Head)
lst is a copy of the pointer, so changes do not modify the original.
To update lst, the function returns the modified list.
The caller must reassign lst after each call.
*/
t_list *init_lst(t_list *lst, int value)
{
    t_list *node, *cpy_lst;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node) return (NULL);
    node->data = value;
    node->next = NULL;
    cpy_lst = lst;
    if (!lst)
        return (node);
    while (cpy_lst->next != NULL)
        cpy_lst = cpy_lst->next;
    cpy_lst->next = node;
    return(lst);
}
// cc -Werror -Wextra -Wall sort_list5.c && ./a.out
// cc -g -Werror -Wextra -Wall sort_list5.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *temp;

    t_list *mylist = NULL;
    mylist = init_lst(mylist, 6);
    mylist = init_lst(mylist, 5);
    mylist = init_lst(mylist, -9);
    mylist = init_lst(mylist, 42);
    mylist = init_lst(mylist, 0);

    t_list *bla = mylist;
    while (bla != NULL)
    {
        printf("%d -> ", bla->data);
        temp = bla;
        bla = bla->next;
    }
    printf("NULL\nSORTED:\n");
    mylist = sort_list(mylist, ascending);
    while (mylist != NULL)
    {
        printf("%d -> ", mylist->data);
        temp = mylist;
        mylist = mylist->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}


/*
t_list *init_lst(t_list *lst, int value)
{
    t_list *node, *cpy_lst;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node) return lst;  // ✅ If malloc fails, return unchanged list
    node->data = value;
    node->next = NULL;

    if (!lst)
        return node;  // ✅ Return new node if list was empty

    cpy_lst = lst;
    while (cpy_lst->next != NULL)
        cpy_lst = cpy_lst->next;
    
    cpy_lst->next = node;
    return lst;  // ✅ Return updated list head
}

in main:
t_list *lst = NULL;
lst = init_lst(lst, 5);
lst = init_lst(lst, 3);
lst = init_lst(lst, 8);


void init_lst(t_list **lst, int value)
{
    t_list *node, *cpy_lst;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node) return;
    node->data = value;
    node->next = NULL;

    if (!*lst)
    {
        *lst = node;  // ✅ Directly modifies the list head
        return;
    }

    cpy_lst = *lst;
    while (cpy_lst->next != NULL)
        cpy_lst = cpy_lst->next;
    
    cpy_lst->next = node;
}
in main:
t_list *lst = NULL;
init_lst(&lst, 5);
init_lst(&lst, 3);
init_lst(&lst, 8);
*/