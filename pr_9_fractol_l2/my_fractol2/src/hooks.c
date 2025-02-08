/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 15:22:55 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/06 16:47:34 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"
#include <stdio.h>

/*
    frees resources and exits: for closing btns
 */
void close_hook(void *param)
{
    t_fractal *fr = (t_fractal *)param;
    mlx_terminate(fr->mlx);
    free(fr);
    exit(EXIT_SUCCESS);
}

static void zoom(t_fractal *fr, int x, int y, double zoom_factor)
{
    double zoom_level;

    zoom_level = 1.1; //1.42;
    if (zoom_factor > 0) 
    {
        fr->offset_x = (x / fr->zoom + fr->offset_x) - (x / (fr->zoom * zoom_level));
        fr->offset_y = (y / fr->zoom + fr->offset_y) - (y / (fr->zoom * zoom_level));
        fr->zoom *= zoom_level;
    }
    else if (zoom_factor < 0)  // Scroll down (zoom out)
    {
        fr->offset_x = (x / fr->zoom + fr->offset_x) - (x / (fr->zoom / zoom_level));
        fr->offset_y = (y / fr->zoom + fr->offset_y) - (y / (fr->zoom / zoom_level));
        fr->zoom /= zoom_level;
    }
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_fractal *fr = (t_fractal *)param;

    if (keydata.key == MLX_KEY_LEFT)
        fr->offset_x -= STEP / fr->zoom;
    else if (keydata.key == MLX_KEY_RIGHT)
        fr->offset_x += STEP / fr->zoom;
    else if (keydata.key == MLX_KEY_UP)
        fr->offset_y -= STEP / fr->zoom;
    else if (keydata.key == MLX_KEY_DOWN)
        fr->offset_y += STEP / fr->zoom;
    else if (keydata.key == MLX_KEY_C)
        fr->color += (255 * 255 * 255) / 100; // Color adjustment
    else if (keydata.key == MLX_KEY_R)
        init_fr(fr);
    if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
        close_hook(param);
    // else if (keydata.key == MLX_KEY_M || keydata.key == MLX_KEY_P)
//         // change_iterations(fr, key_code);

    draw_fr(fr, fr->name);
}

void scroll_hook(double xdelta, double ydelta, void *param)
{
    (void)xdelta;
    t_fractal *fr = (t_fractal *)param;
    int x, y;

    mlx_get_mouse_pos(fr->mlx, &x, &y);
    if (ydelta != 0)
        zoom(fr, x, y, ydelta);
    draw_fr(fr, fr->name);
}



