/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_zoom_sq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: petya <petya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:20:38 by pekatsar          #+#    #+#             */
/*   Updated: 2025/05/28 17:24:09 by petya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../lib/MLX42/include/MLX42/MLX42.h"

#define WIDTH 900
#define HEIGHT 600
#define MOVE_STEP 10 // 20 to move faster
#define ZOOM_STEP 5 // 10 to move faster
#define MIN_SIZE 10
#define MAX_SIZE 200

mlx_t *mlx;
mlx_image_t *img;
int square_size = 50;
int square_x = 375;
int square_y = 275;

void draw_square()
{
    mlx_image_t *new_img = mlx_new_image(mlx, square_size, square_size);

    for (int y = 0; y < square_size; y++)
    {
        for (int x = 0; x < square_size; x++)
            mlx_put_pixel(new_img, x, y, 0xFF8000FF);
    }
    //Instead of redrawing the entire window, we only replace the square.
    mlx_image_to_window(mlx, new_img, square_x, square_y);
    mlx_delete_image(mlx, img);
    img = new_img;
}
/*
    prevent the square from moving out of bounds
    has move left, right, up, down, zoom in and out keyboard events
    Holding Shift (Left Shift or Right Shift) doubles movement and zoom speed.
    update movement every frame
*/
void update_movement(void *param)
{
    (void) param;
    int speed = (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT) || mlx_is_key_down(mlx, MLX_KEY_RIGHT_SHIFT) ? 8 : 1);
        
    // Continuous movement if keys are held
    if (mlx_is_key_down(mlx, MLX_KEY_UP) && square_y > 0)
        square_y -= MOVE_STEP * speed;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN) && square_y + square_size + MOVE_STEP * speed < HEIGHT)
        square_y += MOVE_STEP * speed;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT) && square_x > 0)
        square_x -= MOVE_STEP * speed;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) && square_x + square_size + MOVE_STEP * speed < WIDTH)
        square_x += MOVE_STEP * speed;
    if (mlx_is_key_down(mlx, MLX_KEY_Z) && square_size + ZOOM_STEP * speed < MAX_SIZE) // zoom in: bigger
        square_size += ZOOM_STEP * speed;
    if (mlx_is_key_down(mlx, MLX_KEY_X) && square_size - ZOOM_STEP * speed > MIN_SIZE) // zoom out: smaller
        square_size -= ZOOM_STEP * speed;
        
        draw_square(); // redraw with new positions/size
}

/*
    Key callback for exiting
*/
void key_callback(mlx_key_t_data keydata, void *param)
{
    (void) param;
    if (keydata.action == MLX_PRESS)
    {
        if (keydata.key == MLX_KEY_ESCAPE) // nesed in case want to extend later
            mlx_close_window(mlx);
        
    }
}

/*
gcc move_zoom_sq.c ../../../MLX42/build/libmlx42.a -I MLX42/include -ldl -lglfw -pthread -lm 
*/
int main()
{
    mlx = mlx_init(WIDTH, HEIGHT, "Smooth moving and zooming", true);
    if (!mlx)
        return (EXIT_FAILURE);

    img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
        return (EXIT_FAILURE);

    mlx_key_hook(mlx, key_callback, NULL); // Handle ESC key exit
    mlx_loop_hook(mlx, update_movement, NULL); // run movement every frame

    draw_square(); // draws initial square
    mlx_loop(mlx); // kep window open
    
    mlx_delete_image(mlx, img);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}

/*
    FPS = Frames Per Second
    Higher FPS (e.g., 60 FPS, 120 FPS) → Smoother motion.
    Lower FPS (e.g., 30 FPS or below) → Laggy or choppy movement.
    In MLX42, mlx_loop() continuously updates the screen.
    The speed of updates depends on:

    The refresh rate of the display.
    The complexity of rendering (e.g., redrawing too much per frame slows FPS).
    The efficiency of the code (avoiding unnecessary mlx_delete_image() calls helps maintain higher FPS).

    To improve FPS:
    Optimize redrawing logic.
    Use mlx_loop_hook() instead of redrawing on keypress.
    

    you can make the square move and zoom faster and smoother by:
    Increasing step values
    Using MLX_REPEAT properly
    Adding a speed boost (Shift key)
    mlx_delete_image() is called every frame, which is slow. Instead:

    Use a background image
    Only delete/redraw the square

    In graphics programming, the screen updates many times per second to create smooth motion.
    Each update is called a frame.
    Frame rate (FPS - Frames Per Second) is the number of frames displayed per second.
    60 FPS = 60 images (frames) displayed per second.
    Higher FPS = smoother animation.
    Every time mlx_loop() runs, a new frame is drawn.
    If you call mlx_delete_image() every frame, you are deleting and recreating the image on every update, which is slow.
    void draw_square() {
    mlx_delete_image(mlx, img); // Deleting every frame (bad performance)
    img = mlx_new_image(mlx, WIDTH, HEIGHT);
    mlx_image_to_window(mlx, img, square_x, square_y);
    A frame is one screen update.
    MLX42 redraws every frame inside mlx_loop().
    Calling mlx_delete_image() every frame is inefficient.
    Optimize by only redrawing when needed instead of recreating the image every frame.

    This destroys and recreates the image every frame, which is slow and unnecessary.
    Instead, only update the image when needed.


-----------------------------------------------------
MLX_REPEAT is an event type that indicates a key is being held down.
----------------------------------------
. mlx_key_hook(mlx, key_callback, NULL)
-----------------------------------
    Registers a keyboard event listener.
    Calls key_callback() when a key is pressed, released, or held.
    NULL is an optional parameter (used if you want to pass extra data).
void key_callback(mlx_key_t_data keydata, void* param) {
    if (keydata.action == MLX_PRESS) {
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window((mlx_t*)param); // Close on ESC
    }
}
MLX_PRESS triggers when a key is pressed.
mlx_close_window(mlx) stops mlx_loop(), closing the window.

--------------------------------------------------
mlx_loop(mlx)
-------------------------------------------------
    Runs continuously, handling:
        Window updates
        Key & mouse events
        Redrawing graphics
    The program stays open until the user exits.
Without mlx_loop(), the window would open and immediately close.
The loop only stops when mlx_close_window(mlx); is called inside an event callback.

----------------------------------------------------------------
        mlx_delete_image(mlx, img)
----------------------------------------------------------------
    Removes the image from memory.
    Prevents memory leaks.
    Should be called before exiting.
    If you create multiple images but never delete them, the program consumes more memory over time.

--------------------------------------------------------
    mlx_key_hook() → Captures keyboard input.
    mlx_loop() → Keeps the window running.
    mlx_delete_image() → Frees image memory.
    mlx_terminate() → Cleans up MLX42 resources before exit.
-------------------------------------------------------
*/