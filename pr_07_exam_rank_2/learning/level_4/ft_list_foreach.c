#include <stdio.h>
#include <stdlib.h>

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

void    ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
    // (*f)(list_ptr->data);
    t_list *head;
    head = begin_list;

    while (head != NULL)
    {
        (*f)(head->data);
        head = head->next;
    }
}

int add_node(void *data, t_list **lst)
{
    t_list *new_node;
    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return (0);
    new_node -> data = data;
    new_node -> next = NULL;

    if (*lst == NULL)
        *lst = new_node;
    else {
        t_list *temp;
        temp = *lst;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
    return (1);
}

void free_lst(t_list *lst)
{
    t_list *temp;
    while (lst)
    {
        temp = lst;
        lst = lst->next;
        free(temp);
    }
}

void print_data(void *data)
{
    printf("Data: %d\n", (int)(long)data);
}

int main()
{
    t_list *lst;
    lst = NULL;
    add_node((void *)(long)1, &lst);
    add_node((void *)(long)2, &lst);
    add_node((void *)(long)3, &lst);
    
    ft_list_foreach(lst, print_data);

    free_lst(lst);
    return (0);
}