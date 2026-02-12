/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 13:22:42 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/04 13:46:04 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <string.h>

// gcc colors.c ../../lib/MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread -lm ../../lib/MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread -lm

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
#define BPP sizeof(int32_t)

int32_t	main(void)
{
    // Init mlx with a canvas size of 256x256 and the ability to resize the window.
    mlx_t* mlx = mlx_init(256, 256, "MLX42", true);
    
    if (!mlx) exit(EXIT_FAILURE);

    // Create a 128x128 image.
    mlx_image_t* img = mlx_new_image(mlx, 128, 128);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    //void *memset(void *s, int c, size_t n);function fills the first n bytes of the memory area pointed to by s with the constant byte c.
    memset(img->pixels, 137, img->width * img->height * BPP);

    // Draw the image at coordinate (0, 0).
    mlx_image_to_window(mlx, img, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}

/*
Each pixel in an image consists of color information. The amount of memory needed to store an image depends on:

    Width × Height → Total number of pixels in the image.
    BPP (Bytes Per Pixel) → How many bytes each pixel requires.
*/