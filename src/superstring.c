#include "superstring.h"
SuperString SuperString_init(){
	
	SuperString sstr;
	
	sstr.str = NULL;
	sstr.size = 0;
	
	sstr.sprint = &SuperString_sprint;
	sstr.append = &SuperString_append;
	sstr.appendSS = &SuperString_appendSS;
	sstr.appendc = &SuperString_appendc;
	sstr.appendb = &SuperString_appendb;
	sstr.limit = &SuperString_limit;
	sstr.select_and_limit = &SuperString_select_and_limit;
	sstr.cmp = &SuperString_compare;
	
	return sstr;
}
void SuperString_destroy(SuperString *ss){
	free(ss->str);
}
void SuperString_sprint(SuperString *sstr, const char *str) {
	
    if (!str) return;

    if (sstr->str != NULL) {
        free(sstr->str);
    }

    sstr->size = strlen(str) + 1;

    sstr->str = (char *)malloc(sstr->size);
	
    if (sstr->str == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
        sstr->size = 0;
        return;
    }

    strcpy(sstr->str, str);
}

void SuperString_append(SuperString *sstr, const char *str) {
	
    int prev_size = sstr->size;

    if (sstr->str == NULL) {
        sstr->size = strlen(str) + 1;
        sstr->str = (char *)malloc(sstr->size);
        if (sstr->str == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        strcpy(sstr->str, str); 
    } else {
        sstr->size += strlen(str); 
        char *new_str = (char *)realloc(sstr->str, sstr->size + 1);
        if (new_str == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        sstr->str = new_str; 
        strcat(sstr->str, str);
    }

}

void SuperString_appendSS(SuperString *dsstr, SuperString *ssstr){
	
	int prev_size = dsstr->size;
	
	if(dsstr->str == NULL){
		dsstr->size = ssstr->size;
		dsstr->str = (char *)malloc(dsstr->size);
	}else{
		dsstr->size = ssstr->size + dsstr->size - 1;
		char *buff = realloc(dsstr->str, dsstr->size);
		dsstr->str = buff;
	}
	for(int i = 0; i < ssstr->size; i++){
		dsstr->str[(prev_size) ? prev_size + i - 1 : i] = ssstr->str[i];
	}
}
void SuperString_appendc(SuperString *sstr, const char c){
	
	int prev_size = sstr->size;
	
	if(sstr->str == NULL){
		sstr->size = 1;
		sstr->str = (char *)malloc(sstr->size);
	}
	
	sstr->str[sstr->size - 1] = c;
	
	if(c != '\0'){
		sstr->size = sizeof(char) + sstr->size;
		sstr->str = realloc(sstr->str, sstr->size);
		sstr->str[sstr->size - 1] = '\0';
	}
}
void SuperString_appendb(SuperString *sstr, const char c){
	
	sstr->size = sizeof(char) + sstr->size;
	sstr->str = realloc(sstr->str, sstr->size);
	
	sstr->str[sstr->size - 1] = c;
	
}
int SuperString_limit(SuperString *ssstr, SuperString *dstr, const char c){
		
	int index;
	
	if(ssstr->str == NULL){
		return;
	}
	
	for(int i = 0; i < ssstr->size; i++){
		if(ssstr->str[i] == c) break;
		SuperString_appendc(dstr, ssstr->str[i]);
		index = i;
	}

	return index+1;
}
int SuperString_select_and_limit(SuperString *ssstr, SuperString *dstr, const int start, const char c){
		
	int index;
	
	if(ssstr->str == NULL){
		return;
	}
	
	for(int i = 0; i < ssstr->size; i++){
		if(ssstr->str[i + start] == c) break;
		SuperString_appendc(dstr, ssstr->str[i + start]);
		index = i;
	}

	return index+1;
}
void SuperString_delete_char_from_index(SuperString *ssstr, const int index){
	
	for(int i = 0; i < ssstr->size - 1; i++){
		ssstr->str[index + i] = ssstr->str[index + i + 1];
	}
	ssstr->size--;
	ssstr->str = realloc(ssstr->str, ssstr->size);
	
}
int SuperString_compare(SuperString *sstr, const char *str){
	
	if(sstr->str != NULL){
		return -1;
	}
	
	return strcmp(sstr->str, str);
}