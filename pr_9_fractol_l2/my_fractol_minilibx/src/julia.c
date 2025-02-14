/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 13:10:35 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/14 14:11:48 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

static void	calculate_julia(t_fractal *fr)
{
	int		i;
	double	temp;

	fr->name = "julia";
	fr->zx = fr->x / fr->zoom + fr->offset_x;
	fr->zy = fr->y / fr->zoom + fr->offset_y;
	i = 0;
	while (++i < fr->max_iterations)
	{
		temp = fr->zx;
		fr->zx = fr->zx * fr->zx - fr->zy * fr->zy + fr->cx;
		fr->zy = 2 * fr->zy * temp + fr->cy;
		if (fr->zx * fr->zx + fr->zy * fr->zy >= __DBL_MAX__)
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
