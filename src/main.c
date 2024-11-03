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
#define IP 4

void *screen_thread_(void *arg) {

	while(1){
		//displayHour();
	}
	pthread_exit(EXIT_SUCCESS);
}


int main(){
	
	
	initNAS();
	initClock();
	if (!bcm2835_init()) return 1;
	
	//Initialisation de l'écran LCD
	bcm2835_i2c_begin();
	bcm2835_i2c_set_baudrate(BAUD_RATE);
	
	SSD1306 screen;
	SSD1306_init(&screen, SCREEN_ADDR);
	
	SSD1306Writer sw;
	SSD1306Writer_init(&sw, &screen);
	
	displayHour(&sw);
	screen.blit(&screen);
	pthread_t screen_thread;
	pthread_create(&screen_thread, NULL, screen_thread_, NULL);
	
	listUUID();
	//printf("%d o\n", getDiskSize("sdb"));
	//Création du socket
	fprintf(stdout, "UWU CREATE\n");
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
	
	if(serverSocket == -1){
		fprintf(stderr, "SAD UWU :( 1");
		exit(1);
	}
	
	//Config du socket
	fprintf(stdout, "UWU CONFIG\n");
	struct sockaddr_in socketAddress;
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_port = htons(PORT);
	socketAddress.sin_addr.s_addr = INADDR_ANY;
	
	int socketAddresslength = sizeof(socketAddress);
	
	//Liaison
	fprintf(stdout, "UWU BIND\n");
	if(bind(serverSocket, (struct sockaddr *)&socketAddress, socketAddresslength) == -1){
		fprintf(stderr, "SAD UWU :( 2a");
		exit(1);
	}
	
	//Ecoute
	fprintf(stdout, "UWU ECOUTE\n");
	if(listen(serverSocket, 4) == -1){
		fprintf(stderr, "SAD UWU :( 2");
		exit(1);
	}
	
	int clientSocket;
	char buff[BUFFER_SIZE] = {0};
	int receivedByte;
	
	while(1){
		fprintf(stdout, "UWU WAIT\n");
		clientSocket = accept(serverSocket, NULL, NULL);
		if(clientSocket == -1){
			fprintf(stderr, "SAD UWU :( 3");
			exit(1);
		}else{
			fprintf(stdout, "HAPPY UWU :)\n");
			receivedByte = recv(clientSocket, buff, BUFFER_SIZE, 0);
			fprintf(stdout, "Request:%s", buff);
			
			manageRequest(clientSocket, buff, sizeof(buff));
		}
	}
	pthread_join(screen_thread, NULL);
	close(clientSocket);
	close(serverSocket);
	bcm2835_close();
	return 0;
}
