#include "http.h"

void HTTPServer_init(HTTPServer *hs, int port){
	
	//Init socket
	hs->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(hs->server_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
	
	//Init socket address
	hs->socket_addr.sin_family = AF_INET;
	hs->socket_addr.sin_port = htons(port);
	hs->socket_addr.sin_addr.s_addr = INADDR_ANY;
	
	hs->socket_addr_length = sizeof(hs->socket_addr);
	
	//Set HTTPServer method
	hs->bind = &HTTPServer_bind;
	hs->start_listen = &HTTPServer_listen;
	
	//Check socket 
	if(hs->server_socket == -1){
		fprintf(stderr, "SAD UWU :( 1");
		exit(1);
	}
}

/******************************** socket function ***************************************/

void HTTPServer_bind(HTTPServer *hs){
	
	//Binding socket 
	fprintf(stdout, "UWU BIND\n");
	if(bind(hs->server_socket, (struct sockaddr *)&(hs->socket_addr), hs->socket_addr_length) == -1){
		fprintf(stderr, "SAD UWU :( 2a");
		exit(1);
	}
	
}
void HTTPServer_listen(HTTPServer *hs){
	
	//Listenning
	fprintf(stdout, "UWU ECOUTE\n");
	if(listen(hs->server_socket, MAX_QUEUE) == -1){
		fprintf(stderr, "SAD UWU :( 2");
		exit(1);
	}
	
	//Create the listenning thread
	pthread_create(&(hs->listen_thread), NULL, _HTTPServer_thread, (void *)hs);
	
}

/******************************** thread function ***************************************/

void *_HTTPServer_thread(void *hs_buff){
	
	HTTPServer *hs = (HTTPServer *)hs_buff;
	
	int cs;
	int *cs_buff=NULL;
	while(1){
		
		cs = accept(hs->server_socket, NULL, NULL);
		pthread_t client_thread;
		cs_buff = malloc(sizeof(int));
		*cs_buff = cs;
		
		pthread_create(&client_thread, NULL, _HTTPClient_handler, (void *)cs_buff);
		pthread_detach(client_thread);
		
	}
	
	
}

void *_HTTPClient_handler(void *cs){
	
	int csock = *(int *)cs;
	char buff[BUFFER_SIZE] = {0};
	SuperString request = SuperString_init();
	
	int recv_byte = recv(csock, buff, BUFFER_SIZE, 0);
	request.sprint(&request, buff);

	manageRequest(csock, &request);
	
	close(csock);
	if(cs != NULL)free(cs);
	pthread_exit(EXIT_SUCCESS);
}

/******************************** http function ***************************************/

void HTTPPageRequest_init(HTTPRequest* hr){
	hr->http_header = SuperString_init();
	hr->content = SuperString_init();
	hr->getHeader = &HTTPPageRequest_get_header;
}
void HTTPStyleSheetRequest_init(HTTPRequest* hr){
	hr->http_header = SuperString_init();
	hr->content = SuperString_init();
	hr->getHeader = &HTTPStyleSheetRequest_get_header;
}
void HTTPFaviconRequest_init(HTTPRequest* hr){
	hr->http_header = SuperString_init();
	hr->content = SuperString_init();
	hr->getHeader = &HTTPFaviconRequest_get_header;
}
void HTTPImageRequest_init(HTTPRequest* hr){
	hr->http_header = SuperString_init();
	hr->content = SuperString_init();
	hr->getHeader = &HTTPImageRequest_get_header;
}
void HTTPRequest_destroy(HTTPRequest *hr){
	//free(hr->http_header);
	//free(hr->content); have to make destroy super string
}
void _HTTPRequest_get_generic_header(SuperString *header){
	
	char date[HEADER_INF_SIZE] = {0};
	char buff[92] = {0};
	time_t timestamp = time(NULL);
	strftime(date, sizeof(date), "Date: %a, %d %b %Y %X GMT\n", localtime(&timestamp)); 
	
	sprintf(buff, "HTTP/1.0 200 OK\n%s\nServer: LegoUWUnaS\n", date);
	
	header->sprint(header, buff);
}
void _HTTPRequest_write_content_information(int size, SuperString *header){
	
	char buff[BUFFER_SIZE*4] = {0};
	char expire[BUFFER_SIZE] = {0};
	char last_modified[BUFFER_SIZE] = {0};
	
	time_t timestamp = time(NULL);
	strftime(expire, sizeof(expire), "Expires: %a, %d %b %Y %X GMT\n", localtime(&timestamp)); 
	strftime(last_modified, sizeof(last_modified), "Last-modified: %a, %d %b %Y %X GMT\n", localtime(&timestamp));
	
	sprintf(buff, "Content-Length: %d\n%s%s", size, expire, last_modified);
	header->append(header, buff);
	
}
void HTTPPageRequest_get_header(HTTPRequest *hr){
	
	_HTTPRequest_get_generic_header(&(hr->http_header));
	hr->http_header.append(&(hr->http_header), "Content-Type: text/html\n"); 
	hr->size = hr->content.size;
	_HTTPRequest_write_content_information(hr->size, &(hr->http_header));

	hr->http_header.append(&(hr->http_header), "\n\n");

}
void HTTPStyleSheetRequest_get_header(HTTPRequest *hr){
		
	_HTTPRequest_get_generic_header(&(hr->http_header));
	hr->http_header.append(&(hr->http_header), "Content-Type: text/css\n"); 
	hr->size = hr->content.size;
	_HTTPRequest_write_content_information(hr->size, &(hr->http_header));
	
	hr->http_header.append(&(hr->http_header), "\n\n");
	
}
void HTTPFaviconRequest_get_header(HTTPRequest *hr){
		
	_HTTPRequest_get_generic_header(&(hr->http_header));
	hr->http_header.append(&(hr->http_header), "Content-Type: image/x-icon\n"); 
	hr->size = hr->content.size;
	_HTTPRequest_write_content_information(hr->size, &(hr->http_header));
	
	hr->http_header.append(&(hr->http_header), "\n\n");
	
}
void HTTPImageRequest_get_header(HTTPRequest *hr){
		
	_HTTPRequest_get_generic_header(&(hr->http_header));
	hr->http_header.append(&(hr->http_header), "Content-Type: image/png\n"); 
	hr->size = hr->content.size;
	_HTTPRequest_write_content_information(hr->size, &(hr->http_header));
	
	hr->http_header.append(&(hr->http_header), "\n\n");
	
}
void HTTPServer_send(int clientSocket, HTTPRequest *hr){

	//Assemblage de la requete 
	SuperString message = SuperString_init();
	message.appendSS(&message, &hr->http_header);
	message.appendSS(&message, &hr->content);

	//Envoie
	send(clientSocket, message.str, message.size, 0);
}
