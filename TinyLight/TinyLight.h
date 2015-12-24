
#ifndef TINYLIGHT_H
#define TINYLIGHT_H

#include "./tl_mem.h"
#include "./tl_dispatch.h"

#define CONST_STR(n,str); static char* n(void) {return str;}


struct TINYLIGHT_STRUCT
{
	void (*init)(void);
	char* (*str1)(void);
	char* (*str2)(void);
	char* (*getVersion)(void);
	char* (*getName)(void);
	sMEM_QUEUE* mem;
};
extern struct TINYLIGHT_STRUCT TinyLight;

#endif
