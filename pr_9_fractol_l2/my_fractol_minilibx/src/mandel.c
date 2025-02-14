/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandel.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 14:55:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/14 14:12:55 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

static void	calc_mandel(t_fractal *fr)
{
	int		i;
	double	x_temp;

	fr->name = "mandelbrot";
	i = 0;
	fr->zx = 0.0;
	fr->zy = 0.0;
	fr->cx = (fr->x / fr->zoom) + fr->offset_x;
	fr->cy = (fr->y / fr->zoom) + fr->offset_y;
	while (i < fr->max_iterations)
	{
		x_temp = fr->zx * fr->zx - fr->zy * fr->zy + fr->cx;
		fr->zy = 2.0 * fr->zx * fr->zy + fr->cy;
		fr->zx = x_temp;
		if (fr->zx * fr->zx + fr->zy * fr->zy >= __DBL_MAX__)
			break ;
		i++;
	}
	if (i == fr->max_iterations)
		put_color_to_pixel(fr, fr->x, fr->y, 0x000000);
	else
		put_color_to_pixel(fr, fr->x, fr->y, (fr->color * i));
}

void	populate_px_mandel(void *fr_void)
{
	t_fractal	*fr;

	fr = (t_fractal *)fr_void;
	if (!fr)
		exit_fr(fr);
	fr->x = 0;
	fr->y = 0;
	while (fr->x < SIZE)
	{
		while (fr->y < SIZE)
		{
			calc_mandel(fr);
			fr->y++;
		}
		fr->x++;
		fr->y = 0;
	}
}
