/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cost.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:09:09 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:09:12 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Calculate the cost of moving each node from B to the correct position in A.
 * cost_b: moves to bring the node to the head of stack B.
 * cost_a: moves to bring the node from stack B to the correct position in A.
 */
void	get_cost(t_stack **list_a, t_stack **list_b)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;
	int		size_a;
	int		size_b;

	tmp_a = *list_a;
	tmp_b = *list_b;
	size_a = list_size(tmp_a);
	size_b = list_size(tmp_b);
	while (tmp_b)
	{
		tmp_b->cost_b = tmp_b->pos;
		if (tmp_b->pos > size_b / 2)
			tmp_b->cost_b = (size_b - tmp_b->pos) * -1;
		tmp_b->cost_a = tmp_b->target_pos;
		if (tmp_b->target_pos > size_a / 2)
			tmp_b->cost_a = (size_a - tmp_b->target_pos) * -1;
		tmp_b = tmp_b->next;
	}
}

/**
 * Finds the node in list B with the cheapest movements
 * and moves it to that position in list(stack) A.
 */
void	do_cheapest_move(t_stack **list_a, t_stack **list_b)
{
	t_stack	*tmp;
	int		cheapest;
	int		cost_a;
	int		cost_b;

	tmp = *list_b;
	cheapest = INT_MAX;
	while (tmp)
	{
		if (abs_val(tmp->cost_a) + abs_val(tmp->cost_b) < abs_val(cheapest))
		{
			cheapest = abs_val(tmp->cost_b) + abs_val(tmp->cost_a);
			cost_a = tmp->cost_a;
			cost_b = tmp->cost_b;
		}
		tmp = tmp->next;
	}
	move(list_a, list_b, cost_a, cost_b);
}
