#include <bcm2835.h>
#include <stdlib.h>

#ifndef __SSD1306_H__
#define __SSD1306_H__

#ifndef SSD1306_ADDR
#define SSD1306_ADDR 0x3C
#endif

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define COLUMNS 128
#define PAGES 8

#define TURN_ON_SCREEN 0xAF
#define TURN_OFF_SCREEN 0xAE

#define CLEAR_SCREEN 

#define CHARGE_PUMP_SETTINGS 0x8D
#define ENABLE_CHARGE_PUMP 0x14
#define DISABLE_CHARGE_PUMP 0x10

#define DISPLAY_CLOCK_DIVIDE_RATIO 0xD5
#define OSCILLATOR_FRQ 0x80

#define MULTIPLEX_RATIO 0xA8
#define DISPLAY_HEIGHT 0x3F

#define SET_DISPLAY_OFFSET 0xD3

#define SET_COLUMN 0x21
#define SET_PAGE 0x22

#define HORIZONTAL_ADDRESSING_MODE 0x20

void SSD1306InitScreen();
void SSD1306ClearScreen();
void SSD1306DrawSinglePixel(char x, char y);
void SSD1306BlitScreen();
void SSD1306CloseScreen();
	
void SSD1306SendSingleCommand(char command);
void SSD1306SendSingleData(char data);
void SSD1306TurnOnChargePump();
void SSD1306TurnOffChargePump();

void SSD1306SetPage(char page);
void SSD1306SetColumn(char column);

char **getScreenBuff();
#endif
