/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:12:56 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/05 16:00:57 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// https://github.com/PaLucena/fract-ol/blob/main/src/main.c

#include "../include/fract-ol.h"
#include <stdio.h>

int draw_fr(t_fractal *fr, char *query)
{
    if (ft_strncmp(query, "mandelbrot", 11) == 0)
        printf("wtf\n");
        // draw_mandelbrot(fr);
    // more code for julia and bonus fractal
    else
    {
        ft_putendl_fd("Choose from: mandelbrot, julia", 1);
        exit_fr(fr);
    }
    mlx_image_to_window(fr->mlx, fr->img, 0, 0);
    return (0);
}

int main(int argc, char **argv)
{
    t_fractal *fr;

    if (argc != 2)
    {
        ft_putendl_fd("Type: ./fractol <fractal_name>", 1);
        ft_putendl_fd("Available fractals: mandelbrot, julia", 1);
        return (0);
    }

    fr = malloc(sizeof(t_fractal));
    init_fr(fr);
    init_mlx(fr);
    mlx_key_hook(fr->mlx, key_hook, (void *)fr);
    // mlx_scroll_hook(fr->mlx, scroll_hook, fr);
    // handling the window close event on click exit button (the "X" in the window corner):
    mlx_close_hook(fr->mlx, exit_fr, fr);
    draw_fr(fr, argv[1]);
    mlx_loop(fr->mlx);
    return (0);
}
