#include <blkid/blkid.h>
#include <string.h>
#include <stdio.h>

#ifndef __DISKMANAGER_H__
#define __DISKMANAGER_H__
void listUUID(void);
void getDiskSpace(char *UUID);
int getDiskSize(char *devName);
#endif
