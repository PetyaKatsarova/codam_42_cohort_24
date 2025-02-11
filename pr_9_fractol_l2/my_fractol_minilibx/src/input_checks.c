#include "../include/fract-ol.h"

static int  is_in_range(double d)
{
    if (d >= -2.0 && d <= 2)
        return (1);
    return (0);
}

static void print_menu()
{
    ft_putendl_fd("Invalid args.", 1);
    ft_putendl_fd("You can choose from: mandelbrot, julia, tricorn or phoenix. You can add 2 values for julia between -2 and 2", 1);
}

/*
    If not valid input: prints message for wrong args.
*/
int is_valid_input(int argc, char **argv)
{
    double num1;
    double num2;

    num1 = -4.2;
    num2 = -4.2;
    if (argc == 2 && (ft_strncmp(argv[1], "mandelbrot", 10) == 0
        || ft_strncmp(argv[1], "1", 1) == 0))
        return (1); // true
    else if ((argc == 2  || argc == 4) && (ft_strncmp(argv[1], "julia", 5) == 0
    || ft_strncmp(argv[1], "2", 1) == 0))
    {
        // -2.0 <= a <= 2.0
        if (argc == 2)
            return (1);
        if ((is_double(argv[2]) && is_double(argv[3])))
        {
            num1 = str_to_double(argv[2]);
            num2 =str_to_double(argv[3]);
            if (is_in_range(num1) && is_in_range((num2)))
                return (1); // true
        }
    }
    else if (argc == 2 && (ft_strncmp(argv[1], "tricorn", 7) == 0
    || ft_strncmp(argv[1], "3", 1) == 0))
        return (1); // true
    else if (argc == 2 && (ft_strncmp(argv[1], "phoenix", 7) == 0
        || ft_strncmp(argv[1], "4", 1) == 0))
            return (1); // true
    print_menu();
    return (0);
}