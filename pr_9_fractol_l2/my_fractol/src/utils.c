/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 17:01:17 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/05 15:04:26 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

void put_color_to_px(t_fractal *fr, int x, int y, int color)
{
    int *buff;

    buff = fr->pointer_to_img;
    buff[(y * fr->bytes_per_row/4) + x] = color;
}

double generate_random_double()
{
    return ((double)(rand() / RAND_MAX) * 3.0 - 1.5);
}

void exit_fr(void *param)
{
    t_fractal *fr = (t_fractal *)param;
    if (!fr)
        return;

    if (fr->img)
        mlx_delete_image(fr->mlx, fr->img);
    if (fr->mlx)
        mlx_terminate(fr->mlx);

    free(fr);
    exit(0);
}