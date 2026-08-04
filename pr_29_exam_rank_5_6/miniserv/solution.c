#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>

int		g_id[65536];
char	*g_buf[65536];
int		g_maxfd;
int		g_next;
int		g_serv;
fd_set	g_active;
fd_set	g_read;
fd_set	g_write;
char	g_head[128];

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void fatal(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void broadcast(int except, char *s)
{
	int	i;
	int	len;

	len = strlen(s);
	i = 0;
	while (i <= g_maxfd)
	{
		if (i != g_serv && i != except && FD_ISSET(i, &g_write))
			send(i, s, len, 0);
		i++;
	}
}

int main(int argc, char **argv)
{
	struct sockaddr_in	servaddr;
	struct sockaddr_in	cli;
	socklen_t			len;
	int					connfd;
	int					fd;
	int					ret;
	int					r;
	char				*msg;
	char				recv_buf[100001];

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	g_maxfd = 0;
	g_next = 0;
	g_serv = socket(AF_INET, SOCK_STREAM, 0);
	if (g_serv < 0)
		fatal();
	g_maxfd = g_serv;
	FD_ZERO(&g_active);
	FD_SET(g_serv, &g_active);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(argv[1]));
	if (bind(g_serv, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
		fatal();
	if (listen(g_serv, 128) != 0)
		fatal();
	while (1)
	{
		g_read = g_active;
		g_write = g_active;
		if (select(g_maxfd + 1, &g_read, &g_write, NULL, NULL) < 0)
			continue;
		fd = 0;
		while (fd <= g_maxfd)
		{
			if (FD_ISSET(fd, &g_read))
			{
				if (fd == g_serv)
				{
					len = sizeof(cli);
					connfd = accept(g_serv, (struct sockaddr *)&cli, &len);
					if (connfd >= 0)
					{
						if (connfd > g_maxfd)
							g_maxfd = connfd;
						g_id[connfd] = g_next++;
						g_buf[connfd] = NULL;
						FD_SET(connfd, &g_active);
						sprintf(g_head, "server: client %d just arrived\n", g_id[connfd]);
						broadcast(connfd, g_head);
					}
				}
				else
				{
					ret = recv(fd, recv_buf, 100000, 0);
					if (ret <= 0)
					{
						sprintf(g_head, "server: client %d just left\n", g_id[fd]);
						broadcast(fd, g_head);
						free(g_buf[fd]);
						g_buf[fd] = NULL;
						FD_CLR(fd, &g_active);
						close(fd);
					}
					else
					{
						recv_buf[ret] = 0;
						g_buf[fd] = str_join(g_buf[fd], recv_buf);
						if (g_buf[fd] == NULL)
							fatal();
						while ((r = extract_message(&g_buf[fd], &msg)) > 0)
						{
							sprintf(g_head, "client %d: ", g_id[fd]);
							broadcast(fd, g_head);
							broadcast(fd, msg);
							free(msg);
						}
						if (r < 0)
							fatal();
					}
				}
			}
			fd++;
		}
	}
	return (0);
}