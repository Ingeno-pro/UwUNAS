uwunas : main.o nas.o clock.o http.o diskmanager.o SSD1306.o SSD1306_writer.o superstring.o superfile.o
	gcc -o uwunas main.o nas.o clock.o http.o diskmanager.o SSD1306.o SSD1306_writer.o superstring.o superfile.o -lbcm2835 -lblkid -lm -lpng -g

main.o : src/main.c 
	gcc -c src/main.c -o main.o -lbcm2835 -lblkid -lm -g

nas.o : src/nas.c 
	gcc -c src/nas.c -o nas.o -lbcm2835 -lm -g

clock.o : src/clock.c 
	gcc -c src/clock.c -o clock.o -lbcm2835 -lm -g

http.o : src/http.c 
	gcc -c src/http.c -o http.o -lbcm2835 -lm -g
	
diskmanager.o : src/diskmanager.c 
	gcc -c src/diskmanager.c -o diskmanager.o -lbcm2835 -lblkid -lm -g
	
SSD1306.o : src/SSD1306.c 
	gcc -c src/SSD1306.c -o SSD1306.o -lbcm2835 -lm -g

SSD1306_writer.o : src/SSD1306_writer.c 
	gcc -c src/SSD1306_writer.c -o SSD1306_writer.o -lbcm2835 -lm -lpng -g
	
superstring.o : src/superstring.c 
	gcc -c src/superstring.c -o superstring.o -lbcm2835 -lm -lpng -g
	
superfile.o : src/superfile.c 
	gcc -c src/superfile.c -o superfile.o -lbcm2835 -lm -lpng -g

