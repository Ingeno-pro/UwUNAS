#include "uglydictionary.h"

UglyDictionary UglyDictionary_init(){
	
	UglyDictionary ud;
	ud.size = 0;
	ud.stab = NULL;
	return ud;
}
void UglyDictionary_destroy(UglyDictionary *ud){
	
	for(int i = 0; i < ud->size; i++){
		SuperString_destroy(&(ud->stab[i]));
	}
	free(ud);
}
void UglyDictionary_append(UglyDictionary *ud, SuperString word){
	
	ud->size++;
	if(ud->stab != NULL){
		ud->stab = (SuperString *)realloc(ud->stab, sizeof(SuperString) * ud->size); 
	}else{
		ud->stab = (SuperString *)malloc(sizeof(SuperString) * ud->size); 
	}
	
}
SuperString UglyDictionary_search(char *word){
	
	
	
}