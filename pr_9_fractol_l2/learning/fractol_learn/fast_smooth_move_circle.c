/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fast_smooth_move_circle.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:14:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/31 18:17:13 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "/home/pekatsar/Desktop/unstoppable/MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 800
#define MOVE_SPEED 10
#define ZOOM_SPEED 5

mlx_t       *mlx;
mlx_image_t *img;
int         cx = 450;
int         cy = 400;
int         radius = 50;

/*
gcc fast_smooth_move_circle.c ../../../MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread -lm && ./a.out
 */

/*
void put_pixel()
put a px on the img buffer
*/
void put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        mlx_put_pixel(img, x, y, color);
}

void draw_circle()
{
    mlx_delete_image(mlx, img); // del prev img
    img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
    {
        printf("Image recreation failed!\n");
        return;
    }
    
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
                put_pixel(img, cx + x, cy + y, 0x800080FF);
        }
    }
    // render updated img
    mlx_image_to_window(mlx, img, 0, 0); // start from center of window
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(mlx);
        else if (keydata.key == MLX_KEY_LEFT)
            cx -= MOVE_SPEED;
        else if (keydata.key == MLX_KEY_RIGHT)
            cx += MOVE_SPEED;
        else if (keydata.key == MLX_KEY_UP)
            cy -= MOVE_SPEED;
        else if (keydata.key == MLX_KEY_DOWN)
            cy += MOVE_SPEED;
        else if (keydata.key == MLX_KEY_W)
            radius += ZOOM_SPEED;
        else if (keydata.key == MLX_KEY_S && radius > ZOOM_SPEED)
            radius -= ZOOM_SPEED;

        draw_circle();
    }
}

int main()
{
    mlx = mlx_init(WIDTH, HEIGHT, "purple cirlce", true);
    if (!mlx)
    {
        printf("MLX initialization failed!\n");
        return EXIT_FAILURE;
    }

    img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
    {
        printf("Image creation failed!\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    draw_circle(img, radius, 0x800080FF);
    mlx_key_hook(mlx, key_hook, NULL);
    mlx_loop(mlx);

    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}


