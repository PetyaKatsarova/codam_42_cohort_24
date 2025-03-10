#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Flood fill is a recursive algorithm used to fill connected regions in a grid-based structure. It's commonly used in:

Graphics: Color-filling tools (like MS Paint).
Games: Marking visited areas in tile-based maps.
Robotics: Mapping unknown environments.
Maze Solving: Identifying reachable areas.

Given a starting point (x, y), flood fill replaces all connected cells of the same value with a new value.
It explores in four directions (up, down, left, right).
Uses recursion (or a stack-based approach) to process neighboring cells.

char **tab is a dynamically allocated 2D array (grid).
Each row is a char * (array of characters), and tab is a pointer to these rows.
*/

typedef struct s_point
{
    int x;
    int y;
} t_point;

void	flood_fill(char **tab, t_point size, t_point begin)
{
    char    temp;
    t_point next;

    temp = tab[begin.y][begin.x];
    if (temp == 'Y') return;
    tab[begin.y][begin.x] = 'Y';
    if (begin.y > 0 && tab[begin.y - 1][begin.x] == temp)
    {

        next.y = begin.y - 1;
        next.x = begin.x;
        flood_fill(tab, size, next);
    }
    if (begin.x > 0 && tab[begin.y][begin.x -1] == temp)
    {
        next.y = begin.y;
        next.x = begin.x - 1;
        flood_fill(tab, size, next);

    }
    if (begin.y < size.y - 1 && tab[begin.y +1][begin.x] == temp)
    {
        next.y = begin.y + 1;
        next.x = begin.x;
        flood_fill(tab, size, next);
    }
    if (begin.x < size.x - 1 && tab[begin.y][begin.x + 1] == temp)
    {
        next.y = begin.y;
        next.x = begin.x + 1;
        flood_fill(tab, size, next);
    }
}

void print_the_thing(char **tab, t_point size)
{
    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
            printf("%c - ", tab[i][j]);
        printf("\n");
    }
}
// cc -Werror -Wextra -Wall flood_fill.c && ./a.out
// cc -g -Werror -Wextra -Wall flood_fill.c && valgrind --leak-check=full ./a.out
int main()
{
    char **tab;
    t_point size = {5, 5};

    tab = malloc(sizeof(char *) * size.y);
    if (!tab) return (-1);
    for (int i = 0; i < size.y; i++)
    {
        tab[i] = malloc(sizeof(char) * size.x);
        for (int j = 0; j < size.x; j++)
        {
            tab[i][j] = (i % 2 == 0 ? 'X' : '*');
        }
    }
    printf("b4 flood-fill:\n");
    print_the_thing(tab, size);
    printf("Afrter flood-fill:\n");
    t_point begin = {1, 1};
    flood_fill(tab, size, begin);
    print_the_thing(tab, size);
    for (int i = 0; i < size.y; i++)
        free(tab[i]);
    free(tab);
}



