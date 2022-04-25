#ifndef _COMMON_LIB_
#define _COMMON_LIB_


//#define _POSIX_SOURCE 200112L  // for getaddrinfo(3), must be before include others


#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>

#define	QLEN		6   // size of request queue
#define MAX_LENG 4096

extern int errno;
void 	error(char*);
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t	writen(int fd, const void *vptr, size_t n);
void 	read_rest(int fd);

long int get_file_len(char *fname);
void 	send_file(int sd2, char *fname);
int 	open_server_tcp_socket (int port);
int 	open_client_tcp_socket(char *host, int port);
#endif
