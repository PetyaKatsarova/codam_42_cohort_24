#include "sort_list.h"
#include <stdio.h>
#include <stdlib.h>

int ascending (int a, int b)
{
    return (a <= b);
}

/**
 * Functions passed as cmp will always return a value different from
0 if a and b are in the right order, 0 otherwise.
int ascending(int a, int b)
{
	return (a <= b);
}
 */
t_list *sort_list(t_list *lst, int (*cmp)(int, int))
{
    int     swapped;
    t_list  *head = lst;    

    do
    {
        swapped = 0;

        while (head->next != NULL)
        {
            int assend = cmp(head->data, head->next->data);
    
            if (assend == 0)
            {
                int tmp = head->data;
                head->data = head->next->data;
                head->next->data = tmp;
                swapped = 1;
            }
            head = head->next;
        }
    } while (swapped);
    return (lst);
}

void print_lst(t_list *lst)
{
    int count = 0;

    while (lst != NULL)
    {
        printf("[%d] %d\n", ++count, lst->data);
        lst = lst->next;
    }
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

/**
Allocate memory for a new node
Assign the given data
Insert it at the end of the list
Returns the newly created node, while added to the list the new node
*/
t_list *push_node(t_list **head, int data)
{
    t_list *last = *head;
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node) return (NULL);

    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL)
    {
        *head = new_node;
        return (new_node);
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return (new_node);

}

// cc -Wall -Wextra -Werror sort_list.c && ./a.out
int main()
{
    printf("ascend: %d\n", ascending(3,4)); // 1
    printf("ascend: %d\n", ascending(5,4)); // 0

    t_list *lst = NULL;
    push_node(&lst, 5);
    push_node(&lst, 3);
    push_node(&lst, 8);


    sort_list(lst, ascending);
    print_lst(lst);
    free_lst(lst);
    return (0);
}