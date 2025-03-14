#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

int	lst_len (t_list *lst)
{
	int count = 0;
	t_list *cpy = lst;

	while (cpy != NULL)
	{
		cpy = cpy->next;
		count++;
	}
	return (count);
}

t_list	*sort_list(t_list *lst)
{
	t_list *cpy_lst;
	t_list *last_node = NULL;
	int		swapped = 0, temp = 0;

	do {
		cpy_lst = lst;
		swapped = 0;
		while (cpy_lst->next != last_node)
		{
			if (cpy_lst->data > cpy_lst->next->data)
			{
				temp = cpy_lst->data;
				cpy_lst->data = cpy_lst->next->data;
				cpy_lst->next->data = temp;
				swapped = 1;
			}
			cpy_lst = cpy_lst->next;
		}
		last_node = cpy_lst;
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

// cc -Werror -Wextra -Wall list_sort2.c && ./a.out
// cc -g -Werror -Wextra -Wall list_sort2.c && valgrind --leak-check=full ./a.out
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
    mylist = sort_list(mylist);
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