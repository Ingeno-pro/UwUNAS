#include <stdio.h>
#include <stdlib.h>

#include "superstring.h"



#ifndef __UGLY_DICTIONNARY_H__
#define __UGLY_DICTIONNARY_H__

typedef struct UglyDictionary
{
	int size;
	SuperString *stab;
}UglyDictionary;

UglyDictionary UglyDictionary_init();
void UglyDictionary_destroy(UglyDictionary *ud);

void UglyDictionary_append(UglyDictionary *ud, SuperString word);
UglyDictionary UglyDictionary_load(char *path);

SuperString UglyDictionary_search(char *word);
#endif