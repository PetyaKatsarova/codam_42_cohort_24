#include "../include/fract_ol.h"

static double get_main_part(char *str)
{
    int     i;
    double  main;
    double  factor;

    i = 0;
    factor = 1.0;
    main = 0.0;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            factor = -1.0;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        main = main * 10.0 + (str[i] - '0');
        i++;
    }
    return (main * factor);
}

static int main_len(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
        i++;
    return (i);
}

double str_to_double(char *str)
{
    double  result;
    int     i;
    double  decimal_place;

    result = get_main_part(str);
    i = main_len(str);
    
    if (str[i] == '.' || str[i] == ',')
    {
        i++;
        decimal_place = 0.1;
        while (str[i] >= '0' && str[i] <= '9')
        {
            result += (str[i] - '0') * decimal_place;
            decimal_place /= 10.0;
            i++;
        }
    }
    return (result);
}

int is_double(char *str)
{
    unsigned int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (str[i] < '0' || str[i] > '9')
        return (EXIT_FAILURE);
    while (str[i] >= '0' && str[i] <= '9')
        i++;
    if (str[i] == '.' || str[i] == ',')
    {
        i++;
        while (str[i] >= '0' && str[i] <= '9')
            i++;
    }
    if (str[i] == '\0')
        return (1); // true Ensure no extra characters after the number
    return (0);
}