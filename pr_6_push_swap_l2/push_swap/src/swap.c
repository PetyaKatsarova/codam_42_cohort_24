/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:10:41 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/12 16:10:44 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Swaps only the index and value of two nodes.
 * Does not swap the entire nodes as the rest is all set to -1,
 * and the pointer to the next node stays the same.
 */
static void	swap(t_stack *list)
{
	int	num;

	if (list == NULL || list->next == NULL)
		return ;
	num = list->value;
	list->value = list->next->value;
	list->next->value = num;
	num = list->index;
	list->index = list->next->index;
	list->next->index = num;
}

/**
 * Swaps the top/head two elements in stack A.
 */
void	sa(t_stack **list)
{
	swap(*list);
	ft_putstr("sa\n");
}

/**
 * Swaps the top/head two elements in stack B.
 */
void	sb(t_stack **list)
{
	swap(*list);
	ft_putstr("sb\n");
}

/**
 * Swaps the top two elements in both stacks A and B.
 */
void	ss(t_stack **list_a, t_stack **list_b)
{
	swap(*list_a);
	swap(*list_b);
	ft_putstr("ss\n");
}
