/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:12:56 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/04 18:17:49 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

int main(int argc, char **argv)
{
    t_fractal *fr;

    if (argc != 2)
    {
        ft_putendl_fd("Type: ./fractol <fractal_name>", 1);
        ft_putendl_fd("Available fractals: mandelbrot, julia");
        return (0);
    }

    fr = malloc(sizeof(t_fractal));
    init_fractal(fr);
    init_mlx(fr);
}