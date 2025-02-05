/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:40:33 by palucena          #+#    #+#             */
/*   Updated: 2023/08/28 14:47:29 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fract(t_info *info, char **av)
{
	info->name = check_name(av[1]);
	info->args.real = -1.35;
	info->args.imag = 0;
	if (info->name == 2 && av[2] && av[3])
	{
		info->args.real = ft_atof(av[2]);
		info->args.imag = ft_atof(av[3]);
	}
	info->smooth = 0;
}

void	reset_fract(t_info *info)
{
	info->max_iterations = 30;
	info->zoom = 4;
	if (info->color == -1094795586)
		info->color = 0;
	info->offset_x = -0.5;
	info->offset_y = 0;
	if (info->name == 2)
		info->offset_x = -0.5;
	else if (info->name == 3)
		info->offset_y = -0.4;
	info->palettes = ft_get_palettes();
	info->palette = &info->palettes[info->color];
}

void	mandelship(t_info *info)
{
	info->cx = (info->pos_x - SIZE / 2) * info->zoom / SIZE + info->offset_x;
	info->cy = (info->pos_y - SIZE / 2) * info->zoom / SIZE + info->offset_y;
	info->zx = 0.0;
	info->zy = 0.0;
	fractal(info);
}
 
void	julia(t_info *info)
{
	double	zoom_s;

	zoom_s = info->zoom / SIZE;
	info->cx = info->args.real;
	info->cy = info->args.imag;
	info->zx = (info->pos_x - SIZE / 2) * zoom_s + info->offset_x + 0.5;
	info->zy = (info->pos_y - SIZE / 2) * zoom_s + info->offset_y;
	fractal(info);
}
