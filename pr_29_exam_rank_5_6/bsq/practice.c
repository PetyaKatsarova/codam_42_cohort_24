#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
    char    **grid;
    int     h;
    int     w;
    char    e;
    char    o;
    char    f;
} t_map;

static void free_grid(char **grid, int row)
{
    for (int i = 0; i < row; i++)
        free(grid[i]);
    free(grid);
}

void print_map(t_map *m)
{
    for (int i = 0; i < m->h; i++)
    {
        fputs(m->grid[i], stdout);
        fputs("\n", stdout);
    }
}

int read_header(t_map *m, FILE *fp)
{
    char *junk = NULL;
    size_t cap = 0;
    ssize_t len;

    if (fscanf("%d %c %c %c", &m->h, &m->e, &m->o, &m->f) != 4)
        return (-1);
    if (m->e < 32 || m->e > 126 ||
        m->o < 32 || m->o > 126 ||
        m->f < 32 || m->f > 126 )
        return (-1);
    if (m->e == m->o || m->e == m->f || m->f == m->o || m->h < 1)
        return (fputs("map err\n", stderr), -1);
    if ((len = getline(&junk, &cap, fp)) == -1)
        return (free(junk), -1);
    free(junk);
    if (len != 1 || junk[0] != '\n') //nb: junk,no len!!
        return (fputs("map err\n", stderr), -1);
    
    return 0;
}

int process(FILE *fp)
{
    t_map m;

    if (read_header(&m, fp) == -1)
        return (fputs("map err\n", stderr), -1);
    if (read_map(&m, fp) == -1)
        return (fputs("map err\n", stderr), -1);
    if (solve(&m) == -1)
        return (fputs("map err\n", stderr), -1);
    print_map(&m);
    free_grid(m.grid, m.h);    
    return 0;
}

int main (int argc, char **argv)
{
    FILE *fp;
    if (argc == 1)
    {
        if (process(stdin) == -1)
            fputs("map err\n", stderr);
        return 0;
    }
    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (!fp) return (fputs("map err\n", stderr), 1);
        if (process(fp) == -1)
            return (close(fp), fputs("map err\n", stderr), 1);
        fclose(fp);
        if (argc > 2)
            fputs("\n", stdout);
    }
    return 0;
}
