/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:14:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/13 17:21:51 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

/*
GLFW: graphics library framework: connection between my software and the display, loads too OpenGL func pointers, compiling the shaders
*/

// gcc fast_smooth_move_circle.c ../../lib/MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread  -Ofast -lm && ./a.out

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./fract-ol

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fract-ol

// valgrind --suppressions=mlx42.supp ./fract-ol

static void handle_julia(t_fractal *fr)
{
        if (!fr->cx && !fr->cy)
		{
            fr->cx = -0.8;
            fr->cy = 0.156;
		}
        populate_px_julia(fr);
}

int draw_fr(t_fractal *fr, char *name)
{
    if (ft_strncmp(name, "mandelbrot", 10) == 0
    || ft_strncmp(name, "1", 1) == 0)
        populate_px_mandel(fr);
    else if (ft_strncmp(name, "julia", 5) == 0
    || ft_strncmp(name, "2", 1) == 0)
        handle_julia(fr);
    else if (ft_strncmp(name, "tricorn", 7) == 0
    || ft_strncmp(name, "3", 1) == 0)
        populate_px_tricorn(fr);
    else if (ft_strncmp(name, "phoenix", 7) == 0
        || ft_strncmp(name, "4", 1) == 0)
            populate_px_phoenix(fr);
    else
    {
        ft_putendl_fd("Choose from: mandelbrot, julia or pine", 1);
        exit_fr(fr);
    }
    mlx_put_image_to_window(fr->mlx, fr->window, fr->img, 0, 0);
    return (0);
}

// julia: .355 1.01
int main(int argc, char **argv)
{
    int is_valid_i;

    is_valid_i = is_valid_input(argc, argv);
    if (is_valid_i == 1)
    {
        t_fractal *fr = malloc(sizeof(t_fractal));
        if (!fr)
            exit_fr(fr);
        init_fr(fr);
        init_mlx(fr);
        mlx_key_hook(fr->window, key_hook, fr);
	    mlx_mouse_hook(fr->window, mouse_hook, fr);
	    mlx_hook(fr->window, 17, 0L, exit_fr, fr);
        if (argc == 4)
        {
            double d1 = str_to_double(argv[2]);
            double d2 = str_to_double(argv[3]);
            fr->cx = d1;
            fr->cy = d2;
            draw_fr(fr, argv[1]);
        }
        draw_fr(fr, argv[1]);
        mlx_loop(fr->mlx);
    }
    return (0);
}
