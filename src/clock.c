#include "clock.h"

void initClock(){
	fprintf(stderr, "Init clock UwU");
	
}
void displayHour(){
	
	char hour[6];
	
	time_t timestamp = time(NULL);
	struct tm * timeInfos = localtime( &timestamp );
	
	sprintf(hour, "%d:%d", timeInfos->tm_hour, timeInfos->tm_min);
	drawSmallString(0, 0, hour);
}


void closeClock(){
	
	//à faire
}