/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:17:03 by ykarimi       #+#    #+#                 */
/*   Updated: 2025/02/12 22:01:48 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *errormsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(errormsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	free_mlx_data(t_cub3d *cub3d)
{
	if (cub3d->textures->north)
		mlx_delete_texture(cub3d->textures->north);
	if (cub3d->textures->east)
		mlx_delete_texture(cub3d->textures->east);
	if (cub3d->textures->south)
		mlx_delete_texture(cub3d->textures->south);
	if (cub3d->textures->west)
		mlx_delete_texture(cub3d->textures->west);
	if (cub3d->floor_and_ceiling)
		mlx_delete_image(cub3d->mlx, cub3d->floor_and_ceiling);
	if (cub3d->scene)
		mlx_delete_image(cub3d->mlx, cub3d->scene);
}

void	cleanup(t_cub3d *game)
{
	if (game->input)
	{
		if (game->input->map)
		{
			free_grid(game->input->map->grid);
			if (game->input->map->player)
				free(game->input->map->player);
			free(game->input->map);
		}
		free(game->input);
	}
	free_mlx_data(game);
	if (game->render)
		free(game->render);
}

void	end_game(t_cub3d *game, char *message)
{
	printf("%s\n", message);
	cleanup(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
