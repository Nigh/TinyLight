
#ifndef TL_MEM_H
#define TL_MEM_H

#ifndef NULL
#define NULL ((void*)0)
#endif

#define TL_POOL_SIZE (10)	// size=2<<n

#define NODE_LENGTH (64)

typedef enum{false=0,true=1}bool;

typedef enum sNodeType
{
	NT_FREE,
	NT_USED
}eNODE_TYPE;

typedef struct sMem_pool
{
	unsigned char pool[2<<TL_POOL_SIZE];
}sMEM_POOL;

typedef struct sMem_node
{
	eNODE_TYPE type;		// node所指向的内存类型
	unsigned short offset;	// node所指向的内存偏移
	unsigned short length;	// node所占用的内存长度(对齐后的长度)
	void* next;
	void* prev;				// LL双向索引
}sMEM_NODE;

typedef struct sMem_queue
{
	sMEM_POOL ram;
	void* head;	// head of LL
	void* tail;	// tail of LL
	unsigned char length;	// length of LL
	bool isInit;
}sMEM_QUEUE;

sMEM_QUEUE* tl_init(void);
int tl_malloc(unsigned short size,void** ptr);

#endif
