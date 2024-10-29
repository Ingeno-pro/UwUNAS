#include <math.h> 

#include "clock.h"

char ****asciiChar=NULL;

void initClock(){
	
	char j, k, i;
	
	//Allocate memory
	asciiChar = (char ****)malloc(sizeof(char ***) * 3);
	for(i = 0 ; i < 3 ; i++){
		asciiChar[i] = (char ***)malloc(sizeof(char **) * N_ASCII_CHAR);
	}
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[j] = (char **)malloc(sizeof(char *) * LITTLE_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[j][k] = (char *)malloc(sizeof(char) * LITTLE_CHAR_SIZE);
		}
	}
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[j] = (char **)malloc(sizeof(char *) * MEDIUM_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[j][k] = (char *)malloc(sizeof(char) * MEDIUM_CHAR_SIZE);
		}
	}
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[j] = (char **)malloc(sizeof(char *) * BIG_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[j][k] = (char *)malloc(sizeof(char) * BIG_CHAR_SIZE);
		}
	}
	
	//Load font
	FILE *f = fopen("res/fonts/medium", "rb");
	
	
	
	fclose(f)
}
void displayHour(){
	
	
}
void drawChar(char id, char x, char y, char size){
	
	char **screen_buff = getScreenBuff();
	char page, pixelmask;
	
	char letter[LITTLE_CHAR_SIZE][LITTLE_CHAR_SIZE] = {{0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 1, 0}};
	
	for(char i = 0; i < size; i++){
		for(char j = 0; j < size; j++){
			if((i + y) >= SCREEN_HEIGHT || (j + x) >= SCREEN_WIDTH){
				exit(0);
			}
			if(letter[i][j]){
				char page = (i + y)/(SCREEN_HEIGHT/PAGES);
				char pixelmask = (i + y)%(SCREEN_HEIGHT/PAGES);
				pixelmask = pow(2, (2*pixelmask));

				screen_buff[(j + x)][page] |= pixelmask;		
			}
		}
	}
}

void closeClock(){
	
	//à faire
}