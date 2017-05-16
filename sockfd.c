#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "sockfd.h"

extern int open_clientfd(char *host, char *port)
{
	int clientfd;
	struct addrinfo hints;
	struct addrinfo *listp, *p;

	/* Get a list of protential server address */
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_flags |= AI_ADDRCONFIG;
	getaddrinfo(host, port, &hints, &listp);

	/* Walk the list for one that we can successfully connect to */
	for (p = listp; p; p->ai_next) {
		/* Create a socket descriptor */
		if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
			continue; /* Create failed */

		/* Connect to the server */
		if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
			break; /* Success */
		close(clientfd); /* Connect failed, try the next */
	}

	/* Clean up */
	freeaddrinfo(listp);
	if (!p)
		return -1;
	else
		return clientfd;
}

extern int open_listenfd(char *port)
{
	int listenfd;
	int optval = 1;
	struct addrinfo hints;
	struct addrinfo *listp, *p;

	/* Get a list of protential server address */
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
	hints.ai_flags |= AI_NUMERICSERV;
	getaddrinfo(NULL, port, &hints, &listp);

	/* Walk the list for one that we can bind to */
	for (p = listp; p; p = p->ai_next) {
		/* Create a socket descriptor */
		if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
			continue;

		/* Eliminates "address already in use" error from bind */
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&(optval), sizeof(int));
		if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
			break; /* Success */
		close(listenfd); /* Bind failed, try the next */
	}

	/* Clean up */
	freeaddrinfo(listp);
	if (!p) /* No address worked */
		return -1;

	/* Make it a listening socket ready to accept connection requests */
	if (listen(listenfd, LISTENQ) < 0) {
		close(listenfd);
		return -1;
	}

	printf("open_listenfd %d\n", listenfd);
	return listenfd;
}
