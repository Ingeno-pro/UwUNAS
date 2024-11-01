#include "clock.h"

void initClock(){
	fprintf(stderr, "Init clock UwU");
	
}
void displayHour(){
	
	time_t timestamp = time(NULL);
	struct tm * timeInfos = localtime( &timestamp );
	
	//timeInfos->tm_hour;
	//timeInfos->tm_min;
	drawSmallChar(0, 0, 0, 0);
	drawSmallChar(4, 0, 4, 0);
	drawSmallChar(12, 8, 8, 0);
	drawSmallChar(12, 0, 12, 0);
	drawSmallChar(0, 8, 16, 0);
}


void closeClock(){
	
	//à faire
}