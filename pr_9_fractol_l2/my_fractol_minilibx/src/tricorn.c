#include "../include/fract-ol.h"




static void calc_tricorn(t_fractal *fr)
{
    int     i;
    double  x_temp;

    fr->zx = 0.0;
    fr->zy = 0.0;
    fr->cx = (fr->x / fr->zoom) + fr->offset_x;
    fr->cy = (fr->y / fr->zoom) + fr->offset_y;
    i = 0;
    while (++i < fr->max_iterations)
    {
        x_temp = fr->zx * fr->zx - fr->zy * fr->zy + fr->cx;
        fr->zy = -2.0 * fr->zx * fr->zy + fr->cy;
        fr->zx = x_temp;
        if (fr->zx * fr->zx + fr->zy * fr->zy >= __DBL_MAX__)
            break;
    }
    if (i == fr->max_iterations)
        put_color_to_pixel(fr, fr->x, fr->y, 0x000000);
    else
        put_color_to_pixel(fr, fr->x, fr->y, (fr->color * i));
}

void draw_tricorn(void *fr_void)
{
    t_fractal   *fr;

    fr = (t_fractal *)fr_void;
    fr->x = 0;
    fr->y = 0;
    while (fr->x < SIZE)
    {
        while (fr->y < SIZE)
        {
            calc_tricorn(fr);
            fr->y++;
        }
        fr->x++;
        fr->y = 0;
    }
    mlx_put_image_to_window(fr->mlx, fr->window, fr->img, 0, 0);
}
