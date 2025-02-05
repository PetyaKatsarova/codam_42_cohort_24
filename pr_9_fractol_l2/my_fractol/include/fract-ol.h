/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fract-ol.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 11:31:52 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/05 16:16:26 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/LIBFT/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <pthread.h>

# define    SIZE 700
# define    THREAD_WIDTH 7
# define    THREAD_NUMBER 100
# define    WIDTH 1200
# define    HEIGHT 900
#define     STEP 42  
#define     BLACK 0x000000
// mousecodes
#ifdef __linux__
    # define SCROLL_UP 4
    # define SCROLL_DOWN 5
#elif __APPLE__
    # define SCROLL_UP 3
    # define SCROLL_DOWN 4
#elif _WIN32
    # define SCROLL_UP 0x0800
    # define SCROLL_DOWN 0x1000
#endif

// MLX42 does not use mlx_new_window separately. mlx_init() already creates a window.
// mlx_get_data_addr() is not needed in MLX42. Instead, access the image buffer using fr->img->pixels.
// Removed pointer_to_img, bpp, bytes_per_row, and endian as MLX42 handles these internally.

typedef struct fractal
{
    unsigned int x;
    unsigned int y;
    char        *name;
    void        *mlx;
    void        *window;
    void        *img;
    void        *pointer_to_img;
    int         bpp; // bits per pixel
    int         bytes_per_row; // bytes per row = size_line
    int         endian; //Determines how colors are stored (little-endian vs big-endian) for working with diff architecture: old and new computers
    double      zx; // complex num
    double      zy;
    double      cx; // imaginary part?
    double      cy;
    int         color;
    double      offset_x; // curr position or start?
    double      offset_y;
    double      zoom;
    int         max_iterations;
}               t_fractal;

// utils.c
void        put_color_to_px(t_fractal *fractal, int x, int y, int colour);
void        exit_fr(void *param);

// src/init.c
void        init_fr(t_fractal *fr);
void        init_mlx(t_fractal *fr);

// src/scroll_and_keys.c
void        key_hook(mlx_key_data_t keydata, void *param);
void        zoom(t_fractal *fr, int x, int y, int zoom);
// void        scroll_hook(int mouse_code, int x, int y, t_fractal *fr);

// src/mandelbrot.c
void        calculate_mandelbrot(t_fractal *fr);

// src/main.c
int         draw_fr(t_fractal *fr, char *query);

#endif

/* the struct fractal: 
1. Graphics & Windowing Fields
Field	Type	Purpose
void *mlx	void *	Pointer to the MLX42 instance (initialized with mlx_init()).
void *window	void *	Pointer to the MLX42 window (created with mlx_new_window()).
void *image	void *	Pointer to an image buffer (created with mlx_new_image()).
void *pointer_to_image	void *	Pointer to raw pixel data of the image (obtained via mlx_get_data_addr()).
2. Image Data & Memory Layout
Field	Type	Purpose
int bpp	int	Bits per pixel (e.g., 32 for RGBA). Determines color depth.
int bytes_per_row	int	Bytes per row (size_line). Helps navigate the image buffer.
int endian	int	Byte order (Endianness). 0 = Little-endian, 1 = Big-endian.
3. Fractal Computation (Complex Numbers)
Field	Type	Purpose
double zx	double	Real part of the complex number Z in fractal equations (Z = Z² + C).
double zy	double	Imaginary part of Z.
double cx	double	Real part of C (constant in fractal formulas).
double cy	double	Imaginary part of C.

Used in fractals like Mandelbrot & Julia sets, where:

    Z = (zx + zy * i)
    C = (cx + cy * i)

4. Fractal Display Settings
Field	Type	Purpose
int color	int	Stores current color for rendering the fractal.
double offset_x	double	X-axis offset (panning/movement).
double offset_y	double	Y-axis offset (panning/movement).
double zoom	double	Zoom level (higher = closer view).
int max_iterations	int	Controls fractal detail (higher = more accuracy).

🔹 offset_x and offset_y define the viewport’s starting position.
🔹 zoom determines how much the fractal is magnified.
5. Basic Metadata
Field	Type	Purpose
unsigned int x	unsigned int	Current X position of the pixel being processed.
unsigned int y	unsigned int	Current Y position of the pixel being processed.
char *name	char *	Stores the name of the fractal (e.g., "Mandelbrot").

    A complex number is written as:
Z=x+yi
Z=x+yi

where:

    xx is the real part
    yy is the imaginary part
    ii (or jj in some programming languages) represents −1−1

    ​, which is imaginary

In fractal calculations, we iteratively update ZZ using a mathematical formula.


In fractal rendering (like the Mandelbrot and Julia sets), max iterations defines the upper limit on how many times we iterate the function:
Zn+1=Zn2+C
Zn+1​=Zn2​+C

before deciding whether a point belongs to the fractal or escapes to infinity.

    If ZZ remains bounded within the max iteration count, the point is assumed to be inside the fractal.
    If ZZ escapes (its magnitude ∣Z∣>2∣Z∣>2) before reaching max iterations, we stop early and assign it a color based on how many iterations it lasted.

     Why Do We Need Max Iterations?

    Avoid Infinite Loops
        Some points (inside the set) never escape and would iterate forever.
        We set a limit (e.g., 100, 500, 1000 iterations) to stop after a reasonable amount.

    Control Detail & Smoothness
        A higher max iteration count gives more detail (fine edges, more precision).
        A lower count speeds up rendering but loses detail.

    Coloring the Fractal
        The number of iterations before escape is used for color gradients.
        Points that escape quickly are colored brighter; those that last longer are darker.

    The Flow of Max Iterations in a Fractal Algorithm
    ----------------------------------------------
    For each pixel (x,y)(x,y) on the screen, do the following:
    Convert pixel coordinates to a complex number CC.
    Initialize Z=0Z=0 (for Mandelbrot) or Z=CZ=C (for Julia).
    Start iterating:
        Compute Z=Z2+CZ=Z2+C.
        Check if ∣Z∣>2∣Z∣>2 (escape condition).
        If escaped, stop and color the pixel based on iteration count.
        If not escaped, repeat until max iterations.
    If max iterations reached, assume the point belongs to the fractal and color it accordingly.
    Move to the next pixel and repeat.
    Visual Effect of Max Iterations

    Low max iterations (10-50):
        The fractal is blurry and lacks detail.
    Medium (100-500):
        The edges become clearer, more detail appears.
    High (1000+):
        Extremely detailed fractals, smoother color transitions, but slower rendering.

        Max iterations limits computation to prevent infinite loops.
It determines the escape time, which is used for coloring.
Higher values = more detail but slower rendering.
Lower values = faster but less accurate edges.

∣Z∣ represents the magnitude (absolute value) of a complex number ZZ.

For a complex number:
Z=x+yi
Z=x+yi

where:

    xx = real part
    yy = imaginary part

The magnitude (absolute value) ∣Z∣∣Z∣ is given by:
∣Z∣=x2+y2
∣Z∣=x2+y2
​

This formula comes from the Euclidean distance of ZZ from the origin (0,0)(0,0) in the complex plane.
*/ 
