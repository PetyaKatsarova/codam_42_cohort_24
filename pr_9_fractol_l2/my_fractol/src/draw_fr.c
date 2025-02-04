/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_fr.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 16:35:36 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/04 16:48:35 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

int draw_fractal (t_fractal *fr, char *query, double cx, double cy)
{
    fr->x = 0;
    fr->y = 0;
    while (fr->x < SIZE)
    {
        while (fr->y < SIZE)
        {
            if (ft_strncmp(query, "mandel", 7) == 0) // do i need to free?
                calculate_mandelbrot(fr);
            else
                exit_fractal(fr);
        }
        fr->y++;
    }
    fr->x++;
    mlx_put_image_to_window(fr->mlx, fr->window, fr->img, 0, 0);
    return (0);
}