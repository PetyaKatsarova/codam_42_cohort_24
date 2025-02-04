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

================================================================================
         GLFW (GRAPHICAL LIBRARY FRAMEWOR) OpenGL
===============================================================================

 GLFW as a Library

A library is a collection of reusable functions that help developers perform specific tasks without writing them from scratch.

✅ GLFW provides a set of C functions for:

    Creating windows (glfwCreateWindow()).
    Handling input (glfwSetKeyCallback()).
    Managing OpenGL contexts (glfwMakeContextCurrent()).

📌 Since GLFW is compiled as libglfw.so (Linux) or glfw3.dll (Windows), it acts as a shared/static library.

A framework provides a structured way to develop applications.

✅ GLFW acts as a framework by managing:

    The event loop (glfwPollEvents()).
    Graphics API integration (OpenGL/Vulkan).
    System windowing (cross-platform abstraction).

📌 Because GLFW defines how your program interacts with the OS for graphics, it provides a "framework" for OpenGL development.
GLFW is mainly a library but behaves like a framework because it handles low-level windowing, input, and rendering context, letting you focus on OpenGL/Vulkan code.

🚀 In fract-ol, you use GLFW as both a library (linking -lglfw) and a framework (handling window/input logic).
------------------------------------------------------------------------