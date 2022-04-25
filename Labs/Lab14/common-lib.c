/*
 * Copyright (c) 2012 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

/*
 * Revised by X. Meng
 * -- 2022-03-31: reorganized the files so *.h and *c files are separate
 *                used for CSCI 206
 * Revised by Marchiori
 * -- 2022-04-22: Added a few more helper functions for sockets.
 */

/* Note that to compile this separately, you need to
 * include <sys/types.h> and provide a header file
 * exporting the functions as extern.
 */

#include "common-lib.h"

ssize_t
readn(int fd, void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
		if ((nread = read(fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
				nread = 0; /* and call read() again */
			else
				return (-1);
		}
		else if (nread == 0)
			break; /* EOF */

		nleft -= nread;
		ptr += nread;
	}
	return (n - nleft); /* return >= 0 */
}
/* end readn */

/*
 * Copyright (c) 2012 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

/* Note that to compile this separately, you need to
 * include <sys/types.h> and provide a header file
 * exporting the functions as extern.
 */

/* Write "n" bytes to a descriptor. */

ssize_t
writen(int fd, const void *vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0)
	{
		if ((nwritten = write(fd, ptr, nleft)) <= 0)
		{
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0; /* and call write() again */
			else
				return (-1); /* error */
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return (n);
}
/* end writen */

/*
 * Print the error message and quit
 */
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/*
 * Read the rest from the socket, essentially consume
 * whatever is left over in the channel, not return for use.
 */
void read_rest(int sd)
{
	char buf[MAX_LENG];
	while (read(sd, buf, MAX_LENG) > 0)
		;
}

/*
 * Return the length of the given file using stat.
 * or -1 on error
 */
long int get_file_len(char *fname)
{
	struct stat fstat;

	if (stat(fname, &fstat) != 0)
		return -1;

	return (int)fstat.st_size;
}

/*
 * Read the given file and send through the given socket.
 * If anything goes wrong, it errors out and calls exit
 */
void send_file(int sd2, char *fname)
{
	char buff[MAX_LENG + 1];
	int fd;
	int n;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		error("file open error\n");
	}

	// read the file in chunks of MAX_LENG and send through the socket.
	while ((n = read(fd, buff, MAX_LENG)) > 0)
	{
		int m = writen(sd2, buff, n); // send it through socket
		if (n != m)
		{
			error("send file error\n");
		}
	}
}

/*
 * Create and connect a TCP socket to the given remote host:port
 */
int open_client_tcp_socket(char *host, int port)
{
	struct addrinfo *ptrh;  // pointer to a host table entry
	struct protoent *ptrp;  // pointer to a protocol table entry
	struct sockaddr_in sad; // structure to hold an IP address
	// Convert host name to equivalent IP address and copy to 'sad'.
	int status = getaddrinfo(host, NULL, NULL, &ptrh);
	if (status != 0) {
		fprintf(stderr, "invalid host: %s\n", host);
		exit(1);
	}

	memset(&sad, 0, sizeof(sad)); // clear sockaddr structure
	memcpy(&sad, (struct sockaddr_in *)(ptrh->ai_addr), ptrh->ai_addrlen);
	sad.sin_port = htons((unsigned short)port);

	// Map TCP transport protocol name to protocol number.
	ptrp = getprotobyname("tcp");
	if (ptrp == NULL){
		error("CLIENT: cannot map \"tcp\" to protocol number\n");		
	}

	// Create a socket.
	int sd = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if (sd < 0)	{
		error("CLIENT: socket creation failed\n");		
	}

	// Connect the socket to the specified server.
	if (connect(sd, (struct sockaddr *)&sad, sizeof(sad)) < 0){
		error("CLIENT: connect failed\n");		
	}
	
    freeaddrinfo(ptrh);

	return sd;
}

/*
 * Create and return a bound TCP socket on the given port, ready to accept connections
 */
int open_server_tcp_socket(int port)
{
	struct sockaddr_in sad; // structure to hold server's address

	memset((char *)&sad, 0, sizeof(sad));		// clear sockaddr structure
	sad.sin_port = htons((unsigned short)port); // set port in correct byte order
	sad.sin_family = AF_INET;					// set family to Internet
	sad.sin_addr.s_addr = INADDR_ANY;			// set the local IP address

	// Map TCP transport protocol name to protocol number
	//    --> Look at /etc/protocols
	struct protoent *ptrp = getprotobyname("tcp");
	if (ptrp == NULL)
	{
		error("SERVER: cannot map \"tcp\" to protocol number");
	}

	// Create a socket
	int sd = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if (sd < 0)
	{
		error("SERVER: socket creation failed\n");
	}

	// enable port re-use
	int enable = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
	{
		error("SERVER: setsockopt(SO_REUSEADDR) failed");
	}

	// Bind a local address to the created socket
	if (bind(sd, (struct sockaddr *)&sad, sizeof(sad)) < 0)
	{
		error("SERVER: bind failed\n");
	}

	// Specify size of request queue
	if (listen(sd, QLEN) < 0)
	{
		error("SERVER: listen failed\n");
	}

	return sd;
}
