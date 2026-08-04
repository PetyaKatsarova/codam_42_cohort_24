#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

int sockfd;
int pfdSize = 0;
struct pollfd pfds[200];

void ft_putstr_fd(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

void calcPfdsSize()
{
	int i = 0;
	while (i < 200 && pfds[i].fd != 0)
		i++;
	pfdSize = i;
}

void handlePollin(int fd)
{
	if (fd == sockfd)
	{
		struct sockaddr_in cli;
		socklen_t len = sizeof(cli);
		int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
		if (connfd == -1) {
			ft_putstr_fd(2, "Fatal error\n");
			exit(1);
		}
		pfds[pfdSize].fd = connfd;
		pfds[pfdSize].events = POLLIN;
		calcPfdsSize();
	}
	else
	{
		char buf[1024];
		int bytesRead = recv(fd, buf, 1024, 0);
		if (bytesRead <= 0)
		{
			close(fd);
			for (int i = 0; i < pfdSize; i++) {
				if (pfds[i].fd == fd) {
					pfds[i] = pfds[pfdSize - 1];
					pfds[pfdSize - 1].fd = 0;
					calcPfdsSize();
					break;
				}
			}
			return;
		}
		buf[bytesRead] = 0;
		ft_putstr_fd(1, "Received: ");
		ft_putstr_fd(1, buf);
		ft_putstr_fd(1, "\n");
	}
}

void handlePollout(int fd)
{
	(void)fd;
}





int main(int argc, char **argv)
{
	if (argc != 2) {
		ft_putstr_fd(2, "Wrong number of arguments\n");
		return (1);
	}

	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1]));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		ft_putstr_fd(2, "Fatal error\n");
		return (1);
	}
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
		ft_putstr_fd(2, "Fatal error\n");
		return (1);
	}
	if (listen(sockfd, 10) != 0) {
		ft_putstr_fd(2, "Fatal error\n");
		return (1);	
	}
	bzero(pfds, sizeof(pfds));
	pfds[0].fd = sockfd;
	pfds[0].events = POLLIN;
	calcPfdsSize();

	while (1) {
		int events = poll(pfds, pfdSize, -1);

		if (events == -1) {
			ft_putstr_fd(2, "Fatal error\n");
			return (1);
		}
		if (events == 0)
			continue;
		if (events >= 0)
		{
			for (int i = 0; i < pfdSize; i++) {
				if (pfds[i].revents & POLLIN)
					handlePollin(pfds[i].fd);
				else if (pfds[i].revents & POLLOUT)
					handlePollout(pfds[i].fd);
			}
		}
	}

}