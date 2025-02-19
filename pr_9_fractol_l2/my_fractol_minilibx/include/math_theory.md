cx, cy	Complex number C, corresponding to a pixel's mapped coordinate.
zx, zy	Current complex number ZnZn​ in iteration.
x_temp	Temporary storage for zx during the update.
x, y	Pixel coordinates on the screen.
zoom	Controls the scaling of the Mandelbrot set.
offset_x, offset_y	Allows panning by shifting the center of the view.
max_iterations	Limits the number of iterations per pixel.

MANDELBROT:
Before iteration:

    Set Z0=(zx,zy)=(0,0)Z0​=(zx,zy)=(0,0).
    Compute C=(cx,cy)C=(cx,cy), which represents a transformed pixel coordinate:

cx=xzoom+offsetx
cx=zoomx​+offsetx​
cy=yzoom+offsety
cy=zoomy​+offsety​