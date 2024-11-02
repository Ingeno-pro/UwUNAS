#include "ssd1306_text.h"
char **smallChar;
char ***smallCharFromID;
char **mediumChar;
char **bigChar;

void createCharTable(){
	
	char j, i;
	
	//Allocate memory
	smallChar = (char **)malloc(sizeof(char *) * SPRITE_TABLE_SIZE);
	smallCharFromID = (char ***)malloc(sizeof(char **) * N_ASCII_CHAR);
	
	for(j = 0 ; j < SPRITE_TABLE_SIZE ; j++){
		smallChar[j] = (char *)malloc(sizeof(char) * SPRITE_TABLE_SIZE);
	}
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		smallCharFromID[j] = (char **)malloc(sizeof(char *) * SMALL_CHAR_SIZE);
		for(i = 0 ; i < SMALL_CHAR_SIZE; i++){
			smallCharFromID[j][i] = (char *)malloc(sizeof(char) * (SMALL_CHAR_SIZE/2));
		}
	}
	
	//To do ??
	mediumChar = (char **)malloc(sizeof(char *) * SPRITE_TABLE_SIZE);
	
	for(j = 0 ; j < SPRITE_TABLE_SIZE ; j++){
		mediumChar[j] = (char *)malloc(sizeof(char) * SPRITE_TABLE_SIZE);
	}
	
	bigChar = (char **)malloc(sizeof(char *) * SPRITE_TABLE_SIZE);
	
	for(j = 0 ; j < SPRITE_TABLE_SIZE ; j++){
		bigChar[j] = (char *)malloc(sizeof(char) * SPRITE_TABLE_SIZE);
	}
	
}

void SSD1306InitText(){
	
	fprintf(stderr, "SSD1306 text init");
	createCharTable();
	loadSmallChar();
	fprintf(stderr, "SSD1306 initialised succesfully");
}
void SSD1306CloseText(){
	
	destroyCharTable();
	
}
void destroyCharTable(){
	
	char j, k, i;
	
	//Desallocate memory ( to do )
	for(j = 0 ; j < SPRITE_TABLE_SIZE ; j++){
		free(smallChar[j]); 
	}
	free(smallChar);
	
	for(j = 0 ; j < SPRITE_TABLE_SIZE ; j++){
		free(mediumChar[j]); 
	}
	free(mediumChar);
	
	for(j = 0 ; j < SPRITE_TABLE_SIZE ; j++){
		free(bigChar[j]); 
	}
	free(bigChar);
}

void loadSmallChar(){
	
	png_byte **row_pointers;
	
	FILE *f = fopen("res/img/smallChar.png", "rb");
	if(!f){
		fprintf(stderr, "smallChar non trouvé :(");
	}
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info = png_create_info_struct(png);
	 
	if (setjmp(png_jmpbuf(png))) {
        fprintf(stderr, "Erreur de lecture de l'image PNG");
        png_destroy_read_struct(&png, &info, NULL);
        fclose(f);
        exit(EXIT_FAILURE);
    }
	
	png_init_io(png, f);
	
	png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
	
	row_pointers = (png_byte**)malloc(sizeof(png_byte *) * height);
	for(int y = 0; y < height; y++) {
		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
	}

	
	png_read_image(png, row_pointers);

	for(int y = 0; y < height; y++){
 		for(int x = 0; x < width; x++){
			if(!row_pointers[y][x*3 + 0] && !row_pointers[y][x*3 + 1] && !row_pointers[y][x*3 + 2]){
				smallChar[y][x] = 1;
			}else{
				smallChar[y][x] = 0;
			}
		}
	}
	
	int sy, sx;
	for(int id = 0; id < N_ASCII_CHAR; id++){
		sy = (id / (SPRITE_TABLE_SIZE/(SMALL_CHAR_SIZE/2)))*8;
		sx = (id % (SPRITE_TABLE_SIZE/(SMALL_CHAR_SIZE/2)))*4;
		for(int y = sy; y < sy + SMALL_CHAR_SIZE; y++){
			for(int x = sx; x < sx + SMALL_CHAR_SIZE/2; x++){
				smallCharFromID[id][y-sy][x-sx] = smallChar[y][x];
			}
		}
	}
	
	
    png_destroy_read_struct(&png, &info, NULL);
    fclose(f);

	
}
void drawSmallChar(char cx, char cy, char x, char y){
	
	char **screen_buff = getScreenBuff();
	char page, pixelmask;
	
	for(char i = 0; i < SMALL_CHAR_SIZE; i++){
		for(char j = 0; j < SMALL_CHAR_SIZE/2; j++){
			
			page = (i + y)/(SCREEN_HEIGHT/PAGES);
			pixelmask = (i + y)%(SCREEN_HEIGHT/PAGES);
			pixelmask = pow(2, (2*pixelmask));
			
			if((i + y) >= SCREEN_HEIGHT || (j + x) >= SCREEN_WIDTH){
				exit(0);
			}
			if(smallChar[cy + i][cx + j]){
				screen_buff[(j + x)][page] |= pixelmask;		
			}else{
				screen_buff[(j + x)][page] &= ~pixelmask;
			}
		}
	}
}
void drawSmallCharFromID(char id, char x, char y){
	
	char **screen_buff = getScreenBuff();
	char page, pixelmask;
	
	for(char i = 0; i < SMALL_CHAR_SIZE; i++){
		for(char j = 0; j < SMALL_CHAR_SIZE/2; j++){
			
			page = (i + y)/(SCREEN_HEIGHT/PAGES);
			pixelmask = (i + y)%(SCREEN_HEIGHT/PAGES);
			pixelmask = pow(2, (2*pixelmask));
			
			if((i + y) >= SCREEN_HEIGHT || (j + x) >= SCREEN_WIDTH){
				exit(0);
			}
			if(smallCharFromID[id][i][j]){
				screen_buff[(j + x)][page] |= pixelmask;		
			}else{
				screen_buff[(j + x)][page] &= ~pixelmask;
			}
		}
	}
}
void drawSmallString(char x, char y, char *str){
	
	for(int i = 0; i < strlen(str); i++){
		drawSmallCharFromID((int)str[i] - ASCII_TABLE_OFFSET, x + i*(SMALL_CHAR_SIZE/2), y);
	}
	
}

