#ifndef _RIO_PACKET_H_
#define _RIO_PACKET_H_

#define RIO_BUFSIZE 8192
typedef struct {
	int rio_fd;
	int rio_cnt;
	char *rio_bufptr;
	char rio_buf[RIO_BUFSIZE];
} rio_t;

extern ssize_t Rio_readn(int fd, void *ptr, size_t nbytes);
extern void Rio_writen(int fd, void *usrbuf, size_t n);
extern void Rio_readinitb(rio_t *rp, int fd);
extern ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n);
extern ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
#endif
