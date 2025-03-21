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

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
    t_list dummmy = {0, NULL}, cpy = *lst;
    int temp = 0s;
    
    do {
    statements
    }while ()

}
