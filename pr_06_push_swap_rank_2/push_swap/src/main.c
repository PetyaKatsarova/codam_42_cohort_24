/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/12 16:09:38 by pekatsar      #+#    #+#                 */
/*   Updated: 2024/12/14 16:22:17 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Checks if the list is sorted.
 * Return: 1 if true, 0 if not sorted.
 */
int	is_sorted(t_stack *list)
{
	while (list && list->next)
	{
		if (list->value > list->next->value)
			return (0);
		list = list->next;
	}
	return (1);
}

/**
 * Selects the sorting method depending on the list size.
 */
static void	select_method(t_stack **list_a, t_stack **list_b, int list_size)
{
	if (list_size == 2 && !is_sorted(*list_a))
		sa(list_a);
	else if (list_size == 3)
		tiny_sort(list_a);
	else if (list_size > 3 && !is_sorted(*list_a))
		sort(list_a, list_b);
}

/**
 * Frees a dynamically allocated char ** array.
 */
static void	free_2d_arr(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/* returns 0 if >intmax || < intmin */

/**
 * Splits a single string into arguments and preserves argv[0].
 */
static char	**prepare_arguments(char **argv, int *argc)
{
	char	**split_args;
	char	**new_argv;
	int		split_argc;
	int		i;

	split_args = split_argv(argv[1]);
	if (!split_args)
		exit_error(NULL, NULL);
	split_argc = 0;
	while (split_args[split_argc])
		split_argc++;
	new_argv = malloc((split_argc + 2) * sizeof(char *));
	if (!new_argv)
	{
		free_2d_arr(split_args);
		exit_error(NULL, NULL);
	}
	new_argv[0] = argv[0];
	i = -1;
	while (++i < split_argc)
		new_argv[i + 1] = split_args[i];
	new_argv[split_argc + 1] = NULL;
	free(split_args);
	*argc = split_argc + 1;
	return (new_argv);
}

/**
 * Main function:
 * - Validates input.
 * - Initializes stacks.
 * - Sorts the list using the appropriate method.
 * - Frees allocated memory before exiting.
 * to test: ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG
 * or: make test500
 * valgrind --leak-check=full ./push_swap "1 2 54 3 -9"
 */
int	main(int argc, char **argv)
{
	t_stack	*list_a;
	t_stack	*list_b;
	int		size;
	int		flag;

	flag = 0;
	if (argc == 1)
		return (0);
	if (argc == 2 && ft_strchr(argv[1], ' '))
	{
		argv = prepare_arguments(argv, &argc);
		flag = 1;
	}
	is_all_correct(argc, argv);
	list_b = NULL;
	list_a = populate_list(argc, argv);
	size = list_size(list_a);
	assign_index(list_a, size + 1);
	select_method(&list_a, &list_b, size);
	free_list(&list_a);
	free_list(&list_b);
	if (flag == 1)
		free_argv(argv);
	return (0);
}
