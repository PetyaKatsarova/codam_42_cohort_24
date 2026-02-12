#include <stdlib.h>
#include <stdio.h>

  typedef struct  s_point
  {
    int           x;
    int           y;
  }               t_point;

void  flood_fill(char **tab, t_point size, t_point begin)
{
    int el = tab[begin.y][begin.x];
    
    if (begin.y < 0 || begin.y >= size.y || begin.x < 0 || begin.x >= size.x || tab[begin.y][begin.x] != el)
        return;
    tab[begin.y][begin.x] = 'F';
    //(t_point){...} creates a temporary struct of type t_point with specified values.
    flood_fill(tab, size, (t_point){begin.x-1, begin.y});
    flood_fill(tab, size, (t_point){begin.x+1, begin.y});
    flood_fill(tab, size, (t_point){begin.x, begin.y-1});
    flood_fill(tab, size, (t_point){begin.x, begin.y+1});
}

int fill_arr(int x, int y)
{
    // TODO
}