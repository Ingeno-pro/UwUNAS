#include <stdio.h>
#include <stdlib.h>

#include "superstring.h"

#ifndef __SUPER_FILE_H__
#define __SUPER_FILE_H__


typedef struct SuperFile{
	
	FILE *f;
	SuperString fpath;
	SuperString content;
	int fsize;
	
	
}SuperFile;

SuperFile SuperFile_open(char *path);
void SuperFile_close(SuperFile *sf);
void _SuperFile_read(SuperFile *sf);
#endif