
#ifndef DISPATCH_EXAMPLE_H
#define DISPATCH_EXAMPLE_H
#include "./TinyLight/TinyLight.h"

typedef struct
{
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	unsigned char array[100];
}sTIME;
void printTime(sTIME* content);
void taskAdd_example(void);


#endif
