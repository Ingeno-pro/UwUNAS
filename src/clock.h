#include <stdio.h>
#include <time.h>
#include <string.h>

#include "ssd1306.h"

#ifndef __UWUCLOCK_H__
#define __UWUCLOCK_H__


#define SMALL_CHAR_SIZE 8
#define MEDIUM_CHAR_SIZE 16
#define BIG_CHAR_SIZE 24

#define LITTLE 0
#define MEDIUM 1
#define BIG 2

#define N_ASCII_CHAR 128

void initClock();


#endif