/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palucena <palucena@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:38:50 by palucena          #+#    #+#             */
/*   Updated: 2023/08/31 14:07:09 by palucena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define SIZE 700
# define LIMIT 3.5

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <math.h>
# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"

typedef struct s_rgba
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
}	t_rgba;

typedef struct s_palette
{
	uint8_t		count;
	int			cycle;
	int			colors[16];
}	t_palette;

typedef union u_color
{
	int			value;
	t_rgba		rgba;
}					t_color;

typedef struct s_move
{
	int32_t	mx;
	int32_t	my;
	double	d_mx;
	double	d_my;
}		t_move;

typedef struct s_args
{
	double	real;
	double	imag;
}			t_args;

typedef struct s_info
{
	int			name;
	mlx_t		*mlx;
	mlx_image_t	*win;
	int32_t		pos_x;
	int32_t		pos_y;
	double		zx;
	double		zy;
	double		cx;
	double		cy;
	double		zoom;
	double		offset_x;
	double		offset_y;
	int			max_iterations;
	int			color;
	bool		smooth;
	t_args		args;
	t_palette	*palette;
	t_palette	*palettes;
}			t_info;

void		print_fractal(t_info *info);
void		fractal(t_info *info);

void		hook(void	*param);
void		shook(double x, double y, void *param);
void		mhook(mouse_key_t b, action_t a, modifier_key_t mods, void *param);

t_info		*create_window(void);
t_palette	*ft_get_palettes(void);
void		ft_put_pixel(t_info *info, int i);

t_color		get_color_struct(t_info *info, int i);

void		init_fract(t_info *info, char **av);
void		reset_fract(t_info *info);
void		mandelship(t_info *info);
void		julia(t_info *info);

int			check_name(char *name);
int			julia_params(char *p);
void		usage(void);
void		error_msg(void);
double		ft_atof(char *str);

#endif