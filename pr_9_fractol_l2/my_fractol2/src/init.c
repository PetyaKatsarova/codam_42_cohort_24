/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:04:12 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/06 16:46:19 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"


void    init_fr(t_fractal *fr)
{
    fr->x = 0;
    fr->y = 0;
    fr->color = 0x800080FF;
    fr->zoom = 300; //why
    fr->offset_x = -1.21;
    fr->offset_y = -1.21;
    fr->max_iterations = 42; // change??
}

void init_mlx(t_fractal *fr)
{
    fr->mlx = mlx_init(SIZE, SIZE, "Fractals", true);
    if (!fr->mlx)
    {
        free(fr);
        return;
    }

    fr->img = mlx_new_image(fr->mlx, SIZE, SIZE); // too
    fr->buffer_img = mlx_new_image(fr->mlx, SIZE, SIZE);  // Off-screen buffer
    if (!fr->img)
    {
        mlx_terminate(fr->mlx);
        free(fr);
        return;
    }
}
