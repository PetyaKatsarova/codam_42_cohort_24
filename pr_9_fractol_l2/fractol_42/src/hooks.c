/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:41:45 by palucena          #+#    #+#             */
/*   Updated: 2023/08/27 15:42:29 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	hook3(t_info *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_Z))
		info->max_iterations -= 5;
	if (mlx_is_key_down(info->mlx, MLX_KEY_X))
		info->max_iterations += 5;
	if (mlx_is_key_down(info->mlx, MLX_KEY_4))
	{
		info->color = 0;
		info->palette = &info->palettes[info->color];
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_5))
	{
		info->color = 1;
		info->palette = &info->palettes[info->color];
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_6))
	{
		info->color = 2;
		info->palette = &info->palettes[info->color];
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
}

void	hook2(t_info *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_1))
	{
		info->name = 1;
		reset_fract(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_2))
	{
		info->name = 2;
		reset_fract(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_3))
	{
		info->name = 3;
		reset_fract(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		info->smooth = 0;
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		info->smooth = 1;
	hook3(info);
}

void	hook(void	*param)
{
	t_info	*info;
	t_move	m;

	info = param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_UP))
		info->offset_y += -(LIMIT * info->zoom * 0.02);
	if (mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
		info->offset_y -= -(LIMIT * info->zoom * 0.02);
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		info->offset_x += LIMIT * info->zoom * 0.02;
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		info->offset_x -= LIMIT * info->zoom * 0.02;
	if (mlx_is_key_down(info->mlx, MLX_KEY_J) && info->name == 2)
	{
		mlx_get_mouse_pos(info->mlx, &m.mx, &m.my);
		m.d_mx = m.mx - SIZE / 2;
		m.d_my = m.my - SIZE / 2;
		info->args.real = m.d_mx / 100;
		info->args.imag = m.d_my / 100;
		reset_fract(info);
	}
	hook2(info);
	print_fractal(info);
}

void	shook(double x, double y, void *param)
{
	t_info	*info;
	t_move	m;

	info = (t_info *)param;
	(void)x;
	mlx_get_mouse_pos(info->mlx, &m.mx, &m.my);
	if (m.mx < 0 || m.mx >= SIZE || m.my < 0 || m.my >= SIZE)
		return ;
	m.d_mx = (m.mx - SIZE / 2) * info->zoom / SIZE;
	m.d_my = (m.my - SIZE / 2) * info->zoom / SIZE;
	if (y > 0)
		info->zoom /= 1.1;
	else
		info->zoom *= 1.1;
	info->offset_x += m.d_mx - (m.mx - SIZE / 2) * info->zoom / SIZE;
	info->offset_y += m.d_my - (m.my - SIZE / 2) * info->zoom / SIZE;
	print_fractal(info);
}
