/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:04:12 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/13 17:24:19 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

void	init_fr(t_fractal *fr)
{
	fr->x = 0;
	fr->y = 0;
	fr->color = 0x3A5F7D;
	fr->zoom = 300;
	fr->offset_x = -2.42;
	fr->offset_y = -2.42;
	fr->max_iterations = 42;
}

static void	exit_error(const char *msg)
{
	int	len;

	len = ft_strlen(msg);
	write(1, msg, len);
	exit(EXIT_FAILURE);
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		exit_error("Error: MLX initialization failed");
	fractal->window = mlx_new_window(fractal->mlx, SIZE, SIZE, "Fract-ol");
	if (!fractal->window)
		exit_error("Error: Window creation failed");
	fractal->img = mlx_new_image(fractal->mlx, SIZE, SIZE);
	if (!fractal->img)
		exit_error("Error: Image creation failed");
	fractal->pointer_to_image = mlx_get_data_addr(fractal->img,
			&fractal->bits_per_pixel, &fractal->size_line, &fractal->endian);
	if (!fractal->pointer_to_image)
		exit_error("Error: Failed to get image data address");
}
