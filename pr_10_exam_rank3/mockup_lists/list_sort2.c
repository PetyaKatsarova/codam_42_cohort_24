#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
    t_list  *cpy = lst, *last_node = NULL;
    int     swapped = 0, temp = 0;

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

void init_lst(t_list **lst, int val)
{
    if (!lst) return;
    t_list *node = malloc(sizeof(t_list));
    t_list *cpy = *lst;
    if (!node) return; // probably need to free entire list?
    node->data = val;
    node->next = NULL;
    if (!*lst)
    {
        *lst = node;
        return;
    }
    while (cpy->next)
        cpy = cpy->next;
    cpy->next = node;
}

// cc -Werror -Wextra -Wall list_sort2.c && ./a.out
// cc -g -Werror -Wextra -Wall list_sort2.c && valgrind --leak-check=full ./a.out

int main()
{
    t_list *lst = NULL;
    init_lst(&lst, 5);
    init_lst(&lst, 1);
    init_lst(&lst, 4);
    init_lst(&lst, 2);
    init_lst(&lst, 3);
    
    t_list *cpy1 = lst;
    while (cpy1)
    {
        printf("%d->", cpy1->data);
        cpy1 = cpy1->next;
    }
    printf("NUL\n");
    sort_list(lst, ascending);
    while (lst)
    {
        printf("%d->", lst->data);
        t_list *temp = lst;
        lst = lst->next;
        free(temp);
    }

    return (0);
}