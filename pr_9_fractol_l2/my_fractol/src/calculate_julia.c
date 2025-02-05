/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_julia.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pekatsar <pekatsar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/05 11:13:02 by pekatsar      #+#    #+#                 */
/*   Updated: 2025/02/05 11:14:30 by pekatsar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract-ol.h"



/*
Zn+1​=Zn2​+C
Difference from Mandelbrot

    In Mandelbrot, CC is different for each pixel.
    In Julia, CC is a fixed constant, and each pixel starts at a different Z value (the pixel's complex coordinate).

Thus, the formulas are identical, but:

    Mandelbrot: Starts at Z0=0Z0​=0, varies CC.
    Julia: Starts at Z0Z0​ (pixel’s position), fixes CC.
    For each pixel (x,y)(x,y), we:

    Convert it to a complex number.
    Apply the iteration formula.
    Check if ∣Z∣∣Z∣ exceeds 2 or we reach max iterations.
    Color the pixel based on how many iterations before escaping.
*/