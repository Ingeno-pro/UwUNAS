#include "nas.h"
#include "http.h"
int initNAS(void){
	
	fprintf(stderr, "CHECK DISK CFG UWU\n");
	//Try to open disk configuration file
	FILE *diskCfg = NULL;
	diskCfg = fopen("config/disk.cfg", "r");
	
	//if not exist then create it
	if(!diskCfg){
		fprintf(stderr, "OH NO ! NO CFG UWU\n");
		fprintf(stderr, "CREATING ONE UWU...\n");
		diskCfg = fopen("config/disk.cfg", "w");
	}	

	fclose(diskCfg);

}
int manageRequest(int clientSocket, char *request, int request_size){
	
	char *token;
	char method[REQUEST_METHOD_SIZE] = {0};
	token = strtok(request, " ");
	strcpy(method, token);
	
	char url[MAX_URL_SIZE] = {0};
	strcpy(url, "page");
	token = strtok(NULL, " ");
	(!strcmp(token, "/")) ? strcat(url, "/home.html") : strcat(url, token);
	
	FILE *page;
	long pageSize;
	char *html_content;
	  
	if(!strcmp(method, "GET")){
		page = fopen(url, "r");
		
		if(page == NULL){
			fprintf(stderr, "UWU introuvable : %s", url);
		}else{
			fseek(page, 0, SEEK_END);
			pageSize = ftell(page);
			fseek(page, 0, SEEK_SET);
		
			if(pageSize < BUFFER_SIZE - HEADER_SIZE){
				html_content = malloc(pageSize + 1);
				fread(html_content, pageSize, 1, page);
				sendHTTPResponse(clientSocket, html_content, pageSize);
				fclose(page);
			}
		}
				
	}else if(!strcmp(method, "POST")){
	
	}
	
}
