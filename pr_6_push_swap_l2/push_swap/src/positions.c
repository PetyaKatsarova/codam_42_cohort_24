/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   positions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:09:53 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:09:55 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * assigns dinamically current position to each node from top/head(first node
 * in) to bottom/tail(last node in);
 *      value:		 3	 0	 9	 1
 *		index:		[3]	[1]	[4]	[2]
 *		position:	<0>	<1>	<2>	<3>
 * in the example above if list b: will cost nothing to push node with position
 * 0 to list a, if we want to push highest value(4, with position 2) will cost
 * us 2 moves to bring it to the top: position indicates how many moves we need
 * to bring the node to the top/head of the list
 */

static void	set_positions(t_stack **list)
{
	t_stack	*temp;
	int		i;

	temp = *list;
	i = 0;
	while (temp)
	{
		temp->pos = i;
		temp = temp->next;
		i++;
	}
}

/**
 * returns the curr position of the node with the lowest index from the list
 */

int	get_pos_lowest_index(t_stack **list)
{
	t_stack	*temp;
	int		lowest_i;
	int		position;

	temp = *list;
	lowest_i = INT_MAX;
	set_positions(list);
	position = temp->pos;
	while (temp)
	{
		if (temp->index < lowest_i)
		{
			lowest_i = temp->index;
			position = temp->pos;
		}
		temp = temp->next;
	}
	return (position);
}

/**
 * returns the best target position in stack a in relation with the index of
 * that node. first: checks if the index can be placed in between nodes in
 * stack a by checking if there is node with bigger index; if not: returns the
 * node with smallest index in a(this would be target position)
 */

static int	get_target(t_stack **a, int ind_b, int target_i, int target_pos)
{
	t_stack	*temp;

	temp = *a;
	while (temp)
	{
		if (temp->index > ind_b && temp->index < target_i)
		{
			target_i = temp->index;
			target_pos = temp->pos;
		}
		temp = temp->next;
	}
	if (target_i != INT_MAX)
		return (target_pos);
	temp = *a;
	while (temp)
	{
		if (temp->index < target_i)
		{
			target_i = temp->index;
			target_pos = temp->pos;
		}
		temp = temp->next;
	}
	return (target_pos);
}

/**
 * assigns target position to each node in linked list(stack) a. this is the
 * spot the node from list b needs to get for the sorting. this is needed to
 * calculate the cost of moving each node to target positon in a;
 */

void	set_target_pos(t_stack **a, t_stack **b)
{
	t_stack	*temp_b;
	int		target;

	temp_b = *b;
	set_positions(a);
	set_positions(b);
	target = 0;
	while (temp_b)
	{
		target = get_target(a, temp_b->index, INT_MAX, target);
		temp_b->target_pos = target;
		temp_b = temp_b->next;
	}
}
