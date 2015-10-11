
#ifndef TINYLIGHT_H
#define TINYLIGHT_H

struct TINYLIGHT_STRUCT
{
	void (*init)(void);
	char* (*str1)(void);
	char* (*str2)(void);
	char* (*getVersion)(void);
	char* (*getName)(void);
};
extern struct TINYLIGHT_STRUCT TinyLight;

#endif
