#include "superfile.h"

SuperFile SuperFile_open(char *path){
	
	SuperFile sf;
	sf.fpath = SuperString_init();
	sf.fpath.sprint(&(sf.fpath), path);
	
	sf.content = SuperString_init();
	
	sf.f = fopen(path, "rb");
	
	if(sf.f != NULL){ 
		_SuperFile_read(&sf);
		fclose(sf.f);
	}
	
	return sf;
	
}
void SuperFile_close(SuperFile *sf){
	
	SuperString_destroy(&(sf->fpath));
	SuperString_destroy(&(sf->content));
}
void _SuperFile_read(SuperFile *sf){
	
	char c;
	
	fseek(sf->f, 0, SEEK_END);
    sf->fsize = ftell(sf->f);
    rewind(sf->f);
	
	for(int i = 0; i < sf->fsize; i++){
		c = fgetc(sf->f);
		sf->content.appendb(&(sf->content), c);
	}
}