/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/14 14:09:42 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/19 18:10:27 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

void	put_color_to_pixel(t_fractal *fr, int x, int y, int color)
{
	int	*buffer;

	buffer = fr->pointer_to_image;
	buffer[(y * fr->size_line / 4) + x] = color;
}

/**
 * check all t_fractol fields: cleans only the existing ones & prints
 *  exit msg
 * mlx_destroy_display(fr->mlx); needed only for linux
 * If you only used mlx_init(), then you should not call free(fr->mlx). The MiniLibX library manages that memory internally, and freeing it manually can cause undefined behavior: but chatGBT is wrong: if i dont free(fr->mlx) get still reachable bytes on exit
*/

int	exit_fr(t_fractal *fr)
{
	if (fr->img)
		mlx_destroy_image(fr->mlx, fr->img);
	if (fr->window)
		mlx_destroy_window(fr->mlx, fr->window);
	if (fr->mlx)
	{
		mlx_destroy_display(fr->mlx);
		free(fr->mlx);
	}
	ft_putendl_fd("Clean exit", 1);
	exit(0);
}

/**
 * M: minus: reduces step per zoom: shows less detail, faster
 * P: plus: increases step per zomm: shows more detail, slower
*/
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
