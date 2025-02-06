ow Constant Pixel Drawing Works in MLX42
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