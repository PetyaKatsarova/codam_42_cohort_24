/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 17:01:17 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/04 18:03:55 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

void put_color_to_px(t_fractal *fr, int x, int y, int color)
{
    int *buff;

    buff = fr->pointer_to_image;
    buff[(y * fr->size_line/4) + x] = color;
}

double generate_random_double()
{
    return ((double)(rand() / RAND_MAX) * 3.0 - 1.5);
}

// int exit_fr(t_fractal *fr)
// {
//     mlx_destroy_image(fr->mlx, fr->image)
// }