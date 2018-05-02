#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>

/* #define MAXFDS 16 * 1024 */
/* #define SENDBUF_SIZE 1024 */

#define MAX_CLIENT 10000
#define false 0
#define true 1
typedef unsigned short bool;


struct epoll_event events[MAX_CLIENT];


int main(int argc, char* argv[])
{
	int fd_epoll = 0;
	bool test = true;

	fd_epoll = epoll_create(MAX_CLIENT);
	if (fd_epoll)
	{
		fprintf(stderr, "epoll_create() was failed..\n");
		return -1;
	}

	for (;;)
	{
	}
	
	return 0;
}











