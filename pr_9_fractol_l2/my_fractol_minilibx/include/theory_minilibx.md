Screen & Image Handling

void *mlx; → Pointer to the MiniLibX connection (MLX instance).
void *window; → The window where the fractal is displayed.
void *img; → Image buffer to draw the fractal before rendering.
void *pointer_to_image; → a pointer to raw pixel data for direct manipulation.
int bits_per_pixel; → Number of bits per pixel (color depth, typically 32).
int size_line; → Bytes per row of pixels (important for accessing specific pixels).
int endian; → Determines how pixel colors are stored (big-endian or little-endian).

================================================
                ENDIAN
=================================================

"Endian" refers to the byte order in which multi-byte values (like colors, integers, etc.) are stored in memory.
Two Types of Endianness

    Big-endian
        Stores the most significant byte (MSB) first (at the lowest memory address).
        Example: 0x11223344 stored as

    Address:   0x00   0x01   0x02   0x03  
    Value:     0x11   0x22   0x33   0x44  
    Used by Motorola, PowerPC, some network protocols.

Little-endian
----------------------------

    Stores the least significant byte (LSB) first (at the lowest memory address).
    Example: 0x11223344 stored as

        Address:   0x00   0x01   0x02   0x03  
        Value:     0x44   0x33   0x22   0x11  

        Used by Intel (x86, x86-64), ARM (default on most systems).

How It Affects MiniLibX (int endian)

    The endian variable determines how pixel colors are stored in memory.
    0 → Little-endian (RGBA stored as AABBGGRR in memory).
    1 → Big-endian (RGBA stored as RRGGBBAA in memory).

When working with MiniLibX's mlx_get_data_addr(), knowing the endian type ensures you correctly manipulate pixel colors in the framebuffer.

======================================================

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

fr->color += (255 * 255 * 255) / 100;
(255 * 255 * 255) = 16777215 (this is the maximum 24-bit color value, i.e., pure white 0xFFFFFF).
Dividing by 100 makes the increment small, ensuring gradual color changes.
fr->color is being increased, so colors change gradually.
2. Extract the lowest byte (blue component)

int grayscale = (fr->color & 0xFF);
& 0xFF isolates the last 8 bits (least significant byte).
This byte represents the blue component in an RGB color:
Example: 0x123456 & 0xFF → 0x56 (only the blue part remains).
The problem: This value is not necessarily a correct grayscale intensity.
3. Force the color to grayscale

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


int grayscale = (fr->color + 5) % 256; // Smooth grayscale transition
fr->color = (grayscale << 16) | (grayscale << 8) | grayscale;
Now, only shades of gray will appear without unwanted colors.


======================================================
            OFFSET
======================================================
The offset values shift the fractal in the complex plane, allowing panning (moving the view without zooming).
Why is Offset Needed?

Each pixel on the screen maps to a complex number C=(cx,cy)
By default, fractals are centered at (0,0) in the complex plane.
To move the view left, right, up, or down, you add offsets to the coordinates.
Mathematical Effect

Each pixel's complex coordinate is calculated as:
cx=(x/zoom)+offsetx
cx=(x/zoom)+offsetx​
cy=(y/zoom)+offsety
cy=(y/zoom)+offsety​

    offset_x moves the fractal left/right in the real axis.
    offset_y moves the fractal up/down in the imaginary axis.

Example

    Moving Right → Increase offset_x (e.g., offset_x += 0.1)
    Moving Left → Decrease offset_x (e.g., offset_x -= 0.1)
    Moving Up → Decrease offset_y (e.g., offset_y -= 0.1)
    Moving Down → Increase offset_y (e.g., offset_y += 0.1)

=======================================================
            FRACTALS LOGIC
========================================================
Understanding Complex Numbers in Mandelbrot & Julia Sets

In complex numbers:
Z=x+yi
Z=x+yi

    xx → Real part
    yy → Imaginary part

In Mandelbrot & Julia sets, zx and zy represent Z, while cx and cy represent **C`.
Why zx (Real) and zy (Imaginary)?

    Mandelbrot Set:
        CC varies per pixel: C=(cx,cy)C=(cx,cy) is the coordinate of the pixel.
        ZZ starts at (0,0) and iterates with:
        Zn+1=Zn2+C
        Zn+1​=Zn2​+C
            zx (real part of Z)
            zy (imaginary part of Z)
            cx, cy stay fixed for each pixel.

    Julia Set:
        CC is fixed: C=(cx,cy)C=(cx,cy).
        ZZ starts at the pixel coordinate and iterates:
        Zn+1=Zn2+C
        Zn+1​=Zn2​+C

Summary of Variables

    zx → Real part of ZZ.
    zy → Imaginary part of ZZ.
    cx → Real part of CC.
    cy → Imaginary part of CC.

================================================
   color:
   A color in MiniLibX uses 3 bytes (24-bit color) → RGB (0xRRGGBB).

==============================================
        BITWISE
=========================================

The bitwise AND (&) compares each bit of two numbers.
It keeps only the bits that are 1 in both numbers:

  10110110  (binary of some number)
& 00001111  (bit mask, keeps last 4 bits)
------------
  00000110  (result)

0xFF (hex) is 11111111 in binary (only last 8 bits are 1).
fr->color & 0xFF extracts only the lowest byte (last 8 bits)
Example:

If fr->color = 0x123456 (hex):

  0001 0010  0011 0100  0101 0110  (fr->color = 0x123456)
& 0000 0000  0000 0000  1111 1111  (0xFF mask)
--------------------------------
  0000 0000  0000 0000  0101 0110  (0x56 = 86 in decimal)

  Bit shifting moves bits left (<<) or right (>>), like sliding numbers in a table.
Left Shift (<<)

Moves bits left, multiplying by 2 for each shift.
Example: 5 << 1

  00000101  (5 in binary)
<<       1  (shift left by 1 place)
------------
  00001010  (10 in binary, = 5 * 2)

    5 << 1 = 10
    5 << 2 = 20 (doubles again)

Why use << in colors?

    grayscale << 16 moves red to the correct position.
    grayscale << 8 moves green to its correct place.

    Example: 8 >> 1

  00001000  (8 in binary)
>>       1  (shift right by 1 place)
------------
  00000100  (4 in binary, = 8 / 2)

    8 >> 1 = 4
    8 >> 2 = 2 (halves again)

fr->color = (grayscale << 16) | (grayscale << 8) | grayscale;

    grayscale << 16 → Moves value into red.
    grayscale << 8 → Moves value into green.
    grayscale stays in blue.
    | (bitwise OR) combines all parts.

What does | (Bitwise OR) do?

The bitwise OR (|) operator combines bits.

    If either bit is 1, the result is 1.
    If both bits are 0, the result is 0.
      1010  (A)
| 0101  (B)
---------
  1111  (Result)

  0x560000  (Red)
| 0x005600  (Green)
| 0x000056  (Blue)
-----------------
  0x565656  (Final Grayscale Color)

Final Result

    | merges Red, Green, and Blue into a single RGB value.
    Produces a grayscale color (R = G = B = same value).
& 0xFF keeps only the last 8 bits (Blue component).
Other color components (Red & Green) are zeroed out.
It works because 0xFF is 1111 1111, meaning it keeps only the lowest 8 bits.

Example Calculation (grayscale = 128):

    128 << 16 → 0x800000 (Red channel)
    128 << 8 → 0x008000 (Green channel)
    128 → 0x000080 (Blue channel)
    0x800000 | 0x008000 | 0x000080 = 0x808080 (Final RGB color)

Final Result:

This creates an RGB color where red, green, and blue values are equal, forming a grayscale shade.







