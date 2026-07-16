#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct life
{
    char    **board;
    int     w;
    int     h;
} t_life;

char    **alloc_board(int w, int h);
void    fill_board(t_life *g);
int     count_neighbours(t_life *g, int row, int col);
int     next_gen(t_life *g);
void    print_board(t_life *g);
void    free_board(char **board, int h);

#endif