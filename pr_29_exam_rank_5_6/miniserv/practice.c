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

int g_maxfd, g_next, g_serv;
fd_set g_active, g_read, g_write;
char *g_out;

/*write, close, select, socket, accept, listen, send, recv, bind, strstr, malloc, realloc, free, calloc, bzero, atoi, sprintf, strlen, exit, strcpy, strcat, memset*/
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
	int ret;
	char *rest;


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
				flush_client();
		}

	}
	return 0;
}