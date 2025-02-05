/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malderbrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 16:49:07 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/05 16:16:04 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"

void calculate_mandelbrot(t_fractal *fr)
{
    int i;
    double x_temp;

    fr->name = "mandelbrot";
    i = 0;
    fr->zx = 0.0;
    fr->zy = 0.0;
    fr->cx = (fr-> x / fr->zoom) + fr->offset_x;
    fr->cy = (fr->y / fr->zoom) + fr->offset_y;
    while (++i < fr->max_iterations)
    {
        x_temp = fr->zx * fr->zx - fr->zy * fr->zy + fr->cx;
        fr->zy = 2.0 * fr->zx * fr->zy + fr->cy;
        fr->zx = x_temp;
        if (fr->zx * fr->zx + fr->zy * fr->zy >= __DBL_MAX__)
            break;
    }
    if ( i == fr->max_iterations)
        put_color_to_px(fr, fr->x, fr->y, BLACK);
    else
        put_color_to_px(fr, fr->x, fr->y, fr->color * i);
}

/*
Zn+1​=Zn2​+C

Start with Z0=0+0iZ0​=0+0i (always the same for Mandelbrot).
Compute the next ZZ value by squaring it and adding CC (a constant complex number).
Keep repeating until either:

    ∣Z∣∣Z∣ (its magnitude) exceeds 2, meaning it escapes.
    We reach the maximum iteration limit, meaning it’s inside the fractal.
    Expanding Z2Z2 Mathematically

Since Z=x+yiZ=x+yi, squaring it:
Z2=(x+yi)2=x2−y2+2xyi
Z2=(x+yi)2=x2−y2+2xyi

So, separating real and imaginary parts:

    New Real Part: x′=x2−y2+cxx′=x2−y2+cx​
    New Imaginary Part: y′=2xy+cyy′=2xy+cy​

Thus, the iterative formulas are:
zxn+1=zxn2−zyn2+cx
zxn+1​=zxn2​−zyn2​+cx
zyn+1=2⋅zxn⋅zyn+cy
zyn+1​=2⋅zxn​⋅zyn​+cy

where:

    (cx,cy)(cx,cy) is the constant C (the pixel’s complex coordinate).
    (zx,zy)(zx,zy) is the current value of ZZ.
*/