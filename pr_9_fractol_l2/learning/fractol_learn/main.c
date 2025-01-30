#include <stdio.h>

/*
!!NB:
for using the MLX_42: in the makefile do: git clone -b '2.4.1' https://github.com/codam-coding-college/MLX42.git and aftet that the command for build:asm
if lib not build: to compile: 
https://github.com/codam-coding-college/MLX42.git
cd MLX42
cmake -B build
cmake --build build -j4

gcc main.c ../../../MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread -lm
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <../../../MLX42/include/MLX42/MLX42.h>
#include "/home/pekatsar/Desktop/unstoppable/MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

// #include <GLFW/glfw3.h>
// #include <stdio.h>
// // gcc main.c -o glfw_example -lglfw  // opens black window!!!


// // Callback function for window close event
// void window_close_callback(GLFWwindow* window) {
//     printf("Window is closing...\n");
// }

// int main() {
//     // Initialize GLFW
//     if (!glfwInit()) {
//         printf("Failed to initialize GLFW\n");
//         return -1;
//     }

//     // Create a windowed mode window and OpenGL context
//     GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);
//     if (!window) {
//         printf("Failed to create GLFW window\n");
//         glfwTerminate();
//         return -1;
//     }

//     // Make the OpenGL context current
//     glfwMakeContextCurrent(window);

//     // Set a callback for when the window is closing
//     glfwSetWindowCloseCallback(window, window_close_callback);

//     // Main loop
//     while (!glfwWindowShouldClose(window)) {
//         glfwSwapBuffers(window);  // Swap front and back buffers
//         glfwPollEvents();         // Poll for and process events
//     }

//     // Cleanup
//     glfwDestroyWindow(window);
//     glfwTerminate();
//     return 0;
// }

