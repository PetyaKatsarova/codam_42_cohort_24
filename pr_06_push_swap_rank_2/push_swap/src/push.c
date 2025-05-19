/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:10:01 by pekatsar          #+#    #+#             */
/*   Updated: 2025/03/03 20:28:58 by petya            ###   ########.fr       */
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
	tmp = (*src)->next; // holds the second node(if we start from a, this is b)
	(*src)->next = *dest; // set second node to top of dest(x if second is y)
	*dest = *src; // sets a(first el) the top of dest
	*src = tmp; // src points to b(second el)
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
