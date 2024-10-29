#include <stdlib.h>

#ifndef __NAS_H__
#define __NAS_H__
int initNAS(void);
int manageRequest(int clientSocket, char *request, int request_size);
#endif
