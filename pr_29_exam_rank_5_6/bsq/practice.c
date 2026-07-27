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

static void print_grid(t_map *m)
{
    for (int i = 0; i < m->h; i++)
    {
        fputs(m->grid[i], stdout);
        fputs("\n", stdout);
    }
}

static int read_header(FILE *fp, t_map *m)
{
    char *junk;
    ssize_t len;
    size_t cap;

    if (fscanf(fp, "%d %c %c %c", &m->h, &m->e, &m->o, &m->f) != 4)
        return -1;
    junk = NULL;
    cap = 0;
    len = getline(&junk, &cap, fp);
    free(junk); // remember!!
    if (len == -1 || m->h < 1)
        return (-1);
    if (m->e == m->o || m->e == m->f || m->o == m->f) return -1;
    return 0;
}

static int is_valid_line(t_map *m, char *line)
{
    for (int i = 0; i < m->w; i++)
    {
        if (line[i] != m->e && line[i] != m->o)
            return 0;
    }
    return 1;
}

static int read_grid(FILE *fp, t_map *m)
{
    ssize_t len;
    size_t  cap;
    char    *line;

    m->grid = malloc((size_t)m->h * sizeof(char *));
    if (!m->grid) return -1;
    m->w = -1;
    for (int i = 0; i < m->h; i++)
    {
        line  = NULL;
        cap = 0;
        len = getline(&line, &cap, fp);
        // if (len == -1)  remember Pip!!
        if (len < 1 || line[len - 1] != '\n')
            return (free(line), free_grid(m->grid, i), -1);
        line[--len] = '\0'; // remember !!!  \n check + add \0
        if (m->w == -1)
            m->w = (int)len;
        if (m->w != (int)len || m->w < 1 || !is_valid_line(m, line))
            return (free(line), free_grid(m->grid, i), -1);
        m->grid[i] = line;
    }
    return 0;
}

static int get_lowest(t_map *m, int *dp,  int i, int j)
{
    int v;

    if (m->grid[i][j] == m->o) return 0;
    if (i == 0 || j == 0)
        return 1;
    v = dp[(size_t)i * m->w + j -1]; // left
    if (dp[(size_t)(i - 1) * m->w + j -1] < v)
        v = dp[(size_t)(i - 1) * m->w + j -1];
    if (dp[(size_t)(i - 1) * m->w + j] < v)
        v = dp[(size_t)(i - 1) * m->w + j];
    return (v + 1);
}

static void fill_square(t_map *m, int bi, int bj, int side)
{
    for (int i = bi - side + 1; i <= bi; i++)
    {
        for (int j = bj - side + 1; j <= bj; j++)
        {
            m->grid[i][j] = m->f;
        }
    }
}

static int solve(t_map *m)
{
    int *dp;
    int best = 0, bi = 0, bj = 0;

    dp = calloc((size_t)m->h * (size_t)m->w, sizeof(int));
    if (!dp) return -1;
    for (int i = 0; i < m->h; i++)
    {
        for (int j = 0; j < m->w; j++)
        {
            size_t idx = (size_t)i * m->w + j;
            dp[idx] = get_lowest(m, dp, i, j);
            if (dp[idx] > best)
            {
                best = dp[idx];
                bi = i;
                bj = j;
            }
        }
    }
    if (best > 0)
        fill_square(m, bi, bj, best);
    free(dp); // si it correct???
    return 0;
}

static int process(FILE *fp)
{
    t_map m; // rememmber!! no *

    if (read_header(fp, &m) == -1) return -1;
    if (read_grid(fp, &m) == -1) return -1;
    if (solve(&m) == -1) return (free_grid(m.grid, m.h), -1);
    print_grid(&m);
    free_grid(m.grid, m.h);
    return 0;
}

int main(int argc, char **argv)
{
    FILE *fp;

    if (argc == 1)
    {
        if (process(stdin) == -1)
            fprintf(stderr, "map error\n");
        return 0;
    }
    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (!fp || process(fp) == -1)
            fprintf(stderr, "map error\n");
        if (fp)
            fclose(fp);
        if (argc > 2)
            fprintf(stdout, "\n");
    }
    return 0;
}