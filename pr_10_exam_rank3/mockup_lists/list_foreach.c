#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

void list_foreach(t_list *lst, void (*f)(int))
{
	t_list	*cpy;

	cpy = lst;
	while (cpy)
	{
		f(cpy->data);
		cpy = cpy->next;
	}
}

void print_data(int data)
{
	printf("%d->", data);

}
// cc -g -Wall -Wextra -Werror list_foreach.c && ./a.out
//cc -g -Wall -Wextra -Werror list_foreach.c && valgrind --leak-check=full ./a.out
int main()
{
	t_list node3 = {42, NULL};
	t_list node2 = {5, &node3};
	t_list node1 = {-9, &node2};

	list_foreach(&node1, print_data);
}

/*
!!NB!!
You don’t need to free because the nodes are statically allocated on the stack (t_list node1, node2, node3). Only dynamically allocated (malloc) memory requires free().
*/