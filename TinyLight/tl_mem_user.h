
#ifndef TL_MEM_USER_H
#define TL_MEM_USER_H
#include "tl_mem.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef struct sMem_pool_user {
	unsigned char pool[1024];
} sMEM_POOL_USER;

typedef struct sMem_queue_user {
	sMEM_POOL_USER ram;
	void *head;	// head of LL
	void *tail;	// tail of LL
	unsigned char length;	// length of LL
	_bool isInit;
} sMEM_QUEUE_USER;
sMEM_QUEUE_USER *tl_init_user(void);
int tl_malloc_user(unsigned short size, void **ptr);
int tl_free_user(void *ptr);
void tl_gc_user(void);
#endif
