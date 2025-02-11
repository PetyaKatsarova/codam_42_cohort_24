/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fract-ol.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 11:31:52 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/06 17:15:02 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/LIBFT/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>

# define    SIZE 900
# define    STEP 42  
// # define    BLACK 0x000000

//to del
#define BASE_SPEED 10
#define BOOST_SPEED 25
#define ZOOM_SPEED 5

// mousecodes
#ifdef __linux__
    # define SCROLL_UP 4
    # define SCROLL_DOWN 5
#elif __APPLE__
    # define SCROLL_UP 3
    # define SCROLL_DOWN 4
#elif _WIN32
    # define SCROLL_UP 0x0800
    # define SCROLL_DOWN 0x1000
#endif

// diff key nums per OS
#ifdef __APPLE__
#include "key_macos.h"
#elif __linux__
#include "key_linux.h"
#endif

typedef struct fractal
{
    unsigned int x;
    unsigned int y;
    char        *name;
    void        *mlx;
    void        *window;
    void        *img;
    void        *pointer_to_image;
	int		    bits_per_pixel;
	int		    size_line;
	int		    endian;
    double      zx;
    double      zy;
    double      cx;
    double      cy;
    int         color;
    double      offset_x;
    double      offset_y;
    double      zoom;
    int         max_iterations;
}               t_fractal;

// src/input_utils.c
double          str_to_double(char *str);
int             is_double(char *str);

// src/input_check.c
int             is_valid_input(int argc, char **argv);


// src/utils.c
void	        put_color_to_pixel(t_fractal *fractal, int x, int y, int color);
int	            exit_fr(t_fractal *fractal);

// src/init.c
void            init_fr(t_fractal *fr);
void            init_mlx(t_fractal *fr);

void            draw_mandel(void *fr_void);
void	        draw_julia(void *fr_void);
void            draw_tricorn(void *fr_void);
void	        draw_phoenix(void *fr_void);

// src/hooks.c
void	zoom(t_fractal *fr, int x, int y, int zoom);
int	    key_hook(int key_code, t_fractal *fractal);
int	    mouse_hook(int mouse_code, int x, int y, t_fractal *fractal);
void    change_iterations(t_fractal *, int key_code);

// src/main.c
int             draw_fr(t_fractal *fr, char *name);
#endif

