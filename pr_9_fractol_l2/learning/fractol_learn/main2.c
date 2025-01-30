/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 19:05:05 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/01/30 19:21:11 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <GLFW/glfw3.h>
#include <stdio.h>
// gcc main2.c -o glfw_example -lglfw  // opens black window!!!


// Callback function for window close event
void window_close_callback(GLFWwindow* window) {
    printf("Window is closing...\n");
}

// Callback for keyboard events
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            printf("ESC pressed! Closing window...\n");
            glfwSetWindowShouldClose(window, 1); // Close window
        }
        if (key == GLFW_KEY_UP) {
            printf("Up arrow pressed!\n");
        }
        if (key == GLFW_KEY_DOWN) {
            printf("Down arrow pressed!\n");
        }
    }
}

/*
run the GLWF lightweight graphical framework for display of window, catch events(close, mouse up etc)

    gcc main2.c -lglfw && ./a.out
*/
int main() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // Create a windowed mode window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    
    // Set a callback for when the window is closing
    glfwSetWindowCloseCallback(window, window_close_callback);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);  // Swap front and back buffers
        glfwPollEvents();         // Poll for and process events
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

/*
gcc main.c -o glfw_example -lglfw

    THEORY:
    GLFW is a lightweight library that allows creating windows, handling input (keyboard, mouse), and managing OpenGL contexts. It is used in fract-ol for rendering fractals in an interactive window.
    What is glfwSwapBuffers()?

    glfwSwapBuffers(window); is a function in GLFW that updates the display by swapping the front and back buffers.
    Why Do We Need Buffer Swapping?

        Double buffering is used to avoid flickering and tearing.
        The back buffer is where new frames are drawn off-screen.
        The front buffer is what is currently displayed on the screen.
        glfwSwapBuffers() swaps the back buffer with the front buffer so the new image appears smoothly.
        while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
        glfwSwapBuffers(window);       // Swap back buffer to front
        glfwPollEvents();              // Process user input/events
    }

        Without glfwSwapBuffers(), you won't see updates on the screen
        glfwSwapBuffers() ensures smooth rendering.
    ✅ Prevents screen tearing and flickering.
    ✅ Needed for all OpenGL-based applications.
*/