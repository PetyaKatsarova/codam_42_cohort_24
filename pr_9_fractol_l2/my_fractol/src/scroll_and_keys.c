/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scroll_and_keys.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:19:23 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/05 16:01:07 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"
// void        key_hook(mlx_key_data_t keydata, t_fractal *fr)
void key_hook(mlx_key_data_t keydata, void *param)
{
    t_fractal *fr = (t_fractal *)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        exit_fr(fr);
    else if (keydata.key == MLX_KEY_LEFT)
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
    // else if (keydata.key == MLX_KEY_M || keydata.key == MLX_KEY_P)
//         // change_iterations(fr, key_code);

    // Redraw fractal after any change
    draw_fr(fr, fr->name);
}

void    zoom(t_fractal *fr, int x, int y, int zoom)
{
    double zoom_level;

    zoom_level = 1.42;
    if (zoom == 1)
    {
        fr->offset_x = (x / fr->zoom + fr->offset_x) - (x / (fr->zoom * zoom_level));
        fr->offset_y = (y / fr->zoom + fr->offset_y) - (y / (fr->zoom * zoom_level));
        fr->zoom *= zoom_level;
    }
    else if (zoom == -1)
    {
        fr->offset_x = (x / fr->zoom + fr->offset_x) - (x / (fr->zoom / zoom_level));
        fr->offset_y = (y / fr->zoom + fr->offset_y) - (y / (fr->zoom / zoom_level));
        fr->zoom /= zoom_level;
    }
}
/*
used for mouse scroll up and down
*/
// void scroll_hook(int mouse_code, int x, int y, void *param)
// {
//     t_fractal *fr = (t_fractal *)param;
     
//     if (mouse_code == SCROLL_UP)
//         zoom(fr, x, y, 1);
//     else if (mouse_code == SCROLL_DOWN)
//         zoom(fr, x, y, -1);
//     draw_fractal(fr, fr->name); // try to do without name
// }

/*
MLX42 doesn't automatically free resources when a window is closed.
We need to properly call mlx_terminate(fr->mlx); to clean up memory.
*/