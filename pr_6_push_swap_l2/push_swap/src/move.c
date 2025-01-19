/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:09:46 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:22:56 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Reverse rotates both stacks until one of them is in position.
 * Cost is negative, meaning both nodes are in the second (tail) half
 * of the list. Cost increases toward 0 with each reverse rotation.
 */
static void	reverse_rotations_both(t_stack **list_a, t_stack **list_b,
			int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		rrr(list_a, list_b);
	}
}

/**
 * Rotates both stacks until one of them is in position.
 * Cost is positive, meaning both nodes are in the head (top) half
 * of the list. Cost decreases toward 0 with each rotation.
 */
static void	rotations_both(t_stack **list_a, t_stack **list_b,
			int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		rr(list_a, list_b);
	}
}

/**
 * Rotates stack A until it reaches position 0.
 * If cost is negative, reverse rotate. If positive, rotate. If cost == 0,
 * no move is made.
 */
static void	rotations_a(t_stack **list_a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ra(list_a);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rra(list_a);
			(*cost)++;
		}
	}
}

/**
 * Rotates stack B until it reaches position 0.
 * If cost is negative, reverse rotate. If positive, rotate. If cost == 0,
 * no move is made.
 */
static void	rotations_b(t_stack **list_b, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			rb(list_b);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rrb(list_b);
			(*cost)++;
		}
	}
}

/**
 * Chooses a move to place a node from stack B in the correct
 * position in stack A.
 * If both costs are positive or negative, simultaneous moves are made on both
 * stacks. Otherwise, the stacks are rotated separately before pushing the top
 * of stack B to stack A.
 */
void	move(t_stack **list_a, t_stack **list_b, int cost_a, int cost_b)
{
	if (cost_a > 0 && cost_b > 0)
		rotations_both(list_a, list_b, &cost_a, &cost_b);
	else if (cost_a < 0 && cost_b < 0)
		reverse_rotations_both(list_a, list_b, &cost_a, &cost_b);
	rotations_a(list_a, &cost_a);
	rotations_b(list_b, &cost_b);
	pa(list_a, list_b);
}
