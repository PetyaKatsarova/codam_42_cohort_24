#include <stdio.h>
#include <stdlib.h>

typedef struct  s_list
{
    int             data;
    struct s_list  *next;
}       t_list;

/*
Allocate memory for a new node
Assign the given data
Insert it at the end of the list
Returns the newly created node, while added to the list the new node
*/
t_list *init(t_list **head, int new_data)
{
    t_list *new = (t_list *) malloc(sizeof(t_list));
    t_list *last = *head;

    if (!new) return NULL;
    new->data = new_data;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
        return new;
    }

    while (last->next != NULL)
        last = last->next;
    last->next = new;
    return new;
}

void free_list(t_list *head)
{
    t_list *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
/*
cc llist_tutorial.c && ./a.out
cc -g llist_tutorial.c && valgrind --leak-check=full ./a.out
*/
int main()
{
    t_list  *head = NULL;
    int     count = 0;
        
    init(&head, 5);
    init(&head, 3);
    init(&head, 8);

    // !! You modify head while traversing it, losing the reference to the actual start of the list.
    t_list  *temp = head;

    while (temp != NULL)
    {
        printf("[%d] -> %d\n", ++count, temp->data);
        temp = temp->next;
    }
    free_list(head);
    return (0);
}