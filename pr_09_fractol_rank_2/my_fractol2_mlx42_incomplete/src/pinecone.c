#include "../include/fract-ol.h"

// Recursive function to draw pine cone fractal
static void calculate_pinecone(t_fractal *fr, int x_center, int y_center, double angle, double radius, int depth)
{
    if (depth > 0) {
        // Calculate current point in polar coordinates
        int x = x_center + radius * cos(angle);
        int y = y_center + radius * sin(angle);

        // Draw pixel at the calculated position
        mlx_put_pixel(fr->img, x, y, fr->color);

        // Recursively draw smaller branches
        calculate_pinecone(fr, x_center, y_center, angle + M_PI / 6, radius * 0.9, depth - 1);  // Adjust angle and reduce radius
        calculate_pinecone(fr, x_center, y_center, angle - M_PI / 6, radius * 0.9, depth - 1);  // Adjust angle and reduce radius
    }
}

// Function to initialize and draw the pine cone fractal
void draw_pinecone(void *fr_void)
{
    t_fractal *fr;

    fr = (t_fractal *)fr_void;
    int x_center = SIZE / 2;
    int y_center = SIZE / 2;
    double initial_radius = 200.0;  // Starting radius
    int max_depth = 100;  // Max recursion depth

    // Start drawing the pine cone fractal
    calculate_pinecone(fr, x_center, y_center, 0, initial_radius, max_depth);
    mlx_image_to_window(fr->mlx, fr->img, 0, 0);
}
