/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_position.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@codam.student.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 15:06:03 by diwalaku      #+#    #+#                 */
/*   Updated: 2025/02/12 22:01:03 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_n_and_s(t_render *render, t_player *player)
{
	if (player->orientation == 'N')
	{
		render->player_dir.x = 0;
		render->player_dir.y = -1;
		render->plane.x = -0.66;
		render->plane.y = 0;
	}
	else
	{
		render->player_dir.x = 0;
		render->player_dir.y = 1;
		render->plane.x = 0.66;
		render->plane.y = 0;
	}
}

// Map's origin (0, 0) is top left corner.
// Y is vertical, X is horizontal
// the plane is the camera plane that represents the screen and it always runs
// perpendicular to our direction
static void	set_direction_and_plane(t_render *render, t_player *player)
{
	if (player->orientation == 'N' || player->orientation == 'S')
		set_n_and_s(render, player);
	else if (player->orientation == 'E')
	{
		render->player_dir.x = 1;
		render->player_dir.y = 0;
		render->plane.x = 0;
		render->plane.y = -0.66;
	}
	else if (player->orientation == 'W')
	{
		render->player_dir.x = -1;
		render->player_dir.y = 0;
		render->plane.x = 0;
		render->plane.y = 0.66;
	}
}

// Need to check which variables we need in here.
// Probably angle, FOV etc as well.
t_render	*set_variables(t_cub3d *cub3d)
{
	t_render	*render;

	render = ft_calloc(1, sizeof(*render));
	if (!render)
		return (NULL);
	render->player_pos.x = (double)cub3d->input->map->player->x + 0.5;
	render->player_pos.y = (double)cub3d->input->map->player->y + 0.5;
	set_direction_and_plane(render, cub3d->input->map->player);
	return (render);
}
