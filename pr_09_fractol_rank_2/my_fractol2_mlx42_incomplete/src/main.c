/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:14:57 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/28 17:24:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

/*
GLFW: graphics library framework: connection between my software and the display, loads too OpenGL func pointers, compiling the shaders
*/

// gcc fast_smooth_move_circle.c ../../lib/MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread  -Ofast -lm && ./a.out

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./fract-ol

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fract-ol

// valgrind --suppressions=mlx42.supp ./fract-ol

int draw_fr(t_fractal *fr, char *name)
{
    if (ft_strncmp(name, "mandelbrot", 10) == 0)
    {
        fr->name = "mandelbrot";
        draw_mandel(fr);
    }
    else if (ft_strncmp(name, "julia", 5) == 0)
    {
        fr->name = "julia";
        if (!fr->cx && !fr->cy)
		{
            /*0.285, 0.01; -0.8 0.156*/
			// fr->cx = -0.8;
			// fr->cy = 0.156;
            // fr->cx=-0.70176;
            fr->cx=-0.8;
            fr->cy=0.156;
		}
        draw_julia(fr);
    }
    else if (ft_strncmp(name, "pine", 4) == 0)
    {
        fr->name = "pine";
        draw_pinecone(fr);
    }
    else
    {
        ft_putendl_fd("Choose from: mandelbrot, julia or pine", 1);
        close_hook((void *)fr);
    }
    mlx_image_to_window(fr->mlx, fr->img, 0, 0);
    return (0);
}
// julia: cx=-0.70176, cy=0.3842
int main(int argc, char **argv)
{
    int is_valid_i;

    is_valid_i = is_valid_input(argc, argv);
    if (is_valid_i == 1)
    {
        t_fractal *fr = malloc(sizeof(t_fractal));
        init_fr(fr);
        init_mlx(fr);

        mlx_scroll_hook(fr->mlx, scroll_hook, fr);
        mlx_key_hook(fr->mlx, key_hook, fr);  
        mlx_close_hook(fr->mlx, close_hook, fr);  // Handle `X` button
        if (argc == 4)
        {
            double d1 = str_to_double(argv[2]);
            double d2 = str_to_double(argv[3]);
            fr->cx = d1;
            fr->cy = d2;
        }
        // else
        draw_fr(fr, argv[1]);
        mlx_loop(fr->mlx);

    }
    return (EXIT_SUCCESS); // Cleanup handled inside hooks
}


/*
    he main MLX42 context that manages the window, rendering, and event handling.
    It replaces the old mlx from MiniLibX.
    Created using mlx_init(), which also creates the window.

How to Initialize mlx_t

mlx_t *mlx = mlx_init(800, 600, "My Window", true);
if (!mlx)
    return (EXIT_FAILURE); // Handle errors

    800x600 → Window size (width × height).
    "My Window" → Window title.
    true → Enables MLX42's built-in FPS counter.

    Handling Keyboard Input (mlx_key_hook)
    Registers a function that runs when a key is pressed or released.
    Takes a callback function that receives an mlx_key_t_data struct.

Structure of mlx_key_t_data
typedef struct {
    mlx_key_t key;      // Which key was pressed
    action_t action;    // MLX_PRESS, MLX_RELEASE, or MLX_REPEAT
    modifier_key_t mods; // Modifier keys (Shift, Ctrl, etc.)
} mlx_key_data_

FPS (Frames Per Second) Counter measures how many frames the program renders per second. It helps monitor performance and detect lag or slow rendering.
MLX42 FPS Counter

    Enabled when initializing MLX:

mlx_t *mlx = mlx_init(800, 600, "My Window", true);

The true parameter activates the built-in FPS counter.
Displays FPS in the console/log.
*/
