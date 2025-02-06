/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandel.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 14:55:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/06 17:25:51 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

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

void	draw_mandel(void *fr_void)
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
}

// static void calc_mandel(t_fractal *fr, int x, int y)
// {
//     int i = 0;
//     double x_temp, cx, cy, zx = 0.0, zy = 0.0;

//     // Correct per-pixel mapping
//     cx = ((x - (SIZE / 2.0)) / (0.5 * fr->zoom * SIZE)) + fr->offset_x;
//     cy = ((y - (SIZE / 2.0)) / (0.5 * fr->zoom * SIZE)) + fr->offset_y;

//     while (++i < fr->max_iterations)
//     {
//         x_temp = zx * zx - zy * zy + cx;
//         zy = 2.0 * zx * zy + cy;
//         zx = x_temp;

//         if (zx * zx + zy * zy >= 4.0)
//             break;
//     }

//     // **Ensure we have an image before drawing**
//     if (fr->img)
//     {
//         if (i == fr->max_iterations)
//             mlx_put_pixel(fr->img, x, y, 0x000000);
//         else
//             mlx_put_pixel(fr->img, x, y, fr->color * i);
//     }
// }

// void draw_mandel(void *fr_void)
// {
//     t_fractal *fr = (t_fractal *)fr_void;

//     // Ensure image is created before drawing
//     if (!fr->img)
//         fr->img = mlx_new_image(fr->mlx, SIZE, SIZE);

//     for (int x = 0; x < SIZE; x++)
//     {
//         for (int y = 0; y < SIZE; y++)
//         {
//             calc_mandel(fr, x, y);
//         }
//     }

//     // **Refresh the image in the window**
//     mlx_image_to_window(fr->mlx, fr->img, 0, 0);
// }

