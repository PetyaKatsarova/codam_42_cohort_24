/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:10:21 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:22:37 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Pushes the smallest values first (keeps the last 3),
 *  helping with sorting efficiently.
 */
static void	push_all_save3(t_stack **a, t_stack **b)
{
	int	size;
	int	pushed;
	int	i;

	size = list_size(*a);
	pushed = 0;
	i = 0;
	while (size > 6 && size > i && (size / 2) > pushed)
	{
		if ((size / 2) >= (*a)->index)
		{
			pb(a, b);
			pushed++;
		}
		else
			ra(a);
		i++;
	}
	while (size - pushed > 3)
	{
		pb(a, b);
		pushed++;
	}
}

/**
 * Rotates or reverse rotates stack A to put the lowest position
 *  as the head of the stack.
 */
static void	shift_list(t_stack **list)
{
	int	lowest_pos;
	int	size;

	lowest_pos = get_pos_lowest_index(list);
	size = list_size(*list);
	if (lowest_pos > (size / 2))
	{
		while (lowest_pos < size)
		{
			rra(list);
			lowest_pos++;
		}
	}
	else
	{
		while (lowest_pos > 0)
		{
			ra(list);
			lowest_pos--;
		}
	}
}

/**
 * Sorting algorithm for a stack larger than 3.
 * - Push everything but 3 numbers to stack B.
 * - Sort the 3 numbers left in stack A.
 * - Calculate the most cost-effective move.
 * - Shift elements until stack A is in order.
 */
void	sort(t_stack **stack_a, t_stack **stack_b)
{
	push_all_save3(stack_a, stack_b);
	tiny_sort(stack_a);
	while (*stack_b)
	{
		set_target_pos(stack_a, stack_b);
		get_cost(stack_a, stack_b);
		do_cheapest_move(stack_a, stack_b);
	}
	if (!is_sorted(*stack_a))
		shift_list(stack_a);
}
