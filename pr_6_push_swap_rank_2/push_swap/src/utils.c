/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:10:58 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 16:30:58 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* Frees each element in the linked_list and sets the stack pointer to NULL.
* 
* *list:
*    *list accesses the current node of the list.
*    It holds the address of the current node in the linked list (t_stack *).
* tmp:
*    tmp is used to store the address of the next node ((*list)->next).
*    This address is stored directly in tmp, so no dereferencing is needed.
*/

void	free_list(t_stack **list)
{
	t_stack	*temp;

	if (!list || !(*list))
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

/* exit_error:
*   Writes "Error\n" to the standard output after freeing stack a and b.
*	Exits with standard error code 1.
*/
void	exit_error(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_a == NULL || *stack_a != NULL)
		free_list(stack_a);
	if (stack_b == NULL || *stack_b != NULL)
		free_list(stack_b);
	write(2, "Error\n", 6);
	exit (1);
}

/*
* Prints a string to the standard output.
*/

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

/* ft_atoi:
*   Converts a string of chars into a long integer.
*/
long int	ft_atoi(const char *str)
{
	long int	num;
	int			ismin;
	int			i;

	num = 0;
	ismin = 1;
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		ismin *= -1;
		i++;
	}
	while (is_digit(str[i]))
	{
		if (num * ismin > INT_MAX || num * ismin < INT_MIN)
			exit_error(NULL, NULL);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * ismin);
}

/*
* THEORY:
* t_stack **a:
*    a == NULL; or: t_stack **a = NULL;
*    Checks if a (a pointer to a pointer of type t_stack) is NULL.
*    The pointer a itself does not point to a valid memory location.
* *a != NULL:
*    Dereferences a to access the t_stack * it points to.
*    Checks if this t_stack * (the head of the stack) is not NULL, meaning
*    the stack still contains some nodes or is valid.
*/
