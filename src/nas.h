#include <stdlib.h>

#ifndef __NAS_H__
#define __NAS_H__

#define BAUD_RATE 100000
int initNAS(void);
int manageRequest(int clientSocket, char *request, int request_size);
#endif
