#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "ssd1306.h"

#ifndef __SSD1306_TEXT_H__
#define __SSD1306_TEXT_H__

#define SMALL_CHAR_SIZE 8
#define MEDIUM_CHAR_SIZE 16
#define BIG_CHAR_SIZE 24

#define LITTLE 0
#define MEDIUM 1
#define BIG 2

#define N_ASCII_CHAR 128
#define SPRITE_TABLE_SIZE 64

void SSD1306InitText();
void createCharTable();
void destroyCharTable();
void drawSmallChar(char cx, char cy, char x, char y);
void drawSmallCharFromID(char id, char x, char y);
void drawSmallString(char x, char y, char *c);
void loadSmallChar();


#endif