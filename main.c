#include <stdio.h>
/* Define socklen_t */
#include <unistd.h>
/* Define struct sockaddr_storage */
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "sockfd.h"

#define HOSTNAME_LEN (16)
#define PORT_LEN (6)
typedef struct sockaddr SA;

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
		clientlen = sizeof(struct sockaddr_storage);
		connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
		if (getnameinfo((SA *)&(clientaddr), clientlen,
			hostname, HOSTNAME_LEN, port, PORT_LEN, 0)) {
			fprintf(stderr, "Failed to grep client socket infomation\n");
		}

		printf("Accepted connection from (%s, %s)\n", hostname, port);
		close(connfd);
	}
}
