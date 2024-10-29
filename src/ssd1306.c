#include "ssd1306.h"
#include <stdio.h>
#include <math.h> 

char **screen_data=NULL;

void SSD1306InitScreen(){
	
	
	SSD1306SendSingleCommand(TURN_OFF_SCREEN);
	
	//Clock frequency
	SSD1306SendSingleCommand(DISPLAY_CLOCK_DIVIDE_RATIO);
	SSD1306SendSingleCommand(OSCILLATOR_FRQ);
	
	//Give display size to SSD1306
	SSD1306SendSingleCommand(MULTIPLEX_RATIO); 
	SSD1306SendSingleCommand(DISPLAY_HEIGHT); //Display height from 0 
	
	//Set display offset 0
	SSD1306SendSingleCommand(SET_DISPLAY_OFFSET); 
	SSD1306SendSingleCommand(0x00); 
	
	//Set addressing mode 
	SSD1306SendSingleCommand(HORIZONTAL_ADDRESSING_MODE);
	
	
	screen_data = (char **)malloc(sizeof(char *) * COLUMNS);
	for(char i = 0; i < COLUMNS ; i++){
		screen_data[i] = (char *)malloc(sizeof(char) * PAGES);
	}
	//Blank screen
	SSD1306ClearScreen();
	
	SSD1306TurnOnChargePump();
	SSD1306SendSingleCommand(TURN_ON_SCREEN);
	
}
void SSD1306CloseScreen(){
	
	char i = 0;
	for(i = 0; i < COLUMNS ; i++){
		free(screen_data[i]);
	}
	free(screen_data[i]);
	
	SSD1306SendSingleCommand(TURN_OFF_SCREEN);
	SSD1306TurnOffChargePump();
}
void SSD1306SendSingleCommand(char command){
	
	bcm2835_i2c_setSlaveAddress(SSD1306_ADDR);
	char i2c_command[2] = {0x00, command};
	bcm2835_i2c_write(i2c_command, 2);
	
}
void SSD1306SendSingleData(char data){
	
	bcm2835_i2c_setSlaveAddress(SSD1306_ADDR);
	char i2c_command[2] = {0x40, data};
	bcm2835_i2c_write(i2c_command, 2);
	
}
void SSD1306TurnOnChargePump(){
	
	bcm2835_i2c_setSlaveAddress(SSD1306_ADDR);
	char i2c_command[3] = {0x00, CHARGE_PUMP_SETTINGS, ENABLE_CHARGE_PUMP};
	bcm2835_i2c_write(i2c_command, 3);
	
}
void SSD1306TurnOffChargePump(){
	
	bcm2835_i2c_setSlaveAddress(SSD1306_ADDR);
	char i2c_command[3] = {0x00, CHARGE_PUMP_SETTINGS, DISABLE_CHARGE_PUMP};
	bcm2835_i2c_write(i2c_command, 3);
	
}
void SSD1306SetPage(char page){
	
	bcm2835_i2c_setSlaveAddress(SSD1306_ADDR);
	char i2c_command[4] = {0x00, SET_PAGE, page, PAGES-1};
	bcm2835_i2c_write(i2c_command, 4);
	
}
void SSD1306SetColumn(char column){
	
	bcm2835_i2c_setSlaveAddress(SSD1306_ADDR);
	char i2c_command[4] = {0x00, SET_COLUMN, column, COLUMNS-1};
	bcm2835_i2c_write(i2c_command, 4);
	
}
void SSD1306ClearScreen(){
	
	for(char i = 0;  i < PAGES ; i++){
		for(char j = 0;  j < COLUMNS ; j++){
			SSD1306SetPage(i);
			SSD1306SetColumn(j);
			screen_data[j][i] = 0x00;
			SSD1306SendSingleData(0x00);
		}
	}
}
void SSD1306DrawSinglePixel(char x, char y){
	
	if(x >= SCREEN_WIDTH || y >=SCREEN_HEIGHT){
		exit(0);
	}
	char page = y/(SCREEN_HEIGHT/PAGES);
	char pixelmask = y%(SCREEN_HEIGHT/PAGES);
	pixelmask = pow(2, (2*pixelmask));
	
	SSD1306SetPage(page);
	SSD1306SetColumn(x);
	screen_data[x][page] |= pixelmask;
	
	SSD1306SendSingleData(screen_data[x][page]);
	
}
void SSD1306BlitScreen(){
	
	for(char i = 0;  i < PAGES ; i++){
		for(char j = 0;  j < COLUMNS ; j++){
			SSD1306SetPage(i);
			SSD1306SetColumn(j);
			SSD1306SendSingleData(screen_data[j][i]);
		}
	}
	
}

char **getScreenBuff(){
	return screen_data;
}