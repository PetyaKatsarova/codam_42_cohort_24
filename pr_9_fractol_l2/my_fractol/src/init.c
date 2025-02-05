/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:04:12 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/05 14:40:00 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"


void    init_fr(t_fractal *fr)
{
    fr->x = 0;
    fr->y = 0;
    fr->color = 0x800080FF;
    fr->zoom = 300; //why
    fr->offset_x = -1.21;
    fr->offset_y = -1.21;
    fr->max_iterations = 42; // change??
}

//MLX42 does not use mlx_new_window separately. mlx_init() already creates a window.
// mlx_get_data_addr() is not needed in MLX42. Instead, access the image buffer using fr->img->pixels.
// Removed pointer_to_img, bpp, bytes_per_row, and endian as MLX42 handles these internally.

void init_mlx(t_fractal *fr)
{
    fr->mlx = mlx_init(WIDTH, HEIGHT, "Hellow W", true);
    fr->window = fr->mlx;
    fr->img = mlx_new_image(fr->mlx, SIZE, SIZE);
}

/*
!!NB!!
fr->mlx = mlx_init(WIDTH, HEIGHT, "Hellow W", true);
    fr->window = mlx_new_window(fr->mlx, SIZE, SIZE, "FRACT-OL");
WIDTH and HEIGHT define the size of the framebuffer (a hidden img in memory).
This framebuffer stores pixel data before being displayed in the window.
This is useful because it allows you to draw everything first before updating the screen (reducing flickering).
    A larger WIDTH and HEIGHT means higher resolution, but also more memory usage.
    A smaller buffer may improve performance but reduce image quality.

3. Difference Between Rendering Buffer and Window Size

    The rendering buffer can be larger, smaller, or the same as the window.
    If the window is smaller than the buffer, it scales the buffer to fit.
    If the window is larger than the buffer, it stretches or pads empty space.

                                                                                        visible on the screen:
    mlx_init(WIDTH, HEIGHT, "Title", true);	Initializes MLX + buffer	WIDTH × HEIGHT (off-screen)	❌ No
    mlx_new_window(mlx, SIZE, SIZE, "Title");	Creates the visible window	SIZE × SIZE (window size)	✅ Yes
    mlx_new_image(mlx, SIZE, SIZE);	Creates an image buffer for drawing	SIZE × SIZE (image size)	❌ No (until displayed)
    mlx_get_data_addr() Explanation

    The function mlx_get_data_addr() in MLX42 provides access to the raw pixel data of an image. This is crucial when you want to manipulate individual pixels efficiently.
    fr->pointer_to_image:
→ A memory address (pointer) where the pixel data of fr->image is stored.
→ You can modify this to directly change the image pixels.

fr->image:
→ The image whose pixel data you want to access (created with mlx_new_image()).

&fr->bpp: (bits per pixel)
→ Stores how many bits are used to represent one pixel (usually 32 for RGBA).

&fr->size_line: (bytes per row)
→ The number of bytes in one row of the image (helps with navigation in memory).

&fr->end: (endianness)
→ Determines how colors are stored (little-endian vs big-endian).
→ Typically not needed unless working with different architectures.
xtracts the raw memory address where the image’s pixel data is stored.
Provides format details (bpp, row size) so you can manipulate pixels.
Allows you to modify the image directly in memory, which is much faster than using MLX’s higher-level functions.
char *pixels = fr->pointer_to_image;

// Example: Set a pixel at (x, y) to red
int x = 100, y = 50;
int pixel_index = (y * fr->size_line) + (x * (fr->bpp / 8));
pixels[pixel_index] = 255;       // Red (R)
pixels[pixel_index + 1] = 0;     // Green (G)
pixels[pixel_index + 2] = 0;     // Blue (B)
pixels[pixel_index + 3] = 255;   // Alpha (A)

This method allows fast pixel manipulation, useful for fractals, procedural graphics, and real-time rendering.
GPT Icon
What is Endianness?

Endianness refers to the way bytes are ordered when storing multi-byte data (like colors in an image or integers in memory). There are two main types:

    Little-endian:
        The least significant byte (LSB) is stored first (at the lowest memory address).
        Used by Intel x86, AMD, and most modern CPUs.

    Big-endian:
        The most significant byte (MSB) is stored first.
        Used by older systems, some network protocols, PowerPC, and Motorola CPUs.
        char *pixels = fr->pointer_to_image;

    When setting pixel colors manually, check the end value:
    int x = 100, y = 50;
    int pixel_index = (y * fr->size_line) + (x * (fr->bpp / 8));

    if (fr->end == 0) {  // Little-endian
        pixels[pixel_index] = 255;       // Blue (B)
        pixels[pixel_index + 1] = 0;     // Green (G)
        pixels[pixel_index + 2] = 0;     // Red (R)
        pixels[pixel_index + 3] = 255;   // Alpha (A)
    } else {  // Big-endian
        pixels[pixel_index] = 255;       // Alpha (A)
        pixels[pixel_index + 1] = 0;     // Red (R)
        pixels[pixel_index + 2] = 0;     // Green (G)
        pixels[pixel_index + 3] = 0;     // Blue (B)
    }
    Endianness = Byte Order (Little-endian vs. Big-endian).
    Most modern systems use Little-endian (LSB first).
    MLX42’s end helps you handle pixel storage correctly.
    You need to adjust byte order if running on different architectures.

*/