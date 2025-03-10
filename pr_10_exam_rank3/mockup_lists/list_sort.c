#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

int ascending(int a, int b)
{
	return (a <= b);
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    t_list  *cpy, *last_node = NULL;
    int     temp, swapped;

    do
    {
        swapped = 0;
        cpy = lst;
        while (cpy->next != last_node)
        {
            if (cmp(cpy->data, cpy->next->data) == 0)
            {
                temp = cpy->data;
                cpy->data = cpy->next->data;
                cpy->next->data = temp;
                swapped = 1;
            }
            cpy = cpy->next;
        }
        last_node = cpy;
    } while (swapped);
    return (lst);
}

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

// cc -Werror -Wextra -Wall list_sort.c && ./a.out
// cc -g -Werror -Wextra -Wall list_sort.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list *temp;

    t_list *mylist = NULL;
    mylist = init_lst(mylist, 6);
    mylist = init_lst(mylist, 5);
    mylist = init_lst(mylist, -9);
    mylist = init_lst(mylist, 42);
    mylist = init_lst(mylist, 0);

    t_list *cpy = mylist;
    while (cpy != NULL)
    {
        printf("%d -> ", cpy->data);
        temp = cpy;
        cpy = cpy->next;
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
