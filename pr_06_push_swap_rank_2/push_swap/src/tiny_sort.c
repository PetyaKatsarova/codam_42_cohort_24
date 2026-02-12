/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tiny_sort.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:10:50 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:12:59 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Returns the highest index from a linked list of nodes with index property.
 */
static int	get_highest_index(t_stack *list)
{
	int	highest_index;

	highest_index = list->index;
	while (list)
	{
		if (list->index > highest_index)
			highest_index = list->index;
		list = list->next;
	}
	return (highest_index);
}

/**
 * Sorts a stack of 3 numbers in 2 or fewer moves. The sorting is done by index.
 */
void	tiny_sort(t_stack **list)
{
	int	highest_index;

	if (is_sorted(*list))
		return ;
	highest_index = get_highest_index(*list);
	if ((*list)->index == highest_index)
		ra(list);
	else if ((*list)->next->index == highest_index)
		rra(list);
	if ((*list)->index > (*list)->next->index)
		sa(list);
}
