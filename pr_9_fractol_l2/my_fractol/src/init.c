/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:04:12 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/04 18:11:24 by pekatsar      ########   odam.nl         */
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
    fr->mlx = mlx_init(WIDTH, HEIGHT, "Hellow W", true);
    fr->window = mlx_new_window(fr->mlx, SIZE, SIZE, "FRACT-OL");
    fr->image = mlx_new_image(fr->mlx, SIZE, SIZE);
    fr->pointer_to_image = mlx_get_data_addr(fr->image,
                                        &fr->bpp,
                                        &fr->size_line,
                                        &fr->end);
}
