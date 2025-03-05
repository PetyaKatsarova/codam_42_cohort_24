What is a Frame and How is it Created in MLX42?

A frame is one complete image displayed on the screen. In computer graphics, the screen refreshes multiple times per second, showing different frames to create motion.
How Often is a Frame Updated?

    The frame rate (FPS - Frames Per Second) determines how many frames are drawn per second.
    In MLX42, each iteration of mlx_loop(fr->mlx); corresponds to one frame.
    By default, MLX42 aims for 60 FPS, meaning 60 frames are drawn every second.

MLX42 handles frame creation internally using OpenGL and GLFW.

    When you call mlx_init(), MLX42 creates a window with a hidden frame buffer.
    Each loop iteration (mlx_loop()) updates and redraws this buffer.

    2. How is a Frame Updated?
Step 1: Modify the Hidden Buffer (Off-Screen)

    Every time you change pixels (mlx_put_pixel()), it modifies an off-screen image buffer, not the window.
    This avoids flickering, as all updates happen in memory first.

Step 2: Send the Buffer to the Window

    To display the updated buffer, use:

    mlx_image_to_window(fr->mlx, fr->img, 0, 0);

    This copies the updated image to the visible window.

Step 3: Repeat for Every Frame

    mlx_loop(fr->mlx); continuously redraws the buffer.
    If you modify pixels every frame, changes will appear smoothly (like zooming in and out).

✅ A frame = one complete image displayed on the screen
✅ MLX42 creates frames automatically inside mlx_loop()
✅ mlx_put_pixel() modifies a hidden buffer (off-screen)
✅ mlx_image_to_window() pushes the buffer to the screen
✅ Looping at 60 FPS makes smooth updates possible 

    *******************************************************************************************


how Constant Pixel Drawing Works in MLX42
1. Buffer: What We Keep in Memory

    A buffer is an area in memory where pixel data is stored before being drawn on the screen.
    MLX42 keeps a frame buffer (hidden image in memory) to avoid flickering.
    Every time a pixel is drawn (mlx_put_pixel()), it modifies the off-screen buffer, not the display directly.

2. What We Display

    The buffer is not shown immediately; it must be rendered to the window using:

    mlx_image_to_window(fr->mlx, fr->img, 0, 0);

    This copies the buffer to the screen.

3. How Often Do We Update the Buffer?

    Every frame in mlx_loop(fr->mlx);
    When zooming, we:
        Modify offset_x, offset_y, and zoom.
        Recalculate and redraw every pixel in draw_mandel().
        Refresh the buffer using mlx_image_to_window().
    This happens 60 times per second (FPS) unless manually limited.

How Pixels Are Drawn on Zoom

    Mouse Scroll Event
        scroll_hook() detects ydelta.
        Calls zoom(fr, x, y, ydelta);
        Updates offset_x, offset_y, zoom.

    Fractal is Recomputed
        draw_mandel() iterates over every pixel (x, y), recalculates the fractal color, and calls:

    mlx_put_pixel(fr->img, x, y, color);

    The off-screen buffer is updated.

Image is Rendered

    mlx_image_to_window(fr->mlx, fr->img, 0, 0); sends the updated buffer to the screen.

✅ MLX42 uses a hidden buffer to store pixels before displaying them.
✅ mlx_put_pixel() modifies the buffer, but it must be pushed to the screen.
✅ mlx_image_to_window() copies the buffer to the visible window.
✅ This update happens every time we zoom and redraw the fractal.

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


//MLX42 does not use mlx_new_window separately. mlx_init() already creates a window.
// mlx_get_data_addr() is not needed in MLX42. Instead, access the image buffer using fr->img->pixels.
// Removed pointer_to_img, bpp, bytes_per_row, and endian as MLX42 handles these internally.

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

Main Variables in calc_mandel()
Variable	Represents	How it Works
x, y	Pixel coordinates on screen	Loops through each pixel in draw_mandel()
cx, cy	Scaled complex number for the pixel	cx = (x / zoom) + offset_x; (same for cy)
zx, zy	Current values of the Mandelbrot iteration	Always starts at 0.0
zoom	Zoom level	Multiplies each coordinate to zoom in/out
offset_x, offset_y	Moves the view left/right and up/down	Adjusted based on mouse scroll

/*
fractal->pointer_to_image holds the raw pixel buffer of the image.
Convert (x, y) to a 1D index in the buffer:

buffer[(y * fractal->size_line / 4) + x] = color;

    size_line is the number of bytes per row.
    /4 is used because each pixel is 4 bytes (RGBA, 32-bit).
    y * (size_line / 4) + x calculates the correct pixel index.
*/