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
 *
 * Revised by X. Meng
 * -- 2015-01-31: change from a file server to a fortune cookie server.
 * -- 2022-03-31: reorganized the files so *.h and *c files are separate
 *                used for CSCI 206
 * Revised by X. Meng
 * -- 2022-04-22: Moved socket setup to common-lib. 
 */

#include "common-lib.h"
#include "cookies.h"

// The implementation file is in cookies.c, these are functions needed
int cookie_index = 0; // which cookie to return, round robin
extern char *cookie_buf;
extern char *cookies;
extern int cookie_count;

void process_request(int sd);

/*------------------------------------------------------------------------
 * Program:   fortune-cookie-server
 *
 * Purpose:   allocate a socket and then repeatedly execute the following:
 *		(1) wait for the next connection from a client
 *		(2) send a random fortune cookie to the client
 *		(3) close the connection
 *		(4) go back to step (1)
 *
 * Syntax:    fortune-server [ port ]
 *
 *		 port  - protocol port number to use
 *
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
	int port; // protocol port number

	if (argc > 1)
	{
		port = atoi(argv[1]);
	}
	else
	{
		printf("Usage: fileserver [ port ]\n");
		exit(-1);
	}

	if (port <= 0)
	{
		// test for illegal value
		// print error message and exit
		error("SERVER: bad port number!");
	}

	// common-lib function to configure and open the TCP socket
	int sd = open_server_tcp_socket(port);

	// Read the fortune cookies
	init_cookies("cookies.txt");
	cookie_count = count_cookies();

	// Main server loop - accept and handle requests
	while (1)
	{
		struct sockaddr_in cad; // structure to hold client's address
		int alen = sizeof(cad);
		int sd2; // second socket descriptor

		if ((sd2 = accept(sd, (struct sockaddr *)&cad, (socklen_t *)(&alen))) < 0)
		{
			error("SERVER: accept failed\n");
		}

		// Serve use requests
		process_request(sd2);

		// shutdown the client socket
		shutdown(sd2, SHUT_RDWR);

		// and then close it
		close(sd2);
	}
}

/*
 *------------------------------------------------------
 * process_request: accept and process client requests
 *------------------------------------------------------
 */
void process_request(int sd)
{
	/*
	  TO-DO
	  The server algorithm is as follows:

	  read the request from a client;
	  if the request is 'cook'
		 generate a random index within the range;
		 retrieve the fortune cookie at that index; // use get_cookie(i)
		 return the text of the fortune cookie to the client;
	*/

  int bytes_recv, bytes_recv2;
  char buf[MAX_LENG+1], buf2[MAX_LENG + 1]; // buffer for client request
	int len;

	// first read the size of request
	if (readn(sd, &bytes_recv, sizeof(int)) != sizeof(int))
	{
		error("server read error req site");
	}

	// then read the entire request
	if (readn(sd, buf, bytes_recv) != bytes_recv)
	{
		error("server read error message");
	}
	buf[bytes_recv] = 0; // terminate the string

	printf("server received [%s]\n", buf);

	if (readn(sd, &bytes_recv2, sizeof(int)) != sizeof(int))
	{
		error("server read error req site");
	}

	// then read the entire request
	if (readn(sd, buf2, bytes_recv2) != bytes_recv2)
	{
		error("server read error message");
	}
	buf2[bytes_recv2] = 0; // terminate the string
	
	
	
	if (strcmp(buf, "cookie") == 0)
	{ // valid request
	  //static int cookie_index = 0;  // static int is essentially a private global variable initalized only one time

	  strcpy(buf, get_cookie(atoi(buf2)));
		printf("server: cookie [%s]\n", buf);

		// return next cookie on next call
		//cookie_index = (cookie_index + 1) % cookie_count;

		len = strlen(buf);
		if (writen(sd, &len, sizeof(int)) != sizeof(int))
		{
			error("server write error size");
		}
		if (writen(sd, buf, len) != len)
		{
			error("server write error message");
		}
	}
	else
	{
		error("invalid request");
	}
}
