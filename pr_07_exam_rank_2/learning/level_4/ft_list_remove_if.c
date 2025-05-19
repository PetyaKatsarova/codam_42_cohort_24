#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    if (begin_list == NULL || *begin_list == NULL)
        return;
    
    t_list *curr = *begin_list;

    if (cmp(curr->data, data_ref) == 0)
    {
        *begin_list = curr->next;
        free(curr);
        ft_list_remove_if(begin_list, data_ref, cmp);
    }
    else
    {
        curr = *begin_list;
        ft_list_remove_if(&curr->next, data_ref, cmp);
    }
}

int add_node(void *data, t_list **lst)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return 0;
    new_node->data = data;
    new_node->next = NULL;

    if (*lst == NULL)
    {
        *lst = new_node;
    }
    else
    {
        t_list *temp = *lst;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
    return 1;
}

void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s -> ", (char *)lst->data);
        lst = lst->next;
    }
    printf("NULL\n");
}

int cmp(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
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

void test_ft_list_remove_if()
{
    t_list *lst = NULL;

    // Add nodes to the list
    add_node("apple", &lst);
    add_node("banana", &lst);
    add_node("apple", &lst);
    add_node("cherry", &lst);
    add_node("apple", &lst);

    printf("Original list:\n");
    print_list(lst);

    ft_list_remove_if(&lst, "apple", cmp);

    printf("List after removing 'apple':\n");
    print_list(lst);

    free_list(lst);
}

int main()
{
    test_ft_list_remove_if();
    return 0;
}
