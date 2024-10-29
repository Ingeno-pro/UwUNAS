#include "http.h"

int sendHTTPResponse(int clientSocket, char *htmlContent, int htmlContent_size){

	//Entête
	char message[BUFFER_SIZE] = {0};
	char date[HEADER_INF_SIZE] = {0};
	char expire[HEADER_INF_SIZE] = {0};
	char last_modified[HEADER_INF_SIZE] = {0};
	char content_length[HEADER_INF_SIZE] = {0};
	
	time_t timestamp = time(NULL); 
	strftime(date, sizeof(date), "Date: %a, %d %b %Y %X GMT\n", localtime(&timestamp)); 
	strftime(expire, sizeof(expire), "Expires: %a, %d %b %Y %X GMT\n", localtime(&timestamp)); 
	strftime(last_modified, sizeof(last_modified), "Last-modified: %a, %d %b %Y %X GMT\n", localtime(&timestamp)); 
	
	sprintf(content_length, "Content-Length: %d\n", htmlContent_size);
	
	strcpy(message, "HTTP/1.0 200 OK\n");
	strcat(message, date);
	strcat(message, "Server: LegoUWUnaS\n");
	strcat(message, "Content-Type: text/html\n");
	strcat(message, content_length);
	strcat(message, expire);
	strcat(message, last_modified);
	
	//Séparation
	strcat(message, "\n\n");
	
	//HTML
	strcat(message, htmlContent);
	send(clientSocket, message, BUFFER_SIZE, 0);
}
