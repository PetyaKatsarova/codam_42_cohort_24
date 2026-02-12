/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:04:12 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/28 17:24:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

void	init_fr(t_fractal *fr)
{
	fr->x = 0;
	fr->y = 0;
	fr->color = 0x252525;
	fr->zoom = 200;
	fr->offset_x = -2.21;
	fr->offset_y = -2.21;
	fr->max_iterations = 42;
}

static void	exit_error(const char *msg)
{
	int	len;

	len = ft_strlen(msg);
	write(1, msg, len);
	exit(EXIT_FAILURE);
}

void	init_mlx(t_fractal *fr)
{
	fr->mlx = mlx_init();
	if (!fr->mlx)
		exit_error("Error: MLX initialization failed");
	fr->window = mlx_new_window(fr->mlx, SIZE, SIZE, "Fract-ol");
	if (!fr->window)
		exit_error("Error: Window creation failed");
	fr->img = mlx_new_image(fr->mlx, SIZE, SIZE);
	if (!fr->img)
		exit_error("Error: Image creation failed");
	fr->pointer_to_image = mlx_get_data_addr(fr->img,
			&fr->bits_per_pixel, &fr->size_line, &fr->endian);
	if (!fr->pointer_to_image)
		exit_error("Error: Failed to get image data address");
}
