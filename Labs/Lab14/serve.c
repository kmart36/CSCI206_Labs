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
 * Modified from fortune-client.c by
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 *
 * Revised by X. Meng
 * -- 2022-03-31: reorganized the files so *.h and *c files are separate
 *                used for CSCI 206
 * -- 2015-01-31: change from a file server to a fortune cookie server.
 * 
 * Revised by Marchiori
 * -- 2022-04-22: Modified to be a threaded (simple) web server.
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "common-lib.h"

// declare a function to handle HTTP requests, called in a separate thread
void* process_request(void*);

// params passed to the response thread
struct thread_param_t {
	int 		sd;
	pthread_t 	thread;
};

/*------------------------------------------------------------------------
 * Program:   serve
 *
 * Purpose:   A basic HTTP server
 *
 * Syntax:    serve [ port ]
 *
 *		 port  - protocol port number to use
 *
 *------------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{

	int sd, sd2;			// socket descriptors
	int port;				// protocol port number
	int alen;				// length of address

	if (argc > 1){ 
		port = atoi(argv[1]);
	} else {
		printf("Usage: serve [ port ]\n");
		exit(42);
	}

	if (port <= 0){
		// test for illegal value
		// print error message and exit
		error("SERVER: bad port number!");
	}

	sd = open_server_tcp_socket(port);

	// Main server loop - accept and handle requests
	while (1)
	{
		// structure to hold client's address
		struct sockaddr_in cad; 
		alen = sizeof(cad);

		// accept a clinet connection (blocks until a clinet requests a connection)
		if ((sd2 = accept(sd, (struct sockaddr *)&cad, (socklen_t *)(&alen))) < 0){
			error("SERVER: accept failed\n");			
		}
		
		// Serve use requests in a new thread
		struct thread_param_t *p = malloc(sizeof(struct thread_param_t));
		// pass the connected client socket into the thread
		p->sd = sd2;
		
		if (pthread_create(&p->thread, NULL, process_request, p)){
			error("ERROR in pthread_create\n");
		}
	}
}

/*
 *------------------------------------------------------
 * process_request: process client requests
 *------------------------------------------------------
 */
void* process_request(void *p)
{
	/*
	  The server algorithm is as follows:

	  read the request from a client;
	  parse the first line: "GET <file> HTTP/1.1"
	  check if the file exists locally, if so, create an 200 OK header and send the contents
	  else create and send an 404 error.
	*/
	struct thread_param_t* tp = p;

	int bytes_recv;
	char buf[MAX_LENG + 1]; // buffer for client request
	
	// read the first chunk of the request, the HTTP request *should* be fully
	// contained in this message. (we assume it is) a production server should
	// not make this assumption
	bytes_recv = read(tp->sd, buf, MAX_LENG);
	buf[bytes_recv] = 0; // terminate the string
	
	if (bytes_recv > 0){
		// the HTTP response header
		char head[MAX_LENG+1];

		// parse the first line of the HTTP REQUEST like: 
		// GET /filename HTTP/1.1		
		char method[64];
		char path[MAX_LENG+1];
		char vers[64];
		sscanf(buf, "%s %s %s", method, path, vers);

		// check if this is a GET method
		if (strcmp(method, "GET")== 0){		
			
			/* TODO
			 * Process the GET request for the given path
			 * the path begins with a /<filenname>, you need to convert this to a local path by inserting a . at the front
			 * then if the file exists, construct an HTTP/1.1 200 header (including the Content-Length) and then send the file
			 * contents. 
			 * IF the requested file does not exist locally, return a HTTP/1.1 404 Header with Content-Lenth: 0
			 */




		} else {
			sprintf(head, "HTTP/1.1 406\r\nContent-Length: 0\r\n\r\n");
			printf("Method Not Acceptable!\n");
			int hlen = strlen(head);
			if (writen(tp->sd, head, hlen) != hlen){
				error("Failed to send header\n");
			}	
		}
	}

	// shutdown this connection
	shutdown(tp->sd, SHUT_RDWR);
	// close the socket
	close(tp->sd);
	// free the malloc'ed args for this thread
	free (p);
	return NULL;
}