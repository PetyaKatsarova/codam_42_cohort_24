/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: petya <petya@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 13:56:59 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/18 13:11:45 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

static void	rename_fr(t_fractal *fr, int key_code)
{
	if (key_code == KEY_1)
		fr->name = "mandelbrot";
	else if (key_code == KEY_2)
	{
		fr->name = "julia";
		fr->cx = -0.8;
		fr->cy = 0.156;
	}
	else if (key_code == KEY_3)
		fr->name = "tricorn";
	else if (key_code == KEY_4)
		fr->name = "phoenix";
}

/**
 * copies the last byte (grayscale) into Red, Green, and Blue, making the color
 * grayscale.
*/
static void	grey_scale(t_fractal *fr)
{
	int	grayscale;

	fr->color += (255 * 255 * 255) / 100;
	grayscale = (fr->color & 0xFF);
	fr->color = (grayscale << 16) | (grayscale << 8) | grayscale;
}

int	key_hook(int key_code, t_fractal *fr)
{
	if (key_code == ESC)
		exit_fr(fr);
	else if (key_code == LEFT)
		fr->offset_x += 42 / fr->zoom;
	else if (key_code == RIGHT)
		fr->offset_x -= 42 / fr->zoom;
	else if (key_code == UP)
		fr->offset_y += 42 / fr->zoom;
	else if (key_code == DOWN)
		fr->offset_y -= 42 / fr->zoom;
	else if (key_code == R)
		init_fr(fr);
	else if (key_code == C)
		fr->color += (255 * 255 * 255) / 100;
	else if (key_code == B)
		grey_scale(fr);
	else if (key_code == KEY_1 || key_code == KEY_2
		|| key_code == KEY_3 || key_code == KEY_4)
		rename_fr(fr, key_code);
	else if (key_code == M || key_code == P)
		change_precision(fr, key_code);
	draw_fr(fr, fr->name);
	return (0);
}

/**
 * Adjust offsets to keep zoom centered at the mouse position
 */
void	zoom(t_fractal *fr, int x, int y, int zoom)
{
	double	zoom_level;

	zoom_level = 1.05;
	if (zoom == 1)
	{
		fr->offset_x = (x / fr->zoom + fr->offset_x)
			- (x / (fr->zoom * .5));
		fr->offset_y = (y / fr->zoom + fr->offset_y)
			- (y / (fr->zoom * .5));
		fr->zoom *= .5;
	}
	else if (zoom == -1)
	{
		fr->offset_x = (x / fr->zoom + fr->offset_x)
			- (x / (fr->zoom / .5));
		fr->offset_y = (y / fr->zoom + fr->offset_y)
			- (y / (fr->zoom / .5));
		fr->zoom /= .5;
	}
}

int	mouse_hook(int mouse_code, int x, int y, t_fractal *fr)
{
	if (mouse_code == SCROLL_UP)
		zoom(fr, x, y, -1);
	else if (mouse_code == SCROLL_DOWN)
		zoom(fr, x, y, 1);
	draw_fr(fr, fr->name);
	return (0);
}
