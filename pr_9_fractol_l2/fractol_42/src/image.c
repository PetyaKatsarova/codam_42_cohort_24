/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:50:15 by palucena          #+#    #+#             */
/*   Updated: 2023/08/31 14:06:23 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_info	*create_window(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->mlx = mlx_init(SIZE, SIZE, "fract-ol", false);
	if (!info->mlx)
		exit(EXIT_FAILURE);
	info->win = mlx_new_image(info->mlx, SIZE, SIZE);
	if (!info->win)
		exit(EXIT_FAILURE);
	reset_fract(info);
	usage();
	mlx_image_to_window(info->mlx, info->win, 0, 0);
	mlx_loop_hook(info->mlx, &hook, (void *)info);
	mlx_scroll_hook(info->mlx, &shook, (void *)info);
	return (info);
}

t_palette	*ft_get_palettes(void)
{
	static t_palette	array[3];

	array[0]
		= (t_palette){5, 0, {0x212121, 0x757575, 0xE0E0E0, 0xEEEEEE, 0x4C4C4C}};
	array[1]
		= (t_palette){5, 0, {0xC0C0C0, 0x777777, 0x4D4D4D, 0x2A2A2A, 0x000000}};
	array[2]
		= (t_palette){5, 0, {0x610B4B, 0x01A9DB, 0xF4FA58, 0xFE642E, 0xB40404}};


	return (array);
}

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_put_pixel(t_info *info, int iter)
{
	t_color		c;
	uint32_t	color;

	if (iter >= info->max_iterations)
	{
		if (info->color == 1)
			mlx_put_pixel(info->win, info->pos_x, info->pos_y, 0xFFFFFFFF);
		else
			mlx_put_pixel(info->win, info->pos_x, info->pos_y, 0x000000FF);
	}
	else
	{
		c = get_color_struct(info, iter);
		color = get_rgba(c.rgba.r, c.rgba.g, c.rgba.b, c.rgba.a);
		mlx_put_pixel(info->win, info->pos_x, info->pos_y, color);
	}
}
