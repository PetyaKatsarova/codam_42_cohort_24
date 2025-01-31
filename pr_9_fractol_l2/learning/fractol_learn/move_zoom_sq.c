/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_zoom_sq.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:20:38 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/31 12:12:54 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "/home/pekatsar/Desktop/unstoppable/MLX42/include/MLX42/MLX42.h"

#define WIDTH 900
#define HEIGHT 600
#define MOVE_STEP 10
#define ZOOM_STEP 5

mlx_t *mlx;
mlx_image_t *img;
int square_size = 50;
int square_x = 375;
int square_y = 275;

void draw_square()
{
    mlx_delete_image(mlx, img); // delete old img
    img = mlx_new_image(mlx, WIDTH, HEIGHT);

    for (int y = 0; y < square_size; y++)
    {
        for (int x = 0; x < square_size; x++)
        {
            mlx_put_pixel(img, square_x + x, square_y + y, 0x00FF00FF); // green
        }
    }
    mlx_image_to_window(mlx, img, 0, 0);
}

void key_callback(mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(mlx);

        
    }
}
