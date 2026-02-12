typedef struct s_point
{
    int x;
    int y;
} t_point;

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char tmp;
	t_point next;

	tmp = tab[begin.y][begin.x];
	tab[begin.y][begin.x] = 'F';
	if (begin.y > 0)
	{
		if (tab[begin.y - 1][begin.x] == tmp)
		{
			next.y = begin.y - 1;
			next.x = begin.x;
			flood_fill(tab, size, next);
		}
	}
	if (begin.x > 0)
	{
		if (tab[begin.y][begin.x - 1] == tmp)
		{
			next.y = begin.y;
			next.x = begin.x - 1;
            flood_fill(tab, size, next);
		}
	}
	if (begin.y < size.y - 1)
	{
    	if (tab[begin.y + 1][begin.x] == tmp)
		{
			next.y = begin.y + 1;
			next.x = begin.x;
            flood_fill(tab, size, next);
		}
    }
	if (begin.x	< size.x - 1)
    {
     	if (tab[begin.y][begin.x + 1] == tmp)
		{
			next.y = begin.y;
			next.x = begin.x + 1;
            flood_fill(tab, size, next);
		}
    }
	return ;
}
