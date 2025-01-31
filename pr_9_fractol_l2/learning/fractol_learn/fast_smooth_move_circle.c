/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fast_smooth_move_circle.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 17:14:57 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/31 18:25:12 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "/home/pekatsar/Desktop/unstoppable/MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 1200
#define HEIGHT 1000
#define BASE_SPEED 10
#define BOOST_SPEED 25
#define ZOOM_SPEED 5

mlx_t       *mlx;
mlx_image_t *img;
int         cx = WIDTH / 2;
int         cy = HEIGHT / 2;
int         radius = 50;
int         speed = BASE_SPEED;

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
    mlx_image_to_window(mlx, img, 0, 0); // WHY 0 0?
}

void move_circle()
{
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        cx -= speed;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        cx += speed;
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        cy -= speed;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        cy += speed;
    if (mlx_is_key_down(mlx, MLX_KEY_W))
        radius += ZOOM_SPEED;
    if (mlx_is_key_down(mlx, MLX_KEY_S) && radius > ZOOM_SPEED)
        radius -= ZOOM_SPEED;

    // Speed boost with SHIFT
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT) || mlx_is_key_down(mlx, MLX_KEY_RIGHT_SHIFT))
        speed = BOOST_SPEED;
    else
        speed = BASE_SPEED;

    draw_circle();
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    (void)param;
    if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(mlx);
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
    mlx_loop_hook(mlx, (void(*)(void *))move_circle, NULL);
    mlx_loop(mlx);

    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}


