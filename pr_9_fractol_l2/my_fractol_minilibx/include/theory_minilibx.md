Screen & Image Handling

void *mlx; → Pointer to the MiniLibX connection (MLX instance).
void *window; → The window where the fractal is displayed.
void *img; → Image buffer to draw the fractal before rendering.
void *pointer_to_image; → Likely a pointer to raw pixel data for direct manipulation.
int bits_per_pixel; → Number of bits per pixel (color depth, typically 32).
int size_line; → Bytes per row of pixels (important for accessing specific pixels).
int endian; → Determines how pixel colors are stored (big-endian or little-endian).

Pixel Positioning
unsigned int x; → Current horizontal position (left to right).
unsigned int y; → Current vertical position (top to bottom).
Fractal Calculations (Mandelbrot/Julia)
double zx, zy; → Current complex number (Z), used for iteration (Z = Z² + C).
double cx, cy; → Constant complex number (C), varies per pixel (for Mandelbrot) or is fixed (for Julia).
double offset_x, offset_y; → Shifts the fractal in the complex plane (panning the view).
double zoom; → Zoom level to scale the fractal (higher zoom = more details).
Color & Iterations
int color; → Stores the color of the current pixel.
int max_iterations; → Maximum number of iterations to determine escape time (affects detail level).
Other
char *name; → Name of the fractal (Mandelbrot, Julia, etc.).
Logic
Each (x, y) maps to a complex number (cx, cy), calculated based on zoom and offset_x/y.
Iteration (Z = Z² + C) runs up to max_iterations to determine escape time.
The number of iterations determines the color of the pixel.
Image is stored in img and displayed in window using MiniLibX.
This struct is used per-thread in multi-threaded fractal rendering.

=============================================================================
    COLORS, BYTES AND PIXELS....
==========================================================================
Increase the color value
c
Copy
Edit
fr->color += (255 * 255 * 255) / 100;
(255 * 255 * 255) = 16777215 (this is the maximum 24-bit color value, i.e., pure white 0xFFFFFF).
Dividing by 100 makes the increment small, ensuring gradual color changes.
fr->color is being increased, so colors change gradually.
2. Extract the lowest byte (blue component)
c
Copy
Edit
int grayscale = (fr->color & 0xFF);
& 0xFF isolates the last 8 bits (least significant byte).
This byte represents the blue component in an RGB color:
Example: 0x123456 & 0xFF → 0x56 (only the blue part remains).
The problem: This value is not necessarily a correct grayscale intensity.
3. Force the color to grayscale
c
Copy
Edit
fr->color = (grayscale << 16) | (grayscale << 8) | grayscale;
The extracted grayscale value is placed into all three color channels:
grayscale << 16 → sets Red (0xRR0000).
grayscale << 8 → sets Green (0x00GG00).
grayscale itself remains Blue (0x0000BB).
This guarantees that R = G = B, making the color a perfect grayscale shade.
Problem with this approach
Since the extracted grayscale value comes from fr->color & 0xFF, the blue component is not always the expected grayscale level.
This is why random colors like blue may appear.
Solution
To correctly cycle through grayscale:

c
Copy
Edit
int grayscale = (fr->color + 5) % 256; // Smooth grayscale transition
fr->color = (grayscale << 16) | (grayscale << 8) | grayscale;
Now, only shades of gray will appear without unwanted colors.







