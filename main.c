#include <stdio.h>
/* Define socklen_t */
#include <unistd.h>
/* Define struct sockaddr_storage */
#include <netinet/in.h>
#include <stdlib.h>
#include "sockfd.h"

#define HOSTNAME_LEN (16)
#define PORT_LEN (6)

int main(int argc, char **argv)
{
	int listenfd;
	int connfd;
	char hostname[HOSTNAME_LEN];
	char port[PORT_LEN];
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	
	/* Check command-line arguments */
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}

	listenfd = open_listenfd(argv[1]);

	while (1) {
		printf("sleep 1 second\n");
		sleep(1);
	}

	printf("aaa\n");
	return 0;
}
