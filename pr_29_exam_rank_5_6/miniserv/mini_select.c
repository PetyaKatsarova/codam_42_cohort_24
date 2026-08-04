#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_client
{
	int id;
	char *msg;
}	t_client;

int sockfd = -1;
int maxfd = -1;

fd_set active;
fd_set readfds;
fd_set writefds;

t_client clients[FD_SETSIZE];
int lastClientId = 0;

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

void ft_putstr_fd(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

void fatal()
{
	ft_putstr_fd(2, "Fatal error\n");
	exit(1);
}

void set_max_fd()
{
	maxfd = sockfd;
	for (int i = 0; i <= FD_SETSIZE; ++i)
	{
		if (FD_ISSET(i, &active) && i > maxfd)
			maxfd = i;
	}
}

void broadcast(char *msg, int senderFd)
{
	for (int fd = 0; fd <= FD_SETSIZE; fd++)
	{
		if (FD_ISSET(fd, &writefds) && fd != senderFd)
		send(fd, msg, strlen(msg), 0);
	}
}

void announce_new_client(int fd)
{
	char msg[256];
	sprintf(msg, "server: client %d just arrived\n", clients[fd].id);
	broadcast(msg, fd);
}

void add_client(int fd)
{
	struct sockaddr_in cli;
	socklen_t len = sizeof(cli);
	int client_fd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (client_fd == -1)
		fatal();
	
	clients[client_fd].id = lastClientId;
	lastClientId++;
	FD_SET(client_fd, &active);
	announce_new_client(client_fd);
}

void readFromClient(int fd)
{
	char buffer[256];
	int bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead <= 0)
	{
		char msg[256];
		sprintf(msg, "server: client %d just left\n", clients[fd].id);
		broadcast(msg, fd);

		close(fd);
		FD_CLR(fd, &active);
		clients[fd].id = -1;

		if (clients[fd].msg != NULL)
			free(clients[fd].msg);
		clients[fd].msg = NULL;
		return;
	}
	
	buffer[bytesRead] = '\0';

	clients[fd].msg = str_join(clients[fd].msg, buffer);
	if (!clients[fd].msg)
		fatal();
	
	char *msg;

	while (extract_message(&clients[fd].msg, &msg))
	{
		char out[300];
		sprintf(out, "client %d: %s", clients[fd].id, msg);
		broadcast(out, fd);

		free(msg);
	}
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		ft_putstr_fd(2, "Wrong number of arguments\n");
		exit(1);
	}

	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1]));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		fatal();
	}
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
		fatal();
	}
	if (listen(sockfd, 10) != 0) {
		fatal();
	}
	bzero(clients, sizeof(clients));
	FD_ZERO(&active);
	FD_SET(sockfd, &active);	

	while (1)
	{
		readfds = active;
		writefds = active;
		
		set_max_fd();
		int res = select(maxfd + 1, &readfds, &writefds, NULL, NULL);
		if (res == -1) {
			fatal();
		}
		if (res == 0) {
			continue;	
		}
		for (int fd = 0; fd <= maxfd; ++fd)
		{
			if (FD_ISSET(fd, &readfds)) {
				if (fd == sockfd)
				{
					add_client(fd);
				}
				else
				{
					readFromClient(fd);
				}
			}
		}
	}
}