/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_enum_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:03:42 by tischmid          #+#    #+#             */
/*   Updated: 2025/05/28 17:24:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	as_token_type(t_token_type as_token_type)
{
	return ((t_data){.as_token_type = as_token_type, .type = TYPE_TOKEN_TYPE});
}

t_data	as_tree_type(t_tree_type as_tree_type)
{
	return ((t_data){.as_tree_type = as_tree_type, .type = TYPE_TREE_TYPE});
}
