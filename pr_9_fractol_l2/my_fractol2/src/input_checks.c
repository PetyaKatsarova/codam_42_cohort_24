#include "../include/fract-ol.h"

static void print_menu()
{
    ft_putendl_fd("Invalid args.", 1);
    ft_putendl_fd("You can choose from: mandelbrot or julia", 1);
}

int is_valid_input(int argc, char **argv)
{
    if (argc == 2 && (ft_strncmp(argv[1], "mandelbrot", 10) == 0 || ft_strncmp(argv[1], "julia", 5) == 0))
        return (1); // true
    else
        print_menu();
    return (0);
}