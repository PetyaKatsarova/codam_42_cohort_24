/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:19:43 by palucena          #+#    #+#             */
/*   Updated: 2023/08/26 19:42:38 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_lerpi(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

static t_color	clerp(t_color c1, t_color c2, double p)
{
	t_color	c;

	if (c1.value == c2.value)
		return (c1);
	c.rgba.r = (char)ft_lerpi((int)c1.rgba.r, (int)c2.rgba.r, p);
	c.rgba.g = (char)ft_lerpi((int)c1.rgba.g, (int)c2.rgba.g, p);
	c.rgba.b = (char)ft_lerpi((int)c1.rgba.b, (int)c2.rgba.b, p);
	c.rgba.a = (char)0xFF;
	return (c);
}

static t_color	linear_color(double iter, int max, t_palette *p)
{
	double		index;
	double		adjust;
	int			c;

	if (p->cycle)
		index = fmod(iter, p->cycle - 1) / (p->cycle - 1);
	else
		index = iter / max;
	c = p->count - 1;
	adjust = fmod(index, 1.0 / c) * c;
	return (clerp((t_color)(p->colors[(int)(index * c) + 1]),
		(t_color)(p->colors[(int)(index * c)]),
		(int)(adjust + 1) - adjust));
}

static t_color	smooth_color(t_info *info, int iter)
{
	double	j;
	double	zn;
	double	nu;

	zn = log(info->zx * info->zx + info->zy * info->zy) / 2.0;
	nu = log(zn / log(2)) / log(2);
	j = iter + 1 - nu;
	if (j < 0)
		j = 0;
	return (linear_color(j, info->max_iterations, info->palette));
}

t_color	get_color_struct(t_info *info, int iter)
{
	if (info->smooth)
		return (smooth_color(info, iter));
	return (linear_color(iter, info->max_iterations, info->palette));
}
