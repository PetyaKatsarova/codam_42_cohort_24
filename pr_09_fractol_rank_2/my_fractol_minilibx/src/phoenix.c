/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phoenix.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 16:00:00 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/18 12:29:50 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

static void	calc_phoenix(t_fractal *fr)
{
	int		i;
	double	x_temp;
	double	zy_prev;

	fr->name = "phoenix";
	i = 0;
	fr->zx = 0.0;
	fr->zy = 0.0;
	zy_prev = 0.0;
	fr->cx = (fr->x / fr->zoom) + fr->offset_x;
	fr->cy = (fr->y / fr->zoom) + fr->offset_y;
	while (++i < fr->max_iterations)
	{
		x_temp = fr->zx * fr->zx - fr->zy * fr->zy + fr->cx;
		fr->zy = 2. * fr->zx * fr->zy + fr->cy + 0.5 * zy_prev;
		zy_prev = fr->zy;
		fr->zx = x_temp;
		if (fr->zx * fr->zx + fr->zy * fr->zy >= 4)
			break ;
	}
	if (i == fr->max_iterations)
		put_color_to_pixel(fr, fr->x, fr->y, 0x000000);
	else
		put_color_to_pixel(fr, fr->x, fr->y, (fr->color * i));
}

void	populate_px_phoenix(void *fr_void)
{
	t_fractal	*fr;

	fr = (t_fractal *)fr_void;
	fr->x = 0;
	fr->y = 0;
	while (fr->x < SIZE)
	{
		while (fr->y < SIZE)
		{
			calc_phoenix(fr);
			fr->y++;
		}
		fr->x++;
		fr->y = 0;
	}
}
