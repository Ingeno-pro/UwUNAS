#include "clock.h"

void initClock(){
	fprintf(stderr, "Init clock UwU");
	
}
void displayHour(SSD1306Writer *sw){
	
	char hour[6];
	
	time_t timestamp = time(NULL);
	struct tm * timeInfos = localtime( &timestamp );
	
	sprintf(hour, "%02d:%02d", timeInfos->tm_hour, timeInfos->tm_min);
	SSD1306Writer_draw_small_string(sw, 0, 0, hour);
}


void closeClock(){
	
	//à faire
}