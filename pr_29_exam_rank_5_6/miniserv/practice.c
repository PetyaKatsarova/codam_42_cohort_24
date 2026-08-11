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

/*
plan:
main()->setupserver(),acceptclient() , handle_client()
setupserver()->fatal();
acceptclient()->broadcast()
*/
int g_maxfd;
int g_next;
int g_servfd;

fd_set 	g_master;
fd_set	g_read;
fd_set  g_write;

int 	g_id[FD_SETSIZE];
char	*g_buf[FD_SETSIZE];
char	*g_out[FD_SETSIZE];
char	g_head[128];

/*pulls first line out of *buf, leaving erst in buf */
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

/*concats add onto buf into dynamically grown alloc buff*/
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
// socket(), fd_zero(), fdset(), bzero(), bind(), listen()
void setup_server(int port)
{
	struct sockaddr_in servaddr;

	g_servfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (g_servfd == -1)
		fatal();
	g_maxfd = g_servfd;
	FD_ZERO(&g_master); //fdset
	FD_SET(g_servfd, &g_master);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); 
	servaddr.sin_port = htons(port);
  
	// Binding newly created socket to given IP and verification 
	if (bind(g_servfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
		fatal();
	if (listen(g_servfd, 128) != 0)
		fatal();
}

void broadcast(int cfd, char *g_h)
{
	int i, len;

	len = strlen(g_h);
	i = 0;
	while (i <= g_maxfd)
	{
		if (i != g_servfd && i != cfd && FD_ISSET(i, &g_write))
			send(i, g_h, len, 0);
		i++;
	}
}

void accept_client()
{
	struct sockaddr_in 	cl;
	socklen_t			len;
	int					connfd;

	len = sizeof(cl);
	connfd = accept(g_servfd, (struct sockaddr *)&cl, &len);
	if (connfd < 0) return;
	if (connfd >= FD_SETSIZE)
	{
		close(connfd);
		return;
	}
	if (connfd > g_maxfd)
		g_maxfd = connfd;
	g_id[connfd] = g_next++;
	g_buf[connfd] = NULL;
	FD_SET(connfd, &g_master);
	sprintf(g_head, "server: client %d just arrived\n", g_id[connfd]); // write to g_head str
	broadcast(connfd, g_head);
}

void handle_client(int fd)
{
	int ret, r;
	char *msg, recv_buf[100001];

	ret = recv(fd, recv_buf, 100000, 0);
	if (ret <= 0)
	{
		sprintf(g_head, "server: client %d just left\n", g_id[fd]);
		broadcast(fd, g_head);
		free(g_buf[fd]);
		g_buf[fd] = NULL;
		FD_CLR(fd, &g_master);
		close(fd);
		return;
	}
	recv_buf[ret] = 0;
	g_buf[fd] = str_join(g_buf[fd], recv_buf);
	if (g_buf[fd] == NULL) fatal();
	while ((r = extract_message(&g_buf[fd], &msg)) > 0)
	{
		sprintf(g_head, "client %d: ", g_id[fd]);
		broadcast(fd, g_head);
		broadcast(fd, msg);
		free(msg);
	}
	if (r < 0) fatal();
}

int main(int argc, char** argv)
{
	int fd;

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	g_maxfd = 0;
	g_next  = 0;
	setup_server(atoi(argv[1]));
	while(1)
	{
		g_read = g_master;
		g_write = g_master;
		// memorize
		if (select(g_maxfd + 1, &g_read, &g_write, NULL, NULL) < 0) continue;
		fd = 0;
		while (fd <= g_maxfd)
		{
			if (FD_ISSET(fd, &g_read))
			{
				if (fd == g_servfd)
					accept_client();
				else
					handle_client(fd);
			}
			fd++;
		}
	}
	return 0;
}