/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandel.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 14:55:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/06 15:19:23 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

/*
fractal->pointer_to_image holds the raw pixel buffer of the image.
Convert (x, y) to a 1D index in the buffer:

buffer[(y * fractal->size_line / 4) + x] = color;

    size_line is the number of bytes per row.
    /4 is used because each pixel is 4 bytes (RGBA, 32-bit).
    y * (size_line / 4) + x calculates the correct pixel index.
*/

// static void	put_color_to_pixel(t_fractal *fractal, int x, int y, int color)
// {
// 	int	*buffer;

// 	buffer = fractal->pointer_to_image;
// 	buffer[(y * fractal->size_line / 4) + x] = color;

// Old MLX (Your Code)	MLX42 (New)
// Uses mlx_get_data_addr() to access raw pixel buffer	No need for mlx_get_data_addr(), directly modifies image
// Modifies memory directly (pointer_to_image)	Uses mlx_put_pixel() to draw pixels safely
// Requires size_line and pixel format knowledge	MLX42 abstracts this, handles it internally
// }



static void calc_mandel(t_fractal *fr)
{
    int		i;
	double	x_temp;

	fr->name = "mandel";
	i = 0;
	fr->zx = 0.0;
	fr->zy = 0.0;
	fr->cx = (fr->x / fr->zoom) + fr->offset_x;
	fr->cy = (fr->y / fr->zoom) + fr->offset_y;
	while (++i < fr->max_iterations)
	{
		x_temp = fr->zx * fr->zx - fr->zy * fr->zy
			+ fr->cx;
		fr->zy = 2. * fr->zx * fr->zy + fr->cy;
		fr->zx = x_temp;
		if (fr->zx * fr->zx + fr->zy
			* fr->zy >= __DBL_MAX__)
			break ;
	}
	if (i == fr->max_iterations)
        mlx_put_pixel(fr->img, fr->x, fr->y, 0x000000);
	else
        mlx_put_pixel(fr->img, fr->x, fr->y, fr->color * i);
                
}

void	*draw_mandel(void *fr_void)
{
	t_fractal	*fr;

	fr = (t_fractal *)fr_void;
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
    mlx_image_to_window(fr->mlx, fr->img, 0, 0);
	return (NULL);
}