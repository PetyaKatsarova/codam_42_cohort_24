#include <stdio.h>
#include <stdlib.h>

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};


t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    t_list  *start;
    int     temp;

    start = lst;
    while (lst != NULL && lst->next != NULL)
    {
        if ((*cmp)(lst->data, lst->next->data) == 0)
        {
            temp = lst->data;
            lst->data = lst->next->data;
            lst->next->data = temp;
            lst = start;
        }
        else
            lst = lst->next;
    }
    return (start);
}

t_list *new_node(int data)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node)
        return NULL;
    node->data = data;
    node->next = NULL;
    return (node);
}

void append_node(t_list **head, int data)
{
    t_list *temp;
    t_list *node = new_node(data);
    if (!*head)
    {
        *head = node;
        return;
    }
    temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;

}

int ascending(int a, int b) {
    return (a > b); // swap required: a is bigger, return 0
}

int descending(int a, int b) {
    return (a < b);
}

void print_lst(t_list *lst)
{
    int i = 0;
    while (lst)
    {
        printf("node[%d] data: %d\n", ++i, lst->data);
        lst = lst->next;
    }
}

void free_list(t_list *lst)
{
    t_list *temp;
    while (lst)
    {
        temp = lst;
        lst = lst->next;
        free(temp);
    }
}

/// gcc -g myfile.c
/// valgrind --leak-check=full --track-origins=yes ./sort_list

int main()
{
    t_list *lst = NULL;
    append_node(&lst, 3);
    append_node(&lst, 1);
    append_node(&lst, 4);
    append_node(&lst, 2);
    // append_node(&lst, 4);

    printf("or lst:\n");
    print_lst(lst);
    lst = sort_list(lst, ascending);
    printf("sorted ascending:\n");
    print_lst(lst);
    lst = sort_list(lst, descending);
    printf("sorted descending:\n");
    print_lst(lst);
    free_list(lst);
    return (0);
}