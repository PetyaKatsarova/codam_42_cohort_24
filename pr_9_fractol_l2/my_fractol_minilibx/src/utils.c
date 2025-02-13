#include "../include/fract_ol.h"

void	put_color_to_pixel(t_fractal *fr, int x, int y, int color)
{
	int	*buffer;

	buffer = fr->pointer_to_image;
	buffer[(y * fr->size_line / 4) + x] = color;
}
/**
 * check all t_fractol fields: cleans only the existing ones & prints exit msg
*/

int	exit_fr(t_fractal *fr)
{
	if (fr->mlx && fr->img)
		mlx_destroy_image(fr->mlx, fr->img);
	if (fr->mlx && fr->window)
		mlx_destroy_window(fr->mlx, fr->window);
	if (fr->mlx)
		free(fr->mlx);
	if (fr)
		free(fr);
	write(1, "Clean exit program.", 19);
	exit(1);
	return (0);
}

void	change_precision(t_fractal *fr, int key_code)
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
