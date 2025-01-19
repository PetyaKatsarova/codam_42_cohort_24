#include <stdlib.h>
#include <stdio.h>

// Definition of the t_list struct
typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;

// Function to create a new node
t_list *ft_lstnew(void *content)
{
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return (NULL);
    new_node->content = content;
    new_node->next = NULL;
    return (new_node);
}

// Function to add a node at the end of the list
void ft_lstadd_back(t_list **lst, t_list *new_node)
{
    t_list *temp;

    if (*lst == NULL)
    {
        *lst = new_node;
        return;
    }
    temp = *lst;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
}

// Function to delete all nodes in a list
void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *temp;

    while (*lst)
    {
        temp = (*lst)->next;
        del((*lst)->content);
        free(*lst);
        *lst = temp;
    }
}

// Function to free content
void del_content(void *content)
{
    free(content);
}

// Function to transform content (multiply integer by 2)
void *multiply_by_two(void *content)
{
    int *new_content = (int *)malloc(sizeof(int));
    if (!new_content)
        return (NULL);
    *new_content = (*(int *)content) * 2;
    return new_content;
}

// Print list content (for testing purposes)
void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%d -> ", *(int *)(lst->content));
        lst = lst->next;
    }
    printf("NULL\n");
}

// ft_lstmap implementation
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_list = NULL;
    t_list *new_node;
    void *content;

    if (!f || !del)
        return (NULL);

    while (lst)
    {
        content = f(lst->content);
        if (!content)
        {
            ft_lstclear(&new_list, del);
            return (NULL);
        }
        new_node = ft_lstnew(content);
        if (!new_node)
        {
            del(content);
            ft_lstclear(&new_list, del);
            return (NULL);
        }
        ft_lstadd_back(&new_list, new_node);
        lst = lst->next;
    }
    return (new_list);
}

int main()
{
    // Create the original list with three nodes
    t_list *original_list = NULL;
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    *a = 1;
    *b = 2;
    *c = 3;
    ft_lstadd_back(&original_list, ft_lstnew(a));
    ft_lstadd_back(&original_list, ft_lstnew(b));
    ft_lstadd_back(&original_list, ft_lstnew(c));

    // Print the original list
    printf("Original list:\n");
    print_list(original_list);

    // Apply ft_lstmap
    t_list *new_list = ft_lstmap(original_list, multiply_by_two, del_content);

    // Print the new list
    printf("Mapped list (values multiplied by 2):\n");
    print_list(new_list);

    // Clean up
    ft_lstclear(&original_list, del_content);
    ft_lstclear(&new_list, del_content);

    return 0;
}
