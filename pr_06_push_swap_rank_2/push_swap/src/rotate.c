/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:10:15 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:10:17 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * rotate each node 1 place fwd (first becomes last)
 */
static void	rotate(t_stack **list)
{
	t_stack	*temp;
	t_stack	*last;

	if (!list || !(*list) || !((*list)->next))
		return ;
	temp = *list;
	*list = (*list)->next;
	last = get_last(*list);
	last->next = temp;
	temp->next = NULL;
}

void	ra(t_stack **a)
{
	rotate(a);
	ft_putstr("ra\n");
}

void	rb(t_stack **b)
{
	rotate(b);
	ft_putstr("rb\n");
}

void	rr(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
	ft_putstr("rr\n");
}
