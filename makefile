uwunas : main.o nas.o clock.o http.o diskmanager.o ssd1306.o
	gcc -o uwunas main.o nas.o clock.o http.o diskmanager.o ssd1306.o -lbcm2835 -lblkid -lm

main.o : src/main.c 
	gcc -c src/main.c -o main.o -lbcm2835 -lblkid -lm

nas.o : src/nas.c 
	gcc -c src/nas.c -o nas.o -lbcm2835 -lm

clock.o : src/clock.c 
	gcc -c src/clock.c -o clock.o -lbcm2835 -lm

http.o : src/http.c 
	gcc -c src/http.c -o http.o -lbcm2835 -lm
	
diskmanager.o : src/diskmanager.c 
	gcc -c src/diskmanager.c -o diskmanager.o -lbcm2835 -lblkid -lm
	
ssd1306.o : src/ssd1306.c 
	gcc -c src/ssd1306.c -o ssd1306.o -lbcm2835 -lm

