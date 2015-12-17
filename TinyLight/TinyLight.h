
#ifndef TINYLIGHT_H
#define TINYLIGHT_H

#define CONST_STR(n,str); static char* n(void) {return str;}

typedef enum{false,true}bool;

struct TINYLIGHT_STRUCT
{
	void (*init)(void);
	char* (*str1)(void);
	char* (*str2)(void);
	char* (*getVersion)(void);
	char* (*getName)(void);
};
extern struct TINYLIGHT_STRUCT TinyLight;

#define TL_POOL_SIZE (9)	// size=2<<n
#define ALIGN_SIZE (8)		// 8 byte align

#endif
