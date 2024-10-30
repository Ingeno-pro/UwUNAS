#include "ssd1306_text.h"
char ****asciiChar=NULL;

void createCharTable(){
	
	char j, k, i;
	
	//Allocate memory
	asciiChar = (char ****)malloc(sizeof(char ***) * 3);
	for(i = 0 ; i < 3 ; i++){
		asciiChar[i] = (char ***)malloc(sizeof(char **) * N_ASCII_CHAR);
	}
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[0][j] = (char **)malloc(sizeof(char *) * SMALL_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[0][j][k] = (char *)malloc(sizeof(char) * SMALL_CHAR_SIZE/2);
		}
	}
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[1][j] = (char **)malloc(sizeof(char *) * MEDIUM_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[1][j][k] = (char *)malloc(sizeof(char) * MEDIUM_CHAR_SIZE/2);
		}
	}
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[2][j] = (char **)malloc(sizeof(char *) * BIG_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[2][j][k] = (char *)malloc(sizeof(char) * BIG_CHAR_SIZE/2);
		}
	}
	
}
void SSD1306InitText(){
	
	createCharTable();
	loadSmallChar();
	
}
void destroyCharTable(){
	
	char j, k, i;
	
	//Desallocate memory ( to do )
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[0][j] = (char **)malloc(sizeof(char *) * SMALL_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[0][j][k] = (char *)malloc(sizeof(char) * SMALL_CHAR_SIZE/2);
		}
	}
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[1][j] = (char **)malloc(sizeof(char *) * MEDIUM_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[1][j][k] = (char *)malloc(sizeof(char) * MEDIUM_CHAR_SIZE/2);
		}
	}
	
	for(j = 0 ; j < N_ASCII_CHAR ; j++){
		asciiChar[2][j] = (char **)malloc(sizeof(char *) * BIG_CHAR_SIZE);
		for(k = 0 ; k < N_ASCII_CHAR ; k++){
			asciiChar[2][j][k] = (char *)malloc(sizeof(char) * BIG_CHAR_SIZE/2);
		}
	}
	
	
	for(i = 0 ; i < 3 ; i++){
		asciiChar[i] = (char ***)malloc(sizeof(char **) * N_ASCII_CHAR);
	}
	
	asciiChar = (char ****)malloc(sizeof(char ***) * 3);
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

   
    png_destroy_read_struct(&png, &info, NULL);
    fclose(f);

	
}
void drawChar(char id, char x, char y, char size){
	
	char **screen_buff = getScreenBuff();
	char page, pixelmask;
	char letter_size;
	
	switch(size){
		case 0:
			letter_size = SMALL_CHAR_SIZE;
		break;
		case 1:
			letter_size = MEDIUM_CHAR_SIZE;
		break;
		case 2:
			letter_size = BIG_CHAR_SIZE;
		break;
	}
	
	for(char i = 0; i < letter_size; i++){
		for(char j = 0; j < letter_size; j++){
			if((i + y) >= SCREEN_HEIGHT || (j + x) >= SCREEN_WIDTH){
				exit(0);
			}
			if(asciiChar[size][id][i][j]){
				char page = (i + y)/(SCREEN_HEIGHT/PAGES);
				char pixelmask = (i + y)%(SCREEN_HEIGHT/PAGES);
				pixelmask = pow(2, (2*pixelmask));

				screen_buff[(j + x)][page] |= pixelmask;		
			}
		}
	}
}