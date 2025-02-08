#include "../include/fract-ol.h"

static void calculate_julia(t_fractal *fr)
{
    int i;
    double temp;
    fr->name = "julia";
    fr->zx = fr->x / fr->zoom + fr->offset_x;
    fr->zy = fr->y / fr->zoom + fr->offset_y;
    i = 0;
    while (++i < fr->max_iterations)
    {
        temp = fr->x;
        fr->zx = fr->zx * fr->zx - fr->zy * fr->zy + fr->cx;
        fr->zy = 2 * fr->zy * temp + fr->cy;
        if (fr->zx * fr->zx + fr->zy * fr->zy >= __DBL_MAX__)
            break;
    }
    if (i == fr->max_iterations)
        mlx_put_pixel(fr->buffer_img, fr->x, fr->y, 0x000000);
    else
        mlx_put_pixel(fr->buffer_img, fr->x, fr->y, fr->color*(i % 255));
}

void	draw_julia(void *fr_void)
{
	t_fractal	*fr;

	fr = (t_fractal *)fr_void;
	fr->x = 0;
	fr->y = 0;
	while (fr->x < SIZE)
	{
		while (fr->y < SIZE)
		{
			calculate_julia(fr);
			fr->y++;
		}
		fr->x++;
		fr->y = 0;
	}
    mlx_image_to_window(fr->mlx, fr->buffer_img, 0, 0);
}
