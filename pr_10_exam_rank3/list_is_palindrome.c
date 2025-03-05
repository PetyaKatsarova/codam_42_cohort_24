#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sort_list.h"

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

t_list *reverse_list(t_list *lst)
{
    t_list *prev = NULL, *curr = lst, *next = NULL;

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
    if (!lst || !lst->next) return (1); // empty or single node is palindrome
    t_list *slow = lst, *fast = lst, *cpy, *slow_cpy;

    while (fast && fast->next)
    {
        fast = fast->next->next; // end of lst
        slow = slow->next; // reaches 1/2 of lst
    }
    slow = reverse_list(slow);
    slow_cpy = slow;
    cpy = lst;
    while (slow_cpy != NULL)
    {
        if (slow_cpy->data != cpy->data)
        {
            reverse_list(slow);
            return (0);
        }
        slow_cpy = slow_cpy->next;
        cpy = cpy->next;
    }
    reverse_list(slow);
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
    init_lst(&bla, 1); // comment out if testing not polindrome

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