/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:04:12 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/13 12:39:15 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

void    init_fr(t_fractal *fr)
{
    fr->x = 0;
    fr->y = 0;
    fr->color = 0xFFD3D3D3;
    fr->zoom = 300;
    // put in center of window
    fr->offset_x = -2.42;
    fr->offset_y = -2.42;
    fr->max_iterations = 42;
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx, SIZE, SIZE, "Fract-ol");
	fractal->img = mlx_new_image(fractal->mlx, SIZE, SIZE);
	fractal->pointer_to_image = mlx_get_data_addr(fractal->img,
			&fractal->bits_per_pixel,
			&fractal->size_line,
			&fractal->endian);
}
