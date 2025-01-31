/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   first_use_mlx42.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:09:49 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/31 11:21:03 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "/home/pekatsar/Desktop/unstoppable/MLX42/include/MLX42/MLX42.h"

#define WIDTH 900
#define HEIGHT 600


/*
gcc first_use_mlx42.c ../../../MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread -lm
*/
void draw_circle(mlx_image_t *img, int cx, int cy, int radius, uint32_t color)
{
	for (int y = -radius; y <= radius; y++) 
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x*x + y*y <= radius*radius)
			{
				mlx_put_pixel(img, cx + x, cy + y, color);
			}
		}
	}
}

int main (void)
{
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "MLX42 - 3 Circles", true);
	if (!mlx)
		return (EXIT_FAILURE);
	
	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (EXIT_FAILURE);

	// 300 is: center is on the same y axis: horizontally same
	draw_circle(img, 100, 300, 50, 0xFF0000FF); // red
	draw_circle(img, 300, 300, 60, 0x00FF00FF); // Green
    draw_circle(img, 500, 300, 70, 0x0000FFFF); // Blue

	mlx_image_to_window(mlx, img, 100, 50);
	mlx_loop(mlx); // keep the window open
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}



/*
	cx, cy → The center coordinates of the circle.
	radius → The distance from the center to the edge of the circle.
    mlx_image_t is a structure (struct) used in MLX42 to represent an image or a texture.
    It stores pixel data and can be drawn onto the window.
    Defined in MLX42/include/MLX42/MLX42.h.
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);

    Creates a new image buffer (img) where you can draw pixels.
    You can modify it using functions like mlx_put_pixel().
    The image is later sent to the window using mlx_image_to_window().
	mlx_image_t* mlx_new_image(mlx_t* mlx, int width, int height);
	mlx_put_pixel(mlx_image_t* img, int x, int y, uint32_t color);
	mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int x, int y);
	mlx_delete_image(mlx_t* mlx, mlx_image_t* img);
	mlx_image_t* mlx_new_image(mlx_t* mlx, int width, int height);
	mlx_put_pixel(mlx_image_t* img, int x, int y, uint32_t color);
	mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int x, int y);
	mlx_delete_image(mlx_t* mlx, mlx_image_t* img);

	uint32_t is a standard integer type from <stdint.h>, defined as:

    typedef unsigned int uint32_t;

    It stores colors in ARGB format (Alpha, Red, Green, Blue).
    Each byte (8 bits) in uint32_t represents a color channel.

	Color Format in uint32_t: 0xAARRGGBB

    AA = Alpha (transparency)
    RR = Red
    GG = Green
    BB = Blue
	0xFF0000FF  // Solid Red   (Alpha=FF, R=FF, G=00, B=00)
	0x00FF00FF  // Solid Green (Alpha=FF, R=00, G=FF, B=00)
	0x0000FFFF  // Solid Blue  (Alpha=FF, R=00, G=00, B=FF)
	0x80FFFFFF  // Semi-transparent white (Alpha=80, R=FF, G=FF, B=FF

	1. Circle Equation

	A circle centered at (cx, cy) with radius r follows:
	(x−cx)2+(y−cy)2≤r2
	(x−cx)2+(y−cy)2≤r2

	Since the loop already iterates relative to the center (cx, cy), we simplify:
	x2+y2≤r2
	x2+y2≤r2

	Why Use Squared Values?

✅ Avoids expensive sqrt() function (faster computation).
✅ Works directly with integers, avoiding floating-point precision issues.

----------------- CIRCLE ----------------------------------------------------
A circle is a set of points that are all the same distance (radius) from the center (cx, cy). To find how far a point (x, y) is from the center (cx, cy), use the distance formula:
Distance=(x−cx)2+(y−cy)2
Distance=(x−cx)2+(y−cy)2
This formula gives the straight-line distance between two points.
Understanding the Circle Equation (For Dummies) 🎯

A circle is a set of points that are all the same distance (radius) from the center (cx, cy).
Step 1: What is Distance?

To find how far a point (x, y) is from the center (cx, cy), use the distance formula:
Distance=(x−cx)2+(y−cy)2
Distance=(x−cx)2+(y−cy)2
​

📌 This formula gives the straight-line distance between two points.
Step 2: Circle Definition

A point (x, y) is inside or on the circle if its distance to the center is less than or equal to the radius r:
(x−cx)2+(y−cy)2≤r
(x−cx)2+(y−cy)2​≤r
*/

/*
!!NB:
for using the MLX_42: in the makefile do: git clone -b '2.4.1' https://github.com/codam-coding-college/MLX42.git and aftet that the command for build:asm
if lib not build: to compile: 
https://github.com/codam-coding-college/MLX42.git
cd MLX42
cmake -B build
cmake --build build -j4

gcc first_use_mlx42.c ../../../MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread -lm
------------------------------------------------------
export DISPLAY=$(ip route list default | awk '{print $3}'):0

    ip route list default → Finds the default gateway (your host machine's IP).
    awk '{print $3}' → Extracts the gateway IP.
    :0 → Specifies display number 0 (default for X11).

    echo 'export DISPLAY=$(ip route list default | awk "{print $3}"):0' >> ~/.bashrc
    echo 'export LIBGL_ALWAYS_INDIRECT=0' >> ~/.bashrc
    Then apply the changes:
    source ~/.bashrc
    echo $DISPLAY
    xclock  # (if installed, to test GUI output)

    sudo apt update
    sudo apt install mesa-utils


To run Linux GUI apps, you should first install the driver matching your system below. This will enable you to use a virtual GPU (vGPU) so you can benefit from hardware accelerated OpenGL rendering.

https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps
    Intel GPU driver
    AMD GPU driver
    NVIDIA GPU driver

    wsl --update
    wsl --shutdown

    sudo apt install gnome-text-editor -y
    GIMP is a free and open-source raster graphics editor used for image manipulation and image editing, free-form drawing, transcoding between different image file formats, and more specialized tasks.

sudo apt install gimp -y

-- install dependencies on ubuntu(in wsl are extra steps)
sudo apt update
sudo apt install cmake make gcc libglfw3 libglfw3-dev libgl1-mesa-dev xorg-dev


libglfw3:amd64 (Runtime Library)

    This is the GLFW shared library that applications use at runtime.
    It provides functions to create windows, handle input, and manage OpenGL contexts.
    Installed at /usr/lib/x86_64-linux-gnu/libglfw.so.3.

2. libglfw3-dev:amd64 (Development Files)

    This package contains the headers and static libraries needed to compile programs using GLFW.
    It includes GLFW/glfw3.h (needed for #include <GLFW/glfw3.h>).
    Installed at /usr/include/GLFW/ and /usr/lib/x86_64-linux-gnu/libglfw.a.

Why Do You Need Both?

    libglfw3 → Required to run applications that use GLFW.
    libglfw3-dev → Required to compile applications that use GLFW.
    dpkg -l | grep glfw

    #include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return 1;
    }
    printf("GLFW initialized successfully\n");
    glfwTerminate();
    return 0;
}

Compile:

gcc glfw_test.c -o test -lglfw
./test

f0r3s13% which Xorg
which xclock
 
/usr/bin/Xorg
xclock not found

f0r3s13% ps aux | grep Xorg
 
root      999600  2.8  1.6 971864 135408 tty7    Ssl+ 17:18   2:26 /usr/lib/xorg/Xorg -core :0 -seat seat0 -auth /var/run/lightdm/root/:0 -nolisten tcp vt7 -novtswitch
pekatsar 1028020  0.0  0.0   8984  2432 pts/0    S+   18:42   0:00 grep Xorg


f0r3s13% echo $DISPLAY
glxinfo | grep "direct rendering"

f0r3s13% ps aux | grep Xorg

root      999600  2.9  1.6 975912 134788 tty7    Ssl+ 17:18   2:36 /usr/lib/xorg/Xorg -core :0 -seat seat0 -auth /var/run/lightdm/root/:0 -nolisten tcp vt7 -novtswitch
pekatsar 1029782  0.0  0.0   8984  2380 pts/0    S+   18:46   0:00 grep Xorg
f0r3s13% export DISPLAY=:0

f0r3s13% ./test

GLFW initialized successfully

f0r3s13% ./test

GLFW initialized successfully
f0r3s13% echo $DISPLAY
xhost
ls -l ~/.Xauthority

:0
access control enabled, only authorized clients can connect
SI:localuser:pekatsar
-rw------- 1 pekatsar piscine 1209 jan 30 17:45 /home/pekatsar/.Xauthority

echo 'export DISPLAY=:0' >> ~/.bashrc
source ~/.bashrc

echo 'export DISPLAY=:0' >> ~/.zshrc
source ~/.zshrc

GLFW (Graphics Library Framework) is an open-source library used to create windows, OpenGL contexts, and handle input events (keyboard, mouse, gamepads, etc.). It is lightweight and designed for applications that need OpenGL, Vulkan, or OpenGL ES rendering.
If you're developing graphics applications (like games, 3D rendering, fractals, or simulations), you need a way to:

    Create a window.
    Manage an OpenGL context.
    Handle input events (keyboard, mouse, etc.). GLFW does all this while remaining small, fast, and cross-platform.

    sudo apt install libglfw3 libglfw3-dev

it installs:

    Runtime Library (libglfw3) → /usr/lib/x86_64-linux-gnu/libglfw.so.3
    Development Files (libglfw3-dev) → /usr/include/GLFW/glfw3.h
    Static Library (libglfw3.a) → /usr/lib/x86_64-linux-gnu/libglfw.a
*/
// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------


