#ifndef CI2_H
#define CI2_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int validate_map(char *buf, int *width, int *height);
void flood_fill(char *buf, int w, int h, int x, int y, char fill);
int count_is(char *buf, int w, int h);
void print_is(char *buf, int w, int h);
void putnbr(int n);

#endif