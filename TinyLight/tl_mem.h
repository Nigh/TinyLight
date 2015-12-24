
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
	unsigned char next,prev;	// LL双向索引
}sMEM_NODE;

typedef struct sMem_queue
{
	sMEM_POOL ram;
	// warning:node[0]不要使用
	// 因为此LL使用了unsigned char作为索引
	// 0在这里起到了一个显式的NULL的作用
	// length为0的node会在gc中被释放掉
	sMEM_NODE node[NODE_LENGTH];
	unsigned char head;	// head of LL
	unsigned char tail;	// tail of LL
	unsigned char length;	// length of LL
	bool isInit;
}sMEM_QUEUE;

sMEM_QUEUE* tl_init(void);
int tl_malloc(unsigned short size,void** ptr);

#endif
