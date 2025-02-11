#include "../include/fract-ol.h"

void	put_color_to_pixel(t_fractal *fr, int x, int y, int color)
{
	int	*buffer;

	buffer = fr->pointer_to_image;
	buffer[(y * fr->size_line / 4) + x] = color;
}

int	exit_fr(t_fractal *fr)
{
	mlx_destroy_image(fr->mlx, fr->img);
	mlx_destroy_window(fr->mlx, fr->window);
	free(fr->mlx);
	free(fr);
	exit(1);
	return (0);
}

void	change_iterations(t_fractal *fr, int key_code)
{
	if (key_code == M)
	{
		if (fr->max_iterations > 42)
			fr->max_iterations -= 42;
	}
	else if (key_code == P)
	{
		if (fr->max_iterations < 4200)
			fr->max_iterations += 42;
	}
}
