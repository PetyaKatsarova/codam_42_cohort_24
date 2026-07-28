typedef struct s_map
{
	char	**grid;
	int		h;
	int		w;
	char	e;
	char	o;
	char	f;
} t_map;

static int read_header(fp, *m)
{
	fscan(fp, "%d %c %c %c", m->h, ..)
	junk = NULL;
	size_t cap = 0;
	ssize_t len = getline(fp, &junk, &cap);
	free(junk)
	if (len < 1) ....
	if (m->e == m->o etc... 
}

static int read_map(*fp, *m)
{
	ssize len, size cap;
	char *line;
	m->grid = malloc((size_t)m->h * sizeof(char *))
	m->w = -1;
	for (int i = 0; i < m=>h)

		len = getline(fp, &line, &cap);
		if (mw ==-1)
			mw = (int)len;
		if (mw < 1 || mw != '\n')..
		if (validate_line(only mo, me), what else????)..
		map->grid[i] = line;
}

int find_lowest(*dp!!,m, i, j)
{
	int v;
	if (m->grid[idx] == mo) return 0;
	if (i == 0 || j == 0) return 1;
	v = m->grid[(size_t)(i - 1) * mg->w + j];
	...
	return v + 1;
}

int fill_sq(dp, m, bi, bj, best)
{
	for (i < bi - best + 1; i <= bi; i++)
		for (j < )
			m->gr[i][j] = m->f;
}

static int solve(*m)
{
	int *dp;
	int bi, bj, best = 0;
	dp = calloc
	for (int i < h)
		for (int j < w)
			dp[idx] = find_lowest(m, i, j);
		
		
}

static int process(fp)
{ 
	t_map map;// !! no*
	read_header // &m everywhere
	read_map
	solve 
	printsqr
	free_grid
}

int main()
{
	FILE *fp;

	fp = fopen(argv[i], "r");
	if (!fp) // !! fclose(fp)
		...
	process(fp);
}