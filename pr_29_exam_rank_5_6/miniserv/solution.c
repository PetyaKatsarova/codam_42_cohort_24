#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>

// FD_SETSIZE: defined by <sys/select.h> (usually via <bits/typesizes.h>), the
// max number of fds an fd_set can hold. On Linux glibc it's a compile-time
// constant, normally 1024. Sizing these arrays (and the accept_client() guard
// below) to it keeps every fd we track inside what FD_SET/FD_ISSET can
// safely address.
int		g_id[FD_SETSIZE]; //max number of FDs a fd_set can hold
char	*g_buf[FD_SETSIZE];
int		g_maxfd;
int		g_next;
int		g_serv;
// fd_set: an opaque bitmap type from <sys/select.h>, fixed at FD_SETSIZE bits
// (one bit per possible fd). Never touch the bits directly -- always go
// through FD_ZERO/FD_SET/FD_CLR/FD_ISSET. select() reads it as "which fds to
// watch" and overwrites it with "which fds are ready", so a set passed to
// select() must be rebuilt before every call.
fd_set	g_active;	// the "master" list: every fd we're currently tracking (server + clients)
fd_set	g_read;		// scratch copy passed to select() as the read-interest set
fd_set	g_write;	// scratch copy passed to select() as the write-interest set
char	g_head[128];

/*
** Pulls the first '\n'-terminated message out of *buf, leaving the rest in *buf.
** Takes: pointer to the source buffer, pointer to store the extracted message.
** Returns: 1 if a message was extracted, 0 if no '\n' found, -1 on malloc failure.
*/
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

/*
** Concatenates 'add' onto 'buf' into a freshly allocated buffer, freeing 'buf'.
** Takes: existing buffer (NULL allowed), string to append.
** Returns: new joined string, or NULL on malloc failure.
*/
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

/*
** Prints "Fatal error" to stderr and terminates the program.
** Takes: nothing.
** Returns: nothing (exits with status 1).
*/
void fatal(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

/*
** Sends string 's' to every active client except the listening socket and 'except'.
** Takes: fd to skip (e.g. the sender), message to send.
** Returns: nothing.
*/
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

/*
** Creates the listening socket bound to localhost:port and starts listening.
** Takes: the port number to listen on.
** Returns: nothing (calls fatal() on any socket/bind/listen failure).
*/
void setup_server(int port)
{
	struct sockaddr_in	servaddr; //struct for IPv4 socket addresses.

	g_serv = socket(AF_INET, SOCK_STREAM, 0);
	if (g_serv < 0)
		fatal();
	g_maxfd = g_serv;
	FD_ZERO(&g_active); // clear all fds
	FD_SET(g_serv, &g_active); // add a fd
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(port);
	if (bind(g_serv, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
		fatal();
	if (listen(g_serv, 128) != 0)
		fatal();
}

/*
** Accepts a pending connection on the listening socket, registers it, and
** announces its arrival to the other clients.
** Takes: nothing.
** Returns: nothing (does nothing if accept() fails).
*/
void accept_client(void)
{
	struct sockaddr_in	cli;
	socklen_t			len;
	int					connfd;

	len = sizeof(cli);
	connfd = accept(g_serv, (struct sockaddr *)&cli, &len);
	if (connfd < 0)
		return ;
	if (connfd >= FD_SETSIZE)
	{
		// fd_set can't safely represent this fd (FD_SET/FD_ISSET would read/write
		// past the bitmap) -- drop the connection instead of corrupting memory.
		close(connfd);
		return ;
	}
	if (connfd > g_maxfd)
		g_maxfd = connfd;
	g_id[connfd] = g_next++;
	g_buf[connfd] = NULL;
	FD_SET(connfd, &g_active);
	sprintf(g_head, "server: client %d just arrived\n", g_id[connfd]);
	broadcast(connfd, g_head);
}

/*
** Reads available data from 'fd'; on disconnect, cleans it up and announces
** it left; otherwise buffers the data and broadcasts every complete message.
** Takes: the client fd that is ready for reading.
** Returns: nothing (calls fatal() on allocation failure).
*/
void handle_client(int fd)
{
	int		ret;
	int		r;
	char	*msg;
	char	recv_buf[100001];

	ret = recv(fd, recv_buf, 100000, 0);
	if (ret <= 0)
	{
		sprintf(g_head, "server: client %d just left\n", g_id[fd]);
		broadcast(fd, g_head);
		free(g_buf[fd]);
		g_buf[fd] = NULL;
		FD_CLR(fd, &g_active);
		close(fd);
		return ;
	}
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

/*
** Sets up the server, then loops on select() dispatching ready fds to
** accept_client() (listening socket) or handle_client() (existing clients).
** Takes: argc/argv, expects argv[1] to be the port number.
** Returns: 0 (unreachable; loop runs until fatal() exits).
*/
int main(int argc, char **argv)
{
	int	fd;

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
		g_read = g_active;		// fresh copy every iteration — select() will clobber this
		g_write = g_active;		// same fd set, but asking "who's writable" this time
		if (select(g_maxfd + 1, &g_read, &g_write, NULL, NULL) < 0)
			continue;			// interrupted syscall etc. — just retry
		fd = 0;
		while (fd <= g_maxfd)
		{
			if (FD_ISSET(fd, &g_read))	// this fd has data to read (or accept, or disconnect)
			{
				if (fd == g_serv)
					accept_client();		// it's the listening socket -> new connection
				else
					handle_client(fd);		// it's a client -> data ready (or they hung up)
			}
			fd++;
		}
	}
	return (0);
}
