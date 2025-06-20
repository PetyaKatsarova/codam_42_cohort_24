#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "../../lib/MLX42/include/MLX42/MLX42.h"
#define WIDTH 5120
#define HEIGHT 2880

// gcc images.c ../../lib/MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread  -Ofast -lm && ./a.out
static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, 512, 512);
	if (!img)
		error();

	// Set every pixel to white
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}