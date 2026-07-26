#include <stdio.h>
#include <stdlib.h>


typedef struct s_map
{
    char    **grid;
    int     w;      /* width  (cols) */
    int     h;      /* height (rows) */
    char    e;      /* empty    */
    char    o;      /* obstacle */
    char    f;      /* full     */
}   t_map;

void free_grid(char **grid, int rows)
{
    for (int i = 0; i < rows; i++)
        free(grid[i]);
    free (grid);
}

/*fscanf(), getline(consume trailing new line of header)*/
static int read_header(FILE *fp, t_map *m)
{
    char *junk;
    size_t cap;
    ssize_t r;

    if (fscanf(fp, "%d %c %c %c", &m->h, &m->e, &m->o, &m->f) != 4)
        return -1;
    junk = NULL;
    cap = 0;
    r =  getline(&junk, &cap, fp);
    free(junk);
    if (r == -1 || m->h < 1) return -1;
    if (m->e == m->o || m->e == m->f || m->o == m->f) return -1;
    return 0;
}

static int is_valid_line(const char *line, t_map *m)
{
    for (int i = 0; i < m->w; i++)
        if (line[i] != m->e && line[i] != m->o)
            return 0;
    return 1;
}

/* only here alloc grid memory */
static int read_grid(FILE *fp, t_map *m) {
    char    *line;
    size_t  cap;
    ssize_t len;

    m->grid = malloc((size_t)m->h * sizeof(char *));
    if (!m->grid)   return -1;
    m->w = -1;
    for (int i = 0; i < m->h; i++)
    {
        line = NULL;
        cap = 0;
        len = getline(&line, &cap, fp);
        if (len < 1 || line[len - 1] != '\n')
            return (free_grid(m->grid, i), free(line), -1);
        line[--len] = '\0';
        if (m->w == -1)
            m->w = (int)len;
        if ((int)len != m->w || m->w < 1 || !is_valid_line(line, m))
            return (free(line), free_grid(m->grid, i), -1);
        m->grid[i] = line;
    }
    return 0;
}

/* from map get lowest to assing later to dp */
static int get_lowest(int *dp, t_map *m, int i, int j)
{
    int v;

    if (m->grid[i][j] == m->o) return 0;
    if (i == 0 || j == 0) return 1;
    v = dp[(size_t)(i - 1) * m->w + j]; // top
    if ( v > dp[(size_t)i * m->w + j - 1]) // left
        v = dp[(size_t)i * m->w + j - 1];
    if (v > dp[(size_t)(i - 1) * m->w + j - 1]) // top left
        v = dp[(size_t)(i - 1) * m->w + j - 1];
    return v + 1;
}


/* start from bi/bj - side + 1: to assign the fill till bi/bj */
static void fill_square(t_map *m, int bi, int bj, int side)
{
    for (int i = bi; i > bi - side; i--)
    {
        for (int j = bj; j > bj - side; j--)
            m->grid[i][j] = m->f;
    }
}

/* alloc mem for dp:calloc(size buff, sizeof(int)) */
static int solve(t_map *m)
{
    int *dp, best = 0, bi = 0, bj = 0;

    dp = calloc((size_t)m->h * (size_t)m->w, sizeof(int));
    if (!dp) return -1;
    for (int i = 0; i < m->h; i++)
    {
        for (int j = 0; j < m->w; j++)
        {
            size_t idx = i * m->w + j;
            dp[idx] = get_lowest(dp, m, i, j); // next cell is + 1
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
    free(dp);
    return 0;
}

// fprintf(stdout, str) 
static void print_grid(t_map *m)
{
    for (int i = 0; i < m->h; i++)
    {
        fputs(m->grid[i], stdout);
        fputs("\n", stdout);
    }
}

int process(FILE *fp)
{
    t_map m;

    if (read_header(fp, &m) == -1) return -1;
    if (read_grid(fp, &m) == -1) return -1;
    if (solve(&m) == -1) return (free_grid(m.grid, m.h), -1);
    print_grid(&m);
    free_grid(m.grid, m.h);
    return 0;
}


int main(int argc, char** argv)
{
    FILE    *fp;

    if (argc == 1) /* no args -> stdin */
    {
        if (process(stdin) == -1)
            fprintf(stderr, "map err\n");
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (!fp || process(fp) == -1)
            fprintf(stderr, "map err\n"); 
        if (fp)
            fclose(fp);
        if (argc > 2) /* blank line betwen maps */
            fprintf(stdout, "\n");
    }
// todo: do we need \n  at the end??
    return 0;
}
