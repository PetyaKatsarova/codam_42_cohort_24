/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 13:10:35 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/15 16:13:32 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

static void	calculate_julia(t_fractal *fr)
{
	int		i;
	double	temp;
	double	scale;

	fr->name = "julia";
	scale = 1.0 / fr->zoom;
	fr->zx = fr->x * scale + fr->offset_x; // changed: / fr->zoom cause * is faster
	fr->zy = fr->y * scale + fr->offset_y;
	i = 0;
	while (++i < fr->max_iterations)
	{
		temp = fr->zx;
		fr->zx = fr->zx * fr->zx - fr->zy * fr->zy + fr->cx;
		fr->zy = 2 * fr->zy * temp + fr->cy;
		if (fr->zx * fr->zx + fr->zy * fr->zy >= 4) // escape early
			break ;
	}
	if (i == fr->max_iterations)
		put_color_to_pixel(fr, fr->x, fr->y, 0x000000);
	else
		put_color_to_pixel(fr, fr->x, fr->y, fr->color * (i % 255));
}

void	populate_px_julia(void *fr_void)
{
	t_fractal	*fr;

	fr = (t_fractal *)fr_void;
	if (!fr)
		exit_fr(fr);
	fr->x = 0;
	fr->y = 0;
	while (fr->x < SIZE)
	{
		fr->y = 0;
		while (fr->y < SIZE)
		{
			calculate_julia(fr);
			fr->y++;
		}
		fr->x++;
	}
}
