/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 15:22:55 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/06 16:47:34 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"
#include <stdio.h>

// void	set_random_julia(double *cx, double *cy)
// {
// 	*cx = generate_random_c();
// 	*cy = generate_random_c();
// }

int	key_hook(int key_code, t_fractal *fractal)
{
	if (key_code == ESC)
		exit(1);
	else if (key_code == LEFT)
		fractal->offset_x -= 42 / fractal->zoom;
	else if (key_code == RIGHT)
		fractal->offset_x += 42 / fractal->zoom;
	else if (key_code == UP)
		fractal->offset_y -= 42 / fractal->zoom;
	else if (key_code == DOWN)
		fractal->offset_y += 42 / fractal->zoom;
	else if (key_code == R)
		init_fr(fractal);
	else if (key_code == C)
		fractal->color += (255 * 255 * 255) / 100;
	// else if (key_code == J)
		// set_random_julia(&fractal->cx, &fractal->cx);
	// else if (key_code == M || key_code == P)
		// change_iterations(fractal, key_code);
	draw_fr(fractal, fractal->name);
	return (0);
}

void	zoom(t_fractal *fr, int x, int y, int zoom)
{
	double	zoom_level;

	zoom_level = 1.42;
	if (zoom == 1)
	{
		fr->offset_x = (x / fr->zoom + fr->offset_x) - (x
				/ (fr->zoom * zoom_level));
		fr->offset_y = (y / fr->zoom + fr->offset_y) - (y
				/ (fr->zoom * zoom_level));
		fr->zoom *= zoom_level;
	}
	else if (zoom == -1)
	{
		fr->offset_x = (x / fr->zoom + fr->offset_x) - (x
				/ (fr->zoom / zoom_level));
		fr->offset_y = (y / fr->zoom + fr->offset_y) - (y
				/ (fr->zoom / zoom_level));
		fr->zoom /= zoom_level;
	}
	else
		return ;
}

int	mouse_hook(int mouse_code, int x, int y, t_fractal *fr)
{
	if (mouse_code == SCROLL_UP)
		zoom(fr, x, y, 1);
	else if (mouse_code == SCROLL_DOWN)
		zoom(fr, x, y, -1);
	draw_fr(fr, fr->name);
	return (0);
}
