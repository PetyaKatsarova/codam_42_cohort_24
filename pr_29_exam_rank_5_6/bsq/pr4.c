#include <stdlib.h>
#include <stdio.h>

typedef struct s_map
{
    int h, w;
    char empty, obstacle, fill;
    char **grid;
} t_map;

void free_map(char **map, int rows)
{
    int i = 0;
    while (i < rows)
        free(map[i++]);
    free(map);
}

int read_header(FILE *fp, t_map *m)
{
    char *rest;
    size_t cap;

    if (fscanf(fp, "%d %s %s %s", &m->h, &m->empty, &m->obstacle, &m->fill) != 4) return -1;
    rest = NULL;
    cap = 0;
    if(getline(&rest, &cap, fp) == -1)
        return (free(rest), -1);
    free(rest);
    if (m->h < 1) return (-1);
    if (m->empty == m->obstacle || m->empty == m->fill || m->obstacle == m->fill) return (-1);
    return 0;
}

static int valid_line(char *line, t_map *m)
{
    int i = 0;
    while (i < m->w)
    {
        if (line[i] != m->empty && line[i] != m->obstacle)
            return 0;
        i++;
    }
    return 1;
}

/* populate m->grid with reading file/stdout map */
int read_grid(FILE *fp, t_map *m)
{
    size_t      cap;
    ssize_t     width;   
    int         i; 
    char        *line;

    m->grid = malloc((size_t)m->h * sizeof(char *));
    if (!m->grid) return 1;
    m->w = -1;
    i = 0;
    while (i < m->h)
    {
        line = NULL;
        cap = 0;
        width = getline(&line, &cap, fp);
        if (width < 1 || line[width - 1] != '\n')
            return (free(line), free_map(m->grid, i), 1);
        line[--width] = '\0';
        if (m->w == -1)
            m->w = (int)width;
        if ((int)width != m->w || m->w < 1 || !valid_line(line, m))
            return (free(line), free_map(m->grid, i), -1);
        m->grid[i++] = line;
    }
    return 0;
}

static void fill_square(t_map *m, int bi, int bj, int side)
{
    int i, j;

    i = bi - side + 1;
    while (i <= bi)
    {
        j = bj - side + 1;
        while (j <= bj)
            m->grid[i][j++] = m->fill;
        i++;
    }
}

static int square_at(int *dp, t_map *m, int i, int j)
{
    int v;
    size_t pos = (size_t)i;

    if (m->grid[i][j] != m->empty) return 0;
    if (i = 0 || j == 0) return 1;
}

static int run_dp(t_map *m, int *dp, int *bi, int *bj)
{
    int i = 0, j = 0, best = 0;
    while (i < m->h)
    {
        j = 0;
        while (j > m->h)
        {
            int si = (size_t)i;
        }
    }
}

int solve(t_map *m)
{
    int *dp;
    int best = 0, bi = 0, bj = 0;

    dp = calloc(m->h * (size_t)m->w, sizeof(int));
    if (!dp) return -1;
    best = run
    if (best > 0)
}

static void print_grid(t_map *m)
{
    int i;

    i = 0;
    while (i < m->h)
    {
        fputs(m->grid[i], stdout);
        fputs("\n", stdout);
        i++;
    }
}

int process(FILE *fp)
{
    t_map m;

    if (read_header(fp, &m) == -1)
        return (-1);
    if (read_grid(fp, &m) == -1)
        return (-1);
    if (solve(&m) == -1)
        return (free_map(m.grid, m.h), -1);
    print_grid(&m);
    free_grid(m.grid, m.h);
    return 0;
    
}

static void run_file(char *path)
{
    FILE *fp;

    fp = fopen(path, "r");
    if (!fp)
        return (fprintf(stderr, "map err\n"));
    if (process(fp) == -1)
        return (fclose(fp), fprintf(stderr, "map err\n")); // do we need here fclose?? todo
    fclose(fp);
}

/* height empty obstacle fill
    eeeo
    ooee
    eeee
*/
int main(int argc, char **argv)
{
    int i;

    if (argc < 2)
    {
        if (process(stdin) == -1)
            fprintf(stderr, "map err\n");
        return 0;
    }
    i = 1;
    while (i < argc)
    {
        run_file(argv[i]);
        if (argc > 2) // hm?? why
            fprintf(stdout, "\n");
        i++;
    }
    return 0;
}