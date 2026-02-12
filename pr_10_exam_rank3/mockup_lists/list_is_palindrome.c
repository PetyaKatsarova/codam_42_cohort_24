#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Write a function that checks if a linked list is a palindrome.

int is_palindrome(t_list *lst);
Example
Input
1 -> 2 -> 3 -> 2 -> 1 -> NULL
Output
1 (Palindrome)
Input
1 -> 2 -> 3 -> 4 -> NULL
Output
0 (Not a palindrome)
Constraints
Solve it without extra memory (O(1) space complexity).
The function must modify the list only temporarily.
*/

typedef struct s_list t_list;

struct s_list
{
	int     data;
	t_list  *next;
};

t_list *reverse_lst(t_list *lst)
{
    t_list  *prev = NULL;
    t_list  *curr = lst;
    t_list  *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return (prev);
}

int is_palindrome(t_list *lst)
{
    if (!lst || !lst->next) return (1);
    //empty or single node r polindrome
    t_list *slow = lst;
    t_list *fast = lst;
    t_list *reversed_slow, *cpy;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next; // get second half of lst
    }
    slow = reverse_lst(slow);
    reversed_slow = slow;
    cpy = lst;
    while (reversed_slow != NULL)
    {
        if (reversed_slow->data != cpy->data)
        {
            reverse_lst(slow);
            return (0); // not polindrome
        }
        reversed_slow = reversed_slow->next;
        cpy = cpy->next;
    }
    reverse_lst(slow);
    return (1);
}

void init_lst(t_list **lst, int value)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node) return;
    node->data = value;
    node->next = NULL;
    t_list *cpy;
    
    if (!*lst)
    {
        *lst = node;
        return;
    }
    cpy = *lst;
    while (cpy->next != NULL)
        cpy = cpy->next;
    cpy->next = node;
}
// cc -Werror -Wextra -Wall list_is_palindrome.c && ./a.out
// cc -g -Werror -Wextra -Wall list_is_palindrome.c && valgrind --leak-check=full ./a.out
int main()
{
    t_list  *temp = NULL;
    t_list  *bla = NULL;
    int     is_p;

    init_lst(&bla, 1);
    init_lst(&bla, 2);
    init_lst(&bla, 3);
    init_lst(&bla, 2);
    // init_lst(&bla, 1); // comment out if testing not polindrome

    t_list *cpy = bla;
    while (cpy)
    {
        printf("%d -> ", cpy->data);
        cpy = cpy->next;
    }
    printf("NULL\n");
    is_p = is_palindrome(bla);
    printf("is_palindrome = %d\n", is_p);
    while (bla != NULL)
    {
        temp = bla;
        printf("%d -> ", bla->data);
        bla = bla->next;
        free(temp);
    }
    printf("NULL\n");
    return (0);
}

/*
Uses Floyd’s Tortoise and Hare algorithm:
slow moves one step at a time.
fast moves two steps at a time.
When fast reaches the end, slow is at the middle.
*/