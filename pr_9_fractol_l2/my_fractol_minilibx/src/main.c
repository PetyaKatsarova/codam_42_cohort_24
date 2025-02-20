/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:14:57 by pekatsar          #+#    #+#             */
/*   Updated: 2025/02/20 14:43:33 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

/**
 * if it doesnt work on wsl, type DISPLAY=:0 ./fract-ol 1
*/

static void	add_julia_c(t_fractal *fr, int argc, char **argv)
{
	double	d1;
	double	d2;

	d1 = -1;
	d2 = -1;
	if (ft_strncmp(argv[1], "julia", 5) == 0
		|| ft_strncmp(argv[1], "2", 1) == 0)
	{
		if (argc == 4)
		{
			d1 = str_to_double(argv[2]);
			d2 = str_to_double(argv[3]);
			fr->cx = d1;
			fr->cy = d2;
		}
		else
		{
			fr->cx = -0.8;
			fr->cy = 0.156;
		}
	}
}

int	draw_fr(t_fractal *fr, char *name)
{
	if (ft_strncmp(name, "mandelbrot", 10) == 0
		|| ft_strncmp(name, "1", 1) == 0)
		populate_px_mandel(fr);
	else if (ft_strncmp(name, "julia", 5) == 0
		|| ft_strncmp(name, "2", 1) == 0)
		populate_px_julia(fr);
	else if (ft_strncmp(name, "tricorn", 7) == 0
		|| ft_strncmp(name, "3", 1) == 0)
		populate_px_tricorn(fr);
	else if (ft_strncmp(name, "phoenix", 7) == 0
		|| ft_strncmp(name, "4", 1) == 0)
		populate_px_phoenix(fr);
	else
	{
		ft_putendl_fd("Choose from: mandelbrot, julia, tricorn or phoenix", 1);
		exit_fr(fr);
	}
	mlx_put_image_to_window(fr->mlx, fr->window, fr->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int			is_valid_i;
	t_fractal	fr;

	is_valid_i = is_valid_input(argc, argv);
	if (is_valid_i == 1)
	{
		add_julia_c(&fr, argc, argv);
		init_fr(&fr);
		init_mlx(&fr);
		mlx_key_hook(fr.window, key_hook, &fr);
		mlx_mouse_hook(fr.window, mouse_hook, &fr);
		mlx_hook(fr.window, 17, 0L, exit_fr, &fr);
		draw_fr(&fr, argv[1]);
		mlx_loop(fr.mlx);
	}
	return (0);
}
