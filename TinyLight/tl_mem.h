
#ifndef TL_MEM_H
#define TL_MEM_H

#ifndef NULL
#define NULL ((void*)0)
#endif

#define NODE_LENGTH (64)

#define _ALIGN(addr,size) (((addr)+(size)-1)&(~((size)-1)))
#define _ALIGN_L(addr) _ALIGN(addr,sizeof(long))

typedef enum{false=0,true=1}bool;

void tl_init(void);
int tl_malloc(unsigned short size,void** ptr);
int tl_free(void *ptr);

#endif
