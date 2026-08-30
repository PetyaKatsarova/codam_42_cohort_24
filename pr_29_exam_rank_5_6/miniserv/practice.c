#include <sys/types.h>          /* See NOTES */
#include <sys/select.h> // fd_set
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

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

void fatal()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

int 		g_maxfd, g_next, g_serv;
fd_set 		g_active, g_read, g_write;
char 		*g_out[FD_SETSIZE], *g_buf[FD_SETSIZE], g_head[128];
int 		g_id[FD_SETSIZE]; //max num fds

/*write, close, select, socket, accept, listen, send, recv, bind, strstr, malloc, realloc, free, calloc, bzero, atoi, sprintf, strlen, exit, strcpy, strcat, memset

  fd_set g_active, g_read, g_write;
  No constructor call needed. It's just memory (a struct wrapping a bit array internally) — declaring it reserves the bits, all garbage until you
  initialize them.

  You initialize/manipulate it with 4 macros (not real functions, they're bit-twiddling macros):
  - FD_ZERO(&set) — clear all bits (set all to 0)
  - FD_SET(fd, &set) — turn bit fd on
  - FD_CLR(fd, &set) — turn bit fd off
  - FD_ISSET(fd, &set) — test if bit fd is on

*/
void setup_server(int port)
{
	struct sockaddr_in servaddr;

	g_serv = socket(AF_INET, SOCK_STREAM, 0);  // prot
	if (g_serv < 0) fatal();
	g_maxfd = g_serv;
	FD_ZERO(&g_active);
	FD_SET(g_serv, &g_active);
	bzero(&servaddr, sizeof(servaddr)); //protect?

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = (1 << 24 | 127); 
	servaddr.sin_port = (port << 8 | port >> 8);

	if ((bind(g_serv, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
		fatal();
	if (listen(g_serv, 10) != 0)
		fatal();
}

void flush_client(int fd)
{
	int ret_bytes;
	char *rest;

	if (g_out[fd] == NULL) return;
	ret_bytes = send(fd, g_out[fd], strlen(g_out[fd]), 0);
	if (ret_bytes <= 0) return;
	if (g_out[fd][ret_bytes] == 0)
	{
		free(g_out[fd]);
		g_out[fd] = NULL;
		return;
	}
	rest = malloc(strlen(g_out[fd] + ret_bytes) + 1);
	if (rest == NULL) return;
	free(g_out[fd]);
	g_out[fd] = rest;
}

void broadcast(int except, char *str)
{
	for (int i = 0; i <= g_maxfd; i++)
	{
		if (i != g_serv && i != except && FD_ISSET(i, &g_active))
		{
			g_out[i] = str_join(g_out[i], str);
			if (g_out[i] == NULL) fatal();
		}
	}
}
void accept_client()
{
	struct sockaddr_in  cli;
	socklen_t			len;
	int					connfd;

	len = sizeof(cli);
	connfd = accept(g_serv, (struct sockaddr *)&cli, &len);
	if (connfd < 0) return;
	if (connfd > FD_SETSIZE) return (close(connfd));
	if (connfd > g_maxfd)
		g_maxfd = connfd;
	g_id[connfd] = g_next++;// assign each client id: from 0
	g_buf[connfd] = NULL;
	g_out[connfd] = NULL;
	sprintf(g_head, "server: client %d just arrived\n", g_id[connfd]);
	broadcast(connfd, g_head);
}

void handle_client(int fd)
{
	int r_bytes, r;
	char *msg, recv_buf[10001];

	r_bytes = recv(fd, recv_buf, 100000, 0);
	if (r_bytes <= 0)
	{
		sprintf(g_head, "server: client %fd just left\n", g_id[fd]);
		broadcast(fd, g_head);
		free(g_buf[fd]);
		g_buf[fd] = NULL;
		free(g_out[fd]);
		g_out[fd] = NULL;
		FD_CLR(fd, &g_active);//rmv fd from sellect
		return (close(fd));
	}
	recv_buf[r_bytes] = 0;
	g_buf
}

int main(int argc, char **argv)
{
	int fd;
	
	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	g_maxfd = 0;
	g_next = 0;
	setup_server(atoi(argv[1]));
	while (1)
	{
		g_read = g_active;
		g_write = g_active;
		if (select(g_maxfd + 1, &g_read, &g_write, NULL, NULL) < 0) continue;
		fd = 0;
		while (fd <= g_maxfd)
		{
			if (fd != g_serv && FD_ISSET(fd, &g_write))
				flush_client(fd);
			if (FD_ISSET(fd, &g_read))
			{
				if (fd == g_serv)
					accept_client();
				else
					handle_client(fd);
			}

			fd++;
		}

	}
	return 0;
}