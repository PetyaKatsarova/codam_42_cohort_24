/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reverse_rotate.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:10:07 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:10:10 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * last node becomes first/head
*/
static void	reverse_rotate(t_stack **list)
{
	t_stack	*last;
	t_stack	*second_last;
	t_stack	*temp;

	last = get_last(*list);
	second_last = get_second_last(*list);
	temp = *list;
	*list = last;
	(*list)->next = temp;
	second_last->next = NULL;
}

void	rra(t_stack **a)
{
	reverse_rotate(a);
	ft_putstr("rra\n");
}

void	rrb(t_stack **b)
{
	reverse_rotate(b);
	ft_putstr("rrb\n");
}

void	rrr(t_stack **a, t_stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_putstr("rrr\n");
}
