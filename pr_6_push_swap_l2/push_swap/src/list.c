/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 18:42:17 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 16:31:26 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Create a new node with the given value.
 * Return: Pointer to the newly created node, or NULL if allocation fails.
 * in malloc fails exit the program: returns error: not necessarily
 * needed but no harm in doing it
 */
t_stack	*create_node(int val)
{
	t_stack	*node;

	node = malloc(sizeof(*node));
	if (!node)
		exit_error(NULL, NULL);
	node->value = val;
	node->index = 0;
	node->cost_a = -1;
	node->cost_b = -1;
	node->pos = -1;
	node->target_pos = -1;
	node->next = NULL;
	return (node);
}

/**
 * Get the size of the linked list.
 * Return: Number of elements in the list.
 */
int	list_size(t_stack *list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

/**
 * Return the last node in the linked list.
 */
t_stack	*get_last(t_stack *list)
{
	while (list && list->next != NULL)
		list = list->next;
	return (list);
}

/**
 * Return the second-to-last node in the linked list.
 */
t_stack	*get_second_last(t_stack *list)
{
	while (list && list->next != NULL && list->next->next != NULL)
		list = list->next;
	return (list);
}

/**
 * Add a new node to the end of the linked list.
 */
void	add_last(t_stack **list, t_stack *node)
{
	t_stack	*last;

	if (!node)
		return ;
	if (!*list)
	{
		*list = node;
		return ;
	}
	last = get_last(*list);
	last->next = node;
}
