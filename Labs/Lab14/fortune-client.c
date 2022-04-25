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
 *  Revision:
 *  Xiannong Meng 01-07-2013
 *  -- Change the use of 'gethostbyname' to 'getaddrinfo'
 * -- 2022-03-31: reorganized the files so *.h and *c files are separate
 *                used for CSCI 206
 * Revised by Marchiori
 * -- 2022-04-22: Moved socket setup to common-lib. * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "common-lib.h"

/*------------------------------------------------------------------------
 * Program:   fortune-client
 *
 * Purpose:   allocate a socket, connect to a server, transfer requested
 *            file to local host, and print file contents to stdout
 *
 * Syntax:    fortune-client [ host ] [ port ]
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
	// Check command-line arguments
	if (argc < 4)
	{
		printf("usage: %s [ host ] [ port ] [ cookie number]\n", argv[0]);
		exit(-1);
	}

	char *host = argv[1];
	int port = atoi(argv[2]);

	if (port <= 0)
	{
		// test for legal value
		// print error message and exit
		fprintf(stderr, "%s: bad port number %s\n", argv[0], argv[2]);
		exit(1);
	}

	// open a TCP socket to the remote host:port
	int sd = open_client_tcp_socket(host, port);

	/*
	  Build and send the request to the server;
	  Read back the furtune cookie from the server;
	  Print it on the screen;
	*/
	char buf[MAX_LENG + 1]; 	// buffer for data from the server
	char *request = "cookie"; 	// the request message
	int bytes_sent = strlen(request);
	int bytes_recv; 			// number of bytes read from socket
	
	char *request2 = argv[3];
	int bytes_sent2 = strlen(request2);

	// send the length of the request
	if (writen(sd, &bytes_sent, sizeof(bytes_sent)) != sizeof(bytes_sent))
	{
		error("write error");
	}

	// and then the actual request
	if (writen(sd, request, bytes_sent) != bytes_sent)
	{
		error("write error");
	}

	if (writen(sd, &bytes_sent2, sizeof(bytes_sent2)) != sizeof(bytes_sent2)) {
	  error("write error");
	}

	if (writen(sd, request2, bytes_sent2) != bytes_sent2)
	{
		error("write error");
	}   
		

	// now receive the cookie from the server, first the size
	if (readn(sd, &bytes_recv, sizeof(int)) != sizeof(int))
	{
		error("client read error size");
	}
	printf("client bytes should recv %d\n", bytes_recv);

	// then the cookie itself
	if (bytes_recv > MAX_LENG)
	{
		bytes_recv = MAX_LENG; // maximum amount to receive
	}

	// now read the actual data
	if (readn(sd, buf, bytes_recv) != bytes_recv)
	{
		printf("client bytes recv %d\n", bytes_recv);
		error("client read error message");
	}
	// null terminate raw data into a C style string
	buf[bytes_recv] = 0;

	// in case the server wanted to send more, just consume it
	read_rest(sd);

	// print the result
	printf("cookie [%s]\n", buf);

	// tell the OS we want to shutdown this socket
	shutdown(sd, SHUT_RDWR);
	// and then close the socket.
	close(sd);
	// Terminate the client program gracefully.
	exit(EXIT_SUCCESS);
}
