/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fract_ol.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 14:32:32 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/18 12:34:25 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "../lib/LIBFT/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>

# define SIZE 1000
# define STEP 42  

// Mouse codes
# ifdef __linux__
#  define SCROLL_UP 4
#  define SCROLL_DOWN 5
# elif __APPLE__
#  define SCROLL_UP 3
#  define SCROLL_DOWN 4
# endif

// OS-specific key mappings
# ifdef __APPLE__
#  include "key_macos.h"
# elif __linux__
#  include "key_linux.h"
# endif

typedef struct fractal
{
	unsigned int	x;
	unsigned int	y;
	char			*name;
	void			*mlx;
	void			*window;
	void			*img;
	void			*pointer_to_image;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	double			zx;
	double			zy;
	double			cx;
	double			cy;
	int				color;
	double			offset_x;
	double			offset_y;
	double			zoom;
	int				max_iterations;
}	t_fractal;

// src/input_utils.c
double	str_to_double(char *str);
int		is_double(char *str);

// src/input_check.c
int		is_valid_input(int argc, char **argv);

// src/utils.c
void	put_color_to_pixel(t_fractal *fr, int x, int y, int color);
int		exit_fr(t_fractal *fr);

// src/init.c
void	init_fr(t_fractal *fr);
void	init_mlx(t_fractal *fr);

// src/draw.c
void	populate_px_mandel(void *fr_void);
void	populate_px_julia(void *fr_void);
void	populate_px_tricorn(void *fr_void);
void	populate_px_phoenix(void *fr_void);

// src/hooks.c
void	zoom(t_fractal *fr, int x, int y, int zoom);
int		key_hook(int key_code, t_fractal *fractal);
int		mouse_hook(int mouse_code, int x, int y, t_fractal *fractal);
void	change_precision(t_fractal *fr, int key_code);

// src/main.c
int		draw_fr(t_fractal *fr, char *name);

#endif
