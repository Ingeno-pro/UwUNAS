#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h> 

#ifndef __HTTP_H__
#define __HTTP_H__

#define BUFFER_SIZE 2048
#define HEADER_SIZE 512
#define HEADER_INF_SIZE 32
#define REQUEST_METHOD_SIZE 8
#define MAX_URL_SIZE 128

int sendHTTPResponse(int clientSocket, char *htmlContent, int htmlContent_size);
#endif
