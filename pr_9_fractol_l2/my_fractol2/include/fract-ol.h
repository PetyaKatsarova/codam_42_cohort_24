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
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <pthread.h>
# include <stdlib.h>

# define    SIZE 900
# define    THREAD_WIDTH 7
# define    THREAD_NUMBER 100
#define     STEP 42  
#define     BLACK 0x000000

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

// MLX42 does not use mlx_new_window separately. mlx_init() already creates a window.
// mlx_get_data_addr() is not needed in MLX42. Instead, access the image buffer using fr->img->pixels.
// Removed pointer_to_img, bpp, bytes_per_row, and endian as MLX42 handles these internally.

typedef struct fractal
{
    unsigned int x;
    unsigned int y;
    char        *name;
    void        *mlx;
    void        *window;
    void        *img;
    void        *buffer_img; // off screen buffer
    // void        *pointer_to_img;
    // int         bpp; // bits per pixel
    // int         bytes_per_row; // bytes per row = size_line
    // int         endian; //Determines how colors are stored (little-endian vs big-endian) for working with diff architecture: old and new computers
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

// src/util.c
double          str_to_double(char *str);
int             is_double(char *str);

// src/init.c
void            init_fr(t_fractal *fr);
void            init_mlx(t_fractal *fr);

// src/input_check.c
int             is_valid_input(int argc, char **argv);

// src/mandel.c
void            draw_mandel(void *fr_void);
void	        draw_julia(void *fr_void);

// src/pinecone.c
void            draw_pinecone(void *fr_void);


// src/hooks.c
void            key_hook(mlx_key_data_t keydata, void *param);
void            scroll_hook(double xdelta, double ydelta, void *param);
void            close_hook(void *param);

// src/main.c
// int             draw_fr(t_fractal *fr, char *name);
int             draw_fr(t_fractal *fr, char *name);
#endif

