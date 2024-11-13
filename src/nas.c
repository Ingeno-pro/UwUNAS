#include "nas.h"

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
void UwUNAS_manage_file_request(HTTPRequest *hp){

	
	
}
void UwUNAS_manage_http_web_request(HTTPRequest *hp, SuperString *url){
	
	if(!strcmp(url->str, "/")) url->sprint(url, "page/home.html");
	if(!strcmp(url->str, "/favicon.ico")) url->sprint(url, "page/favicon.ico");
	
	if(url->str[0] == '/') SuperString_delete_char_from_index(url, 0);
	
	if(!strcmp(get_file_extension(url->str), "ico")){
		HTTPFaviconRequest_init(hp);
	}else if(!strcmp(get_file_extension(url->str), "html")){
		HTTPPageRequest_init(hp);
	}else if(!strcmp(get_file_extension(url->str), "css")){
		HTTPStyleSheetRequest_init(hp);
	}else if(!strcmp(get_file_extension(url->str), "js")){
		HTTPPageRequest_init(hp);
	}else{
		//something here
		HTTPPageRequest_init(hp);
	}
	
}
void _UwUNAS_get_file_content(const char *url, SuperString *content_buffer){
	SuperFile file = SuperFile_open(url);
	content_buffer->appendSS(content_buffer, &(file.content));
}
char *get_file_extension(const char *filename){
	const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}
int manageRequest(int clientSocket, SuperString *request){
	
	//Process the request
	SuperString method = SuperString_init(), url = SuperString_init();
	
	int index = request->limit(request, &method, ' ');
	index = request->select_and_limit(request, &url, index+1, ' ');

	//Create the answer
	HTTPRequest hp;
	UwUNAS_manage_http_web_request(&hp, &url);
	_UwUNAS_get_file_content(url.str, &(hp.content));
	hp.getHeader(&hp);
	  
	//Send the answer
	if(!strcmp(method.str, "GET")){
		HTTPServer_send(clientSocket, &hp);
	}else if(!strcmp(method.str, "POST")){
	
	}
	HTTPRequest_destroy(&hp);
}
