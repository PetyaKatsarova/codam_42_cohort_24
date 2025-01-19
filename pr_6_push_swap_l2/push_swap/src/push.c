/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:10:01 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:10:03 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * pushes top/head el from stack(list) B to top/head of stack(list) A
*/
static void	push(t_stack **src, t_stack **dest)
{
	t_stack	*tmp;

	if (*src == NULL)
		return ;
	tmp = (*src)->next;
	(*src)->next = *dest;
	*dest = *src;
	*src = tmp;
}

/*
*	Pushes the head(first in) node of stack b to the top(head) of stack a.
*	Prints "pa" to the standard output.
*/
void	pa(t_stack **list_a, t_stack **list_b)
{
	push(list_b, list_a);
	ft_putstr("pa\n");
}

/*
*	Pushes the head(first in) node of stack a to the top(head) of stack b.
*	Prints "pb" to the standard output.
*/
void	pb(t_stack **list_a, t_stack **list_b)
{
	push(list_a, list_b);
	ft_putstr("pb\n");
}
