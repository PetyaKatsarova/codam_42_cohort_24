/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fract-ol.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 11:31:52 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/04 18:24:57 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/LIBFT/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <pthread.h>

# define    SIZE 700
# define    THREAD_WIDTH 7
# define    THREAD_NUMBER 100
# define    WIDTH 1200
# define    HEIGHT 900
#define     STEP 42  

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define R 15
# define C 8
# define H 4
# define J 38
# define P 35
# define M 46

// mousecodes
# define SCROLL_UP 4
# define SCROLL_DOWN 5



typedef struct fractal
{
    unsigned int x;
    unsigned int y;
    char        *name;
    void        *mlx;
    void        *window;
    void        *image;
    void        *pointer_to_image;
    int         bpp; // bits per pixel
    int         size_line;
    int         end;
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

// utils.c
void		put_color_to_pixel(t_fractal *fractal, int x, int y, int colour);
// int			exit_fractal(t_fractal *fractal);
// double		generate_random_c(void);
// void		change_iterations(t_fractal *fractal, int key_code);

// src/calculate_mandelbrot.c
// void    calculate_mandelbrot(t_fractal *fr);

// src/draw_fr.c
int draw_fractal (t_fractal *fr, char *query, double cx, double cy);

#endif
