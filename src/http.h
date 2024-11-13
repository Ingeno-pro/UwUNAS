#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h> 

#include "superstring.h"

#ifndef __HTTP_H__
#define __HTTP_H__

#define BUFFER_SIZE 2048
#define HEADER_SIZE 512
#define HEADER_INF_SIZE 32
#define REQUEST_METHOD_SIZE 8
#define MAX_URL_SIZE 128

#define MAX_QUEUE 4

typedef struct HTTPServer{
	
	int server_socket;
	int socket_addr_length;
	struct sockaddr_in socket_addr;
	pthread_t listen_thread;
	
	void (*bind)(struct HTTPServer *hs);
	void (*start_listen)(struct HTTPServer *hs);
		
}HTTPServer;

void HTTPServer_init(HTTPServer *hs, int port);


void HTTPServer_bind(HTTPServer *hs);
void HTTPServer_listen(HTTPServer *hs);

/******************************** thread function ***************************************/

void *_HTTPServer_thread(void *hs_buff);
void *_HTTPClient_handler(void *cs);

/******************************** http function ***************************************/
typedef struct HTTPRequest{	

	SuperString http_header, content;	
	int size;	

	void (*getHeader)(struct HTTPRequest *hr); 
	
}HTTPRequest;

void HTTPPageRequest_init(HTTPRequest *hr);
void HTTPStyleSheetRequest_init(HTTPRequest *hr);
void HTTPFaviconRequest_init(HTTPRequest *hr);
void HTTPImageRequest_init(HTTPRequest *hr);

void HTTPRequest_destroy(HTTPRequest *hr);

void _HTTPRequest_get_generic_header(SuperString *header);
void _HTTPRequest_write_content_information(int size, SuperString *header);
	
void HTTPPageRequest_get_header(HTTPRequest *hr);
void HTTPStyleSheetRequest_get_header(HTTPRequest *hr);
void HTTPFaviconRequest_get_header(HTTPRequest *hr);
void HTTPImageRequest_get_header(HTTPRequest *hr);

void HTTPServer_send(int clientSocket, HTTPRequest *hr);


#endif
