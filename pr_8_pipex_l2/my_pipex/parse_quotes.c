/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:08:52 by petya             #+#    #+#             */
/*   Updated: 2025/01/19 21:16:35 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	count_tokens(char **arr)
{
	int count = 0;
	while (arr[count])
		count++;
	return (count);
}

// Merge quoted and unquoted parts into final result
int	process_split_parts(char **quote_split, char **final_result)
{
	char	**space_split;
	int		i, j, k;

	k = 0;
	i = -1;
	while (quote_split[++i])
	{
		if (i % 2 == 0)
		{
			space_split = ft_split(quote_split[i], ' ');
			j = -1;
			while (space_split[++j])
				final_result[k++] = ft_strdup(space_split[j]);
			free_dbl_ptr(space_split);
		}
		else
			final_result[k++] = ft_strdup(quote_split[i]);
	}
	final_result[k] = NULL;
	return (1);
}