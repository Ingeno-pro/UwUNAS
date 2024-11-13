#include <stdlib.h>

#include "superfile.h"
#include "superstring.h"
#include "http.h"

#ifndef __NAS_H__
#define __NAS_H__

#define BAUD_RATE 100000

typedef struct NAS{
	
	void *ssd1;
	void *ssd2;
	void *hdd1;
	void *hdd2;
	
	HTTPServer *hs;
}UwUNAS;
int initNAS(void);
int manageRequest(int clientSocket, SuperString *request);
char *get_file_extension(const char *filename);
#endif
