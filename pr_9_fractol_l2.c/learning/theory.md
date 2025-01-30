=============================================================================
                              PIXELS AND GRAPHICS
==========================================================================
Screen Resolution: The number of pixels horizontally and vertically (e.g., 1920×1080 means 1920 pixels across and 1080 pixels down).
Color: Each pixel can show a color based on a combination of red, green, and blue (RGB). These colors mix to create all the colors you see.

A complex number looks like this: 
c=x+yi.

x: The "real" part (like normal numbers you use every day).
y: The "imaginary" part (it’s a bit weird, but it works for math here).
i: A special symbol that means "the square root of -1."
Think of  𝑥 as the horizontal position of the pixel and 
𝑦 as the vertical position.


∣z∣ is the "distance" of 𝑧 from the origin (0,0) on the complex plane (a grid for complex numbers).
You calculate it using:
∣𝑧∣=𝑥2+𝑦2: koren kvadraten on x na kvadrat + y na kvadrat

 
​After each calculation, check if
∣z∣ (the distance) becomes larger than 2.
If it does, the pixel "escapes."
If it never escapes after many calculations, the pixel is part of the Mandelbrot Set.

Pixels that "escape" (where ∣𝑧∣>2∣z∣>2) are not part of the fractal and are colored differently (e.g., white).
Pixels that never escape are part of the Mandelbrot Set and are colored black (or other colors)

------------------------- SIN COS -----------------------------------------------
sin(x) and cos(x): Trigonometric functions

    What they do: Measure the relationship between angles and sides in a triangle or wave patterns.
        sin(x): Gives the "height" of a point on a circle at angle xx.
        cos(x): Gives the "width" of a point on a circle at angle xx.
    Input: xx is in radians (not degrees—180∘=π radians180∘=π radians).
    Example:
        sin(0) → 0 (height is 0 at the starting point of a circle).
        cos(0) → 1 (width is 1 at the starting point).
    Why they're useful: Used in creating circular or wave-like patterns, like rotating shapes or oscillations.