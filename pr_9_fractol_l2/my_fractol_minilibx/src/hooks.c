/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:22:55 by pekatsar          #+#    #+#             */
/*   Updated: 2025/02/12 18:26:59 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"
#include <stdio.h>

int	key_hook(int key_code, t_fractal *fr)
{
	if (key_code == ESC)
		exit(1);
	else if (key_code == LEFT)
		fr->offset_x -= 42 / fr->zoom;
	else if (key_code == RIGHT)
		fr->offset_x += 42 / fr->zoom;
	else if (key_code == UP)
		fr->offset_y -= 42 / fr->zoom;
	else if (key_code == DOWN)
		fr->offset_y += 42 / fr->zoom;
	else if (key_code == R)
		init_fr(fr);
	else if (key_code == C)
		fr->color += (255 * 255 * 255) / 100;
	else if (key_code == B)
	{
		fr->color += (255 * 255 * 255) / 100;
		int grayscale = (fr->color & 0xFF); // Extract lowest byte
    	fr->color = (grayscale << 16) | (grayscale << 8) | grayscale;
	}
	else if (key_code == M || key_code == P)
		change_iterations(fr, key_code);
	draw_fr(fr, fr->name);
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
