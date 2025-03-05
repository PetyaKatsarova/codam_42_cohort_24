#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

int	ft_list_size(t_list *begin_list)
{
    int i = 0;
    if (begin_list == 0)
        return (0);
    while (begin_list !=  NULL)
    {
        i++;
        begin_list = begin_list->next;
    }

    return (i - 1); // not to count hte list->next;
}

t_list *new_list(char *data)
{
    t_list *my_list = (t_list *)malloc(sizeof(t_list));
    if (!my_list)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    my_list->data = data;
    my_list->next = NULL;

    return (my_list);
}

t_list *fill_list(char *data, int size)
{
    if (size <= 0)
        return (NULL);
    t_list *head = new_list(data);
    t_list *curr = head;

    for (int i = 0; i < size; i++)
    {
         
        curr->next = new_list(data);
        curr = curr->next; 
    }
    return head;
}


//gcc -g -o my_program my_program.c
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./my_program

int main()
{
    t_list *my_list = fill_list("bla ", 12);
    int len = ft_list_size(my_list);
    printf("size is: %d\n", len);
    t_list *temp;
    while (my_list)
    {
        temp = my_list;
        my_list = my_list->next;
        free(temp);
    }
    return (0);
}