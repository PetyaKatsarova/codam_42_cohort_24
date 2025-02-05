/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:08:36 by palucena          #+#    #+#             */
/*   Updated: 2023/07/29 15:25:51 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_fractal(t_info *info)
{
	info->pos_y = 0;
	while (info->pos_y < SIZE)
	{
		info->pos_x = -1;
		while (++info->pos_x < SIZE)
		{
			if (info->name == 1 || info->name == 3)
				mandelship(info);
			else if (info->name == 2)
				julia(info);
		}
		info->pos_y++;
	}
}

void	fractal(t_info *info)
{
	double	tmp;
	int		i;

	i = 1;
	while (i <= info->max_iterations)
	{
		if (info->name == 3)
		{
			info->zx = fabs(info->zx);
			info->zy = fabs(info->zy);
		}
		tmp = info->zx * info->zx - info->zy * info->zy + info->cx;
		info->zy = 2 * info->zx * info->zy + info->cy;
		info->zx = tmp;
		if (info->zx * info->zx + info->zy * info->zy >= LIMIT * 2)
			break ;
		i++;
	}
	ft_put_pixel(info, i);
}

/* void	el4(t_info *info)
{
	double	cx;
	double	cy;
	double	tmp;
	int		i;

	cx = (info->pos_x - SIZE / 2) * info->zoom / SIZE + info->offset_x;
	cy = (info->pos_y - SIZE / 2) * info->zoom / SIZE + info->offset_y;
	i = 1;
	info->zx = 0.0;
	info->zy = 0.0;
	while (i <= info->max_iterations)
	{
		tmp = info->zx * info->zx - info->zy * info->zy + cx;
		info->zy = -2 * info->zx * info->zy + cy;
		info->zx = tmp;
		if (fabs(info->zx) + fabs(info->zy) >= 2.0)
			break ;
		i++;
	}
	draw_pixel(info, i);
} */ // Esto es un fractal?

/* void	ese_raro(t_info *info)
{
	double	x;
	double	y;
	double	z;
	double	tmp;
	int		i;

	x = SIZE / (-2) + info->pos_x;
	y = SIZE / (-2) + info->pos_y;
	info->zx = 0.0;
	info->zy = 0.0;
	i = 0;
	while (i <= info->max_iterations)
	{
		tmp = info->zx * info->zx - info->zy * info->zy + x * 0.02;
		info->zy = 2 * info->zx * info->zy + y * 0.02;
		info->zx = tmp;
		z = info->zx + info->zy;
		if (z >= __DBL_MAX__ || z * (-1) >= __DBL_MAX__)
			break ;
		i++;
	}
	draw_pixel(info, i);
} */ // Pseudo fractal aleatorio encontrado sin querer
