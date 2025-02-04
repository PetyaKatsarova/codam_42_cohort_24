/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   events.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:19:23 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/04 18:29:18 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

int key_hook(int key_code, t_fractal *fr)
{
    if (key_code == ESC)
        exit(1);
    else if (key_code == LEFT)
        fr->offset_x -= STEP / fr->zoom;
    else if (key_code == RIGHT)
        fr->offset_x += STEP / fr->zoom;
    else if (key_code == UP)
        fr->offset_y -= STEP / fr->zoom;
    else if (key_code == DOWN)
        fr->offset_y += STEP / fr->zoom;
    else if (key_code == C)
        fr->color += (255 * 255 * 255) / 100; // why / 100?
    else if (key_code == R)
        init_fr(fr);
    else if (key_code == M || key_code == P)
        // change_iterations(fr, key_code);
    draw_fractal(fr, fr->name);
    return (0);
}