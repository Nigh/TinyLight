
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
	struct TINYLIGHT_MEM
	{
		sMEM_QUEUE* (*init)(void);
		int (*malloc)(unsigned short size,void** ptr);
		int (*free)(void *ptr);
	}mem;
	struct TINYLIGHT_DISPATCH
	{
		sTASK* (*new)(fTask* func,unsigned short size);
		int (*insert)(sTASK* task);
		int (*exec)(sTASK* task);
		int (*dispatch)(void);
	}task;
	sMEM_QUEUE* memq;
};
extern struct TINYLIGHT_STRUCT TL;

#endif
