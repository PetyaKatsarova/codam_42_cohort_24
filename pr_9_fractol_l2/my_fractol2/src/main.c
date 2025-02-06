/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:14:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/06 15:01:54 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

/*
GLFW: graphics library framework: connection between my software and the display, loads too OpenGL func pointers, compiling the shaders
*/

void close_hook(void *param)
{
    t_fractal *fr = (t_fractal *)param;
    mlx_terminate(fr->mlx);
    free(fr);
    exit(EXIT_SUCCESS);
}

// static void draw_circle(void *param)
// {
//     t_fractal *fr = (t_fractal *)param;
    
//     for (int y = -50; y <= 50; y++)
//     {
//         for (int x = -50; x <= 50; x++)
//         {
//             if (x * x + y * y <= 50 * 50)
//                 mlx_put_pixel(fr->img, 400 + x, 300 + y, 0x800080FF);
//         }
//     }
//     // render updated img
//     mlx_image_to_window(fr->mlx, fr->img, 0, 0); // WHY 0 0?
// }

void key_hook2(mlx_key_data_t keydata, void *param)
{  
    if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
    {
        close_hook(param);
    }
}
// gcc fast_smooth_move_circle.c ../../lib/MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread  -Ofast -lm && ./a.out

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./fract-ol

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fract-ol

int main()
{
    t_fractal *fr = malloc(sizeof(t_fractal));
    init_fr(fr);
    init_mlx(fr);

    // draw_circle(fr);
    draw_mandel((void *)fr);
    mlx_key_hook(fr->mlx, key_hook2, fr);  
    mlx_close_hook(fr->mlx, close_hook, fr);  // Handle `X` button
    mlx_loop(fr->mlx);  

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
    Takes a callback function that receives an mlx_key_data_t struct.

Structure of mlx_key_data_t
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
