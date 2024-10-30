#include <png.h>

#ifndef __SSD1306_TEXT_H__
#define __SSD1306_TEXT_H__

void SSD1306InitText();
void createCharTable();
void destroyCharTable();
void drawChar(char id, char x, char y, char size);
void loadSmallChar();


#endif