
validate_map(&buf, &w, &h)
{
	get w, h, buf[i] == 'X' or '.' or '\n'
}

static int flood_fill(*buf, w, h, col_i, row_i)
{
	size = 1;
	if (col_i < 0 || col_i >= w || row_i < 0 || row_i >= h)
		return 0;
	int idx = row_i * (w + 1) + col_i;
	if (buf[idx] != 'X') return 0;
	buf[idx] = 'V';
	size += flood_fill(*buf, w, h, col_i, row_i)
	.....
}

static int get_biggest(*buf, w, h)
{
	int i = 0, size = 0, biggest = 0;
	for (int i; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int idx = i * (w + 1) + j;
			if (buf[idx] == 'X')
			{
				size = flood_fill();
			}
		}
	}
	return biggest;
}

main()
{
	char *buf;
	int w, h;
	fd = open(argv[i], O_RDONLY);
	buf = malloc(buf_size + 1);
	bytes = read(fd, buf, buf_size) /!! nb: no & for buf
	buf[bytes] = '\0';
	validate_map(&buf, &w, &h);
}