#include <pthread.h>
#include <bcm2835.h>

#include "SSD1306.h"
#include "SSD1306_writer.h"
#include "diskmanager.h"
#include "http.h"
#include "clock.h"
#include "nas.h"

#define SCREEN_ADDR 0x3C
#define PORT 4255

void *screen_thread_(void *arg) {

	while(1){
		//displayHour();
	}
	pthread_exit(EXIT_SUCCESS);
}

int main(){
	
	SSD1306 screen;
	SSD1306Writer sw;
	
	HTTPServer server;
	
	initNAS();
	initClock();
	
	pthread_t screen_thread;
	
	//Init CPU library 
	if (bcm2835_init()){
		
		//I2C Init
		bcm2835_i2c_begin();
		bcm2835_i2c_set_baudrate(BAUD_RATE);
	
		SSD1306_init(&screen, SCREEN_ADDR);
		SSD1306Writer_init(&sw, &screen);
	
		displayHour(&sw);
		screen.blit(&screen);
		
		pthread_create(&screen_thread, NULL, screen_thread_, NULL);
	}
	
	listUUID();
	//printf("%d o\n", getDiskSize("sdb"));

	HTTPServer_init(&server, PORT);
	
	server.bind(&server);
	server.start_listen(&server);
	
	while(1){
		
	}
	pthread_join(screen_thread, NULL);
	close(server.server_socket);
	bcm2835_close();
	return 0;
}
