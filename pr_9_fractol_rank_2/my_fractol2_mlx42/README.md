fract’ol
Computer Graphics Fractals
Summary: This project is about creating graphically beautiful fractals.

Use graphical library: the MiniLibX! This library was
developed internally and includes basic necessary tools to open a window, create images
and deal with keyboard and mouse events.
This will be the opportunity for you to get familiar with the MiniLibX, to discover
or use the mathematical notion of complex numbers, to take a peek at the concept of
optimization in computer graphics and practice event handling.

** CONDITIONS **
Program name fractol
Turn in files Makefile, *.h, *.c
Makefile NAME, all, clean, fclean, re
Arguments The type of fractal to display and any other option
available
External functs.
• open, close, read, write,
malloc, free, perror,
strerror, exit
• All functions of the math
library (-lm compiler option,
man 3 math)
• All functions of the MiniLibX
• ft_printf and any equivalent
YOU coded
Libft authorized Yes
Description This project is about creating a small fractal
exploration program. First, you have to know what
a fractal is.

fract’ol Computer Graphics Fractals
V.1 Rendering
• Your program must offer the Julia set and the Mandelbrot set.
• The mouse wheel zooms in and out, almost infinitely (within the limits of the
computer). This is the very principle of fractals.
• You must be able to create different Julia sets by passing different parameters to
the program.
• A parameter is passed on the command line to define what type of fractal will be
displayed in a window.
◦ You can handle more parameters to use them as rendering options.
◦ If no parameter is provided, or if the parameter is invalid, the program displays
a list of available parameters and exits properly.
• You must use at least a few colors to show the depth of each fractal. It’s even
better if you hack away on psychedelic effects.
Graphic management
• Your program has to display the image in a window.
• The management of your window must remain smooth (changing to another win-
dow, minimizing, and so forth).
• Pressing ESC must close the window and quit the program in a clean way.
• Clicking on the cross on the window’s frame must close the window and quit the
program in a clean way.
• The use of the images of the MiniLibX is mandatory.
Bonus
You will get some extra points with the following features:
• One more different fractal (more than a hundred different types of fractals are
referenced online).
• The zoom follows the actual mouse position.
• In addition to the zoom: moving the view by pressing the arrows keys.
• Make the color range shift.
The bonus part will only be assessed if the mandatory part is
PERFECT. Perfect means the mandatory part has been integrally done
and works without malfunctioning. If you have not passed ALL the
mandatory requirements, your bonus part will not be evaluated at all.
