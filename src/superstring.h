#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef __SUPER_STRING_H__
#define __SUPER_STRING_H__

typedef struct SuperString
{
	char *str;
	int size;
	
	void (*sprint)(struct SuperString *sstr, const char *str);
	void (*append)(struct SuperString *sstr, const char *str);
	void (*appendSS)(struct SuperString *dsstr, struct SuperString *ssstr);
	void (*appendc)(struct SuperString *sstr, const char c);
	void (*appendb)(struct SuperString *sstr, const char c);
	int (*limit)(struct SuperString *ssstr, struct SuperString *dstr, const char c);
	int (*select_and_limit)(struct SuperString *ssstr, struct SuperString *dstr, const int start, const char c);
	int (*cmp)(struct SuperString *sstr, const char *str);
	
}SuperString;

SuperString SuperString_init();
void SuperString_destroy(SuperString *ss);

void SuperString_sprint(SuperString *sstr, const char *str);
void SuperString_append(SuperString *sstr, const char *str);
void SuperString_appendSS(SuperString *dsstr, SuperString *ssstr);
void SuperString_appendc(SuperString *sstr, const char c);
void SuperString_appendb(SuperString *sstr, const char c);
void SuperString_delete_char_from_index(SuperString *ssstr, const int index);
int SuperString_limit(SuperString *ssstr, SuperString *dstr, const char c);
int SuperString_select_and_limit(SuperString *ssstr, SuperString *dstr, const int start, const char c);
int SuperString_compare(SuperString *sstr, const char *str);

//SuperString *SuperString_cut(SuperString *sstr, const char *key);

#endif