/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/07 18:16:20 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 14:48:54 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * first node is the head, last node is last added
*/
t_stack	*populate_list(int argc, char **argv)
{
	t_stack	*list;
	int		i;
	int		val;

	list = NULL;
	i = 1;
	val = 0;
	while (argc > i)
	{
		val = ft_atoi(argv[i]);
		if (i == 1)
			list = create_node(val);
		else
			add_last(&list, create_node(val));
		i++;
	}
	return (list);
}

/**
 * assign index to node in sorted order: lowest index is 1
*/
void	assign_index(t_stack *list, int list_size)
{
	t_stack	*ptr;
	t_stack	*highest_node;
	int		highest_val;

	while (--list_size > 0)
	{
		ptr = list;
		highest_val = INT_MIN;
		highest_node = NULL;
		while (ptr)
		{
			if (ptr->value == INT_MIN && ptr->index == 0)
				ptr->index = 1;
			if (ptr->value > highest_val && ptr->index == 0)
			{
				highest_val = ptr->value;
				highest_node = ptr;
				ptr = list;
			}
			else
				ptr = ptr->next;
		}
		if (highest_node != NULL)
			highest_node->index = list_size;
	}
}
