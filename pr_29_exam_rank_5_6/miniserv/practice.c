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

/*data type used with select() to represent a set of file descriptors, allows to mark which descriptors to watch for read, write, or error readiness.*/
int gmaxfd, gnextfd, gservfd;
fd_set gmainset, greadset, gwriteset;

void fatal()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void setup_server(int port)
{
	struct sockaddr_in servaddr;

	gservfd = socket(AF_INET, SOCK_STREAM, 0);    
    if (gservfd < 0)
		fatal();
	//!!
	gmaxfd = gservfd;
	FD_ZERO(&gmainset); //clear all fds
	FD_SET(gservfd, &gmainset);
	bzero(&servaddr, sizeof(servaddr));
	//!!
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (bind(gservfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		fatal();
    
    if (listen(gservfd, 128) < 0)
		fatal();
    
    printf("ready\n");
    close(gservfd);	
}

int main(int argc, char **argv)
{
	int fd;

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	gmaxfd = 0;
	gnextfd = 0;
	setupserver(atoi(argv[1]));
	while (1)
	{
		greadset = gmainset;
		gwriteset = gmainset;
		if (select(gmaxfd + 1, &greadset, &gwriteset, NULL, NULL) < 0) continue;	
		fd = 0;
		while (fd <= gmaxfd)
		{
			if (fd != gservfd && FD_ISSET(fd, &gwriteset))
				flush_client(fd); //todo
			if (FD_ISSET(fd, &greadset))
			{
				if (fd == gservfd)
					accept_client(fd); //todo
				else
					handle_client(fd); //todo
			}
			fd++;
		}
	}
	return 0;
}